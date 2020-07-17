#include "log_reader.h"

#include "pattern.h"
#include "search_engine.h"
#include "search_stream_file_direct.h"
#include "search_stream_file_windowed.h"
#include "log_reader_string_result.h"

CLogReader::CLogReader()
  : m_pPattern(CPattern::create(NULL))
  , m_pEngine(NULL)
{
}

CLogReader::~CLogReader()
{
  Close();
  delete m_pPattern;
}

void CLogReader::Close()
{
  delete m_pEngine;
  m_pEngine = NULL;
}

bool CLogReader::SetFilter(const char *filter)
{
  CPattern *new_pattern = CPattern::create(filter);
  if (NULL == new_pattern) {
    return false;
  }

  m_pPattern = new_pattern;
  return true;
}

bool CLogReader::Open(const wchar_t* name)
{
  ISearchStream *stream = new CSearchStreamFileWindowed(name, 0x10000);
  if (!stream->can_continue()) {
    return false;
  }

  Close();
  m_pEngine = new CSearchEngine(stream);
  return true;
}

bool CLogReader::GetNextLine(char *buf, const size_t bufsize)
{
  CLogReaderStringResult result(buf, bufsize, NULL);
  return _GetNextLine(&result);
}

bool CLogReader::GetNextLine(char *buf, const size_t bufsize, unsigned *line_number)
{
  CLogReaderStringResult result(buf, bufsize, line_number);
  return _GetNextLine(&result);
}

bool CLogReader::_GetNextLine(ILogReaderResult *pResult)
{
  if ((NULL == m_pEngine) || (m_pEngine->eof())) {
    return false;
  }

  while(true) {
    if (m_pEngine->match(m_pPattern)) {
      pResult->SetLineNumber(static_cast<unsigned>(m_pEngine->current_line_number()));
      bool res = m_pEngine->get_line(pResult);
      m_pEngine->next_line();
      return res;
    }
    if (!m_pEngine->next_line()) {
      return false;
    }
  }
  return false;
}
