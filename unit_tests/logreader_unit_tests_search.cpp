#include <clocale>
#include <gtest/gtest.h>

#include "search_stream.h"
#include "search_engine.h"

class StringSearchStream : public ISearchStream
{
public:
  template<size_t N>
  inline StringSearchStream(const char (&str)[N])
    : data_(str)
    , size_(N)
  {}

private:
  const char* data_;
  const uint64_t size_;
};

namespace {
const char st01[] =
    "First line\n"
    "Second line\r\n"
    "Third line\n\r"
    "Last line";

} // namespace {

TEST(SearchEngine, CreateDestroy)
{
  StringSearchStream ss(st01);
  CSearchEngine e(&ss);
}
