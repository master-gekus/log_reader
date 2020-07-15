#include "search_engine.h"

#include <assert.h>

#include "search_stream.h"

CSearchEngine::CSearchEngine(ISearchStream *stream)
  : stream_(stream)
  , current_offset_(0)
{
  assert(NULL != stream);

  if (('\xEF' ==stream_->at(0))
      && ('\xBB' ==stream_->at(1))
      && ('\xBF' ==stream_->at(2))) {
    current_offset_ = 3;
  }
}
