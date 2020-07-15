/**
* \file search_engine.h
*/

#pragma once
#ifndef CSEARCHENGINE_H_INCLUDED
#define CSEARCHENGINE_H_INCLUDED

#include <stdint.h>

class ISearchStream;

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

  uint64_t current_line_begin() const;
  bool next_line() const;

private:
  ISearchStream *stream_;

  uint64_t current_offset_;
};

inline uint64_t CSearchEngine::current_line_begin() const
{
  return current_offset_;
}

#endif // !CSEARCHENGINE_H_INCLUDED
