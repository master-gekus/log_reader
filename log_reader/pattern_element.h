/**
* \file pattern_element.h
*/

#pragma once
#ifndef PATTERN_ELEMENT_H_INCLUDED
#define PATTERN_ELEMENT_H_INCLUDED

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

friend class CPattern;
};

#endif // PATTERN_ELEMENT_H_INCLUDED
