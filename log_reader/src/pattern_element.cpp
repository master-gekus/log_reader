#include "pattern_element.h"

#include <string.h>
#include <assert.h>

CPatternElement::CPatternElement()
  : data_(NULL)
  , size_(0)
{
}

CPatternElement::~CPatternElement()
{
  delete [] data_;
}

void CPatternElement::set_string(const char* begin, const char* end)
{
  assert(begin <= end);

  size_ = end - begin;
  data_ = new char [size_ + 1];
  memcpy(data_, begin, size_);
  data_[size_] = '\0';
}
