/**
* \file log_reader_string_result.h
*/

#pragma once
#ifndef LOG_READER_STRING_RESULT_H_INCLUDED
#define LOG_READER_STRING_RESULT_H_INCLUDED

#include "log_reader_result.h"

class CLogReaderStringResult : public ILogReaderResult
{
public:
  CLogReaderStringResult(void* buffer, size_t size, unsigned *line_number);

public:
  uint64_t Write(const void *data, size_t size);
  void Close();
  void SetLineNumber(unsigned number);

private:
  char *buf_;
  uint64_t size_;
  uint64_t offset_;
  unsigned *line_number_;
};

#endif // !LOG_READER_STRING_RESULT_H_INCLUDED
