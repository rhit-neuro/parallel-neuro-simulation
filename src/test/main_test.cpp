#include "gmock/gmock.h"

TEST(Sample, One) {
  EXPECT_EQ(1, 1);
}

TEST(Sample, Two) {
  EXPECT_GT(1, 0);
}

TEST(Sample, Three) {
  EXPECT_TRUE(true);
  EXPECT_FALSE(false);
}

