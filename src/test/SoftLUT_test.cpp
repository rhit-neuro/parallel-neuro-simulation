#if INCLUDE_LUT_SUPPORT
#include "gmock/gmock.h"
#include "../main/math/LUT.h"

using namespace lut;

class SoftLUT_test : public ::testing::Test {
  protected:
    // Tests pass as long as the absolute error between acutal
    // and expected is less than this number
    const float maxError = 0.00000001;
    SoftLUT lutut = SoftLUT("32pointsConverted.csv");
    float expected, actual, vMem;
    float expectedSlope, expectedOffset;
    CurveSelect curve;
    float calcActual() {
      return lutut.interpolate(vMem, curve);
    }
    float calcExpected() {
      return expectedSlope * vMem + expectedOffset;
    }
    ::testing::AssertionResult closeEnough() {
      if (std::abs(actual - expected) < maxError) {
        return ::testing::AssertionSuccess();
      } else {
        return ::testing::AssertionFailure() << "Curve: " << curve
            << " vMem: " << vMem << " Expected: " << expected
            << " Actual: " << actual;
      }
    }
};


TEST_F(SoftLUT_test, BeforeFirst) {
  // First curve
  curve = M_F_NA;
  vMem = -0.078;
  expectedOffset = 0.021288;
  expectedSlope = 0.26487;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = M_T_KF;
  vMem = -0.098438;
  expectedOffset = 1.25227;
  expectedSlope = -2.4263;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

TEST_F(SoftLUT_test, ExactlyFirst) {
  // First curve
  curve = M_F_NA;
  vMem = -0.077915;
  expectedOffset = 0.021288;
  expectedSlope = 0.26487;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = M_T_KF;
  vMem = -0.098434;
  expectedOffset = 1.25227;
  expectedSlope = -2.4263;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

TEST_F(SoftLUT_test, Middle) {
  // First curve
  curve = M_F_NA;
  vMem = -0.04740;
  expectedOffset = 0.515109;
  expectedSlope = 9.6112;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = M_T_KF;
  vMem = -0.0054;
  expectedOffset = 8.672119;
  expectedSlope = 108.97;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

TEST_F(SoftLUT_test, ExactlyMiddle) {
  // First curve
  curve = M_F_NA;
  vMem = -0.019412;
  expectedOffset = 1.227207;
  expectedSlope = 21.586;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = M_T_KF;
  vMem = -0.005409;
  expectedOffset = 8.672119;
  expectedSlope = 108.97;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

TEST_F(SoftLUT_test, ExactlyLast) {
  // First curve
  curve = M_F_NA;
  vMem = 0.019917;
  expectedOffset = 0.99935;
  expectedSlope = 0;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = M_T_KF;
  vMem = 0.046882;
  expectedOffset = 9.4911;
  expectedSlope = 0;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

TEST_F(SoftLUT_test, AfterLast) {
  // First curve
  curve = M_F_NA;
  vMem = 0.019918;
  expectedOffset = 0.99935;
  expectedSlope = 0;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = M_T_KF;
  vMem = 0.0469;
  expectedOffset = 9.4911;
  expectedSlope = 0;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

#endif //INCLUDE_LUT_SUPPORT