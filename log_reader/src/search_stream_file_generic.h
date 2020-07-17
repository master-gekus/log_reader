/**
* \file search_stream_file_generic.h
*/

#pragma once
#ifndef SEARCH_STREAM_FILE_GENERIC_H_INCLUDED
#define SEARCH_STREAM_FILE_GENERIC_H_INCLUDED

#include <Windows.h>

#include "search_stream.h"

class ISearchStreamGenericFile : public ISearchStream
{
public:
  ISearchStreamGenericFile(const wchar_t* file_name);
  ~ISearchStreamGenericFile();

private:
  bool get_result_(ILogReaderResult* result, uint64_t from, uint64_t to);

protected:
  bool seek(uint64_t offset);

protected:
  HANDLE file_;
  uint64_t file_size_;
};

#endif // !SEARCH_STREAM_FILE_GENERIC_H_INCLUDED
