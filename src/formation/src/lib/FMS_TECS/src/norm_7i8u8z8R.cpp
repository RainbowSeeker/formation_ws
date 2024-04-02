//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: norm_7i8u8z8R.cpp
//
// Code generated for Simulink model 'Formation_FMS'.
//
// Model version                  : 1.159
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Tue Apr  2 21:16:26 2024
//
#include "rtwtypes.h"
#include "norm_7i8u8z8R.h"
#include <cmath>

// Function for MATLAB Function: '<S83>/Dubins Closest Point'
real32_T norm_7i8u8z8R(const real32_T x[2])
{
  real32_T absxk;
  real32_T scale;
  real32_T t;
  real32_T y;
  scale = 1.29246971E-26F;
  absxk = std::abs(x[0]);
  if (absxk > 1.29246971E-26F) {
    y = 1.0F;
    scale = absxk;
  } else {
    t = absxk / 1.29246971E-26F;
    y = t * t;
  }

  absxk = std::abs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * std::sqrt(y);
}

//
// File trailer for generated code.
//
// [EOF]
//
