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
  CLogReaderStringResult(void* buffer, size_t size);

public:
  uint64_t write(const void *data, size_t size);
  void close();

private:
  char *buf_;
  uint64_t size_;
  uint64_t offset_;
};

#endif // !LOG_READER_STRING_RESULT_H_INCLUDED
