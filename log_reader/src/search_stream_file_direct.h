/**
* \file search_stream_file_generic.h
*/

#pragma once
#ifndef SEARCH_STREAM_FILE_DIRECT_H_INCLUDED
#define SEARCH_STREAM_FILE_DIRECT_H_INCLUDED

#include "search_stream_file_generic.h"

class CSearchStreamFileDirect : public ISearchStreamGenericFile
{
public:
  CSearchStreamFileDirect(const wchar_t* file_name);
  ~CSearchStreamFileDirect();

private:
  char at_(uint64_t offset);
};

#endif // !SEARCH_STREAM_FILE_DIRECT_H_INCLUDED
