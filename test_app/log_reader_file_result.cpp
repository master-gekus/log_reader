#include "log_reader_file_result.h"

CLogReaderFileResult::CLogReaderFileResult(FILE *file)
  : file_(file)
{
}

CLogReaderFileResult::~CLogReaderFileResult()
{
}

uint64_t CLogReaderFileResult::Write(const void* data, size_t size)
{
  return fwrite(data, 1, size, file_);
}

void CLogReaderFileResult::Close()
{
  fprintf(file_, "\n");
}

void CLogReaderFileResult::SetLineNumber(unsigned number)
{
  fprintf(file_, "%7u: ", number);
}
