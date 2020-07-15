#include "logreader_unit_tests_sss.h"

char StringSearchStream::at_(uint64_t offset)
{
  if (offset >= size_) {
    return '\0';
  }
  return data_[offset];
}
