#pragma once

#include <stdio.h>

#include "log_reader_result.h"

/**
 * @brief CLogReaderFileResult - класс для вывода результатов сразу в файл
 */
class CLogReaderFileResult : public ILogReaderResult
{
public:
  CLogReaderFileResult(FILE *file);
  ~CLogReaderFileResult();

private:
  uint64_t Write(const void* data, size_t size);
  void Close();
  void SetLineNumber(unsigned number);

private:
  FILE *file_;
};
