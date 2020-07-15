#include <clocale>
#include <gtest/gtest.h>

#include "pattern.h"
#include "search_stream.h"
#include "search_engine.h"
#include "log_reader_string_result.h"

#include "logreader_unit_tests_pointer_guard.h"
#include "logreader_unit_tests_sss.h"

const char st01[] =
    "First line\n"
    "_First line_\n"
    "Second line\r\n"
    "\r\n"
    "Third line\n\r"
    "Last line";

const char st01_bom[] =
    "\xEF\xBB\xBF"
    "First line\n"
    "_First line_\n"
    "Second line\r\n"
    "\r\n"
    "Third line\n\r"
    "Last line";

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
  const char** lines_;
};

::std::ostream& operator <<(::std::ostream& os, const searchengine_params& value)
{
  return os << '"' << ((NULL == value.pattern_) ? "(null)" : value.pattern_) << '"';
}

class SearchEngine : public ::testing::TestWithParam<searchengine_params>
{
protected:
  void PerformSearch(CSearchEngine *e)
  {
    const searchengine_params params = GetParam();

    pointer_guard<CPattern> pattern(CPattern::create(params.pattern_));
    ASSERT_TRUE(pattern);

    const char** p = params.lines_;
    while (true) {
      if (e->match(pattern)) {
        char buf[1024];
        CLogReaderStringResult res(buf, sizeof (buf));
        ASSERT_TRUE(e->get_line(&res));
        ASSERT_NE(*p, static_cast<char*>(NULL));
        EXPECT_STREQ(buf, *p);
        ++p;
      }
      if (!e->next_line()) {
        break;
      }
    }
    EXPECT_EQ(*p, static_cast<char*>(NULL));
  }
};

const char* l00[] = {NULL};

const char* l01[] = {
  "First line", "_First line_", "Second line", "", "Third line", "Last line",
  NULL
};

const char* l02[] = {
  "First line", "_First line_", "Second line", "Third line", "Last line",
  NULL
};

const char* l03[] = {
  "First line", "Second line", "Third line", "Last line",
  NULL
};

const searchengine_params se_params[] {
  {NULL, l01},
  {"*", l01},
  {"**", l01},
  {"q", l00},
  {"*q", l00},
  {"q*", l00},
  {"?", l00},
  {"*?", l02},
  {"?*", l02},
  {"line", l00},
  {"*line", l03},
  {"*line*", l02},
  {"* *line*", l02},
  {"* *line", l03},
  {"?* *line*", l02},
  {"?* *lin?", l03},
};

TEST_P(SearchEngine, Search)
{
  StringSearchStream ss(st01);
  CSearchEngine e(&ss);
  PerformSearch(&e);
}

TEST_P(SearchEngine, SearchWithBOM)
{
  StringSearchStream ss(st01_bom);
  CSearchEngine e(&ss);
  PerformSearch(&e);
}

INSTANTIATE_TEST_SUITE_P(SearchEngine, SearchEngine, ::testing::ValuesIn(se_params));
