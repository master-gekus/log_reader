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

struct patternelement_params
{
  const char* pattern_;
  const uint64_t offset_;
  const bool found_;
  const bool can_continue_;
  const bool at_end_;
  const uint64_t eol_offset_;
};

::std::ostream& operator <<(::std::ostream& os, const patternelement_params& value)
{
  return os << value.pattern_ << "(" << value.offset_ << ")";
}

class Pattern : public ::testing::TestWithParam<patternelement_params>
{
};

const patternelement_params pe_params[] = {
  {"First", 0, true, true, false, static_cast<uint64_t>(-1)},
  {"First", 1, false, true, false, static_cast<uint64_t>(-1)},
  {"First", 5, false, false, false, static_cast<uint64_t>(10)},
  {"line", 6, true, false, true, static_cast<uint64_t>(10)},
};

const char st01[] =
    "First line\n"
    "Second line\r\n"
    "Third line\n\r"
    "Last line";

TEST_P(Pattern, PrimitiveMatch)
{
  const patternelement_params params = GetParam();

  CPatternElement e;
  const char* end = params.pattern_;
  end += strlen(end);
  e.set_string(params.pattern_, end);
  StringSearchStream ss(st01);

  bool can_continue;
  bool at_end;
  uint64_t eol_offset = static_cast<uint64_t>(-1);

  EXPECT_EQ(params.found_, e.match(&ss, params.offset_, can_continue, at_end, eol_offset));
  EXPECT_EQ(params.at_end_, at_end);
  EXPECT_EQ(params.can_continue_, can_continue);
  EXPECT_EQ(params.eol_offset_, eol_offset);
}

INSTANTIATE_TEST_SUITE_P(Pattern, Pattern,::testing::ValuesIn(pe_params));

TEST(SearchEngine, CreateDestroy)
{
  StringSearchStream ss(st01);
  CSearchEngine e(&ss);
}
