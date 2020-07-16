#include "logreader_unit_tests_sss.h"

#include "log_reader_result.h"

char StringSearchStream::at_(uint64_t offset)
{
  if (offset >= size_) {
    return '\0';
  }
  return data_[offset];
}

bool StringSearchStream::get_result_(ILogReaderResult *result, uint64_t from, uint64_t to)
{
  if ((from >= size_) || (to >= size_) || (from > to)) {
    return false;
  }

  uint64_t to_write = to - from;

  while (to_write > 0) {
    uint64_t written = result->write(data_ + from, to_write);
    if (0 == written) {
      return false;
    }
    to_write -= written;
    from += written;
  }

  result->close();
  return true;
}
