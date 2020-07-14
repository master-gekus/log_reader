/**
* \file pattern_element.h
*/

#pragma once
#ifndef PATTERN_ELEMENT_H_INCLUDED
#define PATTERN_ELEMENT_H_INCLUDED

#include <stddef.h>
#include <stdint.h>

class ISearchStream;

/**
 * @brief Элемент скомпилированного паттерна (\sa CPattern)
 *
 * Класс предназначен для внутреннего использоывния
 */
class CPatternElement
{
private:
  CPatternElement();
  ~CPatternElement();

public:
  const char* data() const;
  size_t size() const;
  bool match(ISearchStream* s, uint64_t offset, bool& can_continue, bool& at_end, uint64_t& eol_offset) const;

private:
  void set_string(const char* begin, const char* end);

private:
  char* data_;
  size_t size_;

friend class CPattern;
};

inline const char* CPatternElement::data() const
{
  return data_;
}

inline size_t CPatternElement::size() const
{
  return size_;
}

#endif // PATTERN_ELEMENT_H_INCLUDED
