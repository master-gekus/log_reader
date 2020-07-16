#include "search_stream_file_direct.h"
#include "log_reader_result.h"

SearchStreamFileDirect::SearchStreamFileDirect(const wchar_t* file_name)
  : SearchStreamGenericFile(file_name)
{
}

SearchStreamFileDirect::~SearchStreamFileDirect()
{
}

char SearchStreamFileDirect::at_(uint64_t offset)
{
  if ((!can_continue()) || (offset >= file_size_)) {
    return '\0';
  }

  LONG off_hight = static_cast<uint32_t>(offset >> 32);
  ::SetFilePointer(file_, static_cast<uint32_t>(offset), &off_hight, FILE_BEGIN);

  char c;
  DWORD read;
  if ((!::ReadFile(file_, &c, 1, &read, NULL)) || (read != 1)) {
    error_ = true;
    return '\0';
  }

  return c;
}

bool SearchStreamFileDirect::get_result_(ILogReaderResult* result, uint64_t from, uint64_t to)
{
  if ((from >= file_size_) || (to >= file_size_) || (from > to) || (!can_continue())) {
    return false;
  }

  LONG from_hight = static_cast<uint32_t>(from >> 32);
  ::SetFilePointer(file_, static_cast<uint32_t>(from), &from_hight, FILE_BEGIN);

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
