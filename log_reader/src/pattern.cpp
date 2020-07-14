#include "pattern.h"

#include <stddef.h>

CPattern::CPattern()
{
}

CPattern::~CPattern()
{
}

size_t CPattern::count_parts(const char* filter)
{
  static const char* def_filter = "*";
  if (NULL == filter) {
    filter = def_filter;
  }

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
