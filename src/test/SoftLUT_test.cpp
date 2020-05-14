#if INCLUDE_LUT_SUPPORT
#include "gmock/gmock.h"
#include "../main/math/LUT.h"

using namespace lut;

class SoftLUT_test : public ::testing::Test {
  protected:
    // Tests pass as long as the absolute error between acutal
    // and expected is less than this number
    const float maxError = 0.000001;
    SoftLUT lutut = SoftLUT("3Curve32Point.csv");
    float expected, actual, vMem;
    float expectedSlope, expectedOffset, expectedA, expectedB;
    CurveSelect curve;
    float calcActual() {
      return lutut.interpolate(vMem, curve);
    }
    float calcExpected() {
      return expectedSlope * (expectedA * vMem + expectedB) + expectedOffset;
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
  curve = Mk2_FINF;
  vMem = -7.4;
  expectedA = 83;
  expectedB = 1.66;
  expectedOffset = 0.0136;
  expectedSlope = 0.0018;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = FHINF;
  vMem = -8.0;
  expectedA = 180;
  expectedB = 8.46;
  expectedOffset = 0.9852;
  expectedSlope = -0.0018;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

TEST_F(SoftLUT_test, ExactlyFirst) {
  // First curve
  curve = Mk2_FINF;
  vMem = -7.3364;
  expectedA = 83;
  expectedB = 1.66;
  expectedOffset = 0.0136;
  expectedSlope = 0.0018;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = FHINF;
  vMem = -7.9991;
  expectedA = 180;
  expectedB = 8.46;
  expectedOffset = 0.9852;
  expectedSlope = -0.0018;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

TEST_F(SoftLUT_test, Middle) {
  // First curve
  curve = Mk2_FINF;
  vMem = -0.0251807; // -0.43
  expectedA = 83;
  expectedB = 1.66;
  expectedOffset = 0.5;
  expectedSlope = 0.2461;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = FHINF;
  vMem = -0.0542222; // -1.3
  expectedA = 180;
  expectedB = 8.46;
  expectedOffset = 0.3065;
  expectedSlope = -0.2531;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

TEST_F(SoftLUT_test, ExactlyMiddle) {
  // First curve
  curve = Mk2_FINF;
  vMem = -0.025259;
  expectedA = 83;
  expectedB = 1.66;
  expectedOffset = 0.5;
  expectedSlope = 0.2461;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = FHINF;
  vMem = -0.0547012;
  expectedA = 180;
  expectedB = 8.46;
  expectedOffset = 0.3065;
  expectedSlope = -0.2531;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

TEST_F(SoftLUT_test, ExactlyLast) {
  // First curve
  curve = Mk2_FINF;
  vMem = 7.3375;
  expectedA = 83;
  expectedB = 1.66;
  expectedOffset = 0.9864;
  expectedSlope = 0.0018;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = FHINF;
  vMem = 2.6689;
  expectedA = 180;
  expectedB = 8.46;
  expectedOffset = 0.0125;
  expectedSlope = -0.0045;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

TEST_F(SoftLUT_test, AfterLast) {
  // First curve
  curve = Mk2_FINF;
  vMem = 7.5;
  expectedA = 83;
  expectedB = 1.66;
  expectedOffset = 0.9864;
  expectedSlope = 0.0018;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());

  // Last curve
  curve = FHINF;
  vMem = 2.8;
  expectedA = 180;
  expectedB = 8.46;
  expectedOffset = 0.0125;
  expectedSlope = -0.0045;

  actual = calcActual();
  expected = calcExpected();
  EXPECT_TRUE(closeEnough());
}

#endif //INCLUDE_LUT_SUPPORT
