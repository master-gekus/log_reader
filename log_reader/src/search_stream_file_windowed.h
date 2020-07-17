/**
* \file search_stream_file_windowed.h
*/

#pragma once
#ifndef SEARCH_STREAM_FILE_WINDOWED_H_INCLUDED
#define SEARCH_STREAM_FILE_WINDOWED_H_INCLUDED

#include "search_stream_file_generic.h"

class CSearchStreamFileWindowed : public ISearchStreamGenericFile
{
public:
  CSearchStreamFileWindowed(const wchar_t* file_name, size_t window_size);
  ~CSearchStreamFileWindowed();

private:
  char at_(uint64_t offset);

private:
  bool adjust_window(uint64_t offset);
  bool read_window(uint64_t to_read);

private:
  size_t window_size_;
  char *window_;
  uint64_t window_offset_;
};

#endif // !SEARCH_STREAM_FILE_WINDOWED_H_INCLUDED
