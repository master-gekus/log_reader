#include "search_stream.h"

ISearchStream::ISearchStream()
  : eol_offset_(static_cast<uint64_t>(-1))
  , last_offset_(0)
{
}

ISearchStream::~ISearchStream()
{
}
