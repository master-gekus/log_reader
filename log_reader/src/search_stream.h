/**
* \file search_stream.h
*/

#pragma once
#ifndef ISEARCHSTREAM_H_INCLUDED
#define ISEARCHSTREAM_H_INCLUDED

#include <stdint.h>

class ILogReaderResult;

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

  bool get_result(ILogReaderResult* result, uint64_t from, uint64_t to);

  bool error() const;
  bool interrupted() const;
  bool can_continue() const;

private:
  virtual char at_(uint64_t offset) = 0;
  virtual bool get_result_(ILogReaderResult* result, uint64_t from, uint64_t to) = 0;

protected:
  bool error_;
  bool interrupted_;

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

inline bool ISearchStream::get_result(ILogReaderResult* result, uint64_t from, uint64_t to)
{
  return get_result_(result, from, to);
}

inline bool ISearchStream::error() const
{
  return error_;
}

inline bool ISearchStream::interrupted() const
{
  return interrupted_;
}

inline bool ISearchStream::can_continue() const
{
  return !(error_ || interrupted_);
}

#endif // !ISEARCHSTREAM_H_INCLUDED
