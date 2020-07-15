#include "pattern_element.h"

#include <string.h>
#include <assert.h>

#include "search_stream.h"

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

bool CPatternElement::match(ISearchStream* s, uint64_t offset, bool& can_continue, bool& at_end) const
{
  at_end = false;
  can_continue = false;

  // Проверим, что вообще влезает до конца строки - если он (конец) детектирован
  if ((offset + size_) > s->eol_offset()) {
    return false;
  }

  for (size_t i = 0; i < size_; ++i) {
    char c = s->at_nocrlf(offset + i);
    if ('\0' == c) {
      return false;
    }
    if ((data_[i] != '?') && (data_[i] != c)) {
      can_continue = true;
      return false;
    }
  }

  at_end = ('\0' == s->at_nocrlf(offset + size_));
  can_continue = !at_end;

  return true;
}
