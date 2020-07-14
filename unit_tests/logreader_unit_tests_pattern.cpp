#include <clocale>
#include <gtest/gtest.h>

#include "pattern.h"

struct pattern_params
{
  const char* filter_;
  const char** parts_;
};

::std::ostream& operator <<(::std::ostream& os, const pattern_params& value)
{
  return os << ((NULL == value.filter_) ? "(null)" : value.filter_);
}

const char* p01[] = {"", NULL};
const char* p02[] = {"?", NULL};
const char* p03[] = {"a", NULL};
const char* p04[] = {"abc", NULL};
const char* p05[] = {"a", "b", NULL};
const char* p06[] = {"?", "?", NULL};
const pattern_params testing_params[] = {
  {NULL, p01},
  {"*", p01},
  {"**", p01},
  {"***", p01},

  {"*?*", p02},
  {"**?**", p02},

  {"a", p03},
  {"*a", p03},
  {"a*", p03},
  {"*a*", p03},
  {"*a**", p03},
  {"**a*", p03},

  {"abc", p04},
  {"*abc", p04},
  {"abc*", p04},

  {"a*b", p05},
  {"*a*b", p05},
  {"a*b*", p05},
  {"*a*b*", p05},

  {"*?*?*", p06},
};

class Compile : public ::testing::TestWithParam<pattern_params>
{
};

TEST_P(Compile, Create)
{
  const pattern_params params = GetParam();

  size_t count = 0;
  for (const char** p = params.parts_; *p; ++p) {
    ++count;
  }

  EXPECT_EQ(count, CPattern::count_parts(params.filter_));
}

INSTANTIATE_TEST_SUITE_P(Pattern, Compile,::testing::ValuesIn(testing_params));
