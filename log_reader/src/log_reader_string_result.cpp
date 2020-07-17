#include "log_reader_string_result.h"

#include <assert.h>
#include <string.h>

CLogReaderStringResult::CLogReaderStringResult(void* buffer, size_t size, unsigned *line_number)
  : buf_(static_cast<char*>(buffer))
  , size_(static_cast<uint64_t>(size))
  , offset_(0)
  , line_number_(line_number)
{
  assert(NULL != buf_);
  assert(0 < size_);
}

uint64_t CLogReaderStringResult::Write(const void *data, size_t size)
{
  if ((offset_ + size) >= (size_ - 1)) {
    return 0;
  }

  if (0 < size) {
    memcpy(buf_ + offset_, data, size);
    offset_ += size;
  }

  return size;
}

void CLogReaderStringResult::Close()
{
  if (offset_ >= size_) {
    return;
  }
  buf_[offset_] = '\0';

  // Для возможности повторного использования
  offset_ = 0;
}

void CLogReaderStringResult::SetLineNumber(unsigned number)
{
  if (NULL != line_number_) {
    *line_number_ = number;
  }
}
