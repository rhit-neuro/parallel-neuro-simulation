#if INCLUDE_LUT_SUPPORT
#include "gmock/gmock.h"
#include "../main/math/LUT.h"

using namespace lut;

class LutTest : public ::testing::Test {
  protected:
    SoftLUT softlut = SoftLUT("../../resources/32pointsConverted.csv");
    float expected, actual, vMem;
    float expectedSlope, expectedOffset;
};

float calcActual(SoftLUT softlut, float vMem, CurveSelect curve) {
  return softlut.interpolate(vMem, curve);
}

float calcExpected(float expectedSlope, float expectedOffset, float vMem) {
  return expectedSlope * vMem + expectedOffset;
}

// Returns percent difference between acutal and expected
float pDiff(float expected, float actual) {
  return std::abs((expected - actual)/expected) * 100;
}

// Tests pass as long as the percent difference between acutal
// and expected is less than this number
const float maxError = 0.001;

TEST_F(LutTest, BeforeFirst) {
  // First curve
  vMem = -0.078;
  expectedOffset = 0.021288;
  expectedSlope = 0.26487;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);

  // Last curve
  vMem = -0.098438;
  expectedOffset = 1.25227;
  expectedSlope = -2.4263;

  actual = calcActual(softlut, vMem, M_T_KF);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);
}

TEST_F(LutTest, ExactlyFirst) {
  // First curve
  vMem = -0.077915;
  expectedOffset = 0.021288;
  expectedSlope = 0.26487;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);

  // Last curve
  vMem = -0.098434;
  expectedOffset = 1.25227;
  expectedSlope = -2.4263;

  actual = calcActual(softlut, vMem, M_T_KF);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);
}

TEST_F(LutTest, Middle) {
  // First curve
  vMem = -0.04740;
  expectedOffset = 0.515109;
  expectedSlope = 9.6112;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);

  // Last curve
  vMem = -0.0054;
  expectedOffset = 8.672119;
  expectedSlope = 108.97;

  actual = calcActual(softlut, vMem, M_T_KF);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);
}

TEST_F(LutTest, ExactlyMiddle) {
  // First curve
  vMem = -0.019412;
  expectedOffset = 1.227207;
  expectedSlope = 21.586;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);

  // Last curve
  vMem = -0.005409;
  expectedOffset = 8.672119;
  expectedSlope = 108.97;

  actual = calcActual(softlut, vMem, M_T_KF);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);
}

TEST_F(LutTest, ExactlyLast) {
  // First curve
  vMem = 0.019917;
  expectedOffset = 0.99935;
  expectedSlope = 0;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);

  // Last curve
  vMem = 0.046882;
  expectedOffset = 9.4911;
  expectedSlope = 0;

  actual = calcActual(softlut, vMem, M_T_KF);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);
}

TEST_F(LutTest, AfterLast) {
  // First curve
  vMem = 0.019918;
  expectedOffset = 0.99935;
  expectedSlope = 0;

  actual = calcActual(softlut, vMem, M_F_NA);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);

  // Last curve
  vMem = 0.0469;
  expectedOffset = 9.4911;
  expectedSlope = 0;

  actual = calcActual(softlut, vMem, M_T_KF);
  expected = calcExpected(expectedSlope, expectedOffset, vMem);
  EXPECT_LE(pDiff(expected, actual), maxError);
}

#endif //INCLUDE_LUT_SUPPORT