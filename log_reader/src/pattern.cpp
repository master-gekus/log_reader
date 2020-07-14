#include "pattern.h"

#include <stddef.h>

#include "pattern_element.h"

CPattern::CPattern(CPatternElement* elements, size_t size)
  : size_(size)
  , elements_(elements)
{
}

CPattern::~CPattern()
{
  delete [] const_cast<CPatternElement*>(elements_);
}

size_t CPattern::count_parts(const char* filter)
{
  size_t parts = 0;
  bool in_part = false;
  for (; *filter; ++filter) {
    if ('*' == (*filter)) {
      if (in_part) {
        ++parts;
        in_part = false;
      }
    }
    else {
      if (!in_part) {
        in_part = true;
      }
    }
  }
  if (in_part) {
    ++parts;
  }

  return (0 == parts) ? 1 : parts;
}

CPattern* CPattern::create(const char* filter)
{
  static const char* def_filter = "*";
  if (NULL == filter) {
    filter = def_filter;
  }

  size_t count = count_parts(filter);
  CPatternElement *elements = new CPatternElement [count];

  bool from_begin = ((*filter) != '*');
  bool to_end = false;
  CPatternElement *e = elements;
  const char* part_start = NULL;
  for (; *filter; ++filter) {
    if ('*' == (*filter)) {
      if (NULL != part_start) {
        e->set_string(part_start, filter);
        part_start = NULL;
        ++e;
      }
    }
    else {
      if (NULL == part_start) {
        part_start = filter;
      }
    }
  }

  if (NULL != part_start) {
    e->set_string(part_start, filter);
    to_end = true;
  }

  return new CPattern(elements, count);
}
