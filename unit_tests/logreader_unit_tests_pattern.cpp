#include <clocale>
#include <gtest/gtest.h>

#include "pattern.h"

TEST(Pattern, CalcSize)
{
  EXPECT_EQ(1, CPattern::count_parts(NULL));
  EXPECT_EQ(1, CPattern::count_parts("*"));
  EXPECT_EQ(1, CPattern::count_parts("**"));
  EXPECT_EQ(1, CPattern::count_parts("***"));
  EXPECT_EQ(1, CPattern::count_parts("*?*"));
  EXPECT_EQ(1, CPattern::count_parts("**?**"));
  EXPECT_EQ(1, CPattern::count_parts("*a*"));
  EXPECT_EQ(1, CPattern::count_parts("*a**"));
  EXPECT_EQ(1, CPattern::count_parts("**a*"));
}
