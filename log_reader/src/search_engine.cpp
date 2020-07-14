#include "search_engine.h"

#include <assert.h>

CSearchEngine::CSearchEngine(ISearchStream *stream)
  : stream_(stream)
{
  assert(NULL != stream);
}
