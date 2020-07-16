/**
* \file search_engine.h
*/

#pragma once
#ifndef CSEARCHENGINE_H_INCLUDED
#define CSEARCHENGINE_H_INCLUDED

#include <stdint.h>

class ISearchStream;
class ILogReaderResult;
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
   * Класс \ref CSearchEngine становится "владельцем" потока, и удаляет его в своём деструкторе.
   */
  CSearchEngine(ISearchStream *stream);
  ~CSearchEngine();

public:
  ISearchStream* stream() const;

  uint64_t current_line_begin() const;
  uint64_t current_line_number() const;
  bool eof() const;

  bool next_line();
  bool get_line(ILogReaderResult* result);

  bool match(const CPattern* pattern) const;
  bool match(uint64_t offset, const CPatternElement* element, size_t rest_elements, bool to_end) const;

private:
  uint64_t search_eol();

private:
  ISearchStream *stream_;

  uint64_t current_offset_;
  uint64_t current_line_;
  bool eof_;
};

inline ISearchStream* CSearchEngine::stream() const
{
  return stream_;
}

inline uint64_t CSearchEngine::current_line_begin() const
{
  return current_offset_;
}

inline bool CSearchEngine::eof() const
{
  return eof_;
}

inline uint64_t CSearchEngine::current_line_number() const
{
  return current_line_;
}

#endif // !CSEARCHENGINE_H_INCLUDED
