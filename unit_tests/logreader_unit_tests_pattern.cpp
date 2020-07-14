#include <clocale>
#include <string>

#include <gtest/gtest.h>

#include "pattern.h"
#include "pattern_element.h"

struct pattern_params
{
  const char* filter_;
  const char** parts_;
  const bool from_begin_;
  const bool to_end_;
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
  {NULL, p01, false, false},
  {"*", p01, false, false},
  {"**", p01, false, false},
  {"***", p01, false, false},

  {"?*", p02, true, false},
  {"*?", p02, false, true},
  {"*?*", p02, false, false},
  {"**?**", p02, false, false},

  {"a", p03, true, true},
  {"*a", p03, false, true},
  {"a*", p03, true, false},
  {"*a*", p03, false, false},
  {"*a**", p03, false, false},
  {"**a*", p03, false, false},

  {"abc", p04, true, true},
  {"*abc", p04, false, true},
  {"abc*", p04, true, false},

  {"a*b", p05, true, true},
  {"*a*b", p05, false, true},
  {"a*b*", p05, true, false},
  {"*a*b*", p05, false, false},

  {"*?*?*", p06, false, false},

  {"Quick*brown*fox*jumps*over*the*lazy*dog", p07, true, true},
  {"*Quick*brown*fox*jumps*over*the*lazy*dog", p07, false, true},
  {"Quick*brown*fox*jumps*over*the*lazy*dog*", p07, true, false},
  {"*Quick*brown*fox*jumps*over*the*lazy*dog*", p07, false, false},
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
  EXPECT_EQ(pattern->FromBegin(), params.from_begin_);
  EXPECT_EQ(pattern->ToEnd(), params.to_end_);

  for (size_t i = 0; i < count; ++i) {
    const CPatternElement *e = pattern->elements() + i;
    EXPECT_EQ(::std::string(e->data(), e->size()), ::std::string(params.parts_[i]));
  }
}

INSTANTIATE_TEST_SUITE_P(Pattern, Compile,::testing::ValuesIn(testing_params));
