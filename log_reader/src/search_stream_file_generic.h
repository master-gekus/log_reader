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

protected:
  HANDLE file_;
  uint64_t file_size_;
};

#endif // !SEARCH_STREAM_FILE_GENERIC_H_INCLUDED
