/**
* \file pattern.h
*/

#pragma once
#ifndef PATTERN_H_INCLUDED
#define PATTERN_H_INCLUDED

#ifdef GTEST_INVOKED
#include <gtest/gtest_prod.h>
#endif

#include <stddef.h>

class CPatternElement;

/**
 * @brief Скомпилированный паттерн на основе фильтра
 *
 * Класс предназначен для внутреннего использоывния
 */
class CPattern
{
private:
  CPattern(CPatternElement* elements, size_t size, bool from_begin, bool to_end);

public:
  ~CPattern();

public:
  size_t size() const;
  const CPatternElement* elements() const;
  bool FromBegin() const;
  bool ToEnd() const;

public:
  static CPattern* create(const char* filter);

private:
  static size_t count_parts(const char* filter);

private:
  const size_t size_;
  const CPatternElement* elements_;
  const bool from_begin_;
  const bool to_end_;

#ifdef GTEST_INVOKED
  FRIEND_TEST(Compile, Create);
#endif
};

inline size_t CPattern::size() const
{
  return size_;
}

inline const CPatternElement* CPattern::elements() const
{
  return elements_;
}

inline bool CPattern::FromBegin() const
{
  return from_begin_;
}

inline bool CPattern::ToEnd() const
{
  return to_end_;
}

#endif // !PATTERN_H_INCLUDED
