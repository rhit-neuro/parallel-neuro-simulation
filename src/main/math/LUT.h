#if INCLUDE_LUT_SUPPORT
#ifndef PARALLEL_NEURON_SIMULATION_LUT_H
#define PARALLEL_NEURON_SIMULATION_LUT_H

#include <vector>

namespace lut {
  enum CurveSelect {
    M_F_NA = 0,
    M_T_NA,
    H_F_NA,
    H_T_NA,
    M_F_P,
    M_T_P,
    M_F_CAF,
    M_T_CAF,
    H_F_CAF,
    H_T_CAF,
    M_F_CAS,
    M_T_CAS,
    H_F_CAS,
    H_T_CAS,
    M_F_H,
    M_T_H,
    M_F_K1,
    M_T_K1,
    H_F_K1,
    H_T_K1,
    M_F_K2,
    M_T_K2,
    M_F_KA,
    M_T_KA,
    H_F_KA,
    H_T_KA,
    M_F_KF,
    M_T_KF,
    NUM_CURVES
  };

  class LUT {
    public:
      virtual double interpolate(double vMem, CurveSelect curveSelect) = 0;
  };

  class SoftLUT : public lut::LUT {
    public:
      SoftLUT() {
        initialize();
      }
      double interpolate(double vMem, CurveSelect curveSelect);

    private:
      void initialize();
      std::vector<float> vMemss[NUM_CURVES];
      std::vector<float> slopess[NUM_CURVES];
      std::vector<float> offsetss[NUM_CURVES];
  };

#if RISCV
  class HardLUTROM : public lut::LUT {
    public:
      double interpolate(double vMem, CurveSelect curveSelect);
  };
#endif //RISCV
}

extern lut::LUT *lutSingleton;

#endif //PARALLEL_NEURON_SIMULATION_LUT_H
#endif //INCLUDE_LUT_SUPPORT