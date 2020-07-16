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
    "Last line\n";

const char st01_bom[] =
    "\xEF\xBB\xBF"
    "First line\n"
    "_First line_\n"
    "Second line\r\n"
    "\r\n"
    "Third line\n\r"
    "Last line\n";

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

TEST(SearchEngine, ScanLines)
{
  {
    StringSearchStream ss(st01);
    CSearchEngine e(&ss);

    // "First line\n"
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(1));
    EXPECT_FALSE(e.eof());

    // "_First line_\n"
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(2));
    EXPECT_FALSE(e.eof());

    // "Second line\r\n"
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(3));
    EXPECT_FALSE(e.eof());

    // "\r\n"
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(4));
    EXPECT_FALSE(e.eof());

    // "Third line\n\r"
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(5));
    EXPECT_FALSE(e.eof());

    // "Last line";
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(6));
    EXPECT_FALSE(e.eof());

    // Empty line
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(7));
    EXPECT_FALSE(e.eof());

    EXPECT_FALSE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(8));
    EXPECT_TRUE(e.eof());

    EXPECT_FALSE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(8));
    EXPECT_TRUE(e.eof());
  }

  {
    StringSearchStream ss(st01_bom);
    CSearchEngine e(&ss);

    // "First line\n"
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(1));
    EXPECT_FALSE(e.eof());

    // "_First line_\n"
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(2));
    EXPECT_FALSE(e.eof());

    // "Second line\r\n"
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(3));
    EXPECT_FALSE(e.eof());

    // "\r\n"
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(4));
    EXPECT_FALSE(e.eof());

    // "Third line\n\r"
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(5));
    EXPECT_FALSE(e.eof());

    // "Last line";
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(6));
    EXPECT_FALSE(e.eof());

    // Empty line
    EXPECT_TRUE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(7));
    EXPECT_FALSE(e.eof());

    EXPECT_FALSE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(8));
    EXPECT_TRUE(e.eof());

    EXPECT_FALSE(e.next_line());
    EXPECT_EQ(e.current_line_number(), static_cast<uint64_t>(8));
    EXPECT_TRUE(e.eof());
  }
}

struct searchengine_params
{
  const char* pattern_;
  const char** lines_;
};

::std::ostream& operator <<(::std::ostream& os, const searchengine_params& value)
{
  if (NULL == value.pattern_) {
    return os << "(null)";
  }
  else {
    return os << '"' << value.pattern_ << '"';
  }
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
  "First line", "_First line_", "Second line", "", "Third line", "Last line", "",
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

const char* l04[] = {"","",NULL};

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
  {"", l04},
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
