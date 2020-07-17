#include "search_stream_file_direct.h"

CSearchStreamFileDirect::CSearchStreamFileDirect(const wchar_t* file_name)
  : ISearchStreamGenericFile(file_name)
{
}

CSearchStreamFileDirect::~CSearchStreamFileDirect()
{
}

char CSearchStreamFileDirect::at_(uint64_t offset)
{
  if ((!can_continue()) || (offset >= file_size_) || (!seek(offset))) {
    return '\0';
  }

  char c;
  DWORD read;
  if ((!::ReadFile(file_, &c, 1, &read, NULL)) || (read != 1)) {
    error_ = true;
    return '\0';
  }

  return c;
}
