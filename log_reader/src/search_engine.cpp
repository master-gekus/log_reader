#include "search_engine.h"

#include <assert.h>

#include "search_stream.h"
#include "pattern.h"
#include "pattern_element.h"

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

uint64_t CSearchEngine::search_eol()
{
  uint64_t o = stream_->eol_offset();

  if (static_cast<uint64_t>(-1) == o) {
    for (o = stream_->last_offset() + 1; '\0' != stream_->at_nocrlf(o); ++o) {
    }
  }

  return o;
}

bool CSearchEngine::next_line()
{
  uint64_t o = search_eol();

  bool result = true;
  switch (stream_->at(o)) {
  case '\0':
    result = false;
    break;

  case '\r':
    ++o;
    if ('\n' == stream_->at(o)) {
      ++o;
    }
    break;

  case '\n':
    ++o;
    if ('\r' == stream_->at(o)) {
      ++o;
    }
    break;

  default:
    assert(false);
    break;
  }

  current_offset_ = o;
  stream_->drop_eol_offset();
  return result;
}

bool CSearchEngine::match(const CPattern* pattern) const
{
  const CPatternElement *element = pattern->elements();
  size_t rest_elements = pattern->size();
  uint64_t index = current_offset_;

  if (pattern->FromBegin()) {
    bool can_continue;
    bool at_end;
    if (!element->match(stream_, index, can_continue, at_end)) {
      return false;
    }
    if (0 == (--rest_elements)) {
      return pattern->ToEnd() ? at_end : true;
    }
    index += element->size();
    ++element;
  }

  return match(index, element, rest_elements, pattern->ToEnd());
}

bool CSearchEngine::match(uint64_t offset, const CPatternElement* element, size_t rest_elements, bool to_end) const
{
  for (uint64_t o = offset; true; ++o) {
    bool can_continue;
    bool at_end;
    if (element->match(stream_, o, can_continue, at_end)) {
      if (1 == rest_elements) {
        if ((!to_end) || at_end) {
          return true;
        }
      }
      else {
        return match(o + element->size(), element + 1, rest_elements - 1, to_end);
      }
    }
    if (!can_continue) {
      break;
    }
  }

  return false;
}
