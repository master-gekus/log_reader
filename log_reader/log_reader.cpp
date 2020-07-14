#include "log_reader.h"

#define WINDOW_SIZE 128

CLogReader::CLogReader()
  : m_hFile(INVALID_HANDLE_VALUE)
  , m_hMap(NULL)
{
}

CLogReader::~CLogReader()
{
  Close();
}

void CLogReader::Close()
{
}

bool CLogReader::SetFilter(const char *filter)
{
  if ((NULL == filter) || ('\0' == filter[0])) {
    return false;
  }

  return true;
}
