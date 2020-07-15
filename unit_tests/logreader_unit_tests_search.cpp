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
  char at_(uint64_t offset)
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
  const uint64_t last_offset_;
};

::std::ostream& operator <<(::std::ostream& os, const patternelement_params& value)
{
  return os << value.pattern_ << "(" << value.offset_ << ")";
}

class Pattern : public ::testing::TestWithParam<patternelement_params>
{
};

const patternelement_params pe_params[] = {
  {"First", 0, true, true, false, static_cast<uint64_t>(-1), static_cast<uint64_t>(5)},
  {"First", 1, false, true, false, static_cast<uint64_t>(-1), static_cast<uint64_t>(1)},
  {"First", 5, false, true, false, static_cast<uint64_t>(-1), static_cast<uint64_t>(5)},
  {"line", 6, true, false, true, static_cast<uint64_t>(10), static_cast<uint64_t>(10)},
  {"line1", 6, false, false, false, static_cast<uint64_t>(10), static_cast<uint64_t>(10)},
  {"Second", 11, true, true, false, static_cast<uint64_t>(-1), static_cast<uint64_t>(17)},
  {"Third", 24, true, true, false, static_cast<uint64_t>(-1), static_cast<uint64_t>(29)},
  {"Last", 36, true, true, false, static_cast<uint64_t>(-1), static_cast<uint64_t>(40)},
  {"Se??nd", 11, true, true, false, static_cast<uint64_t>(-1), static_cast<uint64_t>(17)},
  {"T??rd", 24, true, true, false, static_cast<uint64_t>(-1), static_cast<uint64_t>(29)},
  {"L?st", 36, true, true, false, static_cast<uint64_t>(-1), static_cast<uint64_t>(40)},
  {"lin?", 18, true, false, true, static_cast<uint64_t>(22), static_cast<uint64_t>(22)},
  {"lin", 18, true, true, false, static_cast<uint64_t>(-1), static_cast<uint64_t>(21)},
  {"lin?", 30, true, false, true, static_cast<uint64_t>(34), static_cast<uint64_t>(34)},
  {"lin?", 41, true, false, true, static_cast<uint64_t>(45), static_cast<uint64_t>(45)},
};

const char st01[] =
    /*  0 */ "First line\n"
    /* 11 */ "Second line\r\n"
    /* 24 */ "Third line\n\r"
    /* 36 */ "Last line";

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

  EXPECT_EQ(params.found_, e.match(&ss, params.offset_, can_continue, at_end));
  EXPECT_EQ(params.at_end_, at_end);
  EXPECT_EQ(params.can_continue_, can_continue);
  EXPECT_EQ(params.eol_offset_, ss.eol_offset());
  EXPECT_EQ(params.last_offset_, ss.last_offset());
}

INSTANTIATE_TEST_SUITE_P(Pattern, Pattern,::testing::ValuesIn(pe_params));

TEST(SearchEngine, CreateDestroy)
{
  StringSearchStream ss(st01);
  CSearchEngine e(&ss);
}
