#pragma once

#include <stddef.h>

/**
 * @brief CAsciiString - конвертация из UNICODE в ASCII
 *
 * Класс предназначен для memory-safe преобразования строки из UNICODE в ASCII, чтобы не образовалось утечки памяти, т.к.
 * по условиям задачи было запрещено использовать STL (в частности, ::std::unique_ptr).
 */
class CAsciiString
{
public:
  CAsciiString(const wchar_t* sourse);
  ~CAsciiString();

public:
  bool empty() const;
  operator const char* () const;

private:
  char *data_;
  size_t size_;
};

inline bool CAsciiString::empty() const
{
  return (NULL != data_) && (0 < size_);
}

inline CAsciiString::operator const char* () const
{
  return data_;
}
