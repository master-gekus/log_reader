/**
* \file pattern_element.h
*/

#pragma once
#ifndef PATTERN_ELEMENT_H_INCLUDED
#define PATTERN_ELEMENT_H_INCLUDED

#include <stddef.h>

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
