/**
* \file search_stream.h
*/

#pragma once
#ifndef ISEARCHSTREAM_H_INCLUDED
#define ISEARCHSTREAM_H_INCLUDED

#include <stdint.h>

/**
 * @brief ISearchStream - интерфейс для источника поиска
 */
class ISearchStream
{
protected:
  ISearchStream();
public:
  virtual ~ISearchStream();

public:
  char at(uint64_t offset);
  char at_nocrlf(uint64_t offset);

  uint64_t eol_offset() const;
  void drop_eol_offset();

  uint64_t last_offset() const;

private:
  virtual char at_(uint64_t offset) = 0;

private:
  uint64_t eol_offset_;
  uint64_t last_offset_;
};

inline char ISearchStream::at(uint64_t offset)
{
  if (offset > last_offset_) {
    last_offset_ = offset;
  }
  return at_(offset);
}

inline char ISearchStream::at_nocrlf(uint64_t offset)
{
  char c = at(offset);
  if (('\n'== c) || ('\r'== c)) {
    c = '\0';
  }
  if ('\0' == c) {
    eol_offset_ = offset;
  }
  return c;
}

inline uint64_t ISearchStream::eol_offset() const
{
  return eol_offset_;
}

inline void ISearchStream::drop_eol_offset()
{
  eol_offset_ = static_cast<uint64_t>(-1);
}

inline uint64_t ISearchStream::last_offset() const
{
  return last_offset_;
}

#endif // !ISEARCHSTREAM_H_INCLUDED
