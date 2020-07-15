/**
* \file logreader_unit_tests_sss.h
*/

#pragma once
#ifndef LOGREADER_UNIT_TESTS_SSS_H_INCLUDED
#define LOGREADER_UNIT_TESTS_SSS_H_INCLUDED

#include <stddef.h>

#include "search_stream.h"

class StringSearchStream : public ISearchStream
{
public:
  template<size_t N>
  inline StringSearchStream(const char (&str)[N])
    : data_(str)
    , size_(N)
  {}

private:
  char at_(uint64_t offset);
  bool get_result_(ILogReaderResult *result, uint64_t from, uint64_t to);

private:
  const char* data_;
  const uint64_t size_;
};

#endif // !LOGREADER_UNIT_TESTS_SSS_H_INCLUDED
