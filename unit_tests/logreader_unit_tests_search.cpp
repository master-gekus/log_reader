#include <clocale>
#include <gtest/gtest.h>

#include "pattern.h"
#include "search_stream.h"
#include "search_engine.h"

#include "logreader_unit_tests_pointer_guard.h"
#include "logreader_unit_tests_sss.h"

const char st01[] =
    /*  0 */ "First line\n"
    /* 11 */ "Second line\r\n"
    /* 24 */ "Third line\n\r"
    /* 36 */ "Last line";

const char st01_bom[] =
    /*  0 */ "\xEF\xBB\xBF"
    /*  3 */ "First line\n"
    /* 14 */ "Second line\r\n"
    /* 27 */ "Third line\n\r"
    /* 39 */ "Last line";

TEST(SearchEngine, CreateDestroy)
{
  {
    StringSearchStream ss(st01);
    CSearchEngine e(&ss);
    EXPECT_EQ(e.current_line_begin(), static_cast<uint64_t>(0));
  }

  {
    StringSearchStream ss(st01_bom);
    CSearchEngine e(&ss);
    EXPECT_EQ(e.current_line_begin(), static_cast<uint64_t>(3));
  }
}

struct searchengine_params
{
  const char* pattern_;
};

::std::ostream& operator <<(::std::ostream& os, const searchengine_params& value)
{
  return os << ((NULL == value.pattern_) ? "(null)" : value.pattern_);
}

class SearchEngine : public ::testing::TestWithParam<searchengine_params>
{
};

const searchengine_params se_params[] {
  {NULL},
  {"*"},
  {"**"},
};

TEST_P(SearchEngine, Search)
{
  const searchengine_params params = GetParam();

  pointer_guard<CPattern> pattern(CPattern::create(params.pattern_));
  ASSERT_TRUE(pattern);

  StringSearchStream ss(st01);
  CSearchEngine e(&ss);
}

TEST_P(SearchEngine, SearchWithBOM)
{
  const searchengine_params params = GetParam();

  pointer_guard<CPattern> pattern(CPattern::create(params.pattern_));
  ASSERT_TRUE(pattern);

  StringSearchStream ss(st01_bom);
  CSearchEngine e(&ss);
}

INSTANTIATE_TEST_SUITE_P(SearchEngine, SearchEngine, ::testing::ValuesIn(se_params));
