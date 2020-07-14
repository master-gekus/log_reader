/**
* \file pattern.h
*/

#pragma once
#ifndef PATTERN_H_INCLUDED
#define PATTERN_H_INCLUDED

#ifdef GTEST_INVOKED
#include <gtest/gtest_prod.h>
#endif

class CPatternElement;

/**
 * @brief Скомпилированный паттерн на основе фильтра
 *
 * Класс предназначен для внутреннего использоывния
 */
class CPattern
{
private:
  CPattern();

public:
  ~CPattern();

private:
  static size_t count_parts(const char* filter);

#ifdef GTEST_INVOKED
  FRIEND_TEST(Pattern, CalcSize);
#endif
};

#endif // !PATTERN_H_INCLUDED
