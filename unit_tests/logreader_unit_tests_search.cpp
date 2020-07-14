#include <clocale>
#include <gtest/gtest.h>

#include "pattern.h"
#include "pattern_element.h"
#include "search_stream.h"
#include "search_engine.h"

#include "logreader_unit_tests_pointer_guard.h"

class StringSearchStream : public ISearchStream
{
public:
  template<size_t N>
  inline StringSearchStream(const char (&str)[N])
    : data_(str)
    , size_(N)
  {}

public:
  char at(uint64_t offset) const
  {
    if (offset >= size_) {
      return '\0';
    }
    return data_[offset];
  }

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

TEST(Pattern, PrimitiveMatch)
{
  StringSearchStream ss(st01);
  pointer_guard<CPattern> p(CPattern::create("First*first*irst*line*?irst*lin?"));
  ASSERT_EQ(p->size(), 6);

  bool can_continue;
  bool at_end;
  uint64_t eol_offset = static_cast<uint64_t>(-1);

  EXPECT_TRUE(p->elements()[0].match(&ss, 0, can_continue, at_end, eol_offset));
  EXPECT_FALSE(at_end);
  EXPECT_TRUE(can_continue);
  EXPECT_EQ(eol_offset, static_cast<uint64_t>(-1));

  EXPECT_FALSE(p->elements()[0].match(&ss, 1, can_continue, at_end, eol_offset));
  EXPECT_FALSE(at_end);
  EXPECT_TRUE(can_continue);
  EXPECT_EQ(eol_offset, static_cast<uint64_t>(-1));

  EXPECT_FALSE(p->elements()[0].match(&ss, 6, can_continue, at_end, eol_offset));
  EXPECT_FALSE(at_end);
  EXPECT_FALSE(can_continue);
  EXPECT_EQ(eol_offset, static_cast<uint64_t>(10));
}

TEST(SearchEngine, CreateDestroy)
{
  StringSearchStream ss(st01);
  CSearchEngine e(&ss);
}
