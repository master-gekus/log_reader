#include <clocale>
#include <gtest/gtest.h>

#include "pattern.h"
#include "pattern_element.h"
#include "search_stream.h"
#include "search_engine.h"

#include "logreader_unit_tests_pointer_guard.h"
#include "logreader_unit_tests_sss.h"

const char st01[] =
    /*  0 */ "First line\n"
    /* 11 */ "Second line\r\n"
    /* 24 */ "Third line\n\r"
    /* 36 */ "Last line";

TEST(SearchEngine, CreateDestroy)
{
  StringSearchStream ss(st01);
  CSearchEngine e(&ss);
}
