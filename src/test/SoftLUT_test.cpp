#if INCLUDE_LUT_SUPPORT
#include "gmock/gmock.h"
#include "../main/math/LUT.h"

using namespace lut;

class LutTest : public ::testing::Test {
  protected:
    SoftLUT softlut = SoftLUT("../../resources/32pointsM.csv");
    float expected, actual, vMem;
    float expectedSlope, expectedOffset, storedVMem;
};

float calcActual(SoftLUT softlut, float vMem, CurveSelect curve) {
  return softlut.interpolate(vMem, curve);
}

float calcExpected(float expectedSlope, float expectedOffset, float storedVMem, float vMem) {
  return expectedSlope * (vMem - storedVMem) + expectedOffset;
}

TEST_F(LutTest, BeforeFirst) {
  vMem = -0.078;
  storedVMem = -0.077915;
  expectedOffset = 0.00065042;
  expectedSlope = 0.26487;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, storedVMem, vMem);
  EXPECT_EQ(expected, actual);
}

TEST_F(LutTest, ExactlyFirst) {
  vMem = -0.077915;
  storedVMem = -0.077915;
  expectedOffset = 0.00065042;
  expectedSlope = 0.26487;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, storedVMem, vMem);
  EXPECT_EQ(expected, actual);
}

TEST_F(LutTest, Middle) {
  vMem = -0.04740;
  storedVMem = -0.04741;
  expectedOffset = 0.059442;
  expectedSlope = 9.6112;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, storedVMem, vMem);
  EXPECT_EQ(expected, actual);
}

TEST_F(LutTest, ExactlyMiddle) {
  vMem = -0.019412;
  storedVMem = -0.019412;
  expectedOffset = 0.80818;
  expectedSlope = 21.586;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, storedVMem, vMem);
  EXPECT_EQ(expected, actual);
}

TEST_F(LutTest, ExactlyLast) {
  vMem = 0.019917;
  storedVMem = 0.019917;
  expectedOffset = 0.99935;
  expectedSlope = 0;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, storedVMem, vMem);
  EXPECT_EQ(expected, actual);
}

TEST_F(LutTest, AfterLast) {
  // First curve
  vMem = 0.019918;
  storedVMem = 0.019917;
  expectedOffset = 0.99935;
  expectedSlope = 0;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, storedVMem, vMem);
  EXPECT_EQ(expected, actual);

  // Last curve
  vMem = 0.0469;
  storedVMem = 0.046882;
  expectedOffset = 9.4911;
  expectedSlope = 0;

  actual = calcActual(softlut, vMem, M_T_KF);
  expected = calcExpected(expectedSlope, expectedOffset, storedVMem, vMem);
  EXPECT_EQ(expected, actual);
}

#endif //INCLUDE_LUT_SUPPORT