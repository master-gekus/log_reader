#include "search_stream_file_generic.h"

SearchStreamGenericFile::SearchStreamGenericFile(const wchar_t* file_name)
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

SearchStreamGenericFile::~SearchStreamGenericFile()
{
  if (INVALID_HANDLE_VALUE != file_) {
    ::CloseHandle(file_);
    file_ = INVALID_HANDLE_VALUE;
  }
}
