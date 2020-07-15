/**
* \file search_engine.h
*/

#pragma once
#ifndef CSEARCHENGINE_H_INCLUDED
#define CSEARCHENGINE_H_INCLUDED

#include <stdint.h>

class ISearchStream;
class CPattern;
class CPatternElement;

/**
 * @brief CSearchEngine - класс, который, собственно, и осуществляет поиск
 */
class CSearchEngine
{
public:
  /**
   * @brief CSearchEngine
   * @param stream - текстовый поток для поиска в нём
   *
   * Класс \ref CSearchEngine не становится "владельцем" потока. Вызывающий должен сам позаботиться о том, чтобы
   * удалить поток после использования и удаления экземпляра класса \ref CSearchEngine, который их использует.
   *
   * \warning Обращение к методам класса \ref CSearchEngine после удалегия потока может привести к краху.
   */
  CSearchEngine(ISearchStream *stream);

public:
  ISearchStream* stream() const;

  uint64_t current_line_begin() const;
  bool next_line();

  bool match(const CPattern* pattern) const;
  bool match(uint64_t offset, const CPatternElement* element, size_t rest_elements, bool to_end) const;

private:
  uint64_t search_eol();

private:
  ISearchStream *stream_;

  uint64_t current_offset_;
};

inline ISearchStream* CSearchEngine::stream() const
{
  return stream_;
}

inline uint64_t CSearchEngine::current_line_begin() const
{
  return current_offset_;
}

#endif // !CSEARCHENGINE_H_INCLUDED
