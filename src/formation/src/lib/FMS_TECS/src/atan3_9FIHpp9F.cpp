//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: atan3_9FIHpp9F.cpp
//
// Code generated for Simulink model 'Formation_FMS'.
//
// Model version                  : 1.127
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Fri Mar 29 21:28:37 2024
//
#include "rtwtypes.h"
#include "atan3_9FIHpp9F.h"
#include <cmath>

// Function for MATLAB Function: '<S82>/MATLAB Function'
real_T atan3_9FIHpp9F(real_T x, real_T y, real_T x0, real_T b_y0)
{
  real_T deltax;
  real_T deltay;
  real_T result;
  deltax = x - x0;
  deltay = y - b_y0;
  if ((deltax > 0.0) && (deltay > 0.0)) {
    result = std::atan(deltay / deltax);
  } else if ((deltax > 0.0) && (deltay < 0.0)) {
    result = std::atan(deltay / deltax) + 6.2831853071795862;
  } else if (deltax < 0.0) {
    result = std::atan(deltay / deltax) + 3.1415926535897931;
  } else if (deltax == 0.0) {
    if (deltay > 0.0) {
      result = 1.5707963267948966;
    } else {
      result = 4.71238898038469;
    }
  } else if (deltax > 0.0) {
    result = 0.0;
  } else {
    result = 3.1415926535897931;
  }

  return result;
}

//
// File trailer for generated code.
//
// [EOF]
//
