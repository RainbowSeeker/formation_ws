//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: mod_ThuC9Kor.cpp
//
// Code generated for Simulink model 'Formation_FMS'.
//
// Model version                  : 1.159
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Tue Apr  2 21:16:26 2024
//
#include "rtwtypes.h"
#include "mod_ThuC9Kor.h"
#include <cmath>

extern "C"
{

#include "rt_nonfinite.h"

}

// Function for MATLAB Function: '<S83>/Dubins Closest Point'
real32_T mod_ThuC9Kor(real32_T x)
{
  real32_T r;
  if (std::isnan(x)) {
    r = (rtNaNF);
  } else if (std::isinf(x)) {
    r = (rtNaNF);
  } else if (x == 0.0F) {
    r = 0.0F;
  } else {
    boolean_T rEQ0;
    r = std::fmod(x, 6.28318548F);
    rEQ0 = (r == 0.0F);
    if (!rEQ0) {
      real32_T q;
      q = std::abs(x / 6.28318548F);
      rEQ0 = !(std::abs(q - std::floor(q + 0.5F)) > 1.1920929E-7F * q);
    }

    if (rEQ0) {
      r = 0.0F;
    } else if (x < 0.0F) {
      r += 6.28318548F;
    }
  }

  return r;
}

//
// File trailer for generated code.
//
// [EOF]
//
