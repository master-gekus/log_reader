#include <clocale>
#include <string>

#include <gtest/gtest.h>

#include "pattern.h"
#include "pattern_element.h"

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
const char* p07[] = {"Quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog", NULL};
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

  {"Quick*brown*fox*jumps*over*the*lazy*dog", p07},
  {"*Quick*brown*fox*jumps*over*the*lazy*dog", p07},
  {"Quick*brown*fox*jumps*over*the*lazy*dog*", p07},
  {"*Quick*brown*fox*jumps*over*the*lazy*dog*", p07},
};

class Compile : public ::testing::TestWithParam<pattern_params>
{
protected:
  class guard
  {
  public:
    inline explicit guard(CPattern* ptr) : ptr_(ptr) {}
    inline ~guard() {delete ptr_;}
  private:
    CPattern* ptr_;
  };
};

TEST_P(Compile, Create)
{
  const pattern_params params = GetParam();

  size_t count = 0;
  for (const char** p = params.parts_; *p; ++p) {
    ++count;
  }

  if (NULL != params.filter_) {
    EXPECT_EQ(count, CPattern::count_parts(params.filter_));
  }

  CPattern *pattern = CPattern::create(params.filter_);
  EXPECT_NE(pattern, static_cast<CPattern *>(NULL));
  guard g(pattern);

  EXPECT_EQ(pattern->size(), count);

  for (size_t i = 0; i < count; ++i) {
    const CPatternElement *e = pattern->elements() + i;
    EXPECT_EQ(::std::string(e->data(), e->size()), ::std::string(params.parts_[i]));
  }
}

INSTANTIATE_TEST_SUITE_P(Pattern, Compile,::testing::ValuesIn(testing_params));
