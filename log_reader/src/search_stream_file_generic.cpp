#include "search_stream_file_generic.h"

#include "log_reader_result.h"

ISearchStreamGenericFile::ISearchStreamGenericFile(const wchar_t* file_name)
  : file_(INVALID_HANDLE_VALUE)
  , file_size_(0)
{
  file_ = ::CreateFileW(file_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
  if (INVALID_HANDLE_VALUE == file_) {
    error_ = true;
    return;
  }

  DWORD size_low;
  DWORD size_high;
  size_low = ::GetFileSize(file_, &size_high);
  file_size_ = (static_cast<uint64_t>(size_high) << 32) + static_cast<uint64_t>(size_low);
}

ISearchStreamGenericFile::~ISearchStreamGenericFile()
{
  if (INVALID_HANDLE_VALUE != file_) {
    ::CloseHandle(file_);
    file_ = INVALID_HANDLE_VALUE;
  }
}

bool ISearchStreamGenericFile::seek(uint64_t offset)
{
  LONG offset_hight = static_cast<uint32_t>(offset >> 32);
  if (INVALID_SET_FILE_POINTER == ::SetFilePointer(file_, static_cast<uint32_t>(offset), &offset_hight, FILE_BEGIN)) {
    error_ = true;
    return false;
  }
  return true;
}

bool ISearchStreamGenericFile::get_result_(ILogReaderResult* result, uint64_t from, uint64_t to)
{
  if ((from >= file_size_) || (to >= file_size_) || (from > to) || (!can_continue()) || (!seek(from))) {
    return false;
  }

  char buf[4096];
  uint64_t total = to - from;

  while (total > 0) {
    DWORD to_write = sizeof (buf);
    if (to_write > total) {
      to_write = static_cast<DWORD>(total);
    }

    DWORD read;
    if (!::ReadFile(file_, buf, to_write, &read, NULL)) {
      error_ = true;
      return false;
    }

    DWORD written = static_cast<DWORD>(result->write(buf, read));
    if (0 == written) {
      return false;
    }
    total -= read;
  }

  result->close();
  return true;
}
