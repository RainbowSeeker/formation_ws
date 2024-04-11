//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Formation_FMS.cpp
//
// Code generated for Simulink model 'Formation_FMS'.
//
// Model version                  : 1.179
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Thu Apr 11 20:35:49 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "Formation_FMS.h"
#include "rtwtypes.h"
#include <cmath>
#include <cstring>
#include "norm_7i8u8z8R.h"
#include <xmmintrin.h>
#include "rt_atan2f_snf.h"
#include "mod_ThuC9Kor.h"
#include "zero_crossing_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

// Named constants for Chart: '<Root>/FMS State Machine'
const uint8_T Formation_FMS_IN_Follower{ 1U };

const uint8_T Formation_FMS_IN_FormAssemble{ 1U };

const uint8_T Formation_FMS_IN_FormDisband{ 2U };

const uint8_T Formation_FMS_IN_FormMission{ 3U };

const uint8_T Formation_FMS_IN_Formation{ 1U };

const uint8_T Formation_FMS_IN_Forward{ 2U };

const uint8_T Formation_FMS_IN_InvalidMode{ 4U };

const uint8_T Formation_FMS_IN_NextWP{ 1U };

const uint8_T Formation_FMS_IN_NextWP_d{ 3U };

const uint8_T Formation_FMS_IN_Standby{ 2U };

const uint8_T Formation_FMS_IN_WaitForUpdate{ 2U };

const uint8_T Formation_FMS_IN_Waypoint{ 3U };

const uint8_T Formation_FMS_IN_Waypoint_g{ 4U };

const uint8_T Formation_FM_IN_NO_ACTIVE_CHILD{ 0U };

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         (*((rtm)->errorStatus))
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    (*((rtm)->errorStatus) = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  (rtm)->errorStatus
#endif

#ifndef rtmSetErrorStatusPointer
#define rtmSetErrorStatusPointer(rtm, val) ((rtm)->errorStatus = (val))
#endif

//
// Output and update for atomic system:
//    '<S55>/signNoZero'
//    '<S57>/signNoZero'
//
void Formation_FMS::Formation_FMS_signNoZero(real32_T rtu_u, real32_T *rty_y)
{
  *rty_y = static_cast<real32_T>((rtu_u >= 0.0F) - (rtu_u < 0.0F));
}

//
// Output and update for atomic system:
//    '<S119>/NearbyRefWP'
//    '<S25>/NearbyRefWP'
//
void Formation_FMS::Formation_FMS_NearbyRefWP(const real32_T rtu_P2[2], const
  real32_T rtu_P3[2], real32_T rtu_L1, real32_T rty_P[2], real32_T *rty_d)
{
  real32_T dis;
  real32_T y_idx_0;
  dis = rtu_P2[0] - rtu_P3[0];
  y_idx_0 = dis * dis;
  dis = rtu_P2[1] - rtu_P3[1];
  dis = std::sqrt(dis * dis + y_idx_0);
  if (dis <= rtu_L1) {
    *rty_d = dis;
    rty_P[0] = rtu_P2[0];
    rty_P[1] = rtu_P2[1];
  } else {
    *rty_d = -1.0F;
    rty_P[0] = 0.0F;
    rty_P[1] = 0.0F;
  }
}

//
// Output and update for atomic system:
//    '<S119>/OutRegionRegWP'
//    '<S25>/OutRegionRegWP'
//
void Formation_FMS::Formation_FMS_OutRegionRegWP(const real32_T rtu_P1[2], const
  real32_T rtu_P2[2], const real32_T rtu_P3[2], real32_T rty_P[2])
{
  real32_T u;
  real32_T y_idx_0;
  rty_P[0] = rtu_P2[0] - rtu_P1[0];
  u = (rtu_P3[0] - rtu_P1[0]) * rty_P[0];
  y_idx_0 = rty_P[0] * rty_P[0];
  rty_P[1] = rtu_P2[1] - rtu_P1[1];
  u = ((rtu_P3[1] - rtu_P1[1]) * rty_P[1] + u) / (rty_P[1] * rty_P[1] + y_idx_0);
  if (u <= 0.0F) {
    rty_P[0] = rtu_P1[0];
    rty_P[1] = rtu_P1[1];
  } else if (u >= 1.0F) {
    rty_P[0] = rtu_P2[0];
    rty_P[1] = rtu_P2[1];
  } else {
    real32_T a;
    a = (u * rty_P[0] + rtu_P1[0]) - rtu_P3[0];
    y_idx_0 = a * a;
    a = (u * rty_P[1] + rtu_P1[1]) - rtu_P3[1];
    u += std::sqrt(a * a + y_idx_0) * 0.5774F / std::sqrt(rty_P[0] * rty_P[0] +
      rty_P[1] * rty_P[1]);
    if (u > 1.0F) {
      u = 1.0F;
    }

    rty_P[0] = u * rty_P[0] + rtu_P1[0];
    rty_P[1] = u * rty_P[1] + rtu_P1[1];
  }
}

//
// Output and update for atomic system:
//    '<S119>/SearchL1RefWP'
//    '<S25>/SearchL1RefWP'
//
void Formation_FMS::Formation_FMS_SearchL1RefWP(const real32_T rtu_P1[2], const
  real32_T rtu_P2[2], const real32_T rtu_P3[2], real32_T rtu_L1, real32_T rty_P
  [2], real32_T *rty_u)
{
  real32_T A;
  real32_T A_tmp;
  real32_T B;
  real32_T D;
  real32_T a;
  real32_T a_tmp;
  boolean_T guard1;
  a_tmp = rtu_P2[0] - rtu_P1[0];
  A_tmp = rtu_P2[1] - rtu_P1[1];
  A = a_tmp * a_tmp + A_tmp * A_tmp;
  B = ((rtu_P1[0] - rtu_P3[0]) * a_tmp + (rtu_P1[1] - rtu_P3[1]) * A_tmp) * 2.0F;
  D = B * B - (((((rtu_P3[0] * rtu_P3[0] + rtu_P3[1] * rtu_P3[1]) + rtu_P1[0] *
                  rtu_P1[0]) + rtu_P1[1] * rtu_P1[1]) - (rtu_P3[0] * rtu_P1[0] +
    rtu_P3[1] * rtu_P1[1]) * 2.0F) - rtu_L1 * rtu_L1) * (4.0F * A);
  a = -1.0F;
  rty_P[0] = 0.0F;
  rty_P[1] = 0.0F;
  guard1 = false;
  if (D > 0.0F) {
    real32_T u1_tmp;
    u1_tmp = std::sqrt(D);
    D = (-B + u1_tmp) / (2.0F * A);
    A = (-B - u1_tmp) / (2.0F * A);
    if ((D >= 0.0F) && (D <= 1.0F) && (A >= 0.0F) && (A <= 1.0F)) {
      if (D > A) {
        a = D;
      } else {
        a = A;
      }

      guard1 = true;
    } else if ((D >= 0.0F) && (D <= 1.0F)) {
      a = D;
      guard1 = true;
    } else if ((A >= 0.0F) && (A <= 1.0F)) {
      a = A;
      guard1 = true;
    }
  } else if (D == 0.0F) {
    D = -B / (2.0F * A);
    if ((D >= 0.0F) && (D <= 1.0F)) {
      a = D;
      guard1 = true;
    }
  }

  if (guard1) {
    rty_P[0] = a_tmp * a + rtu_P1[0];
    rty_P[1] = A_tmp * a + rtu_P1[1];
  }

  *rty_u = a;
}

// Function for Chart: '<Root>/FMS State Machine'
void Formation_FMS::Formation_exit_internal_Vehicle(void)
{
  if (Formation_FMS_DW.is_Vehicle == Formation_FMS_IN_Formation) {
    if (Formation_FMS_DW.is_Formation == Formation_FMS_IN_FormAssemble) {
      Formation_FMS_DW.is_FormAssemble = Formation_FM_IN_NO_ACTIVE_CHILD;
      Formation_FMS_DW.is_Formation = Formation_FM_IN_NO_ACTIVE_CHILD;
    } else {
      Formation_FMS_DW.is_FormMission = Formation_FM_IN_NO_ACTIVE_CHILD;
      Formation_FMS_DW.is_Formation = Formation_FM_IN_NO_ACTIVE_CHILD;
    }

    Formation_FMS_DW.is_Vehicle = Formation_FM_IN_NO_ACTIVE_CHILD;
  } else {
    Formation_FMS_DW.is_Vehicle = Formation_FM_IN_NO_ACTIVE_CHILD;
  }
}

// Function for MATLAB Function: '<S152>/MATLAB Function'
real_T Formation_FMS::Formation_FMS_atan3_9FIHpp9F(real_T x, real_T y, real_T x0,
  real_T b_y0)
{
  real_T result;
  Formation_FMS_DW.deltax = x - x0;
  Formation_FMS_DW.deltay = y - b_y0;
  if ((Formation_FMS_DW.deltax > 0.0) && (Formation_FMS_DW.deltay > 0.0)) {
    result = std::atan(Formation_FMS_DW.deltay / Formation_FMS_DW.deltax);
  } else if ((Formation_FMS_DW.deltax > 0.0) && (Formation_FMS_DW.deltay < 0.0))
  {
    result = std::atan(Formation_FMS_DW.deltay / Formation_FMS_DW.deltax) +
      6.2831853071795862;
  } else if (Formation_FMS_DW.deltax < 0.0) {
    result = std::atan(Formation_FMS_DW.deltay / Formation_FMS_DW.deltax) +
      3.1415926535897931;
  } else if (Formation_FMS_DW.deltax == 0.0) {
    if (Formation_FMS_DW.deltay > 0.0) {
      result = 1.5707963267948966;
    } else {
      result = 4.71238898038469;
    }
  } else if (Formation_FMS_DW.deltax > 0.0) {
    result = 0.0;
  } else {
    result = 3.1415926535897931;
  }

  return result;
}

// Function for MATLAB Function: '<S152>/MATLAB Function'
void Formation_FMS::Formation_FMS_Dubins(const captured_var_Formation_FMS_T
  *PhiMaximum, const captured_var_Formation_FMS_T *rad2deg, real_T xs, real_T ys,
  real_T psi_s, real_T xf, real_T yf, real_T psi_f, real_T v, real_T xts[4],
  real_T yts[4], real_T xtf[4], real_T ytf[4], real_T cs[4], real_T cf[4],
  real_T lt[4], real_T l[4], real_T pos[4], real_T pof[4], real_T *r, real_T
  m_data[], int32_T *m_size, real_T n_data[], int32_T *n_size)
{
  int32_T idx;
  int32_T ii;
  int32_T jj;
  boolean_T exitg1;
  *r = v * v / 9.81 / std::tan(PhiMaximum->contents / rad2deg->contents);
  Formation_FMS_DW.l_best = psi_s / rad2deg->contents;
  Formation_FMS_DW.pos_tmp = std::sin(Formation_FMS_DW.l_best) * *r;
  pos[0] = Formation_FMS_DW.pos_tmp + xs;
  Formation_FMS_DW.l_best = std::cos(Formation_FMS_DW.l_best) * *r;
  pos[2] = ys - Formation_FMS_DW.l_best;
  pos[1] = xs - Formation_FMS_DW.pos_tmp;
  pos[3] = Formation_FMS_DW.l_best + ys;
  Formation_FMS_DW.l_best = psi_f / rad2deg->contents;
  Formation_FMS_DW.pos_tmp = std::sin(Formation_FMS_DW.l_best) * *r;
  pof[0] = Formation_FMS_DW.pos_tmp + xf;
  Formation_FMS_DW.l_best = std::cos(Formation_FMS_DW.l_best) * *r;
  pof[2] = yf - Formation_FMS_DW.l_best;
  pof[1] = xf - Formation_FMS_DW.pos_tmp;
  pof[3] = Formation_FMS_DW.l_best + yf;
  Formation_FMS_DW.pos_tmp = Formation_FMS_atan3_9FIHpp9F(pof[0], pof[2], pos[0],
    pos[2]);
  Formation_FMS_DW.xts_tmp = *r * std::sin(Formation_FMS_DW.pos_tmp);
  Formation_FMS_DW.l_best = pos[0] - Formation_FMS_DW.xts_tmp;
  Formation_FMS_DW.yts_tmp = *r * std::cos(Formation_FMS_DW.pos_tmp);
  Formation_FMS_DW.pos_tmp = Formation_FMS_DW.yts_tmp + pos[2];
  Formation_FMS_DW.xts_tmp = pof[0] - Formation_FMS_DW.xts_tmp;
  Formation_FMS_DW.yts_tmp += pof[2];
  Formation_FMS_DW.cs_tmp = xs - Formation_FMS_DW.l_best;
  Formation_FMS_DW.cs_tmp_m = ys - Formation_FMS_DW.pos_tmp;
  Formation_FMS_DW.cs_tmp = std::asin(std::sqrt(Formation_FMS_DW.cs_tmp *
    Formation_FMS_DW.cs_tmp + Formation_FMS_DW.cs_tmp_m *
    Formation_FMS_DW.cs_tmp_m) / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_DW.cs_tmp_m = xf - Formation_FMS_DW.xts_tmp;
  Formation_FMS_DW.cf_tmp = yf - Formation_FMS_DW.yts_tmp;
  Formation_FMS_DW.cs_tmp_m = std::asin(std::sqrt(Formation_FMS_DW.cs_tmp_m *
    Formation_FMS_DW.cs_tmp_m + Formation_FMS_DW.cf_tmp *
    Formation_FMS_DW.cf_tmp) / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_DW.cf_tmp = Formation_FMS_DW.xts_tmp - Formation_FMS_DW.l_best;
  Formation_FMS_DW.lt_tmp = Formation_FMS_DW.yts_tmp - Formation_FMS_DW.pos_tmp;
  Formation_FMS_DW.cf_tmp = std::sqrt(Formation_FMS_DW.cf_tmp *
    Formation_FMS_DW.cf_tmp + Formation_FMS_DW.lt_tmp * Formation_FMS_DW.lt_tmp);
  l[0] = (Formation_FMS_DW.cs_tmp + Formation_FMS_DW.cs_tmp_m) +
    Formation_FMS_DW.cf_tmp;
  xts[0] = Formation_FMS_DW.l_best;
  yts[0] = Formation_FMS_DW.pos_tmp;
  xtf[0] = Formation_FMS_DW.xts_tmp;
  ytf[0] = Formation_FMS_DW.yts_tmp;
  cs[0] = Formation_FMS_DW.cs_tmp;
  cf[0] = Formation_FMS_DW.cs_tmp_m;
  lt[0] = Formation_FMS_DW.cf_tmp;
  Formation_FMS_DW.l_best = pof[3] - pos[2];
  Formation_FMS_DW.pos_tmp = pof[1] - pos[0];
  Formation_FMS_DW.pos_tmp = std::acos(*r * 2.0 / std::sqrt
    (Formation_FMS_DW.l_best * Formation_FMS_DW.l_best +
     Formation_FMS_DW.pos_tmp * Formation_FMS_DW.pos_tmp)) +
    Formation_FMS_atan3_9FIHpp9F(pof[1], pof[3], pos[0], pos[2]);
  Formation_FMS_DW.xts_tmp = *r * std::cos(Formation_FMS_DW.pos_tmp);
  Formation_FMS_DW.l_best = Formation_FMS_DW.xts_tmp + pos[0];
  Formation_FMS_DW.yts_tmp = *r * std::sin(Formation_FMS_DW.pos_tmp);
  Formation_FMS_DW.pos_tmp = Formation_FMS_DW.yts_tmp + pos[2];
  Formation_FMS_DW.xts_tmp = pof[1] - Formation_FMS_DW.xts_tmp;
  Formation_FMS_DW.yts_tmp = pof[3] - Formation_FMS_DW.yts_tmp;
  Formation_FMS_DW.cs_tmp = xs - Formation_FMS_DW.l_best;
  Formation_FMS_DW.cs_tmp_m = ys - Formation_FMS_DW.pos_tmp;
  Formation_FMS_DW.cs_tmp = std::asin(std::sqrt(Formation_FMS_DW.cs_tmp *
    Formation_FMS_DW.cs_tmp + Formation_FMS_DW.cs_tmp_m *
    Formation_FMS_DW.cs_tmp_m) / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_DW.cs_tmp_m = xf - Formation_FMS_DW.xts_tmp;
  Formation_FMS_DW.cf_tmp = yf - Formation_FMS_DW.yts_tmp;
  Formation_FMS_DW.cs_tmp_m = std::asin(std::sqrt(Formation_FMS_DW.cs_tmp_m *
    Formation_FMS_DW.cs_tmp_m + Formation_FMS_DW.cf_tmp *
    Formation_FMS_DW.cf_tmp) / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_DW.cf_tmp = Formation_FMS_DW.xts_tmp - Formation_FMS_DW.l_best;
  Formation_FMS_DW.lt_tmp = Formation_FMS_DW.yts_tmp - Formation_FMS_DW.pos_tmp;
  Formation_FMS_DW.cf_tmp = std::sqrt(Formation_FMS_DW.cf_tmp *
    Formation_FMS_DW.cf_tmp + Formation_FMS_DW.lt_tmp * Formation_FMS_DW.lt_tmp);
  l[2] = (Formation_FMS_DW.cs_tmp + Formation_FMS_DW.cs_tmp_m) +
    Formation_FMS_DW.cf_tmp;
  xts[2] = Formation_FMS_DW.l_best;
  yts[2] = Formation_FMS_DW.pos_tmp;
  xtf[2] = Formation_FMS_DW.xts_tmp;
  ytf[2] = Formation_FMS_DW.yts_tmp;
  cs[2] = Formation_FMS_DW.cs_tmp;
  cf[2] = Formation_FMS_DW.cs_tmp_m;
  lt[2] = Formation_FMS_DW.cf_tmp;
  Formation_FMS_DW.l_best = pof[2] - pos[3];
  Formation_FMS_DW.pos_tmp = pof[0] - pos[1];
  Formation_FMS_DW.pos_tmp = Formation_FMS_atan3_9FIHpp9F(pof[0], pof[2], pos[1],
    pos[3]) - std::acos(*r * 2.0 / std::sqrt(Formation_FMS_DW.l_best *
    Formation_FMS_DW.l_best + Formation_FMS_DW.pos_tmp *
    Formation_FMS_DW.pos_tmp));
  Formation_FMS_DW.xts_tmp = *r * std::cos(Formation_FMS_DW.pos_tmp);
  Formation_FMS_DW.l_best = Formation_FMS_DW.xts_tmp + pos[1];
  Formation_FMS_DW.yts_tmp = *r * std::sin(Formation_FMS_DW.pos_tmp);
  Formation_FMS_DW.pos_tmp = Formation_FMS_DW.yts_tmp + pos[3];
  Formation_FMS_DW.xts_tmp = pof[0] - Formation_FMS_DW.xts_tmp;
  Formation_FMS_DW.yts_tmp = pof[2] - Formation_FMS_DW.yts_tmp;
  Formation_FMS_DW.cs_tmp = xs - Formation_FMS_DW.l_best;
  Formation_FMS_DW.cs_tmp_m = ys - Formation_FMS_DW.pos_tmp;
  Formation_FMS_DW.cs_tmp = std::asin(std::sqrt(Formation_FMS_DW.cs_tmp *
    Formation_FMS_DW.cs_tmp + Formation_FMS_DW.cs_tmp_m *
    Formation_FMS_DW.cs_tmp_m) / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_DW.cs_tmp_m = xf - Formation_FMS_DW.xts_tmp;
  Formation_FMS_DW.cf_tmp = yf - Formation_FMS_DW.yts_tmp;
  Formation_FMS_DW.cs_tmp_m = std::asin(std::sqrt(Formation_FMS_DW.cs_tmp_m *
    Formation_FMS_DW.cs_tmp_m + Formation_FMS_DW.cf_tmp *
    Formation_FMS_DW.cf_tmp) / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_DW.cf_tmp = Formation_FMS_DW.xts_tmp - Formation_FMS_DW.l_best;
  Formation_FMS_DW.lt_tmp = Formation_FMS_DW.yts_tmp - Formation_FMS_DW.pos_tmp;
  Formation_FMS_DW.cf_tmp = std::sqrt(Formation_FMS_DW.cf_tmp *
    Formation_FMS_DW.cf_tmp + Formation_FMS_DW.lt_tmp * Formation_FMS_DW.lt_tmp);
  l[1] = (Formation_FMS_DW.cs_tmp + Formation_FMS_DW.cs_tmp_m) +
    Formation_FMS_DW.cf_tmp;
  xts[1] = Formation_FMS_DW.l_best;
  yts[1] = Formation_FMS_DW.pos_tmp;
  xtf[1] = Formation_FMS_DW.xts_tmp;
  ytf[1] = Formation_FMS_DW.yts_tmp;
  cs[1] = Formation_FMS_DW.cs_tmp;
  cf[1] = Formation_FMS_DW.cs_tmp_m;
  lt[1] = Formation_FMS_DW.cf_tmp;
  Formation_FMS_DW.pos_tmp = Formation_FMS_atan3_9FIHpp9F(pof[1], pof[3], pos[1],
    pos[3]);
  Formation_FMS_DW.xts_tmp = *r * std::sin(Formation_FMS_DW.pos_tmp);
  Formation_FMS_DW.l_best = Formation_FMS_DW.xts_tmp + pos[1];
  Formation_FMS_DW.yts_tmp = *r * std::cos(Formation_FMS_DW.pos_tmp);
  Formation_FMS_DW.pos_tmp = pos[3] - Formation_FMS_DW.yts_tmp;
  Formation_FMS_DW.xts_tmp += pof[1];
  Formation_FMS_DW.yts_tmp = pof[3] - Formation_FMS_DW.yts_tmp;
  Formation_FMS_DW.cs_tmp = xs - Formation_FMS_DW.l_best;
  Formation_FMS_DW.cs_tmp_m = ys - Formation_FMS_DW.pos_tmp;
  Formation_FMS_DW.cs_tmp = std::asin(std::sqrt(Formation_FMS_DW.cs_tmp *
    Formation_FMS_DW.cs_tmp + Formation_FMS_DW.cs_tmp_m *
    Formation_FMS_DW.cs_tmp_m) / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_DW.cs_tmp_m = xf - Formation_FMS_DW.xts_tmp;
  Formation_FMS_DW.cf_tmp = yf - Formation_FMS_DW.yts_tmp;
  Formation_FMS_DW.cs_tmp_m = std::asin(std::sqrt(Formation_FMS_DW.cs_tmp_m *
    Formation_FMS_DW.cs_tmp_m + Formation_FMS_DW.cf_tmp *
    Formation_FMS_DW.cf_tmp) / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_DW.cf_tmp = Formation_FMS_DW.xts_tmp - Formation_FMS_DW.l_best;
  Formation_FMS_DW.lt_tmp = Formation_FMS_DW.yts_tmp - Formation_FMS_DW.pos_tmp;
  Formation_FMS_DW.cf_tmp = std::sqrt(Formation_FMS_DW.cf_tmp *
    Formation_FMS_DW.cf_tmp + Formation_FMS_DW.lt_tmp * Formation_FMS_DW.lt_tmp);
  l[3] = (Formation_FMS_DW.cs_tmp + Formation_FMS_DW.cs_tmp_m) +
    Formation_FMS_DW.cf_tmp;
  xts[3] = Formation_FMS_DW.l_best;
  yts[3] = Formation_FMS_DW.pos_tmp;
  xtf[3] = Formation_FMS_DW.xts_tmp;
  ytf[3] = Formation_FMS_DW.yts_tmp;
  cs[3] = Formation_FMS_DW.cs_tmp;
  cf[3] = Formation_FMS_DW.cs_tmp_m;
  lt[3] = Formation_FMS_DW.cf_tmp;
  Formation_FMS_DW.l_best = (rtInf);
  if ((l[0] >= 0.0) && (l[0] < (rtInf))) {
    Formation_FMS_DW.l_best = l[0];
  }

  if ((l[1] >= 0.0) && (l[1] < Formation_FMS_DW.l_best)) {
    Formation_FMS_DW.l_best = l[1];
  }

  if ((l[2] >= 0.0) && (l[2] < Formation_FMS_DW.l_best)) {
    Formation_FMS_DW.l_best = l[2];
  }

  if ((l[3] >= 0.0) && (l[3] < Formation_FMS_DW.l_best)) {
    Formation_FMS_DW.l_best = l[3];
  }

  idx = -1;
  ii = 1;
  jj = 1;
  exitg1 = false;
  while ((!exitg1) && (jj <= 2)) {
    boolean_T guard1;
    guard1 = false;
    if (l[(((jj - 1) << 1) + ii) - 1] == Formation_FMS_DW.l_best) {
      idx++;
      Formation_FMS_DW.i_data[idx] = ii;
      Formation_FMS_DW.j_data[idx] = static_cast<int8_T>(jj);
      if (idx + 1 >= 4) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ii++;
      if (ii > 2) {
        ii = 1;
        jj++;
      }
    }
  }

  if (idx + 1 < 1) {
    jj = -1;
  } else {
    jj = idx;
  }

  *m_size = jj + 1;
  for (ii = 0; ii <= jj; ii++) {
    m_data[ii] = Formation_FMS_DW.i_data[ii];
  }

  if (idx + 1 < 1) {
    idx = -1;
  }

  *n_size = idx + 1;
  for (ii = 0; ii <= idx; ii++) {
    n_data[ii] = Formation_FMS_DW.j_data[ii];
  }

  if ((jj + 1 != 1) || (idx + 1 != 1)) {
    idx = static_cast<int32_T>(m_data[0]);
    *m_size = 1;
    m_data[0] = idx;
    idx = static_cast<int32_T>(n_data[0]);
    *n_size = 1;
    n_data[0] = idx;
  }
}

// Function for Chart: '<Root>/FMS State Machine'
void Formation_FMS::Format_enter_internal_Formation(const INS_Out_Bus
  *BusConversion_InsertedFor_FMS_c, const Formation_Cross_Bus
  *BusConversion_InsertedFor_FMS_p, const PilotMode *Switch)
{
  static const real_T d[8]{ 1000.0, 100.0, 10.0, 1.0, 0.1, 0.01, 0.001, 0.0001 };

  if (*Switch == PilotMode::FormAssemble) {
    Formation_FMS_DW.is_Formation = Formation_FMS_IN_FormAssemble;
    Formation_FMS_DW.Cmd_In.sp_waypoint[0] =
      BusConversion_InsertedFor_FMS_c->x_R;
    Formation_FMS_DW.Cmd_In.sp_waypoint[1] =
      BusConversion_InsertedFor_FMS_c->y_R;
    Formation_FMS_DW.Cmd_In.sp_waypoint[2] =
      BusConversion_InsertedFor_FMS_c->h_R;
    if (FORMATION_PARAM.UAV_ID == 1U) {
      // Outputs for Function Call SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPath' 
      // MATLAB Function: '<S152>/MATLAB Function'
      Formation_FMS_DW.PhiMaximum.contents = 40.0;
      Formation_FMS_DW.rad2deg.contents = 57.295779513082323;
      Formation_FMS_DW.obj.xs = 0.0;
      Formation_FMS_DW.obj.ys = 0.0;
      Formation_FMS_DW.obj.psi_s = 0.0;
      Formation_FMS_DW.obj.xf = 0.0;
      Formation_FMS_DW.obj.yf = 0.0;
      Formation_FMS_DW.obj.psi_f = 0.0;
      Formation_FMS_DW.obj.v = 0.0;
      Formation_FMS_DW.obj.r = 0.0;
      Formation_FMS_DW.obj.pos[0] = 0.0;
      Formation_FMS_DW.obj.pof[0] = 0.0;
      Formation_FMS_DW.obj.xts[0] = 0.0;
      Formation_FMS_DW.obj.yts[0] = 0.0;
      Formation_FMS_DW.obj.xtf[0] = 0.0;
      Formation_FMS_DW.obj.ytf[0] = 0.0;
      Formation_FMS_DW.obj.cs[0] = 0.0;
      Formation_FMS_DW.obj.cf[0] = 0.0;
      Formation_FMS_DW.obj.lt[0] = 0.0;
      Formation_FMS_DW.obj.l[0] = 0.0;
      Formation_FMS_DW.obj.pos[1] = 0.0;
      Formation_FMS_DW.obj.pof[1] = 0.0;
      Formation_FMS_DW.obj.xts[1] = 0.0;
      Formation_FMS_DW.obj.yts[1] = 0.0;
      Formation_FMS_DW.obj.xtf[1] = 0.0;
      Formation_FMS_DW.obj.ytf[1] = 0.0;
      Formation_FMS_DW.obj.cs[1] = 0.0;
      Formation_FMS_DW.obj.cf[1] = 0.0;
      Formation_FMS_DW.obj.lt[1] = 0.0;
      Formation_FMS_DW.obj.l[1] = 0.0;
      Formation_FMS_DW.obj.pos[2] = 0.0;
      Formation_FMS_DW.obj.pof[2] = 0.0;
      Formation_FMS_DW.obj.xts[2] = 0.0;
      Formation_FMS_DW.obj.yts[2] = 0.0;
      Formation_FMS_DW.obj.xtf[2] = 0.0;
      Formation_FMS_DW.obj.ytf[2] = 0.0;
      Formation_FMS_DW.obj.cs[2] = 0.0;
      Formation_FMS_DW.obj.cf[2] = 0.0;
      Formation_FMS_DW.obj.lt[2] = 0.0;
      Formation_FMS_DW.obj.l[2] = 0.0;
      Formation_FMS_DW.obj.pos[3] = 0.0;
      Formation_FMS_DW.obj.pof[3] = 0.0;
      Formation_FMS_DW.obj.xts[3] = 0.0;
      Formation_FMS_DW.obj.yts[3] = 0.0;
      Formation_FMS_DW.obj.xtf[3] = 0.0;
      Formation_FMS_DW.obj.ytf[3] = 0.0;
      Formation_FMS_DW.obj.cs[3] = 0.0;
      Formation_FMS_DW.obj.cf[3] = 0.0;
      Formation_FMS_DW.obj.lt[3] = 0.0;
      Formation_FMS_DW.obj.l[3] = 0.0;
      Formation_FMS_DW.obj.index_dubins[0] = 0.0;
      Formation_FMS_DW.obj.index_dubins[1] = 0.0;
      Formation_FMS_DW.obj.l_ad = 0.0;
      Formation_FMS_DW.obj.precision_flag = 0.0;
      Formation_FMS_DW.obj.xm = 0.0;
      Formation_FMS_DW.obj.ym = 0.0;
      Formation_FMS_DW.object[0] = Formation_FMS_DW.obj;
      Formation_FMS_DW.object[1] = Formation_FMS_DW.obj;
      Formation_FMS_DW.object[2] = Formation_FMS_DW.obj;
      Formation_FMS_DW.object[0].xs = BusConversion_InsertedFor_FMS_p->x_R[0];
      Formation_FMS_DW.object[0].ys = BusConversion_InsertedFor_FMS_p->y_R[0];
      Formation_FMS_DW.object[0].psi_s = rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[0],
         BusConversion_InsertedFor_FMS_p->vn[0]);
      Formation_FMS_DW.object[0].xf = FORMATION_PARAM.FORM_POINT[0];
      Formation_FMS_DW.object[0].yf = FORMATION_PARAM.FORM_POINT[3];
      Formation_FMS_DW.object[0].psi_f = FORMATION_PARAM.FORM_POINT[6];
      Formation_FMS_DW.object[0].v = 25.0;
      Formation_FMS_DW.object[1].xs = BusConversion_InsertedFor_FMS_p->x_R[1];
      Formation_FMS_DW.object[1].ys = BusConversion_InsertedFor_FMS_p->y_R[1];
      Formation_FMS_DW.object[1].psi_s = rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[1],
         BusConversion_InsertedFor_FMS_p->vn[1]);
      Formation_FMS_DW.object[1].xf = FORMATION_PARAM.FORM_POINT[1];
      Formation_FMS_DW.object[1].yf = FORMATION_PARAM.FORM_POINT[4];
      Formation_FMS_DW.object[1].psi_f = FORMATION_PARAM.FORM_POINT[7];
      Formation_FMS_DW.object[1].v = 25.0;
      Formation_FMS_DW.object[2].xs = BusConversion_InsertedFor_FMS_p->x_R[2];
      Formation_FMS_DW.object[2].ys = BusConversion_InsertedFor_FMS_p->y_R[2];
      Formation_FMS_DW.object[2].psi_s = rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[2],
         BusConversion_InsertedFor_FMS_p->vn[2]);
      Formation_FMS_DW.object[2].xf = FORMATION_PARAM.FORM_POINT[2];
      Formation_FMS_DW.object[2].yf = FORMATION_PARAM.FORM_POINT[5];
      Formation_FMS_DW.object[2].psi_f = FORMATION_PARAM.FORM_POINT[8];
      Formation_FMS_DW.object[2].v = 25.0;
      Formation_FMS_DW.target = -1;
      Formation_FMS_DW.l_ref = -1.0;
      Formation_FMS_DW.obj = Formation_FMS_DW.object[0];
      Formation_FMS_Dubins(&Formation_FMS_DW.PhiMaximum,
                           &Formation_FMS_DW.rad2deg, static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->x_R[0]),
                           static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->y_R[0]),
                           static_cast<real_T>(rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[0],
         BusConversion_InsertedFor_FMS_p->vn[0])), FORMATION_PARAM.FORM_POINT[0],
                           FORMATION_PARAM.FORM_POINT[3],
                           FORMATION_PARAM.FORM_POINT[6], 25.0,
                           Formation_FMS_DW.obj.xts, Formation_FMS_DW.obj.yts,
                           Formation_FMS_DW.obj.xtf, Formation_FMS_DW.obj.ytf,
                           Formation_FMS_DW.obj.cs, Formation_FMS_DW.obj.cf,
                           Formation_FMS_DW.obj.lt, Formation_FMS_DW.obj.l,
                           Formation_FMS_DW.obj.pos, Formation_FMS_DW.obj.pof,
                           &Formation_FMS_DW.obj.r, Formation_FMS_DW.b_data,
                           &Formation_FMS_DW.b_size, Formation_FMS_DW.c_data,
                           &Formation_FMS_DW.c_size);
      Formation_FMS_DW.obj.index_dubins[0] = Formation_FMS_DW.b_data[0];
      Formation_FMS_DW.obj.index_dubins[1] = Formation_FMS_DW.c_data[0];
      Formation_FMS_DW.goal = Formation_FMS_DW.obj.l[(((static_cast<int32_T>
        (Formation_FMS_DW.c_data[0]) - 1) << 1) + static_cast<int32_T>
        (Formation_FMS_DW.b_data[0])) - 1];
      if (Formation_FMS_DW.goal > -1.0) {
        Formation_FMS_DW.l_ref = Formation_FMS_DW.goal;
        Formation_FMS_DW.target = 1;
      }

      Formation_FMS_DW.object[0] = Formation_FMS_DW.obj;
      Formation_FMS_DW.obj = Formation_FMS_DW.object[1];
      Formation_FMS_Dubins(&Formation_FMS_DW.PhiMaximum,
                           &Formation_FMS_DW.rad2deg, static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->x_R[1]),
                           static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->y_R[1]),
                           static_cast<real_T>(rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[1],
         BusConversion_InsertedFor_FMS_p->vn[1])), FORMATION_PARAM.FORM_POINT[1],
                           FORMATION_PARAM.FORM_POINT[4],
                           FORMATION_PARAM.FORM_POINT[7], 25.0,
                           Formation_FMS_DW.obj.xts, Formation_FMS_DW.obj.yts,
                           Formation_FMS_DW.obj.xtf, Formation_FMS_DW.obj.ytf,
                           Formation_FMS_DW.obj.cs, Formation_FMS_DW.obj.cf,
                           Formation_FMS_DW.obj.lt, Formation_FMS_DW.obj.l,
                           Formation_FMS_DW.obj.pos, Formation_FMS_DW.obj.pof,
                           &Formation_FMS_DW.obj.r, Formation_FMS_DW.b_data,
                           &Formation_FMS_DW.b_size, Formation_FMS_DW.c_data,
                           &Formation_FMS_DW.c_size);
      Formation_FMS_DW.obj.index_dubins[0] = Formation_FMS_DW.b_data[0];
      Formation_FMS_DW.obj.index_dubins[1] = Formation_FMS_DW.c_data[0];
      Formation_FMS_DW.goal = Formation_FMS_DW.obj.l[(((static_cast<int32_T>
        (Formation_FMS_DW.c_data[0]) - 1) << 1) + static_cast<int32_T>
        (Formation_FMS_DW.b_data[0])) - 1];
      if (Formation_FMS_DW.goal > Formation_FMS_DW.l_ref) {
        Formation_FMS_DW.l_ref = Formation_FMS_DW.goal;
        Formation_FMS_DW.target = 2;
      }

      Formation_FMS_DW.object[1] = Formation_FMS_DW.obj;
      Formation_FMS_DW.obj = Formation_FMS_DW.object[2];
      Formation_FMS_Dubins(&Formation_FMS_DW.PhiMaximum,
                           &Formation_FMS_DW.rad2deg, static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->x_R[2]),
                           static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->y_R[2]),
                           static_cast<real_T>(rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[2],
         BusConversion_InsertedFor_FMS_p->vn[2])), FORMATION_PARAM.FORM_POINT[2],
                           FORMATION_PARAM.FORM_POINT[5],
                           FORMATION_PARAM.FORM_POINT[8], 25.0,
                           Formation_FMS_DW.obj.xts, Formation_FMS_DW.obj.yts,
                           Formation_FMS_DW.obj.xtf, Formation_FMS_DW.obj.ytf,
                           Formation_FMS_DW.obj.cs, Formation_FMS_DW.obj.cf,
                           Formation_FMS_DW.obj.lt, Formation_FMS_DW.obj.l,
                           Formation_FMS_DW.obj.pos, Formation_FMS_DW.obj.pof,
                           &Formation_FMS_DW.obj.r, Formation_FMS_DW.b_data,
                           &Formation_FMS_DW.b_size, Formation_FMS_DW.c_data,
                           &Formation_FMS_DW.c_size);
      Formation_FMS_DW.obj.index_dubins[0] = Formation_FMS_DW.b_data[0];
      Formation_FMS_DW.obj.index_dubins[1] = Formation_FMS_DW.c_data[0];
      Formation_FMS_DW.goal = Formation_FMS_DW.obj.l[(((static_cast<int32_T>
        (Formation_FMS_DW.c_data[0]) - 1) << 1) + static_cast<int32_T>
        (Formation_FMS_DW.b_data[0])) - 1];
      if (Formation_FMS_DW.goal > Formation_FMS_DW.l_ref) {
        Formation_FMS_DW.l_ref = Formation_FMS_DW.goal;
        Formation_FMS_DW.target = 3;
      }

      Formation_FMS_DW.object[2] = Formation_FMS_DW.obj;
      for (Formation_FMS_DW.i_g = 0; Formation_FMS_DW.i_g < 3;
           Formation_FMS_DW.i_g++) {
        if (Formation_FMS_DW.i_g + 1 != Formation_FMS_DW.target) {
          Formation_FMS_DW.search_floor = 0.0;
          Formation_FMS_DW.search = 0.0;
          Formation_FMS_DW.stop_flag = 1;
          for (Formation_FMS_DW.j = 0; Formation_FMS_DW.j < 7;
               Formation_FMS_DW.j++) {
            boolean_T exitg1;
            exitg1 = false;
            while ((!exitg1) && (Formation_FMS_DW.stop_flag != 0)) {
              Formation_FMS_DW.search += d[Formation_FMS_DW.j];
              Formation_FMS_DW.goal =
                Formation_FMS_DW.object[Formation_FMS_DW.i_g].psi_f /
                57.295779513082323;
              Formation_FMS_DW.object[Formation_FMS_DW.i_g].xm =
                Formation_FMS_DW.object[Formation_FMS_DW.i_g].xf - std::cos
                (Formation_FMS_DW.goal) * Formation_FMS_DW.search;
              Formation_FMS_DW.object[Formation_FMS_DW.i_g].ym =
                Formation_FMS_DW.object[Formation_FMS_DW.i_g].yf - std::sin
                (Formation_FMS_DW.goal) * Formation_FMS_DW.search;
              Formation_FMS_Dubins(&Formation_FMS_DW.PhiMaximum,
                                   &Formation_FMS_DW.rad2deg,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .xs,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .ys,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .psi_s,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .xm,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .ym,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .psi_f,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .v,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .xts,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .yts,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .xtf,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .ytf,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .cs,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .cf,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .lt,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .l,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .pos,
                                   Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                                   .pof, &Formation_FMS_DW.goal,
                                   Formation_FMS_DW.b_data,
                                   &Formation_FMS_DW.b_size,
                                   Formation_FMS_DW.c_data,
                                   &Formation_FMS_DW.c_size);
              Formation_FMS_DW.object[Formation_FMS_DW.i_g].index_dubins[0] =
                Formation_FMS_DW.b_data[0];
              Formation_FMS_DW.object[Formation_FMS_DW.i_g].index_dubins[1] =
                Formation_FMS_DW.c_data[0];
              Formation_FMS_DW.goal =
                (Formation_FMS_DW.object[Formation_FMS_DW.i_g].l
                 [(((static_cast<int32_T>
                     (Formation_FMS_DW.object[Formation_FMS_DW.i_g]
                      .index_dubins[1]) - 1) << 1) + static_cast<int32_T>
                   (Formation_FMS_DW.object[Formation_FMS_DW.i_g].index_dubins[0]))
                 - 1] + Formation_FMS_DW.search) - Formation_FMS_DW.l_ref;
              if (Formation_FMS_DW.goal > 0.0) {
                Formation_FMS_DW.object[Formation_FMS_DW.i_g].l_ad =
                  Formation_FMS_DW.search_floor;
                Formation_FMS_DW.object[Formation_FMS_DW.i_g].precision_flag =
                  d[Formation_FMS_DW.j];
                Formation_FMS_DW.search = Formation_FMS_DW.search_floor;
                exitg1 = true;
              } else if (Formation_FMS_DW.goal < 0.0) {
                Formation_FMS_DW.search_floor = Formation_FMS_DW.search;
              } else {
                Formation_FMS_DW.object[Formation_FMS_DW.i_g].l_ad =
                  Formation_FMS_DW.search;
                Formation_FMS_DW.object[Formation_FMS_DW.i_g].precision_flag =
                  0.0;
                Formation_FMS_DW.stop_flag = 0;
              }
            }
          }
        } else {
          Formation_FMS_DW.object[Formation_FMS_DW.i_g].xm =
            Formation_FMS_DW.object[Formation_FMS_DW.i_g].xf;
          Formation_FMS_DW.object[Formation_FMS_DW.i_g].ym =
            Formation_FMS_DW.object[Formation_FMS_DW.i_g].yf;
        }
      }

      if (Formation_FMS_DW.target == 1) {
        Formation_FMS_DW.result[0] = Formation_FMS_DW.object[0].xs;
        Formation_FMS_DW.result[15] = Formation_FMS_DW.object[0].ys;
        Formation_FMS_DW.result[30] = Formation_FMS_DW.object[0].psi_s;
        Formation_FMS_DW.result[45] = Formation_FMS_DW.object[0].r;
        Formation_FMS_DW.i_g = (((static_cast<int32_T>(Formation_FMS_DW.object[0]
          .index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_DW.object[0].index_dubins[0])) - 1;
        Formation_FMS_DW.result[60] = Formation_FMS_DW.object[0]
          .cs[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[3] = Formation_FMS_DW.object[0]
          .xts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[18] = Formation_FMS_DW.object[0]
          .yts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_DW.object[0].xtf[Formation_FMS_DW.i_g],
           Formation_FMS_DW.object[0].ytf[Formation_FMS_DW.i_g],
           Formation_FMS_DW.object[0].xts[Formation_FMS_DW.i_g],
           Formation_FMS_DW.object[0].yts[Formation_FMS_DW.i_g]) *
          57.295779513082323;
        Formation_FMS_DW.result[33] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[48] = 0.0;
        Formation_FMS_DW.result[63] = Formation_FMS_DW.object[0]
          .lt[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[6] = Formation_FMS_DW.object[0]
          .xtf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[21] = Formation_FMS_DW.object[0]
          .ytf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[36] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[51] = Formation_FMS_DW.object[0].r;
        Formation_FMS_DW.result[66] = Formation_FMS_DW.object[0]
          .cf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[9] = Formation_FMS_DW.object[0].xm;
        Formation_FMS_DW.result[24] = Formation_FMS_DW.object[0].ym;
        Formation_FMS_DW.result[39] = Formation_FMS_DW.object[0].psi_f;
        Formation_FMS_DW.result[54] = 0.0;
        Formation_FMS_DW.result[69] = 0.0;
        Formation_FMS_DW.result[12] = Formation_FMS_DW.object[0].xf;
        Formation_FMS_DW.result[27] = Formation_FMS_DW.object[0].yf;
        Formation_FMS_DW.result[42] = Formation_FMS_DW.object[0].psi_f;
        Formation_FMS_DW.result[57] = 0.0;
        Formation_FMS_DW.result[72] = Formation_FMS_DW.object[0]
          .l[Formation_FMS_DW.i_g];
      } else {
        Formation_FMS_DW.result[0] = Formation_FMS_DW.object[0].xs;
        Formation_FMS_DW.result[15] = Formation_FMS_DW.object[0].ys;
        Formation_FMS_DW.result[30] = Formation_FMS_DW.object[0].psi_s;
        Formation_FMS_DW.result[45] = Formation_FMS_DW.object[0].r;
        Formation_FMS_DW.i_g = (((static_cast<int32_T>(Formation_FMS_DW.object[0]
          .index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_DW.object[0].index_dubins[0])) - 1;
        Formation_FMS_DW.result[60] = Formation_FMS_DW.object[0]
          .cs[Formation_FMS_DW.i_g];
        Formation_FMS_DW.l_ref = Formation_FMS_DW.object[0]
          .xts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[3] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.search_floor = Formation_FMS_DW.object[0]
          .yts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[18] = Formation_FMS_DW.search_floor;
        Formation_FMS_DW.search = Formation_FMS_DW.object[0]
          .xtf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.goal = Formation_FMS_DW.object[0]
          .ytf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_DW.search, Formation_FMS_DW.goal,
           Formation_FMS_DW.l_ref, Formation_FMS_DW.search_floor) *
          57.295779513082323;
        Formation_FMS_DW.result[33] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[48] = 0.0;
        Formation_FMS_DW.result[63] = Formation_FMS_DW.object[0]
          .lt[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[6] = Formation_FMS_DW.search;
        Formation_FMS_DW.result[21] = Formation_FMS_DW.goal;
        Formation_FMS_DW.result[36] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[51] = Formation_FMS_DW.object[0].r;
        Formation_FMS_DW.result[66] = Formation_FMS_DW.object[0]
          .cf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[9] = Formation_FMS_DW.object[0].xm;
        Formation_FMS_DW.result[24] = Formation_FMS_DW.object[0].ym;
        Formation_FMS_DW.result[39] = Formation_FMS_DW.object[0].psi_f;
        Formation_FMS_DW.result[54] = 0.0;
        Formation_FMS_DW.result[69] = Formation_FMS_DW.object[0].l_ad;
        Formation_FMS_DW.result[12] = Formation_FMS_DW.object[0].xf;
        Formation_FMS_DW.result[27] = Formation_FMS_DW.object[0].yf;
        Formation_FMS_DW.result[42] = Formation_FMS_DW.object[0].psi_f;
        Formation_FMS_DW.result[57] = 0.0;
        Formation_FMS_DW.result[72] = Formation_FMS_DW.object[0]
          .l[Formation_FMS_DW.i_g] + Formation_FMS_DW.object[0].l_ad;
      }

      if (Formation_FMS_DW.target == 2) {
        Formation_FMS_DW.result[1] = Formation_FMS_DW.object[1].xs;
        Formation_FMS_DW.result[16] = Formation_FMS_DW.object[1].ys;
        Formation_FMS_DW.result[31] = Formation_FMS_DW.object[1].psi_s;
        Formation_FMS_DW.result[46] = Formation_FMS_DW.object[1].r;
        Formation_FMS_DW.i_g = (((static_cast<int32_T>(Formation_FMS_DW.object[1]
          .index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_DW.object[1].index_dubins[0])) - 1;
        Formation_FMS_DW.result[61] = Formation_FMS_DW.object[1]
          .cs[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[4] = Formation_FMS_DW.object[1]
          .xts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[19] = Formation_FMS_DW.object[1]
          .yts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_DW.object[1].xtf[Formation_FMS_DW.i_g],
           Formation_FMS_DW.object[1].ytf[Formation_FMS_DW.i_g],
           Formation_FMS_DW.object[1].xts[Formation_FMS_DW.i_g],
           Formation_FMS_DW.object[1].yts[Formation_FMS_DW.i_g]) *
          57.295779513082323;
        Formation_FMS_DW.result[34] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[49] = 0.0;
        Formation_FMS_DW.result[64] = Formation_FMS_DW.object[1]
          .lt[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[7] = Formation_FMS_DW.object[1]
          .xtf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[22] = Formation_FMS_DW.object[1]
          .ytf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[37] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[52] = Formation_FMS_DW.object[1].r;
        Formation_FMS_DW.result[67] = Formation_FMS_DW.object[1]
          .cf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[10] = Formation_FMS_DW.object[1].xm;
        Formation_FMS_DW.result[25] = Formation_FMS_DW.object[1].ym;
        Formation_FMS_DW.result[40] = Formation_FMS_DW.object[1].psi_f;
        Formation_FMS_DW.result[55] = 0.0;
        Formation_FMS_DW.result[70] = 0.0;
        Formation_FMS_DW.result[13] = Formation_FMS_DW.object[1].xf;
        Formation_FMS_DW.result[28] = Formation_FMS_DW.object[1].yf;
        Formation_FMS_DW.result[43] = Formation_FMS_DW.object[1].psi_f;
        Formation_FMS_DW.result[58] = 0.0;
        Formation_FMS_DW.result[73] = Formation_FMS_DW.object[1]
          .l[Formation_FMS_DW.i_g];
      } else {
        Formation_FMS_DW.result[1] = Formation_FMS_DW.object[1].xs;
        Formation_FMS_DW.result[16] = Formation_FMS_DW.object[1].ys;
        Formation_FMS_DW.result[31] = Formation_FMS_DW.object[1].psi_s;
        Formation_FMS_DW.result[46] = Formation_FMS_DW.object[1].r;
        Formation_FMS_DW.i_g = (((static_cast<int32_T>(Formation_FMS_DW.object[1]
          .index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_DW.object[1].index_dubins[0])) - 1;
        Formation_FMS_DW.result[61] = Formation_FMS_DW.object[1]
          .cs[Formation_FMS_DW.i_g];
        Formation_FMS_DW.l_ref = Formation_FMS_DW.object[1]
          .xts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[4] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.search_floor = Formation_FMS_DW.object[1]
          .yts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[19] = Formation_FMS_DW.search_floor;
        Formation_FMS_DW.search = Formation_FMS_DW.object[1]
          .xtf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.goal = Formation_FMS_DW.object[1]
          .ytf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_DW.search, Formation_FMS_DW.goal,
           Formation_FMS_DW.l_ref, Formation_FMS_DW.search_floor) *
          57.295779513082323;
        Formation_FMS_DW.result[34] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[49] = 0.0;
        Formation_FMS_DW.result[64] = Formation_FMS_DW.object[1]
          .lt[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[7] = Formation_FMS_DW.search;
        Formation_FMS_DW.result[22] = Formation_FMS_DW.goal;
        Formation_FMS_DW.result[37] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[52] = Formation_FMS_DW.object[1].r;
        Formation_FMS_DW.result[67] = Formation_FMS_DW.object[1]
          .cf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[10] = Formation_FMS_DW.object[1].xm;
        Formation_FMS_DW.result[25] = Formation_FMS_DW.object[1].ym;
        Formation_FMS_DW.result[40] = Formation_FMS_DW.object[1].psi_f;
        Formation_FMS_DW.result[55] = 0.0;
        Formation_FMS_DW.result[70] = Formation_FMS_DW.object[1].l_ad;
        Formation_FMS_DW.result[13] = Formation_FMS_DW.object[1].xf;
        Formation_FMS_DW.result[28] = Formation_FMS_DW.object[1].yf;
        Formation_FMS_DW.result[43] = Formation_FMS_DW.object[1].psi_f;
        Formation_FMS_DW.result[58] = 0.0;
        Formation_FMS_DW.result[73] = Formation_FMS_DW.object[1]
          .l[Formation_FMS_DW.i_g] + Formation_FMS_DW.object[1].l_ad;
      }

      if (Formation_FMS_DW.target == 3) {
        Formation_FMS_DW.result[2] = Formation_FMS_DW.object[2].xs;
        Formation_FMS_DW.result[17] = Formation_FMS_DW.object[2].ys;
        Formation_FMS_DW.result[32] = Formation_FMS_DW.object[2].psi_s;
        Formation_FMS_DW.result[47] = Formation_FMS_DW.object[2].r;
        Formation_FMS_DW.i_g = (((static_cast<int32_T>(Formation_FMS_DW.object[2]
          .index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_DW.object[2].index_dubins[0])) - 1;
        Formation_FMS_DW.result[62] = Formation_FMS_DW.object[2]
          .cs[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[5] = Formation_FMS_DW.object[2]
          .xts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[20] = Formation_FMS_DW.object[2]
          .yts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_DW.object[2].xtf[Formation_FMS_DW.i_g],
           Formation_FMS_DW.object[2].ytf[Formation_FMS_DW.i_g],
           Formation_FMS_DW.object[2].xts[Formation_FMS_DW.i_g],
           Formation_FMS_DW.object[2].yts[Formation_FMS_DW.i_g]) *
          57.295779513082323;
        Formation_FMS_DW.result[35] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[50] = 0.0;
        Formation_FMS_DW.result[65] = Formation_FMS_DW.object[2]
          .lt[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[8] = Formation_FMS_DW.object[2]
          .xtf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[23] = Formation_FMS_DW.object[2]
          .ytf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[38] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[53] = Formation_FMS_DW.object[2].r;
        Formation_FMS_DW.result[68] = Formation_FMS_DW.object[2]
          .cf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[11] = Formation_FMS_DW.object[2].xm;
        Formation_FMS_DW.result[26] = Formation_FMS_DW.object[2].ym;
        Formation_FMS_DW.result[41] = Formation_FMS_DW.object[2].psi_f;
        Formation_FMS_DW.result[56] = 0.0;
        Formation_FMS_DW.result[71] = 0.0;
        Formation_FMS_DW.result[14] = Formation_FMS_DW.object[2].xf;
        Formation_FMS_DW.result[29] = Formation_FMS_DW.object[2].yf;
        Formation_FMS_DW.result[44] = Formation_FMS_DW.object[2].psi_f;
        Formation_FMS_DW.result[59] = 0.0;
        Formation_FMS_DW.result[74] = Formation_FMS_DW.object[2]
          .l[Formation_FMS_DW.i_g];
      } else {
        Formation_FMS_DW.result[2] = Formation_FMS_DW.object[2].xs;
        Formation_FMS_DW.result[17] = Formation_FMS_DW.object[2].ys;
        Formation_FMS_DW.result[32] = Formation_FMS_DW.object[2].psi_s;
        Formation_FMS_DW.result[47] = Formation_FMS_DW.object[2].r;
        Formation_FMS_DW.i_g = (((static_cast<int32_T>(Formation_FMS_DW.object[2]
          .index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_DW.object[2].index_dubins[0])) - 1;
        Formation_FMS_DW.result[62] = Formation_FMS_DW.object[2]
          .cs[Formation_FMS_DW.i_g];
        Formation_FMS_DW.l_ref = Formation_FMS_DW.object[2]
          .xts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[5] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.search_floor = Formation_FMS_DW.object[2]
          .yts[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[20] = Formation_FMS_DW.search_floor;
        Formation_FMS_DW.search = Formation_FMS_DW.object[2]
          .xtf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.goal = Formation_FMS_DW.object[2]
          .ytf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_DW.search, Formation_FMS_DW.goal,
           Formation_FMS_DW.l_ref, Formation_FMS_DW.search_floor) *
          57.295779513082323;
        Formation_FMS_DW.result[35] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[50] = 0.0;
        Formation_FMS_DW.result[65] = Formation_FMS_DW.object[2]
          .lt[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[8] = Formation_FMS_DW.search;
        Formation_FMS_DW.result[23] = Formation_FMS_DW.goal;
        Formation_FMS_DW.result[38] = Formation_FMS_DW.l_ref;
        Formation_FMS_DW.result[53] = Formation_FMS_DW.object[2].r;
        Formation_FMS_DW.result[68] = Formation_FMS_DW.object[2]
          .cf[Formation_FMS_DW.i_g];
        Formation_FMS_DW.result[11] = Formation_FMS_DW.object[2].xm;
        Formation_FMS_DW.result[26] = Formation_FMS_DW.object[2].ym;
        Formation_FMS_DW.result[41] = Formation_FMS_DW.object[2].psi_f;
        Formation_FMS_DW.result[56] = 0.0;
        Formation_FMS_DW.result[71] = Formation_FMS_DW.object[2].l_ad;
        Formation_FMS_DW.result[14] = Formation_FMS_DW.object[2].xf;
        Formation_FMS_DW.result[29] = Formation_FMS_DW.object[2].yf;
        Formation_FMS_DW.result[44] = Formation_FMS_DW.object[2].psi_f;
        Formation_FMS_DW.result[59] = 0.0;
        Formation_FMS_DW.result[74] = Formation_FMS_DW.object[2]
          .l[Formation_FMS_DW.i_g] + Formation_FMS_DW.object[2].l_ad;
      }

      std::memset(&Formation_FMS_DW.Other_Mission_Data.x[0], 0, 24U * sizeof
                  (real32_T));
      std::memset(&Formation_FMS_DW.Other_Mission_Data.y[0], 0, 24U * sizeof
                  (real32_T));
      std::memset(&Formation_FMS_DW.Other_Mission_Data.z[0], 0, 24U * sizeof
                  (real32_T));
      std::memset(&Formation_FMS_DW.Other_Mission_Data.heading[0], 0, 24U *
                  sizeof(real32_T));
      std::memset(&Formation_FMS_DW.Other_Mission_Data.ext1[0], 0, 24U * sizeof
                  (real32_T));
      std::memset(&Formation_FMS_DW.Other_Mission_Data.ext2[0], 0, 24U * sizeof
                  (real32_T));
      for (Formation_FMS_DW.j = 0; Formation_FMS_DW.j < 5; Formation_FMS_DW.j++)
      {
        Formation_FMS_DW.Other_Mission_Data.x[3 * Formation_FMS_DW.j] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j]);
        Formation_FMS_DW.Other_Mission_Data.y[3 * Formation_FMS_DW.j] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          15]);
        Formation_FMS_DW.i_g = 3 * Formation_FMS_DW.j + 1;
        Formation_FMS_DW.Other_Mission_Data.x[Formation_FMS_DW.i_g] =
          static_cast<real32_T>(Formation_FMS_DW.result[Formation_FMS_DW.i_g]);
        Formation_FMS_DW.Other_Mission_Data.y[Formation_FMS_DW.i_g] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          16]);
        Formation_FMS_DW.i_g = 3 * Formation_FMS_DW.j + 2;
        Formation_FMS_DW.Other_Mission_Data.x[Formation_FMS_DW.i_g] =
          static_cast<real32_T>(Formation_FMS_DW.result[Formation_FMS_DW.i_g]);
        Formation_FMS_DW.Other_Mission_Data.y[Formation_FMS_DW.i_g] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          17]);
      }

      for (Formation_FMS_DW.i_g = 0; Formation_FMS_DW.i_g < 3;
           Formation_FMS_DW.i_g++) {
        for (Formation_FMS_DW.j = 0; Formation_FMS_DW.j < 5; Formation_FMS_DW.j
             ++) {
          Formation_FMS_DW.Other_Mission_Data.z[Formation_FMS_DW.i_g + 3 *
            Formation_FMS_DW.j] = BusConversion_InsertedFor_FMS_p->
            h_R[Formation_FMS_DW.i_g];
        }
      }

      for (Formation_FMS_DW.j = 0; Formation_FMS_DW.j < 5; Formation_FMS_DW.j++)
      {
        Formation_FMS_DW.Other_Mission_Data.heading[3 * Formation_FMS_DW.j] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          30]);
        Formation_FMS_DW.Other_Mission_Data.ext1[3 * Formation_FMS_DW.j] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          45]);
        Formation_FMS_DW.Other_Mission_Data.ext2[3 * Formation_FMS_DW.j] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          60]);
        Formation_FMS_DW.i_g = 3 * Formation_FMS_DW.j + 1;
        Formation_FMS_DW.Other_Mission_Data.heading[Formation_FMS_DW.i_g] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          31]);
        Formation_FMS_DW.Other_Mission_Data.ext1[Formation_FMS_DW.i_g] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          46]);
        Formation_FMS_DW.Other_Mission_Data.ext2[Formation_FMS_DW.i_g] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          61]);
        Formation_FMS_DW.i_g = 3 * Formation_FMS_DW.j + 2;
        Formation_FMS_DW.Other_Mission_Data.heading[Formation_FMS_DW.i_g] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          32]);
        Formation_FMS_DW.Other_Mission_Data.ext1[Formation_FMS_DW.i_g] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          47]);
        Formation_FMS_DW.Other_Mission_Data.ext2[Formation_FMS_DW.i_g] =
          static_cast<real32_T>(Formation_FMS_DW.result[3 * Formation_FMS_DW.j +
          62]);
      }

      Formation_FMS_DW.Other_Mission_Data.timestamp = 9999U;
      Formation_FMS_DW.Other_Mission_Data.type[0] = 1U;
      Formation_FMS_DW.Other_Mission_Data.valid_items[0] = 5U;
      Formation_FMS_DW.Other_Mission_Data.type[1] = 1U;
      Formation_FMS_DW.Other_Mission_Data.valid_items[1] = 5U;
      Formation_FMS_DW.Other_Mission_Data.type[2] = 1U;
      Formation_FMS_DW.Other_Mission_Data.valid_items[2] = 5U;

      // End of MATLAB Function: '<S152>/MATLAB Function'
      // End of Outputs for SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPath' 
    }

    Formation_FMS_DW.state = VehicleState::FormAssemble;
    Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_WaitForUpdate;
    Formation_FMS_DW.Cmd_In.l1_enable = false;
  } else {
    Formation_FMS_DW.is_Formation = Formation_FMS_IN_InvalidMode;
  }
}

// Function for MATLAB Function: '<S153>/Dubins Closest Point'
void Formation_FMS::Formati_getMinDistanceAtSegment(const real32_T waypoints[25],
  const real32_T pose[3], uint16_T segment, real32_T *dist, real32_T *ratio)
{
  if (segment >= 5) {
    *dist = (rtInfF);
    *ratio = 0.0F;
  } else {
    Formation_FMS_DW.unit_centre_to_pose_idx_0 = waypoints[segment - 1];
    Formation_FMS_DW.unit_norm_vector_idx_0 = waypoints[segment];
    Formation_FMS_DW.unit_point_to_next[0] =
      Formation_FMS_DW.unit_norm_vector_idx_0 -
      Formation_FMS_DW.unit_centre_to_pose_idx_0;
    Formation_FMS_DW.unit_centre_to_pose_idx_1 = waypoints[segment + 4];
    Formation_FMS_DW.unit_norm_vector_idx_1 = waypoints[segment + 5];
    Formation_FMS_DW.unit_point_to_next[1] =
      Formation_FMS_DW.unit_norm_vector_idx_1 -
      Formation_FMS_DW.unit_centre_to_pose_idx_1;
    Formation_FMS_DW.dotProduct = norm_7i8u8z8R
      (Formation_FMS_DW.unit_point_to_next);
    Formation_FMS_DW.nearest_cross = Formation_FMS_DW.unit_point_to_next[0] /
      Formation_FMS_DW.dotProduct;
    Formation_FMS_DW.unit_point_to_next_g = Formation_FMS_DW.unit_point_to_next
      [1] / Formation_FMS_DW.dotProduct;
    Formation_FMS_DW.unit_line_idx_0 = waypoints[segment + 9];
    Formation_FMS_DW.dotProduct = std::cos(Formation_FMS_DW.unit_line_idx_0);
    Formation_FMS_DW.nearest_cross_tmp = std::sin
      (Formation_FMS_DW.unit_line_idx_0);
    Formation_FMS_DW.nearest_cross = Formation_FMS_DW.dotProduct *
      Formation_FMS_DW.unit_point_to_next_g - Formation_FMS_DW.nearest_cross_tmp
      * Formation_FMS_DW.nearest_cross;
    if (std::abs(Formation_FMS_DW.nearest_cross) < 0.017452406437283512) {
      Formation_FMS_DW.unit_line_idx_0 = Formation_FMS_DW.dotProduct;
      Formation_FMS_DW.nearest_cross = pose[0] -
        Formation_FMS_DW.unit_centre_to_pose_idx_0;
      Formation_FMS_DW.dotProduct *= Formation_FMS_DW.nearest_cross;
      Formation_FMS_DW.unit_point_to_next[0] = Formation_FMS_DW.nearest_cross;
      Formation_FMS_DW.nearest_cross = pose[1] -
        Formation_FMS_DW.unit_centre_to_pose_idx_1;
      Formation_FMS_DW.dotProduct += Formation_FMS_DW.nearest_cross *
        Formation_FMS_DW.nearest_cross_tmp;
      Formation_FMS_DW.unit_point_to_next[0] -= Formation_FMS_DW.dotProduct *
        Formation_FMS_DW.unit_line_idx_0;
      Formation_FMS_DW.unit_point_to_next[1] = Formation_FMS_DW.nearest_cross -
        Formation_FMS_DW.dotProduct * Formation_FMS_DW.nearest_cross_tmp;
      *dist = norm_7i8u8z8R(Formation_FMS_DW.unit_point_to_next);
      Formation_FMS_DW.unit_point_to_next[0] =
        Formation_FMS_DW.unit_centre_to_pose_idx_0 -
        Formation_FMS_DW.unit_norm_vector_idx_0;
      Formation_FMS_DW.unit_point_to_next[1] =
        Formation_FMS_DW.unit_centre_to_pose_idx_1 -
        Formation_FMS_DW.unit_norm_vector_idx_1;
      *ratio = Formation_FMS_DW.dotProduct / norm_7i8u8z8R
        (Formation_FMS_DW.unit_point_to_next);
    } else if (Formation_FMS_DW.nearest_cross > 0.017452406437283512) {
      Formation_FMS_DW.unit_norm_vector_idx_0 =
        -Formation_FMS_DW.nearest_cross_tmp;
      Formation_FMS_DW.unit_norm_vector_idx_1 = Formation_FMS_DW.dotProduct;
      Formation_FMS_DW.nearest_cross = waypoints[segment + 14];
      Formation_FMS_DW.unit_point_to_next[0] = pose[0] -
        (Formation_FMS_DW.nearest_cross * -Formation_FMS_DW.nearest_cross_tmp +
         Formation_FMS_DW.unit_centre_to_pose_idx_0);
      Formation_FMS_DW.unit_point_to_next[1] = pose[1] -
        (Formation_FMS_DW.nearest_cross * Formation_FMS_DW.dotProduct +
         Formation_FMS_DW.unit_centre_to_pose_idx_1);
      Formation_FMS_DW.unit_point_to_next_g = norm_7i8u8z8R
        (Formation_FMS_DW.unit_point_to_next);
      Formation_FMS_DW.unit_centre_to_pose_idx_0 =
        Formation_FMS_DW.unit_point_to_next[0] /
        Formation_FMS_DW.unit_point_to_next_g;
      Formation_FMS_DW.unit_centre_to_pose_idx_1 =
        Formation_FMS_DW.unit_point_to_next[1] /
        Formation_FMS_DW.unit_point_to_next_g;
      Formation_FMS_DW.dotProduct = rt_atan2f_snf
        (Formation_FMS_DW.nearest_cross_tmp *
         Formation_FMS_DW.unit_centre_to_pose_idx_1 -
         Formation_FMS_DW.unit_centre_to_pose_idx_0 *
         -Formation_FMS_DW.dotProduct, Formation_FMS_DW.nearest_cross_tmp *
         Formation_FMS_DW.unit_centre_to_pose_idx_0 +
         -Formation_FMS_DW.dotProduct *
         Formation_FMS_DW.unit_centre_to_pose_idx_1);
      if (Formation_FMS_DW.dotProduct < 0.0F) {
        Formation_FMS_DW.dotProduct += ((0.0F - Formation_FMS_DW.dotProduct) /
          6.28318548F + 1.0F) * 6.28318548F;
      }

      *dist = Formation_FMS_DW.unit_point_to_next_g -
        Formation_FMS_DW.nearest_cross;
      Formation_FMS_DW.nearest_cross = waypoints[segment + 10];
      Formation_FMS_DW.nearest_cross_tmp = (Formation_FMS_DW.nearest_cross +
        6.28318548F) - Formation_FMS_DW.unit_line_idx_0;
      if (Formation_FMS_DW.nearest_cross_tmp < 0.0F) {
        Formation_FMS_DW.nearest_cross_tmp += ((0.0F -
          Formation_FMS_DW.nearest_cross_tmp) / 6.28318548F + 1.0F) *
          6.28318548F;
      }

      *ratio = mod_ThuC9Kor(Formation_FMS_DW.dotProduct) / mod_ThuC9Kor
        (Formation_FMS_DW.nearest_cross_tmp);
      if (*ratio > 1.0F) {
        Formation_FMS_DW.unit_point_to_next[0] =
          Formation_FMS_DW.unit_centre_to_pose_idx_0 +
          Formation_FMS_DW.unit_norm_vector_idx_0;
        Formation_FMS_DW.unit_point_to_next[1] =
          Formation_FMS_DW.unit_centre_to_pose_idx_1 +
          Formation_FMS_DW.unit_norm_vector_idx_1;
        Formation_FMS_DW.unit_centre_to_pose[0] = -std::sin
          (Formation_FMS_DW.nearest_cross) +
          Formation_FMS_DW.unit_centre_to_pose_idx_0;
        Formation_FMS_DW.unit_centre_to_pose[1] = std::cos
          (Formation_FMS_DW.nearest_cross) +
          Formation_FMS_DW.unit_centre_to_pose_idx_1;
        *ratio = static_cast<real32_T>(!(norm_7i8u8z8R
          (Formation_FMS_DW.unit_point_to_next) < norm_7i8u8z8R
          (Formation_FMS_DW.unit_centre_to_pose)));
      }
    } else {
      Formation_FMS_DW.unit_norm_vector_idx_0 =
        Formation_FMS_DW.nearest_cross_tmp;
      Formation_FMS_DW.unit_norm_vector_idx_1 = -Formation_FMS_DW.dotProduct;
      Formation_FMS_DW.nearest_cross = waypoints[segment + 14];
      Formation_FMS_DW.unit_point_to_next[0] = pose[0] -
        (Formation_FMS_DW.nearest_cross * Formation_FMS_DW.nearest_cross_tmp +
         Formation_FMS_DW.unit_centre_to_pose_idx_0);
      Formation_FMS_DW.unit_point_to_next[1] = pose[1] -
        (Formation_FMS_DW.nearest_cross * -Formation_FMS_DW.dotProduct +
         Formation_FMS_DW.unit_centre_to_pose_idx_1);
      Formation_FMS_DW.nearest_cross_tmp = norm_7i8u8z8R
        (Formation_FMS_DW.unit_point_to_next);
      Formation_FMS_DW.unit_centre_to_pose_idx_1 =
        Formation_FMS_DW.unit_point_to_next[0] /
        Formation_FMS_DW.nearest_cross_tmp;
      Formation_FMS_DW.dotProduct = Formation_FMS_DW.unit_centre_to_pose_idx_1 *
        -Formation_FMS_DW.unit_norm_vector_idx_0;
      Formation_FMS_DW.unit_centre_to_pose_idx_0 =
        Formation_FMS_DW.unit_centre_to_pose_idx_1;
      Formation_FMS_DW.unit_centre_to_pose_idx_1 =
        Formation_FMS_DW.unit_point_to_next[1] /
        Formation_FMS_DW.nearest_cross_tmp;
      Formation_FMS_DW.dotProduct = rt_atan2f_snf
        (Formation_FMS_DW.unit_centre_to_pose_idx_0 *
         -Formation_FMS_DW.unit_norm_vector_idx_1 -
         -Formation_FMS_DW.unit_norm_vector_idx_0 *
         Formation_FMS_DW.unit_centre_to_pose_idx_1,
         Formation_FMS_DW.unit_centre_to_pose_idx_1 *
         -Formation_FMS_DW.unit_norm_vector_idx_1 + Formation_FMS_DW.dotProduct);
      if (Formation_FMS_DW.dotProduct < 0.0F) {
        Formation_FMS_DW.dotProduct += ((0.0F - Formation_FMS_DW.dotProduct) /
          6.28318548F + 1.0F) * 6.28318548F;
      }

      *dist = Formation_FMS_DW.nearest_cross_tmp -
        Formation_FMS_DW.nearest_cross;
      Formation_FMS_DW.nearest_cross_tmp = (6.28318548F - waypoints[segment + 10])
        + Formation_FMS_DW.unit_line_idx_0;
      if (Formation_FMS_DW.nearest_cross_tmp < 0.0F) {
        Formation_FMS_DW.nearest_cross_tmp += ((0.0F -
          Formation_FMS_DW.nearest_cross_tmp) / 6.28318548F + 1.0F) *
          6.28318548F;
      }

      *ratio = mod_ThuC9Kor(Formation_FMS_DW.dotProduct) / mod_ThuC9Kor
        (Formation_FMS_DW.nearest_cross_tmp);
      if (*ratio > 1.0F) {
        Formation_FMS_DW.unit_point_to_next[0] =
          Formation_FMS_DW.unit_centre_to_pose_idx_0 +
          Formation_FMS_DW.unit_norm_vector_idx_0;
        Formation_FMS_DW.unit_point_to_next[1] =
          Formation_FMS_DW.unit_centre_to_pose_idx_1 +
          Formation_FMS_DW.unit_norm_vector_idx_1;
        Formation_FMS_DW.unit_centre_to_pose[0] = std::sin(waypoints[segment +
          10]) + Formation_FMS_DW.unit_centre_to_pose_idx_0;
        Formation_FMS_DW.unit_centre_to_pose[1] = -std::cos(waypoints[segment +
          10]) + Formation_FMS_DW.unit_centre_to_pose_idx_1;
        *ratio = static_cast<real32_T>(!(norm_7i8u8z8R
          (Formation_FMS_DW.unit_point_to_next) < norm_7i8u8z8R
          (Formation_FMS_DW.unit_centre_to_pose)));
      }
    }
  }
}

// System initialize for referenced model: 'Formation_FMS'
void Formation_FMS::init(uint32_T *rty_FMS_Out_timestamp, VehicleState
  *rty_FMS_Out_state, real32_T *rty_FMS_Out_ax_cmd, real32_T *rty_FMS_Out_ay_cmd,
  real32_T *rty_FMS_Out_vh_cmd, uint32_T *rty_Other_Mission_Data_timestam,
  uint32_T rty_Other_Mission_Data_type[3], uint8_T
  rty_Other_Mission_Data_valid_it[3], real32_T rty_Other_Mission_Data_x[24],
  real32_T rty_Other_Mission_Data_y[24], real32_T rty_Other_Mission_Data_z[24],
  real32_T rty_Other_Mission_Data_heading[24], real32_T
  rty_Other_Mission_Data_ext1[24], real32_T rty_Other_Mission_Data_ext2[24])
{
  // Start for SwitchCase: '<S10>/Switch Case'
  Formation_FMS_DW.SwitchCase_ActiveSubsystem = -1;

  // SystemInitialize for Chart: '<Root>/FMS State Machine'
  Formation_FMS_DW.Cmd_In.form_valid = 0U;
  Formation_FMS_DW.Cmd_In.l1_enable = false;
  Formation_FMS_DW.Other_Mission_Data.timestamp = 0U;
  Formation_FMS_DW.Cmd_In.sp_waypoint[0] = 0.0F;
  Formation_FMS_DW.Cmd_In.cur_waypoint[0] = 0.0F;
  Formation_FMS_DW.Other_Mission_Data.type[0] = 0U;
  Formation_FMS_DW.Other_Mission_Data.valid_items[0] = 0U;
  Formation_FMS_DW.Cmd_In.sp_waypoint[1] = 0.0F;
  Formation_FMS_DW.Cmd_In.cur_waypoint[1] = 0.0F;
  Formation_FMS_DW.Other_Mission_Data.type[1] = 0U;
  Formation_FMS_DW.Other_Mission_Data.valid_items[1] = 0U;
  Formation_FMS_DW.Cmd_In.sp_waypoint[2] = 0.0F;
  Formation_FMS_DW.Cmd_In.cur_waypoint[2] = 0.0F;
  Formation_FMS_DW.Other_Mission_Data.type[2] = 0U;
  Formation_FMS_DW.Other_Mission_Data.valid_items[2] = 0U;
  for (int32_T i{0}; i < 24; i++) {
    Formation_FMS_DW.Other_Mission_Data.x[i] = 0.0F;
    Formation_FMS_DW.Other_Mission_Data.y[i] = 0.0F;
    Formation_FMS_DW.Other_Mission_Data.z[i] = 0.0F;
    Formation_FMS_DW.Other_Mission_Data.heading[i] = 0.0F;
    Formation_FMS_DW.Other_Mission_Data.ext1[i] = 0.0F;
    Formation_FMS_DW.Other_Mission_Data.ext2[i] = 0.0F;

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_x[i] = Formation_FMS_DW.Other_Mission_Data.x[i];

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_y[i] = Formation_FMS_DW.Other_Mission_Data.y[i];

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_z[i] = Formation_FMS_DW.Other_Mission_Data.z[i];

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_heading[i] =
      Formation_FMS_DW.Other_Mission_Data.heading[i];

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_ext1[i] = Formation_FMS_DW.Other_Mission_Data.ext1[i];

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_ext2[i] = Formation_FMS_DW.Other_Mission_Data.ext2[i];
  }

  // End of SystemInitialize for Chart: '<Root>/FMS State Machine'

  // SystemInitialize for IfAction SubSystem: '<S10>/FormMission'
  // SystemInitialize for Resettable SubSystem: '<S13>/FormMission_SubSystem'
  // InitializeConditions for Delay: '<S115>/Delay'
  Formation_FMS_DW.icLoad_k = true;

  // End of SystemInitialize for SubSystem: '<S13>/FormMission_SubSystem'
  // End of SystemInitialize for SubSystem: '<S10>/FormMission'

  // SystemInitialize for IfAction SubSystem: '<S10>/FormAssemble'
  // SystemInitialize for Resettable SubSystem: '<S12>/Mission_SubSystem'
  // InitializeConditions for Delay: '<S20>/Delay'
  Formation_FMS_DW.icLoad_h = true;

  // End of SystemInitialize for SubSystem: '<S12>/Mission_SubSystem'
  // End of SystemInitialize for SubSystem: '<S10>/FormAssemble'

  // SystemInitialize for IfAction SubSystem: '<S10>/Hold'
  // InitializeConditions for Delay: '<S139>/start_vel'
  Formation_FMS_DW.icLoad_c = true;

  // InitializeConditions for Delay: '<S135>/Delay'
  Formation_FMS_DW.icLoad_j = true;

  // End of SystemInitialize for SubSystem: '<S10>/Hold'

  // SystemInitialize for IfAction SubSystem: '<S10>/Default'
  // InitializeConditions for Delay: '<S16>/Delay'
  Formation_FMS_DW.icLoad = true;

  // End of SystemInitialize for SubSystem: '<S10>/Default'

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_type[0] = Formation_FMS_DW.Other_Mission_Data.type[0];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_valid_it[0] =
    Formation_FMS_DW.Other_Mission_Data.valid_items[0];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_type[1] = Formation_FMS_DW.Other_Mission_Data.type[1];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_valid_it[1] =
    Formation_FMS_DW.Other_Mission_Data.valid_items[1];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_type[2] = Formation_FMS_DW.Other_Mission_Data.type[2];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_valid_it[2] =
    Formation_FMS_DW.Other_Mission_Data.valid_items[2];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  *rty_Other_Mission_Data_timestam =
    Formation_FMS_DW.Other_Mission_Data.timestamp;

  // SystemInitialize for Merge: '<S10>/Merge'
  std::memset(&Formation_FMS_DW.Merge, 0, sizeof(FMS_Out_Bus));

  // SystemInitialize for SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_timestamp = Formation_FMS_DW.Merge.timestamp;

  // SystemInitialize for SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_state = Formation_FMS_DW.Merge.state;

  // SystemInitialize for SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_ax_cmd = Formation_FMS_DW.Merge.ax_cmd;

  // SystemInitialize for SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_ay_cmd = Formation_FMS_DW.Merge.ay_cmd;

  // SystemInitialize for SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_vh_cmd = Formation_FMS_DW.Merge.vh_cmd;
}

// Disable for referenced model: 'Formation_FMS'
void Formation_FMS::disable(void)
{
  // Disable for SwitchCase: '<S10>/Switch Case'
  Formation_FMS_DW.SwitchCase_ActiveSubsystem = -1;
}

// Output and update for referenced model: 'Formation_FMS'
void Formation_FMS::step(const uint32_T *rtu_Pilot_Cmd_timestamp, const uint32_T
  *rtu_Pilot_Cmd_mode, const uint32_T *rtu_Mission_Data_timestamp, const
  uint32_T *rtu_Mission_Data_type, const uint8_T *rtu_Mission_Data_valid_items,
  const real32_T rtu_Mission_Data_x[8], const real32_T rtu_Mission_Data_y[8],
  const real32_T rtu_Mission_Data_z[8], const real32_T rtu_Mission_Data_heading
  [8], const real32_T rtu_Mission_Data_ext1[8], const real32_T
  rtu_Mission_Data_ext2[8], const uint32_T *rtu_INS_Out_timestamp, const
  real32_T *rtu_INS_Out_phi, const real32_T *rtu_INS_Out_theta, const real32_T
  *rtu_INS_Out_psi, const real32_T *rtu_INS_Out_p, const real32_T *rtu_INS_Out_q,
  const real32_T *rtu_INS_Out_r, const real32_T rtu_INS_Out_quat[4], const
  real32_T *rtu_INS_Out_x_R, const real32_T *rtu_INS_Out_y_R, const real32_T
  *rtu_INS_Out_h_R, const real32_T *rtu_INS_Out_airspeed, const real32_T
  *rtu_INS_Out_ax, const real32_T *rtu_INS_Out_ay, const real32_T
  *rtu_INS_Out_az, const real32_T *rtu_INS_Out_vn, const real32_T
  *rtu_INS_Out_ve, const real32_T *rtu_INS_Out_vd, const uint32_T
  rtu_Formation_Cross_timestamp[3], const real32_T rtu_Formation_Cross_x_R[3],
  const real32_T rtu_Formation_Cross_y_R[3], const real32_T
  rtu_Formation_Cross_h_R[3], const real32_T rtu_Formation_Cross_vn[3], const
  real32_T rtu_Formation_Cross_ve[3], const real32_T rtu_Formation_Cross_vd[3],
  const real32_T rtu_Formation_Cross_left_time[3], uint32_T
  *rty_FMS_Out_timestamp, VehicleState *rty_FMS_Out_state, real32_T
  *rty_FMS_Out_ax_cmd, real32_T *rty_FMS_Out_ay_cmd, real32_T
  *rty_FMS_Out_vh_cmd, uint32_T *rty_Other_Mission_Data_timestam, uint32_T
  rty_Other_Mission_Data_type[3], uint8_T rty_Other_Mission_Data_valid_it[3],
  real32_T rty_Other_Mission_Data_x[24], real32_T rty_Other_Mission_Data_y[24],
  real32_T rty_Other_Mission_Data_z[24], real32_T
  rty_Other_Mission_Data_heading[24], real32_T rty_Other_Mission_Data_ext1[24],
  real32_T rty_Other_Mission_Data_ext2[24], real32_T *rty_Form_Single)
{
  int8_T rtAction;
  int8_T rtPrevAction;
  boolean_T b_x[2];
  boolean_T rtb_FixPtRelationalOperator_c;

  // BusCreator generated from: '<Root>/FMS State Machine'
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.timestamp =
    *rtu_INS_Out_timestamp;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.phi = *rtu_INS_Out_phi;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.theta = *rtu_INS_Out_theta;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.psi = *rtu_INS_Out_psi;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.p = *rtu_INS_Out_p;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.q = *rtu_INS_Out_q;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.r = *rtu_INS_Out_r;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.quat[0] = rtu_INS_Out_quat[0];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.quat[1] = rtu_INS_Out_quat[1];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.quat[2] = rtu_INS_Out_quat[2];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.quat[3] = rtu_INS_Out_quat[3];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.x_R = *rtu_INS_Out_x_R;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.y_R = *rtu_INS_Out_y_R;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.h_R = *rtu_INS_Out_h_R;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.airspeed =
    *rtu_INS_Out_airspeed;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.ax = *rtu_INS_Out_ax;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.ay = *rtu_INS_Out_ay;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.az = *rtu_INS_Out_az;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.vn = *rtu_INS_Out_vn;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.ve = *rtu_INS_Out_ve;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.vd = *rtu_INS_Out_vd;

  // BusCreator generated from: '<Root>/FMS State Machine'
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.timestamp[0] =
    rtu_Formation_Cross_timestamp[0];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.x_R[0] =
    rtu_Formation_Cross_x_R[0];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.y_R[0] =
    rtu_Formation_Cross_y_R[0];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.h_R[0] =
    rtu_Formation_Cross_h_R[0];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.vn[0] =
    rtu_Formation_Cross_vn[0];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.ve[0] =
    rtu_Formation_Cross_ve[0];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.vd[0] =
    rtu_Formation_Cross_vd[0];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.left_time[0] =
    rtu_Formation_Cross_left_time[0];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.timestamp[1] =
    rtu_Formation_Cross_timestamp[1];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.x_R[1] =
    rtu_Formation_Cross_x_R[1];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.y_R[1] =
    rtu_Formation_Cross_y_R[1];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.h_R[1] =
    rtu_Formation_Cross_h_R[1];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.vn[1] =
    rtu_Formation_Cross_vn[1];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.ve[1] =
    rtu_Formation_Cross_ve[1];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.vd[1] =
    rtu_Formation_Cross_vd[1];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.left_time[1] =
    rtu_Formation_Cross_left_time[1];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.timestamp[2] =
    rtu_Formation_Cross_timestamp[2];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.x_R[2] =
    rtu_Formation_Cross_x_R[2];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.y_R[2] =
    rtu_Formation_Cross_y_R[2];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.h_R[2] =
    rtu_Formation_Cross_h_R[2];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.vn[2] =
    rtu_Formation_Cross_vn[2];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.ve[2] =
    rtu_Formation_Cross_ve[2];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.vd[2] =
    rtu_Formation_Cross_vd[2];
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.left_time[2] =
    rtu_Formation_Cross_left_time[2];

  // BusCreator generated from: '<Root>/FMS State Machine'
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_m = *rtu_Mission_Data_timestamp;
  Formation_FMS_DW.BusConversion_InsertedFor_FMS_n = *rtu_Mission_Data_type;
  for (Formation_FMS_DW.i = 0; Formation_FMS_DW.i < 8; Formation_FMS_DW.i++) {
    Formation_FMS_DW.BusConversion_InsertedFor_FMSSt[Formation_FMS_DW.i] =
      rtu_Mission_Data_x[Formation_FMS_DW.i];
    Formation_FMS_DW.BusConversion_InsertedFor_FMS_k[Formation_FMS_DW.i] =
      rtu_Mission_Data_y[Formation_FMS_DW.i];
    Formation_FMS_DW.BusConversion_InsertedFor_FM_cx[Formation_FMS_DW.i] =
      rtu_Mission_Data_z[Formation_FMS_DW.i];
    Formation_FMS_DW.BusConversion_InsertedFor_FMS_b[Formation_FMS_DW.i] =
      rtu_Mission_Data_heading[Formation_FMS_DW.i];
    Formation_FMS_DW.BusConversion_InsertedFor_FM_pb[Formation_FMS_DW.i] =
      rtu_Mission_Data_ext1[Formation_FMS_DW.i];
    Formation_FMS_DW.BusConversion_InsertedFor_FM_cv[Formation_FMS_DW.i] =
      rtu_Mission_Data_ext2[Formation_FMS_DW.i];
  }

  // End of BusCreator generated from: '<Root>/FMS State Machine'

  // Outputs for Atomic SubSystem: '<Root>/CommandProcess'
  // RelationalOperator: '<S7>/FixPt Relational Operator' incorporates:
  //   UnitDelay: '<S7>/Delay Input1'
  //
  //  Block description for '<S7>/Delay Input1':
  //
  //   Store in Global RAM

  rtb_FixPtRelationalOperator_c = (*rtu_Pilot_Cmd_timestamp !=
    Formation_FMS_DW.DelayInput1_DSTATE);

  // DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
  if (rtb_FixPtRelationalOperator_c) {
    Formation_FMS_DW.DiscreteTimeIntegrator1_DSTATE = 0.0F;
  }

  // RelationalOperator: '<S8>/Compare' incorporates:
  //   Constant: '<S8>/Constant'

  rtb_FixPtRelationalOperator_c = (*rtu_Pilot_Cmd_mode != 0U);

  // Switch: '<S5>/Switch' incorporates:
  //   Constant: '<S6>/Constant'
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
  //   Logic: '<S5>/Logical Operator1'
  //   RelationalOperator: '<S6>/Compare'

  if (rtb_FixPtRelationalOperator_c &&
      (Formation_FMS_DW.DiscreteTimeIntegrator1_DSTATE < 0.5F)) {
    // Switch: '<S5>/Switch' incorporates:
    //   DataTypeConversion: '<S5>/Data Type Conversion2'

    Formation_FMS_DW.Switch = static_cast<PilotMode>(*rtu_Pilot_Cmd_mode);
  } else {
    // Switch: '<S5>/Switch' incorporates:
    //   Delay: '<S5>/Delay'

    Formation_FMS_DW.Switch = Formation_FMS_DW.Delay_DSTATE_j;
  }

  // End of Switch: '<S5>/Switch'

  // Update for UnitDelay: '<S7>/Delay Input1'
  //
  //  Block description for '<S7>/Delay Input1':
  //
  //   Store in Global RAM

  Formation_FMS_DW.DelayInput1_DSTATE = *rtu_Pilot_Cmd_timestamp;

  // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
  Formation_FMS_DW.DiscreteTimeIntegrator1_DSTATE += 0.02F;

  // Update for Delay: '<S5>/Delay'
  Formation_FMS_DW.Delay_DSTATE_j = Formation_FMS_DW.Switch;

  // End of Outputs for SubSystem: '<Root>/CommandProcess'

  // Chart: '<Root>/FMS State Machine' incorporates:
  //   Constant: '<Root>/ACCEPT_R'
  //   MATLAB Function: '<S154>/MATLAB Function'

  Formation_FMS_DW.Mission_Data_timestamp_prev =
    Formation_FMS_DW.Mission_Data_timestamp_start;
  Formation_FMS_DW.Mission_Data_timestamp_start =
    Formation_FMS_DW.BusConversion_InsertedFor_FMS_m;
  Formation_FMS_DW.mode_prev = Formation_FMS_DW.mode_start;
  Formation_FMS_DW.mode_start = Formation_FMS_DW.Switch;
  if (Formation_FMS_DW.is_active_c3_Formation_FMS == 0U) {
    boolean_T exitg1;
    Formation_FMS_DW.Mission_Data_timestamp_prev =
      Formation_FMS_DW.BusConversion_InsertedFor_FMS_m;
    Formation_FMS_DW.mode_prev = Formation_FMS_DW.Switch;
    Formation_FMS_DW.is_active_c3_Formation_FMS = 1U;
    b_x[0] = (Formation_FMS_DW.Switch == PilotMode::FormAssemble);
    b_x[1] = (Formation_FMS_DW.Switch == PilotMode::FormDisband);
    rtb_FixPtRelationalOperator_c = false;
    Formation_FMS_DW.i = 0;
    exitg1 = false;
    while ((!exitg1) && (Formation_FMS_DW.i < 2)) {
      if (b_x[Formation_FMS_DW.i]) {
        rtb_FixPtRelationalOperator_c = true;
        exitg1 = true;
      } else {
        Formation_FMS_DW.i++;
      }
    }

    if (rtb_FixPtRelationalOperator_c) {
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Formation;
      Format_enter_internal_Formation
        (&Formation_FMS_DW.BusConversion_InsertedFor_FMS_c,
         &Formation_FMS_DW.BusConversion_InsertedFor_FMS_p,
         &Formation_FMS_DW.Switch);
    } else {
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Standby;
      Formation_FMS_DW.Cmd_In.cur_waypoint[0] =
        Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.x_R;
      Formation_FMS_DW.Cmd_In.cur_waypoint[1] =
        Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.y_R;
      Formation_FMS_DW.Cmd_In.cur_waypoint[2] =
        Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.h_R;
      Formation_FMS_DW.state = VehicleState::Hold;
    }
  } else if ((Formation_FMS_DW.mode_prev != Formation_FMS_DW.mode_start) &&
             (Formation_FMS_DW.Switch != PilotMode::None)) {
    boolean_T exitg1;
    b_x[0] = (Formation_FMS_DW.Switch == PilotMode::FormAssemble);
    b_x[1] = (Formation_FMS_DW.Switch == PilotMode::FormDisband);
    rtb_FixPtRelationalOperator_c = false;
    Formation_FMS_DW.mask = 0;
    exitg1 = false;
    while ((!exitg1) && (Formation_FMS_DW.mask < 2)) {
      if (b_x[Formation_FMS_DW.mask]) {
        rtb_FixPtRelationalOperator_c = true;
        exitg1 = true;
      } else {
        Formation_FMS_DW.mask++;
      }
    }

    if (rtb_FixPtRelationalOperator_c) {
      Formation_exit_internal_Vehicle();
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Formation;
      Format_enter_internal_Formation
        (&Formation_FMS_DW.BusConversion_InsertedFor_FMS_c,
         &Formation_FMS_DW.BusConversion_InsertedFor_FMS_p,
         &Formation_FMS_DW.Switch);
    } else {
      Formation_exit_internal_Vehicle();
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Standby;
      Formation_FMS_DW.Cmd_In.cur_waypoint[0] =
        Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.x_R;
      Formation_FMS_DW.Cmd_In.cur_waypoint[1] =
        Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.y_R;
      Formation_FMS_DW.Cmd_In.cur_waypoint[2] =
        Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.h_R;
      Formation_FMS_DW.state = VehicleState::Hold;
    }
  } else if (Formation_FMS_DW.is_Vehicle == Formation_FMS_IN_Formation) {
    // Outputs for Function Call SubSystem: '<S3>/Vehicle.Formation.check_form_valid' 
    // MATLAB Function: '<S154>/MATLAB Function'
    Formation_FMS_DW.BusConversion_InsertedFor_FMS_m = 0U;
    for (Formation_FMS_DW.i = 0; Formation_FMS_DW.i < 3; Formation_FMS_DW.i++) {
      if (static_cast<uint32_T>(Formation_FMS_DW.i + 1) !=
          FORMATION_PARAM.UAV_ID) {
        Formation_FMS_DW.Reshape2_bi[0] =
          Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.x_R[Formation_FMS_DW.i]
          - Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.x_R;
        Formation_FMS_DW.Reshape2_bi[1] =
          Formation_FMS_DW.BusConversion_InsertedFor_FMS_p.y_R[Formation_FMS_DW.i]
          - Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.y_R;
        Formation_FMS_DW.scale = 1.29246971E-26F;
        Formation_FMS_DW.absxk = std::abs(Formation_FMS_DW.Reshape2_bi[0]);
        if (Formation_FMS_DW.absxk > 1.29246971E-26F) {
          Formation_FMS_DW.path_ratio = 1.0F;
          Formation_FMS_DW.scale = Formation_FMS_DW.absxk;
        } else {
          Formation_FMS_DW.t_f = Formation_FMS_DW.absxk / 1.29246971E-26F;
          Formation_FMS_DW.path_ratio = Formation_FMS_DW.t_f *
            Formation_FMS_DW.t_f;
        }

        Formation_FMS_DW.absxk = std::abs(Formation_FMS_DW.Reshape2_bi[1]);
        if (Formation_FMS_DW.absxk > Formation_FMS_DW.scale) {
          Formation_FMS_DW.t_f = Formation_FMS_DW.scale / Formation_FMS_DW.absxk;
          Formation_FMS_DW.path_ratio = Formation_FMS_DW.path_ratio *
            Formation_FMS_DW.t_f * Formation_FMS_DW.t_f + 1.0F;
          Formation_FMS_DW.scale = Formation_FMS_DW.absxk;
        } else {
          Formation_FMS_DW.t_f = Formation_FMS_DW.absxk / Formation_FMS_DW.scale;
          Formation_FMS_DW.path_ratio += Formation_FMS_DW.t_f *
            Formation_FMS_DW.t_f;
        }

        if (Formation_FMS_DW.scale * std::sqrt(Formation_FMS_DW.path_ratio) <=
            FORMATION_PARAM.FORM_RADIUS) {
          Formation_FMS_DW.BusConversion_InsertedFor_FMS_m |= 1U <<
            Formation_FMS_DW.i;
        } else {
          Formation_FMS_DW.BusConversion_InsertedFor_FMS_m &= ~(1U <<
            Formation_FMS_DW.i);
        }
      }
    }

    Formation_FMS_DW.Cmd_In.form_valid =
      Formation_FMS_DW.BusConversion_InsertedFor_FMS_m;

    // End of Outputs for SubSystem: '<S3>/Vehicle.Formation.check_form_valid'
    switch (Formation_FMS_DW.is_Formation) {
     case Formation_FMS_IN_FormAssemble:
      {
        switch (Formation_FMS_DW.is_FormAssemble) {
         case Formation_FMS_IN_NextWP:
          {
            if (Formation_FMS_DW.wp_index <= *rtu_Mission_Data_valid_items) {
              boolean_T exitg1;
              Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_Waypoint;
              Formation_FMS_DW.Cmd_In.cur_waypoint[0] =
                Formation_FMS_DW.Cmd_In.sp_waypoint[0];
              Formation_FMS_DW.Cmd_In.cur_waypoint[1] =
                Formation_FMS_DW.Cmd_In.sp_waypoint[1];
              Formation_FMS_DW.Cmd_In.cur_waypoint[2] =
                Formation_FMS_DW.Cmd_In.sp_waypoint[2];
              Formation_FMS_DW.Cmd_In.sp_waypoint[0] =
                Formation_FMS_DW.BusConversion_InsertedFor_FMSSt[Formation_FMS_DW.wp_index
                - 1];
              Formation_FMS_DW.Cmd_In.sp_waypoint[1] =
                Formation_FMS_DW.BusConversion_InsertedFor_FMS_k[Formation_FMS_DW.wp_index
                - 1];
              Formation_FMS_DW.Cmd_In.sp_waypoint[2] =
                Formation_FMS_DW.BusConversion_InsertedFor_FM_cx[Formation_FMS_DW.wp_index
                - 1];
              b_x[0] = (Formation_FMS_DW.Cmd_In.cur_waypoint[0] ==
                        Formation_FMS_DW.Cmd_In.sp_waypoint[0]);
              b_x[1] = (Formation_FMS_DW.Cmd_In.cur_waypoint[1] ==
                        Formation_FMS_DW.Cmd_In.sp_waypoint[1]);
              rtb_FixPtRelationalOperator_c = true;
              Formation_FMS_DW.i = 0;
              exitg1 = false;
              while ((!exitg1) && (Formation_FMS_DW.i < 2)) {
                if (!b_x[Formation_FMS_DW.i]) {
                  rtb_FixPtRelationalOperator_c = false;
                  exitg1 = true;
                } else {
                  Formation_FMS_DW.i++;
                }
              }

              if (rtb_FixPtRelationalOperator_c) {
                Formation_FMS_DW.Cmd_In.sp_waypoint[0] += 0.01F;
                Formation_FMS_DW.Cmd_In.sp_waypoint[1] += 0.01F;
              }

              for (Formation_FMS_DW.i = 0; Formation_FMS_DW.i <= 0;
                   Formation_FMS_DW.i += 4) {
                __m128 tmp;
                tmp = _mm_loadu_ps
                  (&Formation_FMS_DW.BusConversion_InsertedFor_FMSSt[Formation_FMS_DW.i]);
                _mm_storeu_ps(&Formation_FMS_DW.waypoints[Formation_FMS_DW.i],
                              tmp);
                tmp = _mm_loadu_ps
                  (&Formation_FMS_DW.BusConversion_InsertedFor_FMS_k[Formation_FMS_DW.i]);
                _mm_storeu_ps(&Formation_FMS_DW.waypoints[Formation_FMS_DW.i + 5],
                              tmp);
                tmp = _mm_loadu_ps
                  (&Formation_FMS_DW.BusConversion_InsertedFor_FMS_b[Formation_FMS_DW.i]);
                _mm_storeu_ps(&Formation_FMS_DW.waypoints[Formation_FMS_DW.i +
                              10], _mm_mul_ps(_mm_set1_ps(0.0174532924F), tmp));
                tmp = _mm_loadu_ps
                  (&Formation_FMS_DW.BusConversion_InsertedFor_FM_pb[Formation_FMS_DW.i]);
                _mm_storeu_ps(&Formation_FMS_DW.waypoints[Formation_FMS_DW.i +
                              15], tmp);
                tmp = _mm_loadu_ps
                  (&Formation_FMS_DW.BusConversion_InsertedFor_FM_cv[Formation_FMS_DW.i]);
                _mm_storeu_ps(&Formation_FMS_DW.waypoints[Formation_FMS_DW.i +
                              20], tmp);
              }

              for (Formation_FMS_DW.i = 4; Formation_FMS_DW.i < 5;
                   Formation_FMS_DW.i++) {
                Formation_FMS_DW.waypoints[Formation_FMS_DW.i] =
                  Formation_FMS_DW.BusConversion_InsertedFor_FMSSt[Formation_FMS_DW.i];
                Formation_FMS_DW.waypoints[Formation_FMS_DW.i + 5] =
                  Formation_FMS_DW.BusConversion_InsertedFor_FMS_k[Formation_FMS_DW.i];
                Formation_FMS_DW.waypoints[Formation_FMS_DW.i + 10] =
                  0.0174532924F *
                  Formation_FMS_DW.BusConversion_InsertedFor_FMS_b[Formation_FMS_DW.i];
                Formation_FMS_DW.waypoints[Formation_FMS_DW.i + 15] =
                  Formation_FMS_DW.BusConversion_InsertedFor_FM_pb[Formation_FMS_DW.i];
                Formation_FMS_DW.waypoints[Formation_FMS_DW.i + 20] =
                  Formation_FMS_DW.BusConversion_InsertedFor_FM_cv[Formation_FMS_DW.i];
              }
            } else {
              Formation_FMS_DW.is_FormAssemble = Formation_FM_IN_NO_ACTIVE_CHILD;
              Formation_FMS_DW.is_Formation = Formation_FMS_IN_FormMission;
              Formation_FMS_DW.Cmd_In.sp_waypoint[0] =
                Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.x_R;
              Formation_FMS_DW.Cmd_In.sp_waypoint[1] =
                Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.y_R;
              Formation_FMS_DW.Cmd_In.sp_waypoint[2] =
                Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.h_R;
              Formation_FMS_DW.state = VehicleState::FormMission;
              Formation_FMS_DW.is_FormMission = Formation_FMS_IN_NextWP_d;
            }
          }
          break;

         case Formation_FMS_IN_WaitForUpdate:
          if ((Formation_FMS_DW.Mission_Data_timestamp_prev !=
               Formation_FMS_DW.Mission_Data_timestamp_start) &&
              (Formation_FMS_DW.BusConversion_InsertedFor_FMS_n == 1U)) {
            Formation_FMS_DW.wp_index = 1U;
            Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_NextWP;
            Formation_FMS_DW.Cmd_In.l1_enable = true;
          }
          break;

         default:
          {
            // case IN_Waypoint:
            Formation_FMS_DW.P_mr[0] =
              Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.x_R -
              Formation_FMS_DW.Cmd_In.sp_waypoint[0];
            Formation_FMS_DW.P_mr[1] =
              Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.y_R -
              Formation_FMS_DW.Cmd_In.sp_waypoint[1];
            if (norm_7i8u8z8R(Formation_FMS_DW.P_mr) <= FMS_PARAM.ACCEPT_R) {
              Formation_FMS_DW.BusConversion_InsertedFor_FMS_m =
                Formation_FMS_DW.wp_index + 1U;
              if (Formation_FMS_DW.wp_index + 1U > 65535U) {
                Formation_FMS_DW.BusConversion_InsertedFor_FMS_m = 65535U;
              }

              Formation_FMS_DW.wp_index = static_cast<uint16_T>
                (Formation_FMS_DW.BusConversion_InsertedFor_FMS_m);
              Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_NextWP;
              Formation_FMS_DW.Cmd_In.l1_enable = true;
            } else {
              uint16_T wp_index_f;
              Formation_FMS_DW.BusConversion_InsertedFor_FMS_m =
                Formation_FMS_DW.wp_index - 1U;
              if (Formation_FMS_DW.wp_index - 1U > Formation_FMS_DW.wp_index) {
                Formation_FMS_DW.BusConversion_InsertedFor_FMS_m = 0U;
              }

              wp_index_f = static_cast<uint16_T>
                (Formation_FMS_DW.BusConversion_InsertedFor_FMS_m);
              if (static_cast<uint16_T>
                  (Formation_FMS_DW.BusConversion_InsertedFor_FMS_m) < 1) {
                wp_index_f = 1U;
              }

              Formation_FMS_DW.pose[0] =
                Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.x_R;
              Formation_FMS_DW.pose[1] =
                Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.y_R;
              Formation_FMS_DW.pose[2] =
                Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.psi;

              // Outputs for Function Call SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPathRatio' 
              // MATLAB Function: '<S153>/Dubins Closest Point'
              Formati_getMinDistanceAtSegment(Formation_FMS_DW.waypoints,
                Formation_FMS_DW.pose, wp_index_f, &Formation_FMS_DW.t_f,
                &Formation_FMS_DW.scale);
              Formation_FMS_DW.BusConversion_InsertedFor_FMS_m = wp_index_f + 1U;
              if (wp_index_f + 1U > 65535U) {
                Formation_FMS_DW.BusConversion_InsertedFor_FMS_m = 65535U;
              }

              Formati_getMinDistanceAtSegment(Formation_FMS_DW.waypoints,
                Formation_FMS_DW.pose, static_cast<uint16_T>
                (Formation_FMS_DW.BusConversion_InsertedFor_FMS_m),
                &Formation_FMS_DW.path_ratio, &Formation_FMS_DW.absxk);
              if (Formation_FMS_DW.t_f <= Formation_FMS_DW.path_ratio) {
                Formation_FMS_DW.i = static_cast<int32_T>(wp_index_f -
                  /*MW:OvSatOk*/ 1U);
                if (wp_index_f - 1U > wp_index_f) {
                  Formation_FMS_DW.i = 0;
                }

                if (static_cast<uint16_T>(Formation_FMS_DW.i) < 1) {
                  Formation_FMS_DW.t_f = 0.0F;
                } else {
                  Formation_FMS_DW.mask = static_cast<uint16_T>
                    (Formation_FMS_DW.i);
                  Formation_FMS_DW.t_f = Formation_FMS_DW.waypoints[20];
                  for (Formation_FMS_DW.i = 2; Formation_FMS_DW.i <=
                       Formation_FMS_DW.mask; Formation_FMS_DW.i++) {
                    Formation_FMS_DW.t_f +=
                      Formation_FMS_DW.waypoints[Formation_FMS_DW.i + 19];
                  }
                }

                Formation_FMS_DW.path_ratio =
                  (Formation_FMS_DW.waypoints[wp_index_f + 19] *
                   Formation_FMS_DW.scale + Formation_FMS_DW.t_f) /
                  Formation_FMS_DW.waypoints[24];
              } else {
                Formation_FMS_DW.i = wp_index_f;
                Formation_FMS_DW.t_f = Formation_FMS_DW.waypoints[20];
                for (Formation_FMS_DW.mask = 2; Formation_FMS_DW.mask <=
                     Formation_FMS_DW.i; Formation_FMS_DW.mask++) {
                  Formation_FMS_DW.t_f +=
                    Formation_FMS_DW.waypoints[Formation_FMS_DW.mask + 19];
                }

                Formation_FMS_DW.BusConversion_InsertedFor_FMS_m = wp_index_f +
                  1U;
                if (wp_index_f + 1U > 65535U) {
                  Formation_FMS_DW.BusConversion_InsertedFor_FMS_m = 65535U;
                }

                Formation_FMS_DW.path_ratio = (Formation_FMS_DW.waypoints[
                  static_cast<int32_T>
                  (Formation_FMS_DW.BusConversion_InsertedFor_FMS_m) + 19] *
                  Formation_FMS_DW.absxk + Formation_FMS_DW.t_f) /
                  Formation_FMS_DW.waypoints[24];
              }

              // End of MATLAB Function: '<S153>/Dubins Closest Point'
              // End of Outputs for SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPathRatio' 
              Formation_FMS_DW.scale = 1.29246971E-26F;
              Formation_FMS_DW.absxk = std::abs
                (Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.vn);
              if (Formation_FMS_DW.absxk > 1.29246971E-26F) {
                Formation_FMS_DW.Multiply1_f = 1.0F;
                Formation_FMS_DW.scale = Formation_FMS_DW.absxk;
              } else {
                Formation_FMS_DW.t_f = Formation_FMS_DW.absxk / 1.29246971E-26F;
                Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.t_f *
                  Formation_FMS_DW.t_f;
              }

              Formation_FMS_DW.absxk = std::abs
                (Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.ve);
              if (Formation_FMS_DW.absxk > Formation_FMS_DW.scale) {
                Formation_FMS_DW.t_f = Formation_FMS_DW.scale /
                  Formation_FMS_DW.absxk;
                Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.Multiply1_f *
                  Formation_FMS_DW.t_f * Formation_FMS_DW.t_f + 1.0F;
                Formation_FMS_DW.scale = Formation_FMS_DW.absxk;
              } else {
                Formation_FMS_DW.t_f = Formation_FMS_DW.absxk /
                  Formation_FMS_DW.scale;
                Formation_FMS_DW.Multiply1_f += Formation_FMS_DW.t_f *
                  Formation_FMS_DW.t_f;
              }

              *rty_Form_Single = (1.0F - Formation_FMS_DW.path_ratio) *
                Formation_FMS_DW.BusConversion_InsertedFor_FM_cv[4] /
                (Formation_FMS_DW.scale * std::sqrt(Formation_FMS_DW.Multiply1_f));
            }
          }
          break;
        }
      }
      break;

     case Formation_FMS_IN_FormDisband:
      break;

     case Formation_FMS_IN_FormMission:
      if (Formation_FMS_DW.Switch == PilotMode::FormDisband) {
        Formation_FMS_DW.is_FormMission = Formation_FM_IN_NO_ACTIVE_CHILD;
        Formation_FMS_DW.is_Formation = Formation_FMS_IN_FormDisband;
        Formation_FMS_DW.state = VehicleState::FormDisband;
      } else if ((Formation_FMS_DW.Mission_Data_timestamp_prev !=
                  Formation_FMS_DW.Mission_Data_timestamp_start) &&
                 (Formation_FMS_DW.BusConversion_InsertedFor_FMS_n == 3U)) {
        Formation_FMS_DW.wp_index = 1U;
        Formation_FMS_DW.is_FormMission = Formation_FMS_IN_NextWP_d;
      } else {
        switch (Formation_FMS_DW.is_FormMission) {
         case Formation_FMS_IN_Follower:
         case Formation_FMS_IN_Forward:
          break;

         case Formation_FMS_IN_NextWP_d:
          if (FORMATION_PARAM.UAV_ID != 1U) {
            Formation_FMS_DW.is_FormMission = Formation_FMS_IN_Follower;
            Formation_FMS_DW.Cmd_In.l1_enable = false;
          } else if (Formation_FMS_DW.wp_index <= *rtu_Mission_Data_valid_items)
          {
            Formation_FMS_DW.is_FormMission = Formation_FMS_IN_Waypoint_g;
            Formation_FMS_DW.Cmd_In.cur_waypoint[0] =
              Formation_FMS_DW.Cmd_In.sp_waypoint[0];
            Formation_FMS_DW.Cmd_In.cur_waypoint[1] =
              Formation_FMS_DW.Cmd_In.sp_waypoint[1];
            Formation_FMS_DW.Cmd_In.cur_waypoint[2] =
              Formation_FMS_DW.Cmd_In.sp_waypoint[2];
            Formation_FMS_DW.Cmd_In.sp_waypoint[0] =
              Formation_FMS_DW.BusConversion_InsertedFor_FMSSt[Formation_FMS_DW.wp_index
              - 1];
            Formation_FMS_DW.Cmd_In.sp_waypoint[1] =
              Formation_FMS_DW.BusConversion_InsertedFor_FMS_k[Formation_FMS_DW.wp_index
              - 1];
            Formation_FMS_DW.Cmd_In.sp_waypoint[2] =
              Formation_FMS_DW.BusConversion_InsertedFor_FM_cx[Formation_FMS_DW.wp_index
              - 1];
            Formation_FMS_DW.Cmd_In.l1_enable = true;
          } else {
            Formation_FMS_DW.is_FormMission = Formation_FMS_IN_Forward;
            Formation_FMS_DW.Cmd_In.l1_enable = false;
          }
          break;

         default:
          // case IN_Waypoint:
          Formation_FMS_DW.P_mr[0] =
            Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.x_R -
            Formation_FMS_DW.Cmd_In.sp_waypoint[0];
          Formation_FMS_DW.P_mr[1] =
            Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.y_R -
            Formation_FMS_DW.Cmd_In.sp_waypoint[1];
          if (norm_7i8u8z8R(Formation_FMS_DW.P_mr) <= FMS_PARAM.ACCEPT_R) {
            Formation_FMS_DW.BusConversion_InsertedFor_FMS_m =
              Formation_FMS_DW.wp_index + 1U;
            if (Formation_FMS_DW.wp_index + 1U > 65535U) {
              Formation_FMS_DW.BusConversion_InsertedFor_FMS_m = 65535U;
            }

            Formation_FMS_DW.wp_index = static_cast<uint16_T>
              (Formation_FMS_DW.BusConversion_InsertedFor_FMS_m);
            Formation_FMS_DW.is_FormMission = Formation_FMS_IN_NextWP_d;
          }
          break;
        }
      }
      break;

     default:
      // case IN_InvalidMode:
      Formation_FMS_DW.is_Formation = Formation_FM_IN_NO_ACTIVE_CHILD;
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Standby;
      Formation_FMS_DW.Cmd_In.cur_waypoint[0] =
        Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.x_R;
      Formation_FMS_DW.Cmd_In.cur_waypoint[1] =
        Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.y_R;
      Formation_FMS_DW.Cmd_In.cur_waypoint[2] =
        Formation_FMS_DW.BusConversion_InsertedFor_FMS_c.h_R;
      Formation_FMS_DW.state = VehicleState::Hold;
      break;
    }
  } else {
    // case IN_Standby:
  }

  // End of Chart: '<Root>/FMS State Machine'

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_x[0],
              &Formation_FMS_DW.Other_Mission_Data.x[0], 24U * sizeof(real32_T));

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_y[0],
              &Formation_FMS_DW.Other_Mission_Data.y[0], 24U * sizeof(real32_T));

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_z[0],
              &Formation_FMS_DW.Other_Mission_Data.z[0], 24U * sizeof(real32_T));

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_heading[0],
              &Formation_FMS_DW.Other_Mission_Data.heading[0], 24U * sizeof
              (real32_T));

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_ext1[0],
              &Formation_FMS_DW.Other_Mission_Data.ext1[0], 24U * sizeof
              (real32_T));

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_ext2[0],
              &Formation_FMS_DW.Other_Mission_Data.ext2[0], 24U * sizeof
              (real32_T));

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.pose[0] = rtu_Formation_Cross_vd[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.ve[0] = rtu_Formation_Cross_ve[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.t_f = rtu_Formation_Cross_vn[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.absxk = rtu_Formation_Cross_h_R[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.rtb_y_R_idx_0 = rtu_Formation_Cross_y_R[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.rtb_x_R_idx_0 = rtu_Formation_Cross_x_R[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.pose[1] = rtu_Formation_Cross_vd[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.ve[1] = rtu_Formation_Cross_ve[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.rtb_vn_idx_1 = rtu_Formation_Cross_vn[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.path_ratio = rtu_Formation_Cross_h_R[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.rtb_y_R_idx_1 = rtu_Formation_Cross_y_R[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.rtb_x_R_idx_1 = rtu_Formation_Cross_x_R[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.pose[2] = rtu_Formation_Cross_vd[2];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.ve[2] = rtu_Formation_Cross_ve[2];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.Multiply1_f = rtu_Formation_Cross_vn[2];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.scale = rtu_Formation_Cross_h_R[2];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.rtb_y_R_idx_2 = rtu_Formation_Cross_y_R[2];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_DW.rtb_x_R_idx_2 = rtu_Formation_Cross_x_R[2];

  // SwitchCase: '<S10>/Switch Case' incorporates:
  //   MATLAB Function: '<S45>/Calc_Position_Velocity_Setpoint'
  //   Merge: '<S10>/Merge'
  //   Product: '<S149>/Divide'
  //   Product: '<S150>/Divide'

  rtPrevAction = Formation_FMS_DW.SwitchCase_ActiveSubsystem;
  switch (Formation_FMS_DW.state) {
   case VehicleState::FormMission:
    rtAction = 0;
    break;

   case VehicleState::FormAssemble:
    rtAction = 1;
    break;

   case VehicleState::Hold:
    rtAction = 2;
    break;

   default:
    rtAction = 3;
    break;
  }

  Formation_FMS_DW.SwitchCase_ActiveSubsystem = rtAction;
  switch (rtAction) {
   case 0:
    // Outputs for IfAction SubSystem: '<S10>/FormMission' incorporates:
    //   ActionPort: '<S13>/Action Port'

    // RelationalOperator: '<S40>/FixPt Relational Operator' incorporates:
    //   UnitDelay: '<S40>/Delay Input1'
    //
    //  Block description for '<S40>/Delay Input1':
    //
    //   Store in Global RAM

    rtb_FixPtRelationalOperator_c = (Formation_FMS_DW.wp_index !=
      Formation_FMS_DW.DelayInput1_DSTATE_d);

    // Outputs for Resettable SubSystem: '<S13>/FormMission_SubSystem' incorporates:
    //   ResetPort: '<S41>/Reset'

    if (rtb_FixPtRelationalOperator_c &&
        (Formation_FMS_PrevZCX.FormMission_SubSystem_Reset_ZCE != POS_ZCSIG)) {
      // InitializeConditions for Delay: '<S115>/Delay'
      Formation_FMS_DW.icLoad_k = true;

      // InitializeConditions for DiscreteIntegrator: '<S97>/Integrator'
      Formation_FMS_DW.Integrator_DSTATE = 0.0F;
    }

    Formation_FMS_PrevZCX.FormMission_SubSystem_Reset_ZCE =
      rtb_FixPtRelationalOperator_c;

    // SignalConversion generated from: '<S43>/Vector Concatenate'
    Formation_FMS_DW.xyz_O_nx3[0] = Formation_FMS_DW.rtb_x_R_idx_0;

    // SignalConversion generated from: '<S43>/Vector Concatenate'
    Formation_FMS_DW.xyz_O_nx3[3] = Formation_FMS_DW.rtb_y_R_idx_0;

    // SignalConversion generated from: '<S43>/Vector Concatenate'
    Formation_FMS_DW.xyz_O_nx3[6] = Formation_FMS_DW.absxk;

    // SignalConversion generated from: '<S43>/Vector Concatenate1'
    Formation_FMS_DW.vNED_O_nx3[0] = Formation_FMS_DW.t_f;

    // SignalConversion generated from: '<S43>/Vector Concatenate1'
    Formation_FMS_DW.vNED_O_nx3[3] = Formation_FMS_DW.ve[0];

    // SignalConversion generated from: '<S43>/Vector Concatenate1'
    Formation_FMS_DW.vNED_O_nx3[6] = Formation_FMS_DW.pose[0];
    Formation_FMS_DW.ve[0] = 0.0F;
    Formation_FMS_DW.pose[0] = 0.0F;

    // SignalConversion generated from: '<S43>/Vector Concatenate' incorporates:
    //   MATLAB Function: '<S45>/Calc_Position_Velocity_Setpoint'

    Formation_FMS_DW.xyz_O_nx3[1] = Formation_FMS_DW.rtb_x_R_idx_1;

    // SignalConversion generated from: '<S43>/Vector Concatenate'
    Formation_FMS_DW.xyz_O_nx3[4] = Formation_FMS_DW.rtb_y_R_idx_1;

    // SignalConversion generated from: '<S43>/Vector Concatenate'
    Formation_FMS_DW.xyz_O_nx3[7] = Formation_FMS_DW.path_ratio;

    // SignalConversion generated from: '<S43>/Vector Concatenate1'
    Formation_FMS_DW.vNED_O_nx3[1] = Formation_FMS_DW.rtb_vn_idx_1;

    // SignalConversion generated from: '<S43>/Vector Concatenate1'
    Formation_FMS_DW.vNED_O_nx3[4] = Formation_FMS_DW.ve[1];

    // SignalConversion generated from: '<S43>/Vector Concatenate1'
    Formation_FMS_DW.vNED_O_nx3[7] = Formation_FMS_DW.pose[1];
    Formation_FMS_DW.ve[1] = 0.0F;
    Formation_FMS_DW.pose[1] = 0.0F;

    // SignalConversion generated from: '<S43>/Vector Concatenate' incorporates:
    //   MATLAB Function: '<S45>/Calc_Position_Velocity_Setpoint'

    Formation_FMS_DW.xyz_O_nx3[2] = Formation_FMS_DW.rtb_x_R_idx_2;

    // SignalConversion generated from: '<S43>/Vector Concatenate'
    Formation_FMS_DW.xyz_O_nx3[5] = Formation_FMS_DW.rtb_y_R_idx_2;

    // SignalConversion generated from: '<S43>/Vector Concatenate'
    Formation_FMS_DW.xyz_O_nx3[8] = Formation_FMS_DW.scale;

    // SignalConversion generated from: '<S43>/Vector Concatenate1'
    Formation_FMS_DW.vNED_O_nx3[2] = Formation_FMS_DW.Multiply1_f;

    // SignalConversion generated from: '<S43>/Vector Concatenate1'
    Formation_FMS_DW.vNED_O_nx3[5] = Formation_FMS_DW.ve[2];

    // SignalConversion generated from: '<S43>/Vector Concatenate1'
    Formation_FMS_DW.vNED_O_nx3[8] = Formation_FMS_DW.pose[2];
    Formation_FMS_DW.ve[2] = 0.0F;
    Formation_FMS_DW.pose[2] = 0.0F;

    // MATLAB Function: '<S45>/Calc_Position_Velocity_Setpoint' incorporates:
    //   Concatenate: '<S43>/Vector Concatenate'
    //   Concatenate: '<S43>/Vector Concatenate1'

    Formation_FMS_DW.scale = 0.0F;
    for (Formation_FMS_DW.i = 0; Formation_FMS_DW.i < 3; Formation_FMS_DW.i++) {
      if ((1U << Formation_FMS_DW.i & Formation_FMS_DW.Cmd_In.form_valid) != 0U)
      {
        Formation_FMS_DW.mask = (3 * Formation_FMS_DW.i + static_cast<int32_T>
          (FORMATION_PARAM.UAV_ID)) - 1;
        Formation_FMS_DW.d = FORMATION_PARAM.ADJ_MARTIX[Formation_FMS_DW.mask];
        if (!(Formation_FMS_DW.d == 0.0)) {
          Formation_FMS_DW.t_f = rt_atan2f_snf
            (Formation_FMS_DW.vNED_O_nx3[Formation_FMS_DW.i + 3],
             Formation_FMS_DW.vNED_O_nx3[Formation_FMS_DW.i]);
          Formation_FMS_DW.absxk = std::sin(Formation_FMS_DW.t_f);
          Formation_FMS_DW.t_f = std::cos(Formation_FMS_DW.t_f);
          Formation_FMS_DW.t[0] = Formation_FMS_DW.t_f;
          Formation_FMS_DW.t[3] = -Formation_FMS_DW.absxk;
          Formation_FMS_DW.t[6] = 0.0F;
          Formation_FMS_DW.t[1] = Formation_FMS_DW.absxk;
          Formation_FMS_DW.t[4] = Formation_FMS_DW.t_f;
          Formation_FMS_DW.t[7] = 0.0F;
          Formation_FMS_DW.t[2] = 0.0F;
          Formation_FMS_DW.t[5] = 0.0F;
          Formation_FMS_DW.t[8] = 1.0F;
          Formation_FMS_DW.Multiply1_f = static_cast<real32_T>
            (FORMATION_PARAM.REL_X_MATRIX[Formation_FMS_DW.mask]);
          Formation_FMS_DW.rtb_y_R_idx_0 = static_cast<real32_T>
            (FORMATION_PARAM.REL_Y_MATRIX[Formation_FMS_DW.mask]);
          Formation_FMS_DW.rtb_x_R_idx_0 = static_cast<real32_T>
            (FORMATION_PARAM.REL_Z_MATRIX[Formation_FMS_DW.mask]);
          for (Formation_FMS_DW.mask = 0; Formation_FMS_DW.mask < 3;
               Formation_FMS_DW.mask++) {
            Formation_FMS_DW.pose_tmp = 3 * Formation_FMS_DW.mask +
              Formation_FMS_DW.i;
            Formation_FMS_DW.pose[Formation_FMS_DW.mask] +=
              (((Formation_FMS_DW.t[Formation_FMS_DW.mask + 3] *
                 Formation_FMS_DW.rtb_y_R_idx_0 +
                 Formation_FMS_DW.t[Formation_FMS_DW.mask] *
                 Formation_FMS_DW.Multiply1_f) +
                Formation_FMS_DW.t[Formation_FMS_DW.mask + 6] *
                Formation_FMS_DW.rtb_x_R_idx_0) +
               Formation_FMS_DW.xyz_O_nx3[Formation_FMS_DW.pose_tmp]) *
              static_cast<real32_T>(Formation_FMS_DW.d);
            Formation_FMS_DW.ve[Formation_FMS_DW.mask] +=
              Formation_FMS_DW.vNED_O_nx3[Formation_FMS_DW.pose_tmp] *
              static_cast<real32_T>(Formation_FMS_DW.d);
          }

          Formation_FMS_DW.scale++;
        }
      }
    }

    if (Formation_FMS_DW.scale != 0.0F) {
      Formation_FMS_DW.pose[0] = Formation_FMS_DW.pose[0] /
        Formation_FMS_DW.scale - Formation_FMS_DW.xyz_O_nx3[static_cast<int32_T>
        (FORMATION_PARAM.UAV_ID) - 1];
      Formation_FMS_DW.ve[0] /= Formation_FMS_DW.scale;
      Formation_FMS_DW.pose[1] = Formation_FMS_DW.pose[1] /
        Formation_FMS_DW.scale - Formation_FMS_DW.xyz_O_nx3[static_cast<int32_T>
        (FORMATION_PARAM.UAV_ID) + 2];
      Formation_FMS_DW.ve[1] /= Formation_FMS_DW.scale;
      Formation_FMS_DW.pose[2] = Formation_FMS_DW.pose[2] /
        Formation_FMS_DW.scale - Formation_FMS_DW.xyz_O_nx3[static_cast<int32_T>
        (FORMATION_PARAM.UAV_ID) + 5];
    } else {
      Formation_FMS_DW.ve[0] = Formation_FMS_DW.vNED_O_nx3[static_cast<int32_T>
        (FORMATION_PARAM.UAV_ID) - 1];
      Formation_FMS_DW.ve[1] = Formation_FMS_DW.vNED_O_nx3[static_cast<int32_T>
        (FORMATION_PARAM.UAV_ID) + 2];
    }

    // Math: '<S58>/Math Function' incorporates:
    //   Math: '<S51>/Square'
    //   Math: '<S53>/Math Function'
    //   Switch: '<S41>/Switch'

    Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.ve[0] *
      Formation_FMS_DW.ve[0];
    Formation_FMS_DW.rtb_x_R_idx_0 = Formation_FMS_DW.ve[1] *
      Formation_FMS_DW.ve[1];

    // Sum: '<S58>/Sum of Elements' incorporates:
    //   Math: '<S58>/Math Function'

    Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.rtb_y_R_idx_0 +
      Formation_FMS_DW.rtb_x_R_idx_0;

    // Math: '<S58>/Math Function1'
    //
    //  About '<S58>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_DW.Multiply1_f < 0.0F) {
      Formation_FMS_DW.Multiply1_f = -std::sqrt(std::abs
        (Formation_FMS_DW.Multiply1_f));
    } else {
      Formation_FMS_DW.Multiply1_f = std::sqrt(Formation_FMS_DW.Multiply1_f);
    }

    // End of Math: '<S58>/Math Function1'

    // Switch: '<S58>/Switch' incorporates:
    //   Constant: '<S58>/Constant'
    //   Product: '<S58>/Product'
    //   Switch: '<S41>/Switch'

    if (Formation_FMS_DW.Multiply1_f > 0.0F) {
      Formation_FMS_DW.t_f = Formation_FMS_DW.ve[0];
      Formation_FMS_DW.rtb_vn_idx_1 = Formation_FMS_DW.ve[1];
    } else {
      Formation_FMS_DW.t_f = Formation_FMS_DW.ve[0] * 0.0F;
      Formation_FMS_DW.rtb_vn_idx_1 = Formation_FMS_DW.ve[1] * 0.0F;
      Formation_FMS_DW.Multiply1_f = 1.0F;
    }

    // End of Switch: '<S58>/Switch'

    // SignalConversion generated from: '<S52>/Square'
    Formation_FMS_DW.TmpSignalConversionAtSqua_n[0] = *rtu_INS_Out_vn;
    Formation_FMS_DW.TmpSignalConversionAtSqua_n[1] = *rtu_INS_Out_ve;

    // Reshape: '<S118>/Reshape2'
    Formation_FMS_DW.Reshape2_bi[0] = *rtu_INS_Out_x_R;
    Formation_FMS_DW.Reshape2_bi[1] = *rtu_INS_Out_y_R;

    // MATLAB Function: '<S119>/NearbyRefWP' incorporates:
    //   Constant: '<S117>/L1'

    Formation_FMS_NearbyRefWP(&Formation_FMS_DW.Cmd_In.sp_waypoint[0],
      Formation_FMS_DW.Reshape2_bi, FMS_PARAM.L1, Formation_FMS_DW.P_c,
      &Formation_FMS_DW.scale);

    // MATLAB Function: '<S119>/SearchL1RefWP' incorporates:
    //   Constant: '<S117>/L1'

    Formation_FMS_SearchL1RefWP(&Formation_FMS_DW.Cmd_In.cur_waypoint[0],
      &Formation_FMS_DW.Cmd_In.sp_waypoint[0], Formation_FMS_DW.Reshape2_bi,
      FMS_PARAM.L1, Formation_FMS_DW.P_mr, &Formation_FMS_DW.absxk);

    // MATLAB Function: '<S119>/OutRegionRegWP'
    Formation_FMS_OutRegionRegWP(&Formation_FMS_DW.Cmd_In.cur_waypoint[0],
      &Formation_FMS_DW.Cmd_In.sp_waypoint[0], Formation_FMS_DW.Reshape2_bi,
      Formation_FMS_DW.P_b);

    // Delay: '<S115>/Delay' incorporates:
    //   Constant: '<S115>/Constant'

    if (Formation_FMS_DW.icLoad_k) {
      Formation_FMS_DW.Delay_DSTATE_o = FMS_PARAM.FW_HEIGHT_TRIM;
    }

    // Product: '<S58>/Divide'
    Formation_FMS_DW.rtb_x_R_idx_1 = Formation_FMS_DW.t_f /
      Formation_FMS_DW.Multiply1_f;

    // Math: '<S56>/Square' incorporates:
    //   Math: '<S128>/Square'
    //   Math: '<S129>/Math Function'
    //   Math: '<S52>/Square'
    //   Math: '<S63>/Square'
    //   Switch: '<S116>/Switch'
    //   Switch: '<S41>/Switch'
    //   Switch: '<S57>/Switch'

    Formation_FMS_DW.MathFunction_h4[0] =
      Formation_FMS_DW.TmpSignalConversionAtSqua_n[0] *
      Formation_FMS_DW.TmpSignalConversionAtSqua_n[0];

    // Product: '<S58>/Divide'
    Formation_FMS_DW.rtb_y_R_idx_2 = Formation_FMS_DW.rtb_vn_idx_1 /
      Formation_FMS_DW.Multiply1_f;

    // Math: '<S56>/Square' incorporates:
    //   Math: '<S128>/Square'
    //   Math: '<S129>/Math Function'
    //   Math: '<S52>/Square'
    //   Math: '<S63>/Square'
    //   Switch: '<S116>/Switch'
    //   Switch: '<S41>/Switch'
    //   Switch: '<S57>/Switch'

    Formation_FMS_DW.MathFunction_h4[1] =
      Formation_FMS_DW.TmpSignalConversionAtSqua_n[1] *
      Formation_FMS_DW.TmpSignalConversionAtSqua_n[1];

    // Product: '<S54>/Multiply'
    Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.pose[0] *
      Formation_FMS_DW.rtb_y_R_idx_2;

    // Sum: '<S54>/Subtract' incorporates:
    //   Product: '<S54>/Multiply1'

    Formation_FMS_DW.t_f = Formation_FMS_DW.Multiply1_f -
      Formation_FMS_DW.rtb_x_R_idx_1 * Formation_FMS_DW.pose[1];

    // Sum: '<S56>/Sum of Elements' incorporates:
    //   Math: '<S56>/Square'
    //   Sum: '<S52>/Sum of Elements'
    //   Switch: '<S41>/Switch'

    Formation_FMS_DW.rtb_vn_idx_1 = Formation_FMS_DW.MathFunction_h4[0] +
      Formation_FMS_DW.MathFunction_h4[1];

    // Product: '<S56>/Divide' incorporates:
    //   Abs: '<S56>/Abs'
    //   Bias: '<S56>/Bias'
    //   Constant: '<S56>/Ts//2'
    //   Product: '<S56>/Product'
    //   Sum: '<S56>/Sum of Elements'

    Formation_FMS_DW.path_ratio = std::abs(Formation_FMS_DW.t_f) /
      (FORMATION_PARAM.LATERAL_DAMP * FORMATION_PARAM.LATERAL_PERIOD * 0.5F *
       (Formation_FMS_DW.rtb_vn_idx_1 + 1.0F));

    // Saturate: '<S56>/normalized_track_error'
    if (Formation_FMS_DW.path_ratio > 1.0F) {
      Formation_FMS_DW.path_ratio = 1.0F;
    } else if (Formation_FMS_DW.path_ratio < 0.0F) {
      Formation_FMS_DW.path_ratio = 0.0F;
    }

    // End of Saturate: '<S56>/normalized_track_error'

    // Gain: '<S60>/Gain1' incorporates:
    //   Bias: '<S60>/Bias1'
    //   Math: '<S60>/Square1'

    Formation_FMS_DW.rtb_y_R_idx_1 = (Formation_FMS_DW.path_ratio - 1.0F) *
      (Formation_FMS_DW.path_ratio - 1.0F) * 1.57079637F;

    // Trigonometry: '<S55>/Sin'
    Formation_FMS_DW.path_ratio = std::sin(Formation_FMS_DW.rtb_y_R_idx_1);

    // Trigonometry: '<S55>/Cos'
    Formation_FMS_DW.rtb_y_R_idx_1 = std::cos(Formation_FMS_DW.rtb_y_R_idx_1);

    // MATLAB Function: '<S55>/signNoZero'
    Formation_FMS_signNoZero(Formation_FMS_DW.t_f, &Formation_FMS_DW.Multiply1_f);

    // Sum: '<S55>/Add' incorporates:
    //   Gain: '<S55>/Gain'
    //   Gain: '<S55>/Gain1'
    //   Product: '<S55>/Product'
    //   Product: '<S55>/Product1'
    //   Product: '<S55>/unit_track_error'
    //   Product: '<S58>/Divide'

    Formation_FMS_DW.t_f = -Formation_FMS_DW.rtb_y_R_idx_2 *
      -Formation_FMS_DW.Multiply1_f * Formation_FMS_DW.rtb_y_R_idx_1 +
      Formation_FMS_DW.rtb_x_R_idx_1 * Formation_FMS_DW.path_ratio;
    Formation_FMS_DW.rtb_x_R_idx_1 = Formation_FMS_DW.rtb_x_R_idx_1 *
      -Formation_FMS_DW.Multiply1_f * Formation_FMS_DW.rtb_y_R_idx_1 +
      Formation_FMS_DW.rtb_y_R_idx_2 * Formation_FMS_DW.path_ratio;

    // Product: '<S61>/Multiply'
    Formation_FMS_DW.rtb_y_R_idx_1 = *rtu_INS_Out_vn *
      Formation_FMS_DW.rtb_x_R_idx_1;

    // Product: '<S61>/Multiply1'
    Formation_FMS_DW.Multiply1_f = *rtu_INS_Out_ve * Formation_FMS_DW.t_f;

    // Sum: '<S61>/Subtract'
    Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.rtb_y_R_idx_1 -
      Formation_FMS_DW.Multiply1_f;

    // MATLAB Function: '<S57>/signNoZero'
    Formation_FMS_signNoZero(Formation_FMS_DW.Multiply1_f,
      &Formation_FMS_DW.rtb_y_R_idx_1);

    // Switch: '<S41>/Switch' incorporates:
    //   Constant: '<S41>/Constant2'
    //   Constant: '<S42>/Constant'
    //   DiscreteIntegrator: '<S97>/Integrator'
    //   Gain: '<S102>/Proportional Gain'
    //   Gain: '<S114>/Gain'
    //   Gain: '<S57>/Gain'
    //   RelationalOperator: '<S42>/Compare'
    //   Saturate: '<S49>/Saturation'
    //   Saturate: '<S49>/Saturation1'
    //   Sum: '<S106>/Sum'
    //   Sum: '<S49>/Add'
    //   Sum: '<S50>/Add'

    if (FORMATION_PARAM.UAV_ID == 1U) {
      // Sum: '<S114>/Sum' incorporates:
      //   Constant: '<S114>/Constant'

      Formation_FMS_DW.rtb_y_R_idx_1 = FMS_PARAM.FW_AIRSPD_TRIM -
        *rtu_INS_Out_airspeed;

      // Switch: '<S116>/Switch' incorporates:
      //   Constant: '<S116>/Constant'
      //   Product: '<S132>/Divide'

      if (Formation_FMS_DW.Cmd_In.l1_enable) {
        // Switch: '<S119>/Switch1' incorporates:
        //   Constant: '<S122>/Constant'
        //   RelationalOperator: '<S122>/Compare'

        if (!(Formation_FMS_DW.scale > 0.0F)) {
          // Switch: '<S119>/Switch' incorporates:
          //   Constant: '<S121>/Constant'
          //   RelationalOperator: '<S121>/Compare'
          //   Switch: '<S119>/Switch1'

          if (Formation_FMS_DW.absxk >= 0.0F) {
            Formation_FMS_DW.P_c[0] = Formation_FMS_DW.P_mr[0];
            Formation_FMS_DW.P_c[1] = Formation_FMS_DW.P_mr[1];
          } else {
            Formation_FMS_DW.P_c[0] = Formation_FMS_DW.P_b[0];
            Formation_FMS_DW.P_c[1] = Formation_FMS_DW.P_b[1];
          }

          // End of Switch: '<S119>/Switch'
        }

        // End of Switch: '<S119>/Switch1'

        // Sum: '<S120>/Subtract' incorporates:
        //   Reshape: '<S118>/Reshape2'
        //   Switch: '<S119>/Switch1'

        Formation_FMS_DW.absxk = Formation_FMS_DW.P_c[0] -
          Formation_FMS_DW.Reshape2_bi[0];
        Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.P_c[1] -
          Formation_FMS_DW.Reshape2_bi[1];

        // Math: '<S129>/Math Function1' incorporates:
        //   Sum: '<S56>/Sum of Elements'
        //
        //  About '<S129>/Math Function1':
        //   Operator: sqrt

        if (Formation_FMS_DW.rtb_vn_idx_1 < 0.0F) {
          Formation_FMS_DW.scale = -std::sqrt(std::abs
            (Formation_FMS_DW.rtb_vn_idx_1));
        } else {
          Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.rtb_vn_idx_1);
        }

        // End of Math: '<S129>/Math Function1'

        // Switch: '<S129>/Switch' incorporates:
        //   Constant: '<S129>/Constant'
        //   Product: '<S129>/Product'

        if (Formation_FMS_DW.scale > 0.0F) {
          Formation_FMS_DW.ve[0] = *rtu_INS_Out_vn;
          Formation_FMS_DW.ve[1] = *rtu_INS_Out_ve;
          Formation_FMS_DW.ve[2] = Formation_FMS_DW.scale;
        } else {
          Formation_FMS_DW.ve[0] = Formation_FMS_DW.TmpSignalConversionAtSqua_n
            [0] * 0.0F;
          Formation_FMS_DW.ve[1] = Formation_FMS_DW.TmpSignalConversionAtSqua_n
            [1] * 0.0F;
          Formation_FMS_DW.ve[2] = 1.0F;
        }

        // End of Switch: '<S129>/Switch'

        // Product: '<S129>/Divide'
        Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.ve[0] /
          Formation_FMS_DW.ve[2];
        Formation_FMS_DW.rtb_x_R_idx_0 = Formation_FMS_DW.ve[1] /
          Formation_FMS_DW.ve[2];

        // Sum: '<S130>/Sum of Elements' incorporates:
        //   Math: '<S130>/Math Function'

        Formation_FMS_DW.scale = Formation_FMS_DW.absxk * Formation_FMS_DW.absxk
          + Formation_FMS_DW.Multiply1_f * Formation_FMS_DW.Multiply1_f;

        // Math: '<S130>/Math Function1'
        //
        //  About '<S130>/Math Function1':
        //   Operator: sqrt

        if (Formation_FMS_DW.scale < 0.0F) {
          Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
        } else {
          Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
        }

        // End of Math: '<S130>/Math Function1'

        // Switch: '<S130>/Switch' incorporates:
        //   Constant: '<S130>/Constant'
        //   Product: '<S130>/Product'
        //   Sum: '<S120>/Subtract'
        //   Switch: '<S132>/Switch'

        if (Formation_FMS_DW.scale > 0.0F) {
          Formation_FMS_DW.ve[0] = Formation_FMS_DW.absxk;
          Formation_FMS_DW.ve[1] = Formation_FMS_DW.Multiply1_f;
          Formation_FMS_DW.ve[2] = Formation_FMS_DW.scale;
        } else {
          Formation_FMS_DW.ve[0] = Formation_FMS_DW.absxk * 0.0F;
          Formation_FMS_DW.ve[1] = Formation_FMS_DW.Multiply1_f * 0.0F;
          Formation_FMS_DW.ve[2] = 1.0F;
        }

        // End of Switch: '<S130>/Switch'

        // Product: '<S130>/Divide' incorporates:
        //   Product: '<S133>/Divide'

        Formation_FMS_DW.P_c[0] = Formation_FMS_DW.ve[0] / Formation_FMS_DW.ve[2];
        Formation_FMS_DW.P_c[1] = Formation_FMS_DW.ve[1] / Formation_FMS_DW.ve[2];

        // Sqrt: '<S128>/Sqrt' incorporates:
        //   Math: '<S128>/Square'
        //   Sum: '<S128>/Sum of Elements'

        Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.MathFunction_h4[0] +
          Formation_FMS_DW.MathFunction_h4[1]);

        // Gain: '<S126>/Gain' incorporates:
        //   Math: '<S126>/Square'

        Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.scale *
          Formation_FMS_DW.scale * 2.0F;

        // Sum: '<S133>/Sum of Elements' incorporates:
        //   Math: '<S133>/Math Function'
        //   SignalConversion generated from: '<S133>/Math Function'

        Formation_FMS_DW.scale = Formation_FMS_DW.P_c[1] * Formation_FMS_DW.P_c
          [1] + Formation_FMS_DW.P_c[0] * Formation_FMS_DW.P_c[0];

        // Math: '<S133>/Math Function1'
        //
        //  About '<S133>/Math Function1':
        //   Operator: sqrt

        if (Formation_FMS_DW.scale < 0.0F) {
          Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
        } else {
          Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
        }

        // End of Math: '<S133>/Math Function1'

        // Switch: '<S133>/Switch' incorporates:
        //   Constant: '<S133>/Constant'
        //   Product: '<S133>/Product'
        //   SignalConversion generated from: '<S133>/Math Function'

        if (Formation_FMS_DW.scale > 0.0F) {
          Formation_FMS_DW.ve[0] = Formation_FMS_DW.P_c[1];
          Formation_FMS_DW.ve[1] = Formation_FMS_DW.P_c[0];
          Formation_FMS_DW.ve[2] = Formation_FMS_DW.scale;
        } else {
          Formation_FMS_DW.ve[0] = Formation_FMS_DW.P_c[1] * 0.0F;
          Formation_FMS_DW.ve[1] = Formation_FMS_DW.P_c[0] * 0.0F;
          Formation_FMS_DW.ve[2] = 1.0F;
        }

        // End of Switch: '<S133>/Switch'

        // Product: '<S133>/Divide'
        Formation_FMS_DW.P_c[0] = Formation_FMS_DW.ve[0] / Formation_FMS_DW.ve[2];
        Formation_FMS_DW.P_c[1] = Formation_FMS_DW.ve[1] / Formation_FMS_DW.ve[2];

        // Sum: '<S132>/Sum of Elements' incorporates:
        //   Math: '<S132>/Math Function'
        //   SignalConversion generated from: '<S132>/Math Function'

        Formation_FMS_DW.scale = Formation_FMS_DW.rtb_x_R_idx_0 *
          Formation_FMS_DW.rtb_x_R_idx_0 + Formation_FMS_DW.rtb_y_R_idx_0 *
          Formation_FMS_DW.rtb_y_R_idx_0;

        // Math: '<S132>/Math Function1'
        //
        //  About '<S132>/Math Function1':
        //   Operator: sqrt

        if (Formation_FMS_DW.scale < 0.0F) {
          Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
        } else {
          Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
        }

        // End of Math: '<S132>/Math Function1'

        // Switch: '<S132>/Switch' incorporates:
        //   Constant: '<S132>/Constant'
        //   Product: '<S132>/Product'
        //   SignalConversion generated from: '<S132>/Math Function'

        if (Formation_FMS_DW.scale > 0.0F) {
          Formation_FMS_DW.ve[0] = Formation_FMS_DW.rtb_x_R_idx_0;
          Formation_FMS_DW.ve[1] = Formation_FMS_DW.rtb_y_R_idx_0;
          Formation_FMS_DW.ve[2] = Formation_FMS_DW.scale;
        } else {
          Formation_FMS_DW.ve[0] = Formation_FMS_DW.rtb_x_R_idx_0 * 0.0F;
          Formation_FMS_DW.ve[1] = Formation_FMS_DW.rtb_y_R_idx_0 * 0.0F;
          Formation_FMS_DW.ve[2] = 1.0F;
        }

        // End of Switch: '<S132>/Switch'

        // Product: '<S132>/Divide'
        Formation_FMS_DW.absxk = Formation_FMS_DW.ve[0] / Formation_FMS_DW.ve[2];

        // DotProduct: '<S127>/Dot Product'
        Formation_FMS_DW.rtb_x_R_idx_0 = Formation_FMS_DW.absxk *
          Formation_FMS_DW.P_c[0];
        Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.absxk;

        // Product: '<S132>/Divide'
        Formation_FMS_DW.absxk = Formation_FMS_DW.ve[1] / Formation_FMS_DW.ve[2];

        // DotProduct: '<S127>/Dot Product'
        Formation_FMS_DW.rtb_x_R_idx_0 += Formation_FMS_DW.absxk *
          Formation_FMS_DW.P_c[1];

        // Sum: '<S131>/Subtract' incorporates:
        //   Product: '<S131>/Multiply'
        //   Product: '<S131>/Multiply1'

        Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.P_c[0] *
          Formation_FMS_DW.absxk - Formation_FMS_DW.rtb_y_R_idx_0 *
          Formation_FMS_DW.P_c[1];

        // Signum: '<S127>/Sign1'
        if (std::isnan(Formation_FMS_DW.rtb_y_R_idx_0)) {
          Formation_FMS_DW.scale = (rtNaNF);
        } else if (Formation_FMS_DW.rtb_y_R_idx_0 < 0.0F) {
          Formation_FMS_DW.scale = -1.0F;
        } else {
          Formation_FMS_DW.scale = (Formation_FMS_DW.rtb_y_R_idx_0 > 0.0F);
        }

        // End of Signum: '<S127>/Sign1'

        // Trigonometry: '<S127>/Acos' incorporates:
        //   DotProduct: '<S127>/Dot Product'

        if (Formation_FMS_DW.rtb_x_R_idx_0 > 1.0F) {
          Formation_FMS_DW.rtb_x_R_idx_0 = 1.0F;
        } else if (Formation_FMS_DW.rtb_x_R_idx_0 < -1.0F) {
          Formation_FMS_DW.rtb_x_R_idx_0 = -1.0F;
        }

        // Switch: '<S127>/Switch2' incorporates:
        //   Constant: '<S127>/Constant4'

        if (!(Formation_FMS_DW.scale != 0.0F)) {
          Formation_FMS_DW.scale = 1.0F;
        }

        // Product: '<S127>/Multiply' incorporates:
        //   Switch: '<S127>/Switch2'
        //   Trigonometry: '<S127>/Acos'

        Formation_FMS_DW.path_ratio = std::acos(Formation_FMS_DW.rtb_x_R_idx_0) *
          Formation_FMS_DW.scale;

        // Saturate: '<S126>/Saturation'
        if (Formation_FMS_DW.path_ratio > 1.57079637F) {
          Formation_FMS_DW.path_ratio = 1.57079637F;
        } else if (Formation_FMS_DW.path_ratio < -1.57079637F) {
          Formation_FMS_DW.path_ratio = -1.57079637F;
        }

        // Product: '<S126>/Divide' incorporates:
        //   Constant: '<S117>/L1'
        //   Product: '<S126>/Multiply1'
        //   Saturate: '<S126>/Saturation'
        //   Trigonometry: '<S126>/Sin'

        Formation_FMS_DW.rtb_vn_idx_1 = std::sin(Formation_FMS_DW.path_ratio) *
          Formation_FMS_DW.Multiply1_f / FMS_PARAM.L1;

        // Saturate: '<S117>/Saturation1'
        if (Formation_FMS_DW.rtb_vn_idx_1 > FMS_PARAM.ACC_Y_LIM) {
          Formation_FMS_DW.rtb_vn_idx_1 = FMS_PARAM.ACC_Y_LIM;
        } else if (Formation_FMS_DW.rtb_vn_idx_1 < -FMS_PARAM.ACC_Y_LIM) {
          Formation_FMS_DW.rtb_vn_idx_1 = -FMS_PARAM.ACC_Y_LIM;
        }

        // End of Saturate: '<S117>/Saturation1'
      } else {
        Formation_FMS_DW.rtb_vn_idx_1 = 0.0F;
      }

      // Sum: '<S115>/Sum' incorporates:
      //   Delay: '<S115>/Delay'

      Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.Delay_DSTATE_o -
        *rtu_INS_Out_h_R;
      Formation_FMS_DW.t_f = FMS_PARAM.AIRSPD_P * Formation_FMS_DW.rtb_y_R_idx_1;

      // Gain: '<S115>/Gain2' incorporates:
      //   Gain: '<S114>/Gain'

      Formation_FMS_DW.Multiply1_f *= FMS_PARAM.Z_P;

      // Saturate: '<S115>/Saturation'
      if (Formation_FMS_DW.Multiply1_f > CONTROL_PARAM.FW_T_CLMB_MAX) {
        Formation_FMS_DW.Multiply1_f = CONTROL_PARAM.FW_T_CLMB_MAX;
      } else if (Formation_FMS_DW.Multiply1_f < -CONTROL_PARAM.FW_T_SINK_MAX) {
        Formation_FMS_DW.Multiply1_f = -CONTROL_PARAM.FW_T_SINK_MAX;
      }

      // End of Saturate: '<S115>/Saturation'
    } else {
      // Sum: '<S53>/Sum of Elements' incorporates:
      //   Math: '<S53>/Math Function'

      Formation_FMS_DW.scale = Formation_FMS_DW.rtb_y_R_idx_0 +
        Formation_FMS_DW.rtb_x_R_idx_0;

      // Math: '<S53>/Math Function1'
      //
      //  About '<S53>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_DW.scale < 0.0F) {
        Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
      } else {
        Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
      }

      // End of Math: '<S53>/Math Function1'

      // Switch: '<S53>/Switch' incorporates:
      //   Constant: '<S53>/Constant'
      //   Product: '<S53>/Product'

      if (Formation_FMS_DW.scale > 0.0F) {
        Formation_FMS_DW.absxk = Formation_FMS_DW.ve[0];
        Formation_FMS_DW.path_ratio = Formation_FMS_DW.ve[1];
      } else {
        Formation_FMS_DW.absxk = Formation_FMS_DW.ve[0] * 0.0F;
        Formation_FMS_DW.path_ratio = Formation_FMS_DW.ve[1] * 0.0F;
        Formation_FMS_DW.scale = 1.0F;
      }

      // End of Switch: '<S53>/Switch'

      // Switch: '<S57>/Switch' incorporates:
      //   DotProduct: '<S57>/Dot Product'
      //   Math: '<S62>/Square'
      //   Product: '<S57>/Divide'
      //   Product: '<S57>/Product'
      //   Sqrt: '<S62>/Sqrt'
      //   Sqrt: '<S63>/Sqrt'
      //   Sum: '<S55>/Add'
      //   Sum: '<S56>/Sum of Elements'
      //   Sum: '<S62>/Sum of Elements'

      if (Formation_FMS_DW.TmpSignalConversionAtSqua_n[0] * Formation_FMS_DW.t_f
          + Formation_FMS_DW.TmpSignalConversionAtSqua_n[1] *
          Formation_FMS_DW.rtb_x_R_idx_1 >= 0.0F) {
        Formation_FMS_DW.rtb_y_R_idx_1 = Formation_FMS_DW.Multiply1_f / std::
          sqrt(Formation_FMS_DW.t_f * Formation_FMS_DW.t_f +
               Formation_FMS_DW.rtb_x_R_idx_1 * Formation_FMS_DW.rtb_x_R_idx_1);
      } else {
        Formation_FMS_DW.rtb_y_R_idx_1 *= std::sqrt
          (Formation_FMS_DW.rtb_vn_idx_1);
      }

      // Gain: '<S49>/Pos_Kp' incorporates:
      //   DotProduct: '<S49>/Dot Product'
      //   Product: '<S53>/Divide'

      Formation_FMS_DW.path_ratio = (Formation_FMS_DW.absxk /
        Formation_FMS_DW.scale * Formation_FMS_DW.pose[0] +
        Formation_FMS_DW.path_ratio / Formation_FMS_DW.scale *
        Formation_FMS_DW.pose[1]) * 0.3F;

      // Gain: '<S49>/Vel_Kp' incorporates:
      //   Math: '<S51>/Square'
      //   Sqrt: '<S51>/Sqrt'
      //   Sqrt: '<S52>/Sqrt'
      //   Sum: '<S49>/Sum1'
      //   Sum: '<S51>/Sum of Elements'

      Formation_FMS_DW.Multiply1_f = (std::sqrt(Formation_FMS_DW.rtb_y_R_idx_0 +
        Formation_FMS_DW.rtb_x_R_idx_0) - std::sqrt
        (Formation_FMS_DW.rtb_vn_idx_1)) * 0.5F;

      // Saturate: '<S49>/Saturation'
      if (Formation_FMS_DW.path_ratio > 2.0F) {
        Formation_FMS_DW.path_ratio = 2.0F;
      } else if (Formation_FMS_DW.path_ratio < -2.0F) {
        Formation_FMS_DW.path_ratio = -2.0F;
      }

      // Saturate: '<S49>/Saturation1'
      if (Formation_FMS_DW.Multiply1_f > 10.0F) {
        Formation_FMS_DW.Multiply1_f = 10.0F;
      } else if (Formation_FMS_DW.Multiply1_f < -10.0F) {
        Formation_FMS_DW.Multiply1_f = -10.0F;
      }

      Formation_FMS_DW.t_f = Formation_FMS_DW.path_ratio +
        Formation_FMS_DW.Multiply1_f;
      Formation_FMS_DW.rtb_vn_idx_1 = 12.566371F * FORMATION_PARAM.LATERAL_DAMP /
        FORMATION_PARAM.LATERAL_PERIOD * Formation_FMS_DW.rtb_y_R_idx_1;
      Formation_FMS_DW.Multiply1_f = 0.1F * Formation_FMS_DW.pose[2] +
        Formation_FMS_DW.Integrator_DSTATE;
    }

    // End of Outputs for SubSystem: '<S13>/FormMission_SubSystem'
    // End of Outputs for SubSystem: '<S10>/FormMission'
    std::memset(&Formation_FMS_DW.Merge, 0, sizeof(FMS_Out_Bus));

    // Outputs for IfAction SubSystem: '<S10>/FormMission' incorporates:
    //   ActionPort: '<S13>/Action Port'

    // Outputs for Resettable SubSystem: '<S13>/FormMission_SubSystem' incorporates:
    //   ResetPort: '<S41>/Reset'

    // BusAssignment: '<S41>/Bus Assignment' incorporates:
    //   Constant: '<S41>/Constant1'
    //   Merge: '<S10>/Merge'

    Formation_FMS_DW.Merge.state = VehicleState::FormMission;
    Formation_FMS_DW.Merge.ax_cmd = Formation_FMS_DW.t_f;
    Formation_FMS_DW.Merge.ay_cmd = Formation_FMS_DW.rtb_vn_idx_1;
    Formation_FMS_DW.Merge.vh_cmd = Formation_FMS_DW.Multiply1_f;

    // Update for Delay: '<S115>/Delay'
    Formation_FMS_DW.icLoad_k = false;

    // Update for DiscreteIntegrator: '<S97>/Integrator' incorporates:
    //   Gain: '<S94>/Integral Gain'

    Formation_FMS_DW.Integrator_DSTATE += 0.0F * Formation_FMS_DW.pose[2] *
      0.02F;

    // End of Outputs for SubSystem: '<S13>/FormMission_SubSystem'

    // Update for UnitDelay: '<S40>/Delay Input1'
    //
    //  Block description for '<S40>/Delay Input1':
    //
    //   Store in Global RAM

    Formation_FMS_DW.DelayInput1_DSTATE_d = Formation_FMS_DW.wp_index;

    // End of Outputs for SubSystem: '<S10>/FormMission'
    break;

   case 1:
    // Outputs for IfAction SubSystem: '<S10>/FormAssemble' incorporates:
    //   ActionPort: '<S12>/Action Port'

    // RelationalOperator: '<S17>/FixPt Relational Operator' incorporates:
    //   UnitDelay: '<S17>/Delay Input1'
    //
    //  Block description for '<S17>/Delay Input1':
    //
    //   Store in Global RAM

    rtb_FixPtRelationalOperator_c = (Formation_FMS_DW.wp_index !=
      Formation_FMS_DW.DelayInput1_DSTATE_h);

    // Outputs for Resettable SubSystem: '<S12>/Mission_SubSystem' incorporates:
    //   ResetPort: '<S18>/Reset'

    // InitializeConditions for Delay: '<S20>/Delay'
    Formation_FMS_DW.icLoad_h = ((rtb_FixPtRelationalOperator_c &&
      (Formation_FMS_PrevZCX.Mission_SubSystem_Reset_ZCE != POS_ZCSIG)) ||
      Formation_FMS_DW.icLoad_h);
    Formation_FMS_PrevZCX.Mission_SubSystem_Reset_ZCE =
      rtb_FixPtRelationalOperator_c;

    // Reshape: '<S24>/Reshape2'
    Formation_FMS_DW.MathFunction_h4[0] = *rtu_INS_Out_x_R;
    Formation_FMS_DW.MathFunction_h4[1] = *rtu_INS_Out_y_R;

    // MATLAB Function: '<S25>/NearbyRefWP' incorporates:
    //   Constant: '<S23>/L1'

    Formation_FMS_NearbyRefWP(&Formation_FMS_DW.Cmd_In.sp_waypoint[0],
      Formation_FMS_DW.MathFunction_h4, FMS_PARAM.L1, Formation_FMS_DW.P_c,
      &Formation_FMS_DW.rtb_y_R_idx_1);

    // MATLAB Function: '<S25>/SearchL1RefWP' incorporates:
    //   Constant: '<S23>/L1'

    Formation_FMS_SearchL1RefWP(&Formation_FMS_DW.Cmd_In.cur_waypoint[0],
      &Formation_FMS_DW.Cmd_In.sp_waypoint[0], Formation_FMS_DW.MathFunction_h4,
      FMS_PARAM.L1, Formation_FMS_DW.TmpSignalConversionAtSqua_n,
      &Formation_FMS_DW.Multiply1_f);

    // MATLAB Function: '<S25>/OutRegionRegWP'
    Formation_FMS_OutRegionRegWP(&Formation_FMS_DW.Cmd_In.cur_waypoint[0],
      &Formation_FMS_DW.Cmd_In.sp_waypoint[0], Formation_FMS_DW.MathFunction_h4,
      Formation_FMS_DW.Reshape2_bi);

    // Switch: '<S21>/Switch' incorporates:
    //   Constant: '<S21>/Constant'
    //   Math: '<S35>/Math Function'
    //   Product: '<S39>/Divide'

    if (Formation_FMS_DW.Cmd_In.l1_enable) {
      // SignalConversion generated from: '<S34>/Square'
      Formation_FMS_DW.rtb_y_R_idx_0 = *rtu_INS_Out_vn;
      Formation_FMS_DW.rtb_x_R_idx_0 = *rtu_INS_Out_ve;

      // Switch: '<S25>/Switch1' incorporates:
      //   Constant: '<S28>/Constant'
      //   RelationalOperator: '<S28>/Compare'

      if (!(Formation_FMS_DW.rtb_y_R_idx_1 > 0.0F)) {
        // Switch: '<S25>/Switch' incorporates:
        //   Constant: '<S27>/Constant'
        //   RelationalOperator: '<S27>/Compare'
        //   Switch: '<S25>/Switch1'

        if (Formation_FMS_DW.Multiply1_f >= 0.0F) {
          Formation_FMS_DW.P_c[0] =
            Formation_FMS_DW.TmpSignalConversionAtSqua_n[0];
          Formation_FMS_DW.P_c[1] =
            Formation_FMS_DW.TmpSignalConversionAtSqua_n[1];
        } else {
          Formation_FMS_DW.P_c[0] = Formation_FMS_DW.Reshape2_bi[0];
          Formation_FMS_DW.P_c[1] = Formation_FMS_DW.Reshape2_bi[1];
        }

        // End of Switch: '<S25>/Switch'
      }

      // End of Switch: '<S25>/Switch1'

      // Sum: '<S26>/Subtract' incorporates:
      //   Reshape: '<S24>/Reshape2'
      //   Switch: '<S25>/Switch1'

      Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.P_c[0] -
        Formation_FMS_DW.MathFunction_h4[0];
      Formation_FMS_DW.MathFunction_h4[0] = Formation_FMS_DW.rtb_y_R_idx_0 *
        Formation_FMS_DW.rtb_y_R_idx_0;

      // Sum: '<S26>/Subtract' incorporates:
      //   Math: '<S35>/Math Function'
      //   Reshape: '<S24>/Reshape2'
      //   Switch: '<S25>/Switch1'

      Formation_FMS_DW.rtb_vn_idx_1 = Formation_FMS_DW.P_c[1] -
        Formation_FMS_DW.MathFunction_h4[1];

      // Math: '<S35>/Math Function'
      Formation_FMS_DW.rtb_y_R_idx_1 = Formation_FMS_DW.rtb_x_R_idx_0 *
        Formation_FMS_DW.rtb_x_R_idx_0;

      // Sum: '<S35>/Sum of Elements' incorporates:
      //   Math: '<S35>/Math Function'

      Formation_FMS_DW.scale = Formation_FMS_DW.rtb_y_R_idx_1 +
        Formation_FMS_DW.MathFunction_h4[0];

      // Math: '<S35>/Math Function1'
      //
      //  About '<S35>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_DW.scale < 0.0F) {
        Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
      } else {
        Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
      }

      // End of Math: '<S35>/Math Function1'

      // Switch: '<S35>/Switch' incorporates:
      //   Constant: '<S35>/Constant'
      //   Product: '<S35>/Product'

      if (Formation_FMS_DW.scale > 0.0F) {
        Formation_FMS_DW.pose[0] = *rtu_INS_Out_vn;
        Formation_FMS_DW.pose[1] = *rtu_INS_Out_ve;
        Formation_FMS_DW.pose[2] = Formation_FMS_DW.scale;
      } else {
        Formation_FMS_DW.pose[0] = Formation_FMS_DW.rtb_y_R_idx_0 * 0.0F;
        Formation_FMS_DW.pose[1] = Formation_FMS_DW.rtb_x_R_idx_0 * 0.0F;
        Formation_FMS_DW.pose[2] = 1.0F;
      }

      // End of Switch: '<S35>/Switch'

      // Product: '<S35>/Divide'
      Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.pose[0] /
        Formation_FMS_DW.pose[2];
      Formation_FMS_DW.rtb_x_R_idx_0 = Formation_FMS_DW.pose[1] /
        Formation_FMS_DW.pose[2];

      // Sum: '<S36>/Sum of Elements' incorporates:
      //   Math: '<S36>/Math Function'

      Formation_FMS_DW.scale = Formation_FMS_DW.Multiply1_f *
        Formation_FMS_DW.Multiply1_f + Formation_FMS_DW.rtb_vn_idx_1 *
        Formation_FMS_DW.rtb_vn_idx_1;

      // Math: '<S36>/Math Function1'
      //
      //  About '<S36>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_DW.scale < 0.0F) {
        Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
      } else {
        Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
      }

      // End of Math: '<S36>/Math Function1'

      // Switch: '<S36>/Switch' incorporates:
      //   Constant: '<S36>/Constant'
      //   Product: '<S36>/Product'
      //   Switch: '<S39>/Switch'

      if (Formation_FMS_DW.scale > 0.0F) {
        Formation_FMS_DW.pose[0] = Formation_FMS_DW.Multiply1_f;
        Formation_FMS_DW.pose[1] = Formation_FMS_DW.rtb_vn_idx_1;
        Formation_FMS_DW.pose[2] = Formation_FMS_DW.scale;
      } else {
        Formation_FMS_DW.pose[0] = Formation_FMS_DW.Multiply1_f * 0.0F;
        Formation_FMS_DW.pose[1] = Formation_FMS_DW.rtb_vn_idx_1 * 0.0F;
        Formation_FMS_DW.pose[2] = 1.0F;
      }

      // End of Switch: '<S36>/Switch'

      // Product: '<S36>/Divide' incorporates:
      //   Product: '<S39>/Divide'

      Formation_FMS_DW.P_c[0] = Formation_FMS_DW.pose[0] /
        Formation_FMS_DW.pose[2];
      Formation_FMS_DW.P_c[1] = Formation_FMS_DW.pose[1] /
        Formation_FMS_DW.pose[2];

      // Sum: '<S38>/Sum of Elements' incorporates:
      //   Math: '<S38>/Math Function'
      //   SignalConversion generated from: '<S38>/Math Function'

      Formation_FMS_DW.scale = Formation_FMS_DW.rtb_x_R_idx_0 *
        Formation_FMS_DW.rtb_x_R_idx_0 + Formation_FMS_DW.rtb_y_R_idx_0 *
        Formation_FMS_DW.rtb_y_R_idx_0;

      // Math: '<S38>/Math Function1'
      //
      //  About '<S38>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_DW.scale < 0.0F) {
        Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
      } else {
        Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
      }

      // End of Math: '<S38>/Math Function1'

      // Switch: '<S38>/Switch' incorporates:
      //   Constant: '<S38>/Constant'
      //   Product: '<S38>/Product'
      //   SignalConversion generated from: '<S38>/Math Function'

      if (Formation_FMS_DW.scale > 0.0F) {
        Formation_FMS_DW.pose[0] = Formation_FMS_DW.rtb_x_R_idx_0;
        Formation_FMS_DW.pose[1] = Formation_FMS_DW.rtb_y_R_idx_0;
        Formation_FMS_DW.pose[2] = Formation_FMS_DW.scale;
      } else {
        Formation_FMS_DW.pose[0] = Formation_FMS_DW.rtb_x_R_idx_0 * 0.0F;
        Formation_FMS_DW.pose[1] = Formation_FMS_DW.rtb_y_R_idx_0 * 0.0F;
        Formation_FMS_DW.pose[2] = 1.0F;
      }

      // End of Switch: '<S38>/Switch'

      // Product: '<S38>/Divide'
      Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.pose[0] /
        Formation_FMS_DW.pose[2];
      Formation_FMS_DW.rtb_x_R_idx_0 = Formation_FMS_DW.pose[1] /
        Formation_FMS_DW.pose[2];

      // Sum: '<S39>/Sum of Elements' incorporates:
      //   Math: '<S39>/Math Function'
      //   SignalConversion generated from: '<S39>/Math Function'

      Formation_FMS_DW.scale = Formation_FMS_DW.P_c[1] * Formation_FMS_DW.P_c[1]
        + Formation_FMS_DW.P_c[0] * Formation_FMS_DW.P_c[0];

      // Math: '<S39>/Math Function1'
      //
      //  About '<S39>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_DW.scale < 0.0F) {
        Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
      } else {
        Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
      }

      // End of Math: '<S39>/Math Function1'

      // Switch: '<S39>/Switch' incorporates:
      //   Constant: '<S39>/Constant'
      //   Product: '<S39>/Product'
      //   SignalConversion generated from: '<S39>/Math Function'

      if (Formation_FMS_DW.scale > 0.0F) {
        Formation_FMS_DW.pose[0] = Formation_FMS_DW.P_c[1];
        Formation_FMS_DW.pose[1] = Formation_FMS_DW.P_c[0];
        Formation_FMS_DW.pose[2] = Formation_FMS_DW.scale;
      } else {
        Formation_FMS_DW.pose[0] = Formation_FMS_DW.P_c[1] * 0.0F;
        Formation_FMS_DW.pose[1] = Formation_FMS_DW.P_c[0] * 0.0F;
        Formation_FMS_DW.pose[2] = 1.0F;
      }

      // End of Switch: '<S39>/Switch'

      // Product: '<S39>/Divide'
      Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.pose[0] /
        Formation_FMS_DW.pose[2];

      // DotProduct: '<S33>/Dot Product'
      Formation_FMS_DW.absxk = Formation_FMS_DW.rtb_y_R_idx_0 *
        Formation_FMS_DW.Multiply1_f;
      Formation_FMS_DW.P_c[0] = Formation_FMS_DW.Multiply1_f;

      // Product: '<S39>/Divide'
      Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.pose[1] /
        Formation_FMS_DW.pose[2];

      // DotProduct: '<S33>/Dot Product'
      Formation_FMS_DW.absxk += Formation_FMS_DW.rtb_x_R_idx_0 *
        Formation_FMS_DW.Multiply1_f;

      // Sum: '<S37>/Subtract' incorporates:
      //   Product: '<S37>/Multiply'
      //   Product: '<S37>/Multiply1'

      Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.P_c[0] *
        Formation_FMS_DW.rtb_x_R_idx_0 - Formation_FMS_DW.rtb_y_R_idx_0 *
        Formation_FMS_DW.Multiply1_f;

      // Signum: '<S33>/Sign1'
      if (std::isnan(Formation_FMS_DW.rtb_y_R_idx_0)) {
        Formation_FMS_DW.scale = (rtNaNF);
      } else if (Formation_FMS_DW.rtb_y_R_idx_0 < 0.0F) {
        Formation_FMS_DW.scale = -1.0F;
      } else {
        Formation_FMS_DW.scale = (Formation_FMS_DW.rtb_y_R_idx_0 > 0.0F);
      }

      // End of Signum: '<S33>/Sign1'

      // Trigonometry: '<S33>/Acos' incorporates:
      //   DotProduct: '<S33>/Dot Product'

      if (Formation_FMS_DW.absxk > 1.0F) {
        Formation_FMS_DW.absxk = 1.0F;
      } else if (Formation_FMS_DW.absxk < -1.0F) {
        Formation_FMS_DW.absxk = -1.0F;
      }

      // Switch: '<S33>/Switch2' incorporates:
      //   Constant: '<S33>/Constant4'

      if (!(Formation_FMS_DW.scale != 0.0F)) {
        Formation_FMS_DW.scale = 1.0F;
      }

      // Product: '<S33>/Multiply' incorporates:
      //   Switch: '<S33>/Switch2'
      //   Trigonometry: '<S33>/Acos'

      Formation_FMS_DW.path_ratio = std::acos(Formation_FMS_DW.absxk) *
        Formation_FMS_DW.scale;

      // Sqrt: '<S34>/Sqrt' incorporates:
      //   Math: '<S34>/Square'
      //   Math: '<S35>/Math Function'
      //   Sum: '<S34>/Sum of Elements'

      Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.MathFunction_h4[0] +
        Formation_FMS_DW.rtb_y_R_idx_1);

      // Saturate: '<S32>/Saturation'
      if (Formation_FMS_DW.path_ratio > 1.57079637F) {
        Formation_FMS_DW.path_ratio = 1.57079637F;
      } else if (Formation_FMS_DW.path_ratio < -1.57079637F) {
        Formation_FMS_DW.path_ratio = -1.57079637F;
      }

      // Product: '<S32>/Divide' incorporates:
      //   Constant: '<S23>/L1'
      //   Gain: '<S32>/Gain'
      //   Math: '<S32>/Square'
      //   Product: '<S32>/Multiply1'
      //   Saturate: '<S32>/Saturation'
      //   Trigonometry: '<S32>/Sin'

      Formation_FMS_DW.scale = Formation_FMS_DW.scale * Formation_FMS_DW.scale *
        2.0F * std::sin(Formation_FMS_DW.path_ratio) / FMS_PARAM.L1;

      // Saturate: '<S23>/Saturation1'
      if (Formation_FMS_DW.scale > FMS_PARAM.ACC_Y_LIM) {
        Formation_FMS_DW.scale = FMS_PARAM.ACC_Y_LIM;
      } else if (Formation_FMS_DW.scale < -FMS_PARAM.ACC_Y_LIM) {
        Formation_FMS_DW.scale = -FMS_PARAM.ACC_Y_LIM;
      }

      // End of Saturate: '<S23>/Saturation1'
    } else {
      Formation_FMS_DW.scale = 0.0F;
    }

    // End of Switch: '<S21>/Switch'

    // MATLAB Function: '<S19>/Time Consensus Controller'
    Formation_FMS_DW.Multiply1_f = rtu_Formation_Cross_left_time
      [static_cast<int32_T>(FORMATION_PARAM.UAV_ID) - 1];
    Formation_FMS_DW.rtb_y_R_idx_1 = (Formation_FMS_DW.Multiply1_f -
      rtu_Formation_Cross_left_time[0]) * static_cast<real32_T>
      (FORMATION_PARAM.ADJ_MARTIX[static_cast<int32_T>(FORMATION_PARAM.UAV_ID) -
       1]);
    Formation_FMS_DW.rtb_y_R_idx_1 += (Formation_FMS_DW.Multiply1_f -
      rtu_Formation_Cross_left_time[1]) * static_cast<real32_T>
      (FORMATION_PARAM.ADJ_MARTIX[static_cast<int32_T>(FORMATION_PARAM.UAV_ID) +
       2]);
    Formation_FMS_DW.rtb_y_R_idx_1 += (Formation_FMS_DW.Multiply1_f -
      rtu_Formation_Cross_left_time[2]) * static_cast<real32_T>
      (FORMATION_PARAM.ADJ_MARTIX[static_cast<int32_T>(FORMATION_PARAM.UAV_ID) +
       5]);

    // Sum: '<S19>/Sum' incorporates:
    //   Constant: '<S19>/Constant'

    Formation_FMS_DW.Multiply1_f = FMS_PARAM.FW_AIRSPD_TRIM -
      *rtu_INS_Out_airspeed;

    // Delay: '<S20>/Delay' incorporates:
    //   Constant: '<S20>/Constant'

    if (Formation_FMS_DW.icLoad_h) {
      Formation_FMS_DW.Delay_DSTATE_l = FMS_PARAM.FW_HEIGHT_TRIM;
    }

    // Sum: '<S20>/Sum' incorporates:
    //   Delay: '<S20>/Delay'

    Formation_FMS_DW.absxk = Formation_FMS_DW.Delay_DSTATE_l - *rtu_INS_Out_h_R;

    // End of Outputs for SubSystem: '<S12>/Mission_SubSystem'
    // End of Outputs for SubSystem: '<S10>/FormAssemble'
    std::memset(&Formation_FMS_DW.Merge, 0, sizeof(FMS_Out_Bus));

    // Outputs for IfAction SubSystem: '<S10>/FormAssemble' incorporates:
    //   ActionPort: '<S12>/Action Port'

    // Outputs for Resettable SubSystem: '<S12>/Mission_SubSystem' incorporates:
    //   ResetPort: '<S18>/Reset'

    // BusAssignment: '<S18>/Bus Assignment' incorporates:
    //   Constant: '<S18>/Constant1'
    //   Gain: '<S19>/Gain1'
    //   Merge: '<S10>/Merge'
    //   Sum: '<S19>/Sum1'

    Formation_FMS_DW.Merge.state = VehicleState::FormAssemble;
    Formation_FMS_DW.Merge.ax_cmd = FORMATION_PARAM.ASSEMBLE_KT *
      Formation_FMS_DW.rtb_y_R_idx_1 + Formation_FMS_DW.Multiply1_f;
    Formation_FMS_DW.Merge.ay_cmd = Formation_FMS_DW.scale;

    // Gain: '<S20>/Gain2'
    Formation_FMS_DW.path_ratio = FMS_PARAM.Z_P * Formation_FMS_DW.absxk;

    // Saturate: '<S20>/Saturation'
    if (Formation_FMS_DW.path_ratio > CONTROL_PARAM.FW_T_CLMB_MAX) {
      // BusAssignment: '<S18>/Bus Assignment'
      Formation_FMS_DW.Merge.vh_cmd = CONTROL_PARAM.FW_T_CLMB_MAX;
    } else if (Formation_FMS_DW.path_ratio < -CONTROL_PARAM.FW_T_SINK_MAX) {
      // BusAssignment: '<S18>/Bus Assignment'
      Formation_FMS_DW.Merge.vh_cmd = -CONTROL_PARAM.FW_T_SINK_MAX;
    } else {
      // BusAssignment: '<S18>/Bus Assignment'
      Formation_FMS_DW.Merge.vh_cmd = Formation_FMS_DW.path_ratio;
    }

    // End of Saturate: '<S20>/Saturation'

    // Update for Delay: '<S20>/Delay'
    Formation_FMS_DW.icLoad_h = false;

    // End of Outputs for SubSystem: '<S12>/Mission_SubSystem'

    // Update for UnitDelay: '<S17>/Delay Input1'
    //
    //  Block description for '<S17>/Delay Input1':
    //
    //   Store in Global RAM

    Formation_FMS_DW.DelayInput1_DSTATE_h = Formation_FMS_DW.wp_index;

    // End of Outputs for SubSystem: '<S10>/FormAssemble'
    break;

   case 2:
    if (rtAction != rtPrevAction) {
      // InitializeConditions for IfAction SubSystem: '<S10>/Hold' incorporates:
      //   ActionPort: '<S14>/Action Port'

      // InitializeConditions for SwitchCase: '<S10>/Switch Case' incorporates:
      //   Delay: '<S135>/Delay'
      //   Delay: '<S139>/start_vel'

      Formation_FMS_DW.icLoad_c = true;
      Formation_FMS_DW.icLoad_j = true;

      // End of InitializeConditions for SubSystem: '<S10>/Hold'
    }

    // Outputs for IfAction SubSystem: '<S10>/Hold' incorporates:
    //   ActionPort: '<S14>/Action Port'

    // SignalConversion generated from: '<S145>/Square'
    Formation_FMS_DW.P_c[0] = *rtu_INS_Out_vn;
    Formation_FMS_DW.P_c[1] = *rtu_INS_Out_ve;

    // Sum: '<S146>/Sum of Elements' incorporates:
    //   Math: '<S146>/Math Function'
    //   Sum: '<S145>/Sum of Elements'

    Formation_FMS_DW.rtb_vn_idx_1 = Formation_FMS_DW.P_c[0] *
      Formation_FMS_DW.P_c[0] + Formation_FMS_DW.P_c[1] * Formation_FMS_DW.P_c[1];

    // Math: '<S146>/Math Function1' incorporates:
    //   Sum: '<S146>/Sum of Elements'
    //
    //  About '<S146>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_DW.rtb_vn_idx_1 < 0.0F) {
      Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.rtb_vn_idx_1));
    } else {
      Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.rtb_vn_idx_1);
    }

    // End of Math: '<S146>/Math Function1'

    // Switch: '<S146>/Switch' incorporates:
    //   Constant: '<S146>/Constant'
    //   Product: '<S146>/Product'

    if (Formation_FMS_DW.scale > 0.0F) {
      Formation_FMS_DW.pose[0] = *rtu_INS_Out_vn;
      Formation_FMS_DW.pose[1] = *rtu_INS_Out_ve;
      Formation_FMS_DW.pose[2] = Formation_FMS_DW.scale;
    } else {
      Formation_FMS_DW.pose[0] = Formation_FMS_DW.P_c[0] * 0.0F;
      Formation_FMS_DW.pose[1] = Formation_FMS_DW.P_c[1] * 0.0F;
      Formation_FMS_DW.pose[2] = 1.0F;
    }

    // End of Switch: '<S146>/Switch'

    // Delay: '<S139>/start_vel'
    if (Formation_FMS_DW.icLoad_c) {
      Formation_FMS_DW.start_vel_DSTATE[0] = Formation_FMS_DW.P_c[0];
      Formation_FMS_DW.start_vel_DSTATE[1] = Formation_FMS_DW.P_c[1];
    }

    // Sum: '<S151>/Sum of Elements' incorporates:
    //   Delay: '<S139>/start_vel'
    //   Math: '<S151>/Math Function'

    Formation_FMS_DW.scale = Formation_FMS_DW.start_vel_DSTATE[0] *
      Formation_FMS_DW.start_vel_DSTATE[0] + Formation_FMS_DW.start_vel_DSTATE[1]
      * Formation_FMS_DW.start_vel_DSTATE[1];

    // Math: '<S151>/Math Function1'
    //
    //  About '<S151>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_DW.scale < 0.0F) {
      Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
    } else {
      Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
    }

    // End of Math: '<S151>/Math Function1'

    // Switch: '<S151>/Switch' incorporates:
    //   Constant: '<S151>/Constant'
    //   Delay: '<S139>/start_vel'
    //   Product: '<S151>/Product'

    if (Formation_FMS_DW.scale > 0.0F) {
      Formation_FMS_DW.ve[0] = Formation_FMS_DW.start_vel_DSTATE[0];
      Formation_FMS_DW.ve[1] = Formation_FMS_DW.start_vel_DSTATE[1];
      Formation_FMS_DW.ve[2] = Formation_FMS_DW.scale;
    } else {
      Formation_FMS_DW.ve[0] = Formation_FMS_DW.start_vel_DSTATE[0] * 0.0F;
      Formation_FMS_DW.ve[1] = Formation_FMS_DW.start_vel_DSTATE[1] * 0.0F;
      Formation_FMS_DW.ve[2] = 1.0F;
    }

    // End of Switch: '<S151>/Switch'

    // Product: '<S146>/Divide'
    Formation_FMS_DW.P_c[0] = Formation_FMS_DW.pose[0] / Formation_FMS_DW.pose[2];
    Formation_FMS_DW.P_c[1] = Formation_FMS_DW.pose[1] / Formation_FMS_DW.pose[2];

    // Sum: '<S149>/Sum of Elements' incorporates:
    //   Math: '<S149>/Math Function'
    //   SignalConversion generated from: '<S149>/Math Function'

    Formation_FMS_DW.scale = Formation_FMS_DW.P_c[1] * Formation_FMS_DW.P_c[1] +
      Formation_FMS_DW.P_c[0] * Formation_FMS_DW.P_c[0];

    // Math: '<S149>/Math Function1'
    //
    //  About '<S149>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_DW.scale < 0.0F) {
      Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
    } else {
      Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
    }

    // End of Math: '<S149>/Math Function1'

    // Switch: '<S149>/Switch' incorporates:
    //   Constant: '<S149>/Constant'
    //   Product: '<S149>/Product'
    //   SignalConversion generated from: '<S149>/Math Function'

    if (Formation_FMS_DW.scale > 0.0F) {
      Formation_FMS_DW.pose[0] = Formation_FMS_DW.P_c[1];
      Formation_FMS_DW.pose[1] = Formation_FMS_DW.P_c[0];
      Formation_FMS_DW.pose[2] = Formation_FMS_DW.scale;
    } else {
      Formation_FMS_DW.pose[0] = Formation_FMS_DW.P_c[1] * 0.0F;
      Formation_FMS_DW.pose[1] = Formation_FMS_DW.P_c[0] * 0.0F;
      Formation_FMS_DW.pose[2] = 1.0F;
    }

    // End of Switch: '<S149>/Switch'

    // MinMax: '<S137>/Max' incorporates:
    //   Constant: '<S136>/L1'
    //   Constant: '<S136>/R'
    //   Gain: '<S137>/Gain'

    Formation_FMS_DW.rtb_y_R_idx_1 = std::fmax(FMS_PARAM.LOITER_R, 0.5F *
      FMS_PARAM.L1);

    // Reshape: '<S137>/Reshape2'
    Formation_FMS_DW.P_c[0] = *rtu_INS_Out_x_R;
    Formation_FMS_DW.P_c[1] = *rtu_INS_Out_y_R;

    // MATLAB Function: '<S137>/SearchL1RefWP' incorporates:
    //   Constant: '<S136>/L1'
    //   Reshape: '<S137>/Reshape2'

    Formation_FMS_DW.rtb_y_R_idx_0 = 0.0F;
    Formation_FMS_DW.rtb_x_R_idx_0 = 0.0F;
    if ((Formation_FMS_DW.P_c[0] == Formation_FMS_DW.Cmd_In.cur_waypoint[0]) &&
        (Formation_FMS_DW.P_c[1] == Formation_FMS_DW.Cmd_In.cur_waypoint[1]) &&
        (Formation_FMS_DW.rtb_y_R_idx_1 == FMS_PARAM.L1)) {
      Formation_FMS_DW.i = 0;
    } else {
      Formation_FMS_DW.scale = Formation_FMS_DW.Cmd_In.cur_waypoint[0] -
        Formation_FMS_DW.P_c[0];
      Formation_FMS_DW.TmpSignalConversionAtSqua_n[0] = Formation_FMS_DW.scale *
        Formation_FMS_DW.scale;
      Formation_FMS_DW.Reshape2_bi[0] = Formation_FMS_DW.scale;
      Formation_FMS_DW.scale = Formation_FMS_DW.Cmd_In.cur_waypoint[1] -
        Formation_FMS_DW.P_c[1];
      Formation_FMS_DW.absxk = std::sqrt(Formation_FMS_DW.scale *
        Formation_FMS_DW.scale + Formation_FMS_DW.TmpSignalConversionAtSqua_n[0]);
      Formation_FMS_DW.path_ratio = FMS_PARAM.L1 * FMS_PARAM.L1;
      Formation_FMS_DW.Multiply1_f = ((Formation_FMS_DW.absxk *
        Formation_FMS_DW.absxk + Formation_FMS_DW.path_ratio) -
        Formation_FMS_DW.rtb_y_R_idx_1 * Formation_FMS_DW.rtb_y_R_idx_1) / (2.0F
        * Formation_FMS_DW.absxk);
      Formation_FMS_DW.t_f = Formation_FMS_DW.Reshape2_bi[0] /
        Formation_FMS_DW.absxk;
      Formation_FMS_DW.scale /= Formation_FMS_DW.absxk;
      Formation_FMS_DW.absxk = Formation_FMS_DW.Multiply1_f *
        Formation_FMS_DW.Multiply1_f;
      if (Formation_FMS_DW.absxk > Formation_FMS_DW.path_ratio) {
        Formation_FMS_DW.i = 0;
      } else if (Formation_FMS_DW.absxk == Formation_FMS_DW.path_ratio) {
        Formation_FMS_DW.i = 1;
        Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.Multiply1_f *
          Formation_FMS_DW.t_f + Formation_FMS_DW.P_c[0];
        Formation_FMS_DW.rtb_x_R_idx_0 = Formation_FMS_DW.Multiply1_f *
          Formation_FMS_DW.scale + Formation_FMS_DW.P_c[1];
      } else {
        Formation_FMS_DW.i = 2;
        Formation_FMS_DW.absxk = std::sqrt(Formation_FMS_DW.path_ratio -
          Formation_FMS_DW.absxk);
        Formation_FMS_DW.rtb_y_R_idx_0 = (0.0F * Formation_FMS_DW.t_f -
          Formation_FMS_DW.scale) * Formation_FMS_DW.absxk +
          (Formation_FMS_DW.Multiply1_f * Formation_FMS_DW.t_f +
           Formation_FMS_DW.P_c[0]);
        Formation_FMS_DW.rtb_x_R_idx_0 = (0.0F * Formation_FMS_DW.scale +
          Formation_FMS_DW.t_f) * Formation_FMS_DW.absxk +
          (Formation_FMS_DW.Multiply1_f * Formation_FMS_DW.scale +
           Formation_FMS_DW.P_c[1]);
      }
    }

    // End of MATLAB Function: '<S137>/SearchL1RefWP'

    // MATLAB Function: '<S137>/OutRegionRegWP' incorporates:
    //   Reshape: '<S137>/Reshape2'

    Formation_FMS_DW.scale = Formation_FMS_DW.P_c[0] -
      Formation_FMS_DW.Cmd_In.cur_waypoint[0];
    Formation_FMS_DW.TmpSignalConversionAtSqua_n[0] = Formation_FMS_DW.scale *
      Formation_FMS_DW.scale;
    Formation_FMS_DW.scale = Formation_FMS_DW.P_c[1] -
      Formation_FMS_DW.Cmd_In.cur_waypoint[1];

    // Switch: '<S137>/Switch' incorporates:
    //   Constant: '<S140>/Constant'
    //   RelationalOperator: '<S140>/Compare'

    if (Formation_FMS_DW.i <= 0) {
      // MATLAB Function: '<S137>/OutRegionRegWP' incorporates:
      //   Constant: '<S136>/L1'
      //   Product: '<S151>/Divide'
      //   Reshape: '<S137>/Reshape2'

      Formation_FMS_DW.scale = Formation_FMS_DW.scale * Formation_FMS_DW.scale +
        Formation_FMS_DW.TmpSignalConversionAtSqua_n[0];
      Formation_FMS_DW.rtb_y_R_idx_1 *= Formation_FMS_DW.rtb_y_R_idx_1;
      if (Formation_FMS_DW.scale > Formation_FMS_DW.rtb_y_R_idx_1) {
        Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.Cmd_In.cur_waypoint[0];
      } else {
        Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.ve[0] /
          Formation_FMS_DW.ve[2] * FMS_PARAM.L1 + Formation_FMS_DW.P_c[0];
      }

      if (Formation_FMS_DW.scale > Formation_FMS_DW.rtb_y_R_idx_1) {
        Formation_FMS_DW.rtb_x_R_idx_0 = Formation_FMS_DW.Cmd_In.cur_waypoint[1];
      } else {
        Formation_FMS_DW.rtb_x_R_idx_0 = Formation_FMS_DW.ve[1] /
          Formation_FMS_DW.ve[2] * FMS_PARAM.L1 + Formation_FMS_DW.P_c[1];
      }
    }

    // Sum: '<S138>/Subtract' incorporates:
    //   Switch: '<S137>/Switch'

    Formation_FMS_DW.Reshape2_bi[0] = Formation_FMS_DW.rtb_y_R_idx_0 -
      *rtu_INS_Out_x_R;
    Formation_FMS_DW.Reshape2_bi[1] = Formation_FMS_DW.rtb_x_R_idx_0 -
      *rtu_INS_Out_y_R;

    // Sum: '<S147>/Sum of Elements' incorporates:
    //   Math: '<S147>/Math Function'
    //   Sum: '<S138>/Subtract'

    Formation_FMS_DW.scale = Formation_FMS_DW.Reshape2_bi[0] *
      Formation_FMS_DW.Reshape2_bi[0] + Formation_FMS_DW.Reshape2_bi[1] *
      Formation_FMS_DW.Reshape2_bi[1];

    // Math: '<S147>/Math Function1'
    //
    //  About '<S147>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_DW.scale < 0.0F) {
      Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
    } else {
      Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
    }

    // End of Math: '<S147>/Math Function1'

    // Switch: '<S147>/Switch' incorporates:
    //   Constant: '<S147>/Constant'
    //   Product: '<S147>/Product'
    //   Sum: '<S138>/Subtract'
    //   Switch: '<S150>/Switch'

    if (Formation_FMS_DW.scale > 0.0F) {
      Formation_FMS_DW.ve[0] = Formation_FMS_DW.Reshape2_bi[0];
      Formation_FMS_DW.ve[1] = Formation_FMS_DW.Reshape2_bi[1];
      Formation_FMS_DW.ve[2] = Formation_FMS_DW.scale;
    } else {
      Formation_FMS_DW.ve[0] = Formation_FMS_DW.Reshape2_bi[0] * 0.0F;
      Formation_FMS_DW.ve[1] = Formation_FMS_DW.Reshape2_bi[1] * 0.0F;
      Formation_FMS_DW.ve[2] = 1.0F;
    }

    // End of Switch: '<S147>/Switch'

    // Product: '<S147>/Divide' incorporates:
    //   Product: '<S150>/Divide'

    Formation_FMS_DW.P_c[0] = Formation_FMS_DW.ve[0] / Formation_FMS_DW.ve[2];
    Formation_FMS_DW.P_c[1] = Formation_FMS_DW.ve[1] / Formation_FMS_DW.ve[2];

    // Sum: '<S150>/Sum of Elements' incorporates:
    //   Math: '<S150>/Math Function'
    //   SignalConversion generated from: '<S150>/Math Function'

    Formation_FMS_DW.scale = Formation_FMS_DW.P_c[1] * Formation_FMS_DW.P_c[1] +
      Formation_FMS_DW.P_c[0] * Formation_FMS_DW.P_c[0];

    // Math: '<S150>/Math Function1'
    //
    //  About '<S150>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_DW.scale < 0.0F) {
      Formation_FMS_DW.scale = -std::sqrt(std::abs(Formation_FMS_DW.scale));
    } else {
      Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.scale);
    }

    // End of Math: '<S150>/Math Function1'

    // Switch: '<S150>/Switch' incorporates:
    //   Constant: '<S150>/Constant'
    //   Product: '<S150>/Product'
    //   SignalConversion generated from: '<S150>/Math Function'

    if (Formation_FMS_DW.scale > 0.0F) {
      Formation_FMS_DW.ve[0] = Formation_FMS_DW.P_c[1];
      Formation_FMS_DW.ve[1] = Formation_FMS_DW.P_c[0];
      Formation_FMS_DW.ve[2] = Formation_FMS_DW.scale;
    } else {
      Formation_FMS_DW.ve[0] = Formation_FMS_DW.P_c[1] * 0.0F;
      Formation_FMS_DW.ve[1] = Formation_FMS_DW.P_c[0] * 0.0F;
      Formation_FMS_DW.ve[2] = 1.0F;
    }

    // End of Switch: '<S150>/Switch'

    // Product: '<S150>/Divide'
    Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.ve[0] / Formation_FMS_DW.ve
      [2];

    // Product: '<S149>/Divide'
    Formation_FMS_DW.absxk = Formation_FMS_DW.pose[0] / Formation_FMS_DW.pose[2];

    // DotProduct: '<S144>/Dot Product'
    Formation_FMS_DW.rtb_x_R_idx_0 = Formation_FMS_DW.absxk *
      Formation_FMS_DW.Multiply1_f;
    Formation_FMS_DW.P_c[0] = Formation_FMS_DW.Multiply1_f;
    Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.absxk;

    // Product: '<S150>/Divide' incorporates:
    //   Product: '<S149>/Divide'

    Formation_FMS_DW.Multiply1_f = Formation_FMS_DW.ve[1] / Formation_FMS_DW.ve
      [2];

    // Product: '<S149>/Divide'
    Formation_FMS_DW.absxk = Formation_FMS_DW.pose[1] / Formation_FMS_DW.pose[2];

    // DotProduct: '<S144>/Dot Product'
    Formation_FMS_DW.rtb_x_R_idx_0 += Formation_FMS_DW.absxk *
      Formation_FMS_DW.Multiply1_f;

    // Sqrt: '<S145>/Sqrt'
    Formation_FMS_DW.scale = std::sqrt(Formation_FMS_DW.rtb_vn_idx_1);

    // Math: '<S143>/Square'
    Formation_FMS_DW.rtb_y_R_idx_1 = Formation_FMS_DW.scale *
      Formation_FMS_DW.scale;

    // Sum: '<S148>/Subtract' incorporates:
    //   Product: '<S148>/Multiply'
    //   Product: '<S148>/Multiply1'

    Formation_FMS_DW.rtb_y_R_idx_0 = Formation_FMS_DW.P_c[0] *
      Formation_FMS_DW.absxk - Formation_FMS_DW.rtb_y_R_idx_0 *
      Formation_FMS_DW.Multiply1_f;

    // Signum: '<S144>/Sign1'
    if (std::isnan(Formation_FMS_DW.rtb_y_R_idx_0)) {
      Formation_FMS_DW.scale = (rtNaNF);
    } else if (Formation_FMS_DW.rtb_y_R_idx_0 < 0.0F) {
      Formation_FMS_DW.scale = -1.0F;
    } else {
      Formation_FMS_DW.scale = (Formation_FMS_DW.rtb_y_R_idx_0 > 0.0F);
    }

    // End of Signum: '<S144>/Sign1'

    // Trigonometry: '<S144>/Acos' incorporates:
    //   DotProduct: '<S144>/Dot Product'

    if (Formation_FMS_DW.rtb_x_R_idx_0 > 1.0F) {
      Formation_FMS_DW.rtb_x_R_idx_0 = 1.0F;
    } else if (Formation_FMS_DW.rtb_x_R_idx_0 < -1.0F) {
      Formation_FMS_DW.rtb_x_R_idx_0 = -1.0F;
    }

    // Switch: '<S144>/Switch2' incorporates:
    //   Constant: '<S144>/Constant4'

    if (!(Formation_FMS_DW.scale != 0.0F)) {
      Formation_FMS_DW.scale = 1.0F;
    }

    // Product: '<S144>/Multiply' incorporates:
    //   Switch: '<S144>/Switch2'
    //   Trigonometry: '<S144>/Acos'

    Formation_FMS_DW.path_ratio = std::acos(Formation_FMS_DW.rtb_x_R_idx_0) *
      Formation_FMS_DW.scale;

    // Sum: '<S134>/Sum' incorporates:
    //   Constant: '<S134>/Constant'

    Formation_FMS_DW.scale = FMS_PARAM.FW_AIRSPD_TRIM - *rtu_INS_Out_airspeed;

    // Delay: '<S135>/Delay' incorporates:
    //   Constant: '<S135>/Constant'

    if (Formation_FMS_DW.icLoad_j) {
      Formation_FMS_DW.Delay_DSTATE_m = FMS_PARAM.FW_HEIGHT_TRIM;
    }

    // Sum: '<S135>/Sum' incorporates:
    //   Delay: '<S135>/Delay'

    Formation_FMS_DW.absxk = Formation_FMS_DW.Delay_DSTATE_m - *rtu_INS_Out_h_R;

    // End of Outputs for SubSystem: '<S10>/Hold'
    std::memset(&Formation_FMS_DW.Merge, 0, sizeof(FMS_Out_Bus));

    // Outputs for IfAction SubSystem: '<S10>/Hold' incorporates:
    //   ActionPort: '<S14>/Action Port'

    // BusAssignment: '<S14>/Bus Assignment' incorporates:
    //   Constant: '<S14>/Constant1'
    //   Merge: '<S10>/Merge'

    Formation_FMS_DW.Merge.state = VehicleState::Hold;
    Formation_FMS_DW.Merge.ax_cmd = Formation_FMS_DW.scale;

    // Saturate: '<S143>/Saturation'
    if (Formation_FMS_DW.path_ratio > 1.57079637F) {
      Formation_FMS_DW.path_ratio = 1.57079637F;
    } else if (Formation_FMS_DW.path_ratio < -1.57079637F) {
      Formation_FMS_DW.path_ratio = -1.57079637F;
    }

    // BusAssignment: '<S14>/Bus Assignment' incorporates:
    //   Constant: '<S136>/L1'
    //   Gain: '<S143>/Gain'
    //   Product: '<S143>/Divide'
    //   Product: '<S143>/Multiply1'
    //   Saturate: '<S143>/Saturation'
    //   Trigonometry: '<S143>/Sin'

    Formation_FMS_DW.Merge.ay_cmd = 2.0F * Formation_FMS_DW.rtb_y_R_idx_1 * std::
      sin(Formation_FMS_DW.path_ratio) / FMS_PARAM.L1;

    // Gain: '<S135>/Gain2'
    Formation_FMS_DW.path_ratio = FMS_PARAM.Z_P * Formation_FMS_DW.absxk;

    // Saturate: '<S135>/Saturation'
    if (Formation_FMS_DW.path_ratio > CONTROL_PARAM.FW_T_CLMB_MAX) {
      // BusAssignment: '<S14>/Bus Assignment'
      Formation_FMS_DW.Merge.vh_cmd = CONTROL_PARAM.FW_T_CLMB_MAX;
    } else if (Formation_FMS_DW.path_ratio < -CONTROL_PARAM.FW_T_SINK_MAX) {
      // BusAssignment: '<S14>/Bus Assignment'
      Formation_FMS_DW.Merge.vh_cmd = -CONTROL_PARAM.FW_T_SINK_MAX;
    } else {
      // BusAssignment: '<S14>/Bus Assignment'
      Formation_FMS_DW.Merge.vh_cmd = Formation_FMS_DW.path_ratio;
    }

    // End of Saturate: '<S135>/Saturation'

    // Update for Delay: '<S139>/start_vel'
    Formation_FMS_DW.icLoad_c = false;

    // Update for Delay: '<S135>/Delay'
    Formation_FMS_DW.icLoad_j = false;

    // End of Outputs for SubSystem: '<S10>/Hold'
    break;

   default:
    // InitializeConditions for IfAction SubSystem: '<S10>/Default' incorporates:
    //   ActionPort: '<S11>/Action Port'

    // InitializeConditions for SwitchCase: '<S10>/Switch Case' incorporates:
    //   Delay: '<S16>/Delay'

    Formation_FMS_DW.icLoad = ((rtAction != rtPrevAction) ||
      Formation_FMS_DW.icLoad);

    // End of InitializeConditions for SubSystem: '<S10>/Default'

    // Outputs for IfAction SubSystem: '<S10>/Default' incorporates:
    //   ActionPort: '<S11>/Action Port'

    // Sum: '<S15>/Sum' incorporates:
    //   Constant: '<S15>/Constant'

    Formation_FMS_DW.scale = FMS_PARAM.FW_AIRSPD_TRIM - *rtu_INS_Out_airspeed;

    // Delay: '<S16>/Delay'
    if (Formation_FMS_DW.icLoad) {
      Formation_FMS_DW.Delay_DSTATE = *rtu_INS_Out_h_R;
    }

    // Sum: '<S16>/Sum' incorporates:
    //   Delay: '<S16>/Delay'

    Formation_FMS_DW.rtb_y_R_idx_1 = Formation_FMS_DW.Delay_DSTATE -
      *rtu_INS_Out_h_R;

    // End of Outputs for SubSystem: '<S10>/Default'
    std::memset(&Formation_FMS_DW.Merge, 0, sizeof(FMS_Out_Bus));

    // Outputs for IfAction SubSystem: '<S10>/Default' incorporates:
    //   ActionPort: '<S11>/Action Port'

    // BusAssignment: '<S11>/Bus Assignment' incorporates:
    //   Constant: '<S11>/Constant1'
    //   Merge: '<S10>/Merge'

    Formation_FMS_DW.Merge.state = VehicleState::None;
    Formation_FMS_DW.Merge.ax_cmd = Formation_FMS_DW.scale;
    Formation_FMS_DW.Merge.ay_cmd = 0.0F;

    // Gain: '<S16>/Gain2'
    Formation_FMS_DW.path_ratio = FMS_PARAM.Z_P * Formation_FMS_DW.rtb_y_R_idx_1;

    // Saturate: '<S16>/Saturation'
    if (Formation_FMS_DW.path_ratio > CONTROL_PARAM.FW_T_CLMB_MAX) {
      // BusAssignment: '<S11>/Bus Assignment'
      Formation_FMS_DW.Merge.vh_cmd = CONTROL_PARAM.FW_T_CLMB_MAX;
    } else if (Formation_FMS_DW.path_ratio < -CONTROL_PARAM.FW_T_SINK_MAX) {
      // BusAssignment: '<S11>/Bus Assignment'
      Formation_FMS_DW.Merge.vh_cmd = -CONTROL_PARAM.FW_T_SINK_MAX;
    } else {
      // BusAssignment: '<S11>/Bus Assignment'
      Formation_FMS_DW.Merge.vh_cmd = Formation_FMS_DW.path_ratio;
    }

    // End of Saturate: '<S16>/Saturation'

    // Update for Delay: '<S16>/Delay'
    Formation_FMS_DW.icLoad = false;

    // End of Outputs for SubSystem: '<S10>/Default'
    break;
  }

  // End of SwitchCase: '<S10>/Switch Case'

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_type[0] = Formation_FMS_DW.Other_Mission_Data.type[0];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_valid_it[0] =
    Formation_FMS_DW.Other_Mission_Data.valid_items[0];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_type[1] = Formation_FMS_DW.Other_Mission_Data.type[1];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_valid_it[1] =
    Formation_FMS_DW.Other_Mission_Data.valid_items[1];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_type[2] = Formation_FMS_DW.Other_Mission_Data.type[2];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_valid_it[2] =
    Formation_FMS_DW.Other_Mission_Data.valid_items[2];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  *rty_Other_Mission_Data_timestam =
    Formation_FMS_DW.Other_Mission_Data.timestamp;

  // SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_timestamp = Formation_FMS_DW.Merge.timestamp;

  // SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_state = Formation_FMS_DW.Merge.state;

  // SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_ax_cmd = Formation_FMS_DW.Merge.ax_cmd;

  // SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_ay_cmd = Formation_FMS_DW.Merge.ay_cmd;

  // SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_vh_cmd = Formation_FMS_DW.Merge.vh_cmd;
}

// Model initialize function
void Formation_FMS::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  Formation_FMS_PrevZCX.FormMission_SubSystem_Reset_ZCE = POS_ZCSIG;
  Formation_FMS_PrevZCX.Mission_SubSystem_Reset_ZCE = POS_ZCSIG;
}

// Constructor
Formation_FMS::Formation_FMS() :
  Formation_FMS_DW(),
  Formation_FMS_PrevZCX(),
  Formation_FMS_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
Formation_FMS::~Formation_FMS()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
Formation_FMS::RT_MODEL_Formation_FMS_T * Formation_FMS::getRTM()
{
  return (&Formation_FMS_M);
}

// member function to setup error status pointer
void Formation_FMS::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&Formation_FMS_M), rt_errorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
