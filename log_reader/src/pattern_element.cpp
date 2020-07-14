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

namespace {
inline char remove_crlf(char c)
{
  return (('\r' == c) || ('\n' == c)) ? '\0' : c;
}

} // namespace {

bool CPatternElement::match(ISearchStream* s, uint64_t offset, bool& can_continue, bool& at_end, uint64_t& eol_offset) const
{
  // Проверим, что вообще влезает до конца строки - если он (конец) детектирован
  at_end = false;
  if ((offset + size_) > eol_offset) {
    can_continue = false;
    return false;
  }

  // Смотрим по всей длине паттерна, на предмет - а вдруг там конец?
  bool m = true;
  for (size_t i = 0; i < size_; ++i) {
    char c = remove_crlf(s->at(offset + i));
    if ('\0' == c) {
      can_continue = false;
      eol_offset = offset + i;
      return false;
    }
    if (m && ((data_[i] == '?') || (data_[i] == c))) {
      continue;
    }
    m = false;
  }

  if ('\0' == remove_crlf(s->at(offset + size_))) {
    eol_offset = offset + size_;
    at_end = m;
    can_continue = false;
  }
  else {
    can_continue = true;
  }

  return m;
}
