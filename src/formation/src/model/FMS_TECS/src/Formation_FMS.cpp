//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Formation_FMS.cpp
//
// Code generated for Simulink model 'Formation_FMS'.
//
// Model version                  : 1.225
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Sat Apr 20 16:39:47 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "Formation_FMS.h"
#include "rtwtypes.h"
#include <cmath>
#include <cstring>
#include "norm_FqL2z8vo.h"
#include "rt_atan2f_snf.h"
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

const uint8_T Formation_FMS_IN_Hold{ 1U };

const uint8_T Formation_FMS_IN_InvalidMode{ 4U };

const uint8_T Formation_FMS_IN_NextWP{ 2U };

const uint8_T Formation_FMS_IN_Standby{ 2U };

const uint8_T Formation_FMS_IN_WaitForUpdate{ 3U };

const uint8_T Formation_FMS_IN_Waypoint{ 4U };

const uint8_T Formation_FMS_IN_Waypoint_g{ 3U };

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
//    '<S30>/NearbyRefWP'
//    '<S166>/NearbyRefWP'
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
//    '<S30>/OutRegionRegWP'
//    '<S166>/OutRegionRegWP'
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
//    '<S30>/SearchL1RefWP'
//    '<S166>/SearchL1RefWP'
//
void Formation_FMS::Formation_FMS_SearchL1RefWP(const real32_T rtu_P1[2], const
  real32_T rtu_P2[2], const real32_T rtu_P3[2], real32_T rtu_L1, real32_T rty_P
  [2], real32_T *rty_u)
{
  real32_T A;
  real32_T B;
  real32_T D;
  real32_T a_tmp;
  real32_T b_a_tmp;
  real32_T u;
  boolean_T guard1;
  a_tmp = rtu_P2[0] - rtu_P1[0];
  b_a_tmp = rtu_P2[1] - rtu_P1[1];
  A = a_tmp * a_tmp + b_a_tmp * b_a_tmp;
  B = ((rtu_P1[0] - rtu_P3[0]) * a_tmp + (rtu_P1[1] - rtu_P3[1]) * b_a_tmp) *
    2.0F;
  D = B * B - (((((rtu_P3[0] * rtu_P3[0] + rtu_P3[1] * rtu_P3[1]) + rtu_P1[0] *
                  rtu_P1[0]) + rtu_P1[1] * rtu_P1[1]) - (rtu_P3[0] * rtu_P1[0] +
    rtu_P3[1] * rtu_P1[1]) * 2.0F) - rtu_L1 * rtu_L1) * (4.0F * A);
  u = -1.0F;
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
        u = D;
      } else {
        u = A;
      }

      guard1 = true;
    } else if ((D >= 0.0F) && (D <= 1.0F)) {
      u = D;
      guard1 = true;
    } else if ((A >= 0.0F) && (A <= 1.0F)) {
      u = A;
      guard1 = true;
    }
  } else if (D == 0.0F) {
    D = -B / (2.0F * A);
    if ((D >= 0.0F) && (D <= 1.0F)) {
      u = D;
      guard1 = true;
    }
  }

  if (guard1) {
    rty_P[0] = a_tmp * u + rtu_P1[0];
    rty_P[1] = b_a_tmp * u + rtu_P1[1];
  }

  *rty_u = u;
}

//
// Output and update for atomic system:
//    '<S66>/OutRegionRegWP'
//    '<S48>/OutRegionRegWP'
//    '<S184>/OutRegionRegWP'
//
void Formation_FMS::Formation_FMS_OutRegionRegWP_o(const real32_T rtu_P0[2],
  const real32_T rtu_P_Vehicle[2], real32_T rtu_R, real32_T rtu_L1, const
  real32_T rtu_n[2], real32_T rty_P[2])
{
  real32_T x;
  real32_T y_idx_0;
  x = rtu_P_Vehicle[0] - rtu_P0[0];
  y_idx_0 = x * x;
  x = rtu_P_Vehicle[1] - rtu_P0[1];
  if (x * x + y_idx_0 > rtu_R * rtu_R) {
    rty_P[0] = rtu_P0[0];
    rty_P[1] = rtu_P0[1];
  } else {
    rty_P[0] = rtu_n[0] * rtu_L1 + rtu_P_Vehicle[0];
    rty_P[1] = rtu_n[1] * rtu_L1 + rtu_P_Vehicle[1];
  }
}

//
// Output and update for atomic system:
//    '<S66>/SearchL1RefWP'
//    '<S48>/SearchL1RefWP'
//    '<S184>/SearchL1RefWP'
//
void Formation_FMS::Formation_FMS_SearchL1RefWP_i(const real32_T rtu_P_0[2],
  const real32_T rtu_P_Vehicle[2], real32_T rtu_R, real32_T rtu_L1, real32_T
  rty_P[2], real_T *rty_n)
{
  rty_P[0] = 0.0F;
  rty_P[1] = 0.0F;
  if ((rtu_P_Vehicle[0] == rtu_P_0[0]) && (rtu_P_Vehicle[1] == rtu_P_0[1]) &&
      (rtu_R == rtu_L1)) {
    *rty_n = 0.0;
  } else {
    real32_T a;
    real32_T a_tmp;
    real32_T d;
    real32_T n0;
    real32_T n0_idx_0;
    n0 = rtu_P_0[0] - rtu_P_Vehicle[0];
    a = n0 * n0;
    n0_idx_0 = n0;
    n0 = rtu_P_0[1] - rtu_P_Vehicle[1];
    d = std::sqrt(n0 * n0 + a);
    a_tmp = rtu_L1 * rtu_L1;
    a = ((d * d + a_tmp) - rtu_R * rtu_R) / (2.0F * d);
    n0_idx_0 /= d;
    n0 /= d;
    d = a * a;
    if (d > a_tmp) {
      *rty_n = 0.0;
    } else if (d == a_tmp) {
      *rty_n = 1.0;
      rty_P[0] = a * n0_idx_0 + rtu_P_Vehicle[0];
      rty_P[1] = a * n0 + rtu_P_Vehicle[1];
    } else {
      *rty_n = 2.0;
      a_tmp = std::sqrt(a_tmp - d);
      rty_P[0] = (0.0F * n0_idx_0 - n0) * a_tmp + (a * n0_idx_0 + rtu_P_Vehicle
        [0]);
      rty_P[1] = (0.0F * n0 + n0_idx_0) * a_tmp + (a * n0 + rtu_P_Vehicle[1]);
    }
  }
}

//
// Output and update for atomic system:
//    '<S99>/signNoZero'
//    '<S101>/signNoZero'
//
void Formation_FMS::Formation_FMS_signNoZero(real32_T rtu_u, real32_T *rty_y)
{
  *rty_y = static_cast<real32_T>((rtu_u >= 0.0F) - (rtu_u < 0.0F));
}

//
// System initialize for action system:
//    '<S12>/Default'
//    '<S10>/Default'
//
void Formation_FMS::Formation_FMS_Default_Init(DW_Default_Formation_FMS_T
  *localDW)
{
  // InitializeConditions for Delay: '<S22>/Delay'
  localDW->icLoad = true;
}

//
// System reset for action system:
//    '<S12>/Default'
//    '<S10>/Default'
//
void Formation_FMS::Formation_FMS_Default_Reset(DW_Default_Formation_FMS_T
  *localDW)
{
  // InitializeConditions for Delay: '<S22>/Delay'
  localDW->icLoad = true;
}

//
// Output and update for action system:
//    '<S12>/Default'
//    '<S10>/Default'
//
void Formation_FMS::Formation_FMS_Default(const real32_T *rtu_FMS_In, const
  real32_T *rtu_FMS_In_h, FMS_Out_Bus *rty_FMS_Out, DW_Default_Formation_FMS_T
  *localDW)
{
  real32_T rtb_h_err_R_m;
  real32_T rtb_v_error_d;

  // Sum: '<S21>/Sum' incorporates:
  //   Constant: '<S21>/Constant'

  rtb_v_error_d = FMS_PARAM.FW_AIRSPD_TRIM - *rtu_FMS_In;

  // Delay: '<S22>/Delay'
  if (localDW->icLoad) {
    localDW->Delay_DSTATE = *rtu_FMS_In_h;
  }

  // Sum: '<S22>/Sum' incorporates:
  //   Delay: '<S22>/Delay'

  rtb_h_err_R_m = localDW->Delay_DSTATE - *rtu_FMS_In_h;
  std::memset(rty_FMS_Out, 0, sizeof(FMS_Out_Bus));

  // BusAssignment: '<S16>/Bus Assignment' incorporates:
  //   Constant: '<S16>/Constant1'

  rty_FMS_Out->state = VehicleState::None;
  rty_FMS_Out->ax_cmd = rtb_v_error_d;
  rty_FMS_Out->ay_cmd = 0.0F;

  // Gain: '<S22>/Gain2'
  rtb_v_error_d = FMS_PARAM.Z_P * rtb_h_err_R_m;

  // Saturate: '<S22>/Saturation'
  if (rtb_v_error_d > CONTROL_PARAM.FW_T_CLMB_MAX) {
    // BusAssignment: '<S16>/Bus Assignment'
    rty_FMS_Out->vh_cmd = CONTROL_PARAM.FW_T_CLMB_MAX;
  } else if (rtb_v_error_d < -CONTROL_PARAM.FW_T_SINK_MAX) {
    // BusAssignment: '<S16>/Bus Assignment'
    rty_FMS_Out->vh_cmd = -CONTROL_PARAM.FW_T_SINK_MAX;
  } else {
    // BusAssignment: '<S16>/Bus Assignment'
    rty_FMS_Out->vh_cmd = rtb_v_error_d;
  }

  // End of Saturate: '<S22>/Saturation'

  // Update for Delay: '<S22>/Delay'
  localDW->icLoad = false;
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

// Function for MATLAB Function: '<S199>/MATLAB Function'
real_T Formation_FMS::Formation_FMS_atan3_9FIHpp9F(real_T x, real_T y, real_T x0,
  real_T b_y0)
{
  real_T result;
  Formation_FMS_B.deltax = x - x0;
  Formation_FMS_B.deltay = y - b_y0;
  if ((Formation_FMS_B.deltax > 0.0) && (Formation_FMS_B.deltay > 0.0)) {
    result = std::atan(Formation_FMS_B.deltay / Formation_FMS_B.deltax);
  } else if ((Formation_FMS_B.deltax > 0.0) && (Formation_FMS_B.deltay < 0.0)) {
    result = std::atan(Formation_FMS_B.deltay / Formation_FMS_B.deltax) +
      6.2831853071795862;
  } else if (Formation_FMS_B.deltax < 0.0) {
    result = std::atan(Formation_FMS_B.deltay / Formation_FMS_B.deltax) +
      3.1415926535897931;
  } else if (Formation_FMS_B.deltax == 0.0) {
    if (Formation_FMS_B.deltay > 0.0) {
      result = 1.5707963267948966;
    } else {
      result = 4.71238898038469;
    }
  } else if (Formation_FMS_B.deltax > 0.0) {
    result = 0.0;
  } else {
    result = 3.1415926535897931;
  }

  return result;
}

// Function for MATLAB Function: '<S199>/MATLAB Function'
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
  int8_T j_data[4];
  boolean_T exitg1;
  *r = v * v / 9.81 / std::tan(PhiMaximum->contents / rad2deg->contents);
  Formation_FMS_B.l_best = psi_s / rad2deg->contents;
  Formation_FMS_B.pos_tmp = std::sin(Formation_FMS_B.l_best) * *r;
  pos[0] = Formation_FMS_B.pos_tmp + xs;
  Formation_FMS_B.l_best = std::cos(Formation_FMS_B.l_best) * *r;
  pos[2] = ys - Formation_FMS_B.l_best;
  pos[1] = xs - Formation_FMS_B.pos_tmp;
  pos[3] = Formation_FMS_B.l_best + ys;
  Formation_FMS_B.l_best = psi_f / rad2deg->contents;
  Formation_FMS_B.pos_tmp = std::sin(Formation_FMS_B.l_best) * *r;
  pof[0] = Formation_FMS_B.pos_tmp + xf;
  Formation_FMS_B.l_best = std::cos(Formation_FMS_B.l_best) * *r;
  pof[2] = yf - Formation_FMS_B.l_best;
  pof[1] = xf - Formation_FMS_B.pos_tmp;
  pof[3] = Formation_FMS_B.l_best + yf;
  Formation_FMS_B.pos_tmp = Formation_FMS_atan3_9FIHpp9F(pof[0], pof[2], pos[0],
    pos[2]);
  Formation_FMS_B.xts_tmp = *r * std::sin(Formation_FMS_B.pos_tmp);
  Formation_FMS_B.l_best = pos[0] - Formation_FMS_B.xts_tmp;
  Formation_FMS_B.yts_tmp = *r * std::cos(Formation_FMS_B.pos_tmp);
  Formation_FMS_B.pos_tmp = Formation_FMS_B.yts_tmp + pos[2];
  Formation_FMS_B.xts_tmp = pof[0] - Formation_FMS_B.xts_tmp;
  Formation_FMS_B.yts_tmp += pof[2];
  Formation_FMS_B.cs_tmp = xs - Formation_FMS_B.l_best;
  Formation_FMS_B.cs_tmp_c = ys - Formation_FMS_B.pos_tmp;
  Formation_FMS_B.cs_tmp = std::asin(std::sqrt(Formation_FMS_B.cs_tmp *
    Formation_FMS_B.cs_tmp + Formation_FMS_B.cs_tmp_c * Formation_FMS_B.cs_tmp_c)
    / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_B.cs_tmp_c = xf - Formation_FMS_B.xts_tmp;
  Formation_FMS_B.cf_tmp = yf - Formation_FMS_B.yts_tmp;
  Formation_FMS_B.cs_tmp_c = std::asin(std::sqrt(Formation_FMS_B.cs_tmp_c *
    Formation_FMS_B.cs_tmp_c + Formation_FMS_B.cf_tmp * Formation_FMS_B.cf_tmp) /
    2.0 / *r) * (*r * 2.0);
  Formation_FMS_B.cf_tmp = Formation_FMS_B.xts_tmp - Formation_FMS_B.l_best;
  Formation_FMS_B.lt_tmp = Formation_FMS_B.yts_tmp - Formation_FMS_B.pos_tmp;
  Formation_FMS_B.cf_tmp = std::sqrt(Formation_FMS_B.cf_tmp *
    Formation_FMS_B.cf_tmp + Formation_FMS_B.lt_tmp * Formation_FMS_B.lt_tmp);
  l[0] = (Formation_FMS_B.cs_tmp + Formation_FMS_B.cs_tmp_c) +
    Formation_FMS_B.cf_tmp;
  xts[0] = Formation_FMS_B.l_best;
  yts[0] = Formation_FMS_B.pos_tmp;
  xtf[0] = Formation_FMS_B.xts_tmp;
  ytf[0] = Formation_FMS_B.yts_tmp;
  cs[0] = Formation_FMS_B.cs_tmp;
  cf[0] = Formation_FMS_B.cs_tmp_c;
  lt[0] = Formation_FMS_B.cf_tmp;
  Formation_FMS_B.l_best = pof[3] - pos[2];
  Formation_FMS_B.pos_tmp = pof[1] - pos[0];
  Formation_FMS_B.pos_tmp = std::acos(*r * 2.0 / std::sqrt
    (Formation_FMS_B.l_best * Formation_FMS_B.l_best + Formation_FMS_B.pos_tmp *
     Formation_FMS_B.pos_tmp)) + Formation_FMS_atan3_9FIHpp9F(pof[1], pof[3],
    pos[0], pos[2]);
  Formation_FMS_B.xts_tmp = *r * std::cos(Formation_FMS_B.pos_tmp);
  Formation_FMS_B.l_best = Formation_FMS_B.xts_tmp + pos[0];
  Formation_FMS_B.yts_tmp = *r * std::sin(Formation_FMS_B.pos_tmp);
  Formation_FMS_B.pos_tmp = Formation_FMS_B.yts_tmp + pos[2];
  Formation_FMS_B.xts_tmp = pof[1] - Formation_FMS_B.xts_tmp;
  Formation_FMS_B.yts_tmp = pof[3] - Formation_FMS_B.yts_tmp;
  Formation_FMS_B.cs_tmp = xs - Formation_FMS_B.l_best;
  Formation_FMS_B.cs_tmp_c = ys - Formation_FMS_B.pos_tmp;
  Formation_FMS_B.cs_tmp = std::asin(std::sqrt(Formation_FMS_B.cs_tmp *
    Formation_FMS_B.cs_tmp + Formation_FMS_B.cs_tmp_c * Formation_FMS_B.cs_tmp_c)
    / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_B.cs_tmp_c = xf - Formation_FMS_B.xts_tmp;
  Formation_FMS_B.cf_tmp = yf - Formation_FMS_B.yts_tmp;
  Formation_FMS_B.cs_tmp_c = std::asin(std::sqrt(Formation_FMS_B.cs_tmp_c *
    Formation_FMS_B.cs_tmp_c + Formation_FMS_B.cf_tmp * Formation_FMS_B.cf_tmp) /
    2.0 / *r) * (*r * 2.0);
  Formation_FMS_B.cf_tmp = Formation_FMS_B.xts_tmp - Formation_FMS_B.l_best;
  Formation_FMS_B.lt_tmp = Formation_FMS_B.yts_tmp - Formation_FMS_B.pos_tmp;
  Formation_FMS_B.cf_tmp = std::sqrt(Formation_FMS_B.cf_tmp *
    Formation_FMS_B.cf_tmp + Formation_FMS_B.lt_tmp * Formation_FMS_B.lt_tmp);
  l[2] = (Formation_FMS_B.cs_tmp + Formation_FMS_B.cs_tmp_c) +
    Formation_FMS_B.cf_tmp;
  xts[2] = Formation_FMS_B.l_best;
  yts[2] = Formation_FMS_B.pos_tmp;
  xtf[2] = Formation_FMS_B.xts_tmp;
  ytf[2] = Formation_FMS_B.yts_tmp;
  cs[2] = Formation_FMS_B.cs_tmp;
  cf[2] = Formation_FMS_B.cs_tmp_c;
  lt[2] = Formation_FMS_B.cf_tmp;
  Formation_FMS_B.l_best = pof[2] - pos[3];
  Formation_FMS_B.pos_tmp = pof[0] - pos[1];
  Formation_FMS_B.pos_tmp = Formation_FMS_atan3_9FIHpp9F(pof[0], pof[2], pos[1],
    pos[3]) - std::acos(*r * 2.0 / std::sqrt(Formation_FMS_B.l_best *
    Formation_FMS_B.l_best + Formation_FMS_B.pos_tmp * Formation_FMS_B.pos_tmp));
  Formation_FMS_B.xts_tmp = *r * std::cos(Formation_FMS_B.pos_tmp);
  Formation_FMS_B.l_best = Formation_FMS_B.xts_tmp + pos[1];
  Formation_FMS_B.yts_tmp = *r * std::sin(Formation_FMS_B.pos_tmp);
  Formation_FMS_B.pos_tmp = Formation_FMS_B.yts_tmp + pos[3];
  Formation_FMS_B.xts_tmp = pof[0] - Formation_FMS_B.xts_tmp;
  Formation_FMS_B.yts_tmp = pof[2] - Formation_FMS_B.yts_tmp;
  Formation_FMS_B.cs_tmp = xs - Formation_FMS_B.l_best;
  Formation_FMS_B.cs_tmp_c = ys - Formation_FMS_B.pos_tmp;
  Formation_FMS_B.cs_tmp = std::asin(std::sqrt(Formation_FMS_B.cs_tmp *
    Formation_FMS_B.cs_tmp + Formation_FMS_B.cs_tmp_c * Formation_FMS_B.cs_tmp_c)
    / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_B.cs_tmp_c = xf - Formation_FMS_B.xts_tmp;
  Formation_FMS_B.cf_tmp = yf - Formation_FMS_B.yts_tmp;
  Formation_FMS_B.cs_tmp_c = std::asin(std::sqrt(Formation_FMS_B.cs_tmp_c *
    Formation_FMS_B.cs_tmp_c + Formation_FMS_B.cf_tmp * Formation_FMS_B.cf_tmp) /
    2.0 / *r) * (*r * 2.0);
  Formation_FMS_B.cf_tmp = Formation_FMS_B.xts_tmp - Formation_FMS_B.l_best;
  Formation_FMS_B.lt_tmp = Formation_FMS_B.yts_tmp - Formation_FMS_B.pos_tmp;
  Formation_FMS_B.cf_tmp = std::sqrt(Formation_FMS_B.cf_tmp *
    Formation_FMS_B.cf_tmp + Formation_FMS_B.lt_tmp * Formation_FMS_B.lt_tmp);
  l[1] = (Formation_FMS_B.cs_tmp + Formation_FMS_B.cs_tmp_c) +
    Formation_FMS_B.cf_tmp;
  xts[1] = Formation_FMS_B.l_best;
  yts[1] = Formation_FMS_B.pos_tmp;
  xtf[1] = Formation_FMS_B.xts_tmp;
  ytf[1] = Formation_FMS_B.yts_tmp;
  cs[1] = Formation_FMS_B.cs_tmp;
  cf[1] = Formation_FMS_B.cs_tmp_c;
  lt[1] = Formation_FMS_B.cf_tmp;
  Formation_FMS_B.pos_tmp = Formation_FMS_atan3_9FIHpp9F(pof[1], pof[3], pos[1],
    pos[3]);
  Formation_FMS_B.xts_tmp = *r * std::sin(Formation_FMS_B.pos_tmp);
  Formation_FMS_B.l_best = Formation_FMS_B.xts_tmp + pos[1];
  Formation_FMS_B.yts_tmp = *r * std::cos(Formation_FMS_B.pos_tmp);
  Formation_FMS_B.pos_tmp = pos[3] - Formation_FMS_B.yts_tmp;
  Formation_FMS_B.xts_tmp += pof[1];
  Formation_FMS_B.yts_tmp = pof[3] - Formation_FMS_B.yts_tmp;
  Formation_FMS_B.cs_tmp = xs - Formation_FMS_B.l_best;
  Formation_FMS_B.cs_tmp_c = ys - Formation_FMS_B.pos_tmp;
  Formation_FMS_B.cs_tmp = std::asin(std::sqrt(Formation_FMS_B.cs_tmp *
    Formation_FMS_B.cs_tmp + Formation_FMS_B.cs_tmp_c * Formation_FMS_B.cs_tmp_c)
    / 2.0 / *r) * (*r * 2.0);
  Formation_FMS_B.cs_tmp_c = xf - Formation_FMS_B.xts_tmp;
  Formation_FMS_B.cf_tmp = yf - Formation_FMS_B.yts_tmp;
  Formation_FMS_B.cs_tmp_c = std::asin(std::sqrt(Formation_FMS_B.cs_tmp_c *
    Formation_FMS_B.cs_tmp_c + Formation_FMS_B.cf_tmp * Formation_FMS_B.cf_tmp) /
    2.0 / *r) * (*r * 2.0);
  Formation_FMS_B.cf_tmp = Formation_FMS_B.xts_tmp - Formation_FMS_B.l_best;
  Formation_FMS_B.lt_tmp = Formation_FMS_B.yts_tmp - Formation_FMS_B.pos_tmp;
  Formation_FMS_B.cf_tmp = std::sqrt(Formation_FMS_B.cf_tmp *
    Formation_FMS_B.cf_tmp + Formation_FMS_B.lt_tmp * Formation_FMS_B.lt_tmp);
  l[3] = (Formation_FMS_B.cs_tmp + Formation_FMS_B.cs_tmp_c) +
    Formation_FMS_B.cf_tmp;
  xts[3] = Formation_FMS_B.l_best;
  yts[3] = Formation_FMS_B.pos_tmp;
  xtf[3] = Formation_FMS_B.xts_tmp;
  ytf[3] = Formation_FMS_B.yts_tmp;
  cs[3] = Formation_FMS_B.cs_tmp;
  cf[3] = Formation_FMS_B.cs_tmp_c;
  lt[3] = Formation_FMS_B.cf_tmp;
  Formation_FMS_B.l_best = (rtInf);
  if ((l[0] >= 0.0) && (l[0] < (rtInf))) {
    Formation_FMS_B.l_best = l[0];
  }

  if ((l[1] >= 0.0) && (l[1] < Formation_FMS_B.l_best)) {
    Formation_FMS_B.l_best = l[1];
  }

  if ((l[2] >= 0.0) && (l[2] < Formation_FMS_B.l_best)) {
    Formation_FMS_B.l_best = l[2];
  }

  if ((l[3] >= 0.0) && (l[3] < Formation_FMS_B.l_best)) {
    Formation_FMS_B.l_best = l[3];
  }

  idx = -1;
  ii = 1;
  jj = 1;
  exitg1 = false;
  while ((!exitg1) && (jj <= 2)) {
    boolean_T guard1;
    guard1 = false;
    if (l[(((jj - 1) << 1) + ii) - 1] == Formation_FMS_B.l_best) {
      idx++;
      Formation_FMS_B.i_data[idx] = ii;
      j_data[idx] = static_cast<int8_T>(jj);
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
    m_data[ii] = Formation_FMS_B.i_data[ii];
  }

  if (idx + 1 < 1) {
    idx = -1;
  }

  *n_size = idx + 1;
  for (ii = 0; ii <= idx; ii++) {
    n_data[ii] = j_data[ii];
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
  *BusConversion_InsertedFor_FMS_p)
{
  static const real_T d[8]{ 1000.0, 100.0, 10.0, 1.0, 0.1, 0.01, 0.001, 0.0001 };

  int32_T b_size;
  int32_T c_size;

  // Delay: '<S5>/Delay' incorporates:
  //   MATLAB Function: '<S199>/MATLAB Function'

  if (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormAssemble) {
    Formation_FMS_DW.is_Formation = Formation_FMS_IN_FormAssemble;
    Formation_FMS_B.Cmd_In.sp_waypoint[0] = BusConversion_InsertedFor_FMS_c->x_R;
    Formation_FMS_B.Cmd_In.sp_waypoint[1] = BusConversion_InsertedFor_FMS_c->y_R;
    Formation_FMS_B.Cmd_In.sp_waypoint[2] = BusConversion_InsertedFor_FMS_c->h_R;
    if (FORMATION_PARAM.UAV_ID == 1U) {
      int32_T i;

      // Outputs for Function Call SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPath' 
      // MATLAB Function: '<S199>/MATLAB Function'
      Formation_FMS_B.PhiMaximum.contents = 40.0;
      Formation_FMS_B.rad2deg.contents = 57.295779513082323;
      Formation_FMS_B.obj.xs = 0.0;
      Formation_FMS_B.obj.ys = 0.0;
      Formation_FMS_B.obj.psi_s = 0.0;
      Formation_FMS_B.obj.xf = 0.0;
      Formation_FMS_B.obj.yf = 0.0;
      Formation_FMS_B.obj.psi_f = 0.0;
      Formation_FMS_B.obj.v = 0.0;
      Formation_FMS_B.obj.r = 0.0;
      Formation_FMS_B.obj.pos[0] = 0.0;
      Formation_FMS_B.obj.pof[0] = 0.0;
      Formation_FMS_B.obj.xts[0] = 0.0;
      Formation_FMS_B.obj.yts[0] = 0.0;
      Formation_FMS_B.obj.xtf[0] = 0.0;
      Formation_FMS_B.obj.ytf[0] = 0.0;
      Formation_FMS_B.obj.cs[0] = 0.0;
      Formation_FMS_B.obj.cf[0] = 0.0;
      Formation_FMS_B.obj.lt[0] = 0.0;
      Formation_FMS_B.obj.l[0] = 0.0;
      Formation_FMS_B.obj.pos[1] = 0.0;
      Formation_FMS_B.obj.pof[1] = 0.0;
      Formation_FMS_B.obj.xts[1] = 0.0;
      Formation_FMS_B.obj.yts[1] = 0.0;
      Formation_FMS_B.obj.xtf[1] = 0.0;
      Formation_FMS_B.obj.ytf[1] = 0.0;
      Formation_FMS_B.obj.cs[1] = 0.0;
      Formation_FMS_B.obj.cf[1] = 0.0;
      Formation_FMS_B.obj.lt[1] = 0.0;
      Formation_FMS_B.obj.l[1] = 0.0;
      Formation_FMS_B.obj.pos[2] = 0.0;
      Formation_FMS_B.obj.pof[2] = 0.0;
      Formation_FMS_B.obj.xts[2] = 0.0;
      Formation_FMS_B.obj.yts[2] = 0.0;
      Formation_FMS_B.obj.xtf[2] = 0.0;
      Formation_FMS_B.obj.ytf[2] = 0.0;
      Formation_FMS_B.obj.cs[2] = 0.0;
      Formation_FMS_B.obj.cf[2] = 0.0;
      Formation_FMS_B.obj.lt[2] = 0.0;
      Formation_FMS_B.obj.l[2] = 0.0;
      Formation_FMS_B.obj.pos[3] = 0.0;
      Formation_FMS_B.obj.pof[3] = 0.0;
      Formation_FMS_B.obj.xts[3] = 0.0;
      Formation_FMS_B.obj.yts[3] = 0.0;
      Formation_FMS_B.obj.xtf[3] = 0.0;
      Formation_FMS_B.obj.ytf[3] = 0.0;
      Formation_FMS_B.obj.cs[3] = 0.0;
      Formation_FMS_B.obj.cf[3] = 0.0;
      Formation_FMS_B.obj.lt[3] = 0.0;
      Formation_FMS_B.obj.l[3] = 0.0;
      Formation_FMS_B.obj.index_dubins[0] = 0.0;
      Formation_FMS_B.obj.index_dubins[1] = 0.0;
      Formation_FMS_B.obj.l_ad = 0.0;
      Formation_FMS_B.obj.precision_flag = 0.0;
      Formation_FMS_B.obj.xm = 0.0;
      Formation_FMS_B.obj.ym = 0.0;
      Formation_FMS_B.object[0] = Formation_FMS_B.obj;
      Formation_FMS_B.object[1] = Formation_FMS_B.obj;
      Formation_FMS_B.object[2] = Formation_FMS_B.obj;
      Formation_FMS_B.object[0].xs = BusConversion_InsertedFor_FMS_p->x_R[0];
      Formation_FMS_B.object[0].ys = BusConversion_InsertedFor_FMS_p->y_R[0];
      Formation_FMS_B.object[0].psi_s = rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[0],
         BusConversion_InsertedFor_FMS_p->vn[0]);
      Formation_FMS_B.object[0].xf = FORMATION_PARAM.FORM_POINT[0];
      Formation_FMS_B.object[0].yf = FORMATION_PARAM.FORM_POINT[3];
      Formation_FMS_B.object[0].psi_f = FORMATION_PARAM.FORM_POINT[6];
      Formation_FMS_B.object[0].v = 25.0;
      Formation_FMS_B.object[1].xs = BusConversion_InsertedFor_FMS_p->x_R[1];
      Formation_FMS_B.object[1].ys = BusConversion_InsertedFor_FMS_p->y_R[1];
      Formation_FMS_B.object[1].psi_s = rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[1],
         BusConversion_InsertedFor_FMS_p->vn[1]);
      Formation_FMS_B.object[1].xf = FORMATION_PARAM.FORM_POINT[1];
      Formation_FMS_B.object[1].yf = FORMATION_PARAM.FORM_POINT[4];
      Formation_FMS_B.object[1].psi_f = FORMATION_PARAM.FORM_POINT[7];
      Formation_FMS_B.object[1].v = 25.0;
      Formation_FMS_B.object[2].xs = BusConversion_InsertedFor_FMS_p->x_R[2];
      Formation_FMS_B.object[2].ys = BusConversion_InsertedFor_FMS_p->y_R[2];
      Formation_FMS_B.object[2].psi_s = rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[2],
         BusConversion_InsertedFor_FMS_p->vn[2]);
      Formation_FMS_B.object[2].xf = FORMATION_PARAM.FORM_POINT[2];
      Formation_FMS_B.object[2].yf = FORMATION_PARAM.FORM_POINT[5];
      Formation_FMS_B.object[2].psi_f = FORMATION_PARAM.FORM_POINT[8];
      Formation_FMS_B.object[2].v = 25.0;
      Formation_FMS_B.target = -1;
      Formation_FMS_B.l_ref = -1.0;
      Formation_FMS_B.obj = Formation_FMS_B.object[0];

      // MATLAB Function: '<S199>/MATLAB Function'
      Formation_FMS_Dubins(&Formation_FMS_B.PhiMaximum, &Formation_FMS_B.rad2deg,
                           static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->x_R[0]),
                           static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->y_R[0]),
                           static_cast<real_T>(rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[0],
         BusConversion_InsertedFor_FMS_p->vn[0])), FORMATION_PARAM.FORM_POINT[0],
                           FORMATION_PARAM.FORM_POINT[3],
                           FORMATION_PARAM.FORM_POINT[6], 25.0,
                           Formation_FMS_B.obj.xts, Formation_FMS_B.obj.yts,
                           Formation_FMS_B.obj.xtf, Formation_FMS_B.obj.ytf,
                           Formation_FMS_B.obj.cs, Formation_FMS_B.obj.cf,
                           Formation_FMS_B.obj.lt, Formation_FMS_B.obj.l,
                           Formation_FMS_B.obj.pos, Formation_FMS_B.obj.pof,
                           &Formation_FMS_B.obj.r, Formation_FMS_B.b_data,
                           &b_size, Formation_FMS_B.c_data, &c_size);
      Formation_FMS_B.obj.index_dubins[0] = Formation_FMS_B.b_data[0];
      Formation_FMS_B.obj.index_dubins[1] = Formation_FMS_B.c_data[0];
      Formation_FMS_B.goal = Formation_FMS_B.obj.l[(((static_cast<int32_T>
        (Formation_FMS_B.c_data[0]) - 1) << 1) + static_cast<int32_T>
        (Formation_FMS_B.b_data[0])) - 1];
      if (Formation_FMS_B.goal > -1.0) {
        Formation_FMS_B.l_ref = Formation_FMS_B.goal;
        Formation_FMS_B.target = 1;
      }

      Formation_FMS_B.object[0] = Formation_FMS_B.obj;
      Formation_FMS_B.obj = Formation_FMS_B.object[1];

      // MATLAB Function: '<S199>/MATLAB Function'
      Formation_FMS_Dubins(&Formation_FMS_B.PhiMaximum, &Formation_FMS_B.rad2deg,
                           static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->x_R[1]),
                           static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->y_R[1]),
                           static_cast<real_T>(rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[1],
         BusConversion_InsertedFor_FMS_p->vn[1])), FORMATION_PARAM.FORM_POINT[1],
                           FORMATION_PARAM.FORM_POINT[4],
                           FORMATION_PARAM.FORM_POINT[7], 25.0,
                           Formation_FMS_B.obj.xts, Formation_FMS_B.obj.yts,
                           Formation_FMS_B.obj.xtf, Formation_FMS_B.obj.ytf,
                           Formation_FMS_B.obj.cs, Formation_FMS_B.obj.cf,
                           Formation_FMS_B.obj.lt, Formation_FMS_B.obj.l,
                           Formation_FMS_B.obj.pos, Formation_FMS_B.obj.pof,
                           &Formation_FMS_B.obj.r, Formation_FMS_B.b_data,
                           &b_size, Formation_FMS_B.c_data, &c_size);
      Formation_FMS_B.obj.index_dubins[0] = Formation_FMS_B.b_data[0];
      Formation_FMS_B.obj.index_dubins[1] = Formation_FMS_B.c_data[0];
      Formation_FMS_B.goal = Formation_FMS_B.obj.l[(((static_cast<int32_T>
        (Formation_FMS_B.c_data[0]) - 1) << 1) + static_cast<int32_T>
        (Formation_FMS_B.b_data[0])) - 1];
      if (Formation_FMS_B.goal > Formation_FMS_B.l_ref) {
        Formation_FMS_B.l_ref = Formation_FMS_B.goal;
        Formation_FMS_B.target = 2;
      }

      Formation_FMS_B.object[1] = Formation_FMS_B.obj;
      Formation_FMS_B.obj = Formation_FMS_B.object[2];

      // MATLAB Function: '<S199>/MATLAB Function'
      Formation_FMS_Dubins(&Formation_FMS_B.PhiMaximum, &Formation_FMS_B.rad2deg,
                           static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->x_R[2]),
                           static_cast<real_T>
                           (BusConversion_InsertedFor_FMS_p->y_R[2]),
                           static_cast<real_T>(rt_atan2f_snf
        (BusConversion_InsertedFor_FMS_p->ve[2],
         BusConversion_InsertedFor_FMS_p->vn[2])), FORMATION_PARAM.FORM_POINT[2],
                           FORMATION_PARAM.FORM_POINT[5],
                           FORMATION_PARAM.FORM_POINT[8], 25.0,
                           Formation_FMS_B.obj.xts, Formation_FMS_B.obj.yts,
                           Formation_FMS_B.obj.xtf, Formation_FMS_B.obj.ytf,
                           Formation_FMS_B.obj.cs, Formation_FMS_B.obj.cf,
                           Formation_FMS_B.obj.lt, Formation_FMS_B.obj.l,
                           Formation_FMS_B.obj.pos, Formation_FMS_B.obj.pof,
                           &Formation_FMS_B.obj.r, Formation_FMS_B.b_data,
                           &b_size, Formation_FMS_B.c_data, &c_size);
      Formation_FMS_B.obj.index_dubins[0] = Formation_FMS_B.b_data[0];
      Formation_FMS_B.obj.index_dubins[1] = Formation_FMS_B.c_data[0];
      Formation_FMS_B.goal = Formation_FMS_B.obj.l[(((static_cast<int32_T>
        (Formation_FMS_B.c_data[0]) - 1) << 1) + static_cast<int32_T>
        (Formation_FMS_B.b_data[0])) - 1];
      if (Formation_FMS_B.goal > Formation_FMS_B.l_ref) {
        Formation_FMS_B.l_ref = Formation_FMS_B.goal;
        Formation_FMS_B.target = 3;
      }

      Formation_FMS_B.object[2] = Formation_FMS_B.obj;

      // MATLAB Function: '<S199>/MATLAB Function'
      for (Formation_FMS_B.d_i = 0; Formation_FMS_B.d_i < 3; Formation_FMS_B.d_i
           ++) {
        if (Formation_FMS_B.d_i + 1 != Formation_FMS_B.target) {
          Formation_FMS_B.search_floor = 0.0;
          Formation_FMS_B.search = 0.0;
          Formation_FMS_B.stop_flag = 1;
          for (i = 0; i < 7; i++) {
            boolean_T exitg1;
            exitg1 = false;
            while ((!exitg1) && (Formation_FMS_B.stop_flag != 0)) {
              Formation_FMS_B.search += d[i];
              Formation_FMS_B.goal = Formation_FMS_B.object[Formation_FMS_B.d_i]
                .psi_f / 57.295779513082323;
              Formation_FMS_B.object[Formation_FMS_B.d_i].xm =
                Formation_FMS_B.object[Formation_FMS_B.d_i].xf - std::cos
                (Formation_FMS_B.goal) * Formation_FMS_B.search;
              Formation_FMS_B.object[Formation_FMS_B.d_i].ym =
                Formation_FMS_B.object[Formation_FMS_B.d_i].yf - std::sin
                (Formation_FMS_B.goal) * Formation_FMS_B.search;
              Formation_FMS_Dubins(&Formation_FMS_B.PhiMaximum,
                                   &Formation_FMS_B.rad2deg,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   xs,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   ys,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   psi_s,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   xm,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   ym,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   psi_f,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].v,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   xts,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   yts,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   xtf,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   ytf,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   cs,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   cf,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   lt,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].l,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   pos,
                                   Formation_FMS_B.object[Formation_FMS_B.d_i].
                                   pof, &Formation_FMS_B.goal,
                                   Formation_FMS_B.b_data, &b_size,
                                   Formation_FMS_B.c_data, &c_size);
              Formation_FMS_B.object[Formation_FMS_B.d_i].index_dubins[0] =
                Formation_FMS_B.b_data[0];
              Formation_FMS_B.object[Formation_FMS_B.d_i].index_dubins[1] =
                Formation_FMS_B.c_data[0];
              Formation_FMS_B.goal = (Formation_FMS_B.object[Formation_FMS_B.d_i]
                .l[(((static_cast<int32_T>
                      (Formation_FMS_B.object[Formation_FMS_B.d_i].index_dubins
                       [1]) - 1) << 1) + static_cast<int32_T>
                    (Formation_FMS_B.object[Formation_FMS_B.d_i].index_dubins[0]))
                - 1] + Formation_FMS_B.search) - Formation_FMS_B.l_ref;
              if (Formation_FMS_B.goal > 0.0) {
                Formation_FMS_B.object[Formation_FMS_B.d_i].l_ad =
                  Formation_FMS_B.search_floor;
                Formation_FMS_B.object[Formation_FMS_B.d_i].precision_flag = d[i];
                Formation_FMS_B.search = Formation_FMS_B.search_floor;
                exitg1 = true;
              } else if (Formation_FMS_B.goal < 0.0) {
                Formation_FMS_B.search_floor = Formation_FMS_B.search;
              } else {
                Formation_FMS_B.object[Formation_FMS_B.d_i].l_ad =
                  Formation_FMS_B.search;
                Formation_FMS_B.object[Formation_FMS_B.d_i].precision_flag = 0.0;
                Formation_FMS_B.stop_flag = 0;
              }
            }
          }
        } else {
          Formation_FMS_B.object[Formation_FMS_B.d_i].xm =
            Formation_FMS_B.object[Formation_FMS_B.d_i].xf;
          Formation_FMS_B.object[Formation_FMS_B.d_i].ym =
            Formation_FMS_B.object[Formation_FMS_B.d_i].yf;
        }
      }

      if (Formation_FMS_B.target == 1) {
        Formation_FMS_B.result[0] = Formation_FMS_B.object[0].xs;
        Formation_FMS_B.result[15] = Formation_FMS_B.object[0].ys;
        Formation_FMS_B.result[30] = Formation_FMS_B.object[0].psi_s;
        Formation_FMS_B.result[45] = Formation_FMS_B.object[0].r;
        Formation_FMS_B.d_i = (((static_cast<int32_T>(Formation_FMS_B.object[0].
          index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_B.object[0].index_dubins[0])) - 1;
        Formation_FMS_B.result[60] = Formation_FMS_B.object[0]
          .cs[Formation_FMS_B.d_i];
        Formation_FMS_B.result[3] = Formation_FMS_B.object[0]
          .xts[Formation_FMS_B.d_i];
        Formation_FMS_B.result[18] = Formation_FMS_B.object[0]
          .yts[Formation_FMS_B.d_i];
        Formation_FMS_B.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_B.object[0].xtf[Formation_FMS_B.d_i],
           Formation_FMS_B.object[0].ytf[Formation_FMS_B.d_i],
           Formation_FMS_B.object[0].xts[Formation_FMS_B.d_i],
           Formation_FMS_B.object[0].yts[Formation_FMS_B.d_i]) *
          57.295779513082323;
        Formation_FMS_B.result[33] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[48] = 0.0;
        Formation_FMS_B.result[63] = Formation_FMS_B.object[0]
          .lt[Formation_FMS_B.d_i];
        Formation_FMS_B.result[6] = Formation_FMS_B.object[0]
          .xtf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[21] = Formation_FMS_B.object[0]
          .ytf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[36] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[51] = Formation_FMS_B.object[0].r;
        Formation_FMS_B.result[66] = Formation_FMS_B.object[0]
          .cf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[9] = Formation_FMS_B.object[0].xm;
        Formation_FMS_B.result[24] = Formation_FMS_B.object[0].ym;
        Formation_FMS_B.result[39] = Formation_FMS_B.object[0].psi_f;
        Formation_FMS_B.result[54] = 0.0;
        Formation_FMS_B.result[69] = 0.0;
        Formation_FMS_B.result[12] = Formation_FMS_B.object[0].xf;
        Formation_FMS_B.result[27] = Formation_FMS_B.object[0].yf;
        Formation_FMS_B.result[42] = Formation_FMS_B.object[0].psi_f;
        Formation_FMS_B.result[57] = 0.0;
        Formation_FMS_B.result[72] = Formation_FMS_B.object[0]
          .l[Formation_FMS_B.d_i];
      } else {
        Formation_FMS_B.result[0] = Formation_FMS_B.object[0].xs;
        Formation_FMS_B.result[15] = Formation_FMS_B.object[0].ys;
        Formation_FMS_B.result[30] = Formation_FMS_B.object[0].psi_s;
        Formation_FMS_B.result[45] = Formation_FMS_B.object[0].r;
        Formation_FMS_B.d_i = (((static_cast<int32_T>(Formation_FMS_B.object[0].
          index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_B.object[0].index_dubins[0])) - 1;
        Formation_FMS_B.result[60] = Formation_FMS_B.object[0]
          .cs[Formation_FMS_B.d_i];
        Formation_FMS_B.l_ref = Formation_FMS_B.object[0]
          .xts[Formation_FMS_B.d_i];
        Formation_FMS_B.result[3] = Formation_FMS_B.l_ref;
        Formation_FMS_B.search_floor = Formation_FMS_B.object[0]
          .yts[Formation_FMS_B.d_i];
        Formation_FMS_B.result[18] = Formation_FMS_B.search_floor;
        Formation_FMS_B.search = Formation_FMS_B.object[0]
          .xtf[Formation_FMS_B.d_i];
        Formation_FMS_B.goal = Formation_FMS_B.object[0].ytf[Formation_FMS_B.d_i];
        Formation_FMS_B.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_B.search, Formation_FMS_B.goal, Formation_FMS_B.l_ref,
           Formation_FMS_B.search_floor) * 57.295779513082323;
        Formation_FMS_B.result[33] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[48] = 0.0;
        Formation_FMS_B.result[63] = Formation_FMS_B.object[0]
          .lt[Formation_FMS_B.d_i];
        Formation_FMS_B.result[6] = Formation_FMS_B.search;
        Formation_FMS_B.result[21] = Formation_FMS_B.goal;
        Formation_FMS_B.result[36] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[51] = Formation_FMS_B.object[0].r;
        Formation_FMS_B.result[66] = Formation_FMS_B.object[0]
          .cf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[9] = Formation_FMS_B.object[0].xm;
        Formation_FMS_B.result[24] = Formation_FMS_B.object[0].ym;
        Formation_FMS_B.result[39] = Formation_FMS_B.object[0].psi_f;
        Formation_FMS_B.result[54] = 0.0;
        Formation_FMS_B.result[69] = Formation_FMS_B.object[0].l_ad;
        Formation_FMS_B.result[12] = Formation_FMS_B.object[0].xf;
        Formation_FMS_B.result[27] = Formation_FMS_B.object[0].yf;
        Formation_FMS_B.result[42] = Formation_FMS_B.object[0].psi_f;
        Formation_FMS_B.result[57] = 0.0;
        Formation_FMS_B.result[72] = Formation_FMS_B.object[0]
          .l[Formation_FMS_B.d_i] + Formation_FMS_B.object[0].l_ad;
      }

      if (Formation_FMS_B.target == 2) {
        Formation_FMS_B.result[1] = Formation_FMS_B.object[1].xs;
        Formation_FMS_B.result[16] = Formation_FMS_B.object[1].ys;
        Formation_FMS_B.result[31] = Formation_FMS_B.object[1].psi_s;
        Formation_FMS_B.result[46] = Formation_FMS_B.object[1].r;
        Formation_FMS_B.d_i = (((static_cast<int32_T>(Formation_FMS_B.object[1].
          index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_B.object[1].index_dubins[0])) - 1;
        Formation_FMS_B.result[61] = Formation_FMS_B.object[1]
          .cs[Formation_FMS_B.d_i];
        Formation_FMS_B.result[4] = Formation_FMS_B.object[1]
          .xts[Formation_FMS_B.d_i];
        Formation_FMS_B.result[19] = Formation_FMS_B.object[1]
          .yts[Formation_FMS_B.d_i];
        Formation_FMS_B.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_B.object[1].xtf[Formation_FMS_B.d_i],
           Formation_FMS_B.object[1].ytf[Formation_FMS_B.d_i],
           Formation_FMS_B.object[1].xts[Formation_FMS_B.d_i],
           Formation_FMS_B.object[1].yts[Formation_FMS_B.d_i]) *
          57.295779513082323;
        Formation_FMS_B.result[34] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[49] = 0.0;
        Formation_FMS_B.result[64] = Formation_FMS_B.object[1]
          .lt[Formation_FMS_B.d_i];
        Formation_FMS_B.result[7] = Formation_FMS_B.object[1]
          .xtf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[22] = Formation_FMS_B.object[1]
          .ytf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[37] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[52] = Formation_FMS_B.object[1].r;
        Formation_FMS_B.result[67] = Formation_FMS_B.object[1]
          .cf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[10] = Formation_FMS_B.object[1].xm;
        Formation_FMS_B.result[25] = Formation_FMS_B.object[1].ym;
        Formation_FMS_B.result[40] = Formation_FMS_B.object[1].psi_f;
        Formation_FMS_B.result[55] = 0.0;
        Formation_FMS_B.result[70] = 0.0;
        Formation_FMS_B.result[13] = Formation_FMS_B.object[1].xf;
        Formation_FMS_B.result[28] = Formation_FMS_B.object[1].yf;
        Formation_FMS_B.result[43] = Formation_FMS_B.object[1].psi_f;
        Formation_FMS_B.result[58] = 0.0;
        Formation_FMS_B.result[73] = Formation_FMS_B.object[1]
          .l[Formation_FMS_B.d_i];
      } else {
        Formation_FMS_B.result[1] = Formation_FMS_B.object[1].xs;
        Formation_FMS_B.result[16] = Formation_FMS_B.object[1].ys;
        Formation_FMS_B.result[31] = Formation_FMS_B.object[1].psi_s;
        Formation_FMS_B.result[46] = Formation_FMS_B.object[1].r;
        Formation_FMS_B.d_i = (((static_cast<int32_T>(Formation_FMS_B.object[1].
          index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_B.object[1].index_dubins[0])) - 1;
        Formation_FMS_B.result[61] = Formation_FMS_B.object[1]
          .cs[Formation_FMS_B.d_i];
        Formation_FMS_B.l_ref = Formation_FMS_B.object[1]
          .xts[Formation_FMS_B.d_i];
        Formation_FMS_B.result[4] = Formation_FMS_B.l_ref;
        Formation_FMS_B.search_floor = Formation_FMS_B.object[1]
          .yts[Formation_FMS_B.d_i];
        Formation_FMS_B.result[19] = Formation_FMS_B.search_floor;
        Formation_FMS_B.search = Formation_FMS_B.object[1]
          .xtf[Formation_FMS_B.d_i];
        Formation_FMS_B.goal = Formation_FMS_B.object[1].ytf[Formation_FMS_B.d_i];
        Formation_FMS_B.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_B.search, Formation_FMS_B.goal, Formation_FMS_B.l_ref,
           Formation_FMS_B.search_floor) * 57.295779513082323;
        Formation_FMS_B.result[34] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[49] = 0.0;
        Formation_FMS_B.result[64] = Formation_FMS_B.object[1]
          .lt[Formation_FMS_B.d_i];
        Formation_FMS_B.result[7] = Formation_FMS_B.search;
        Formation_FMS_B.result[22] = Formation_FMS_B.goal;
        Formation_FMS_B.result[37] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[52] = Formation_FMS_B.object[1].r;
        Formation_FMS_B.result[67] = Formation_FMS_B.object[1]
          .cf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[10] = Formation_FMS_B.object[1].xm;
        Formation_FMS_B.result[25] = Formation_FMS_B.object[1].ym;
        Formation_FMS_B.result[40] = Formation_FMS_B.object[1].psi_f;
        Formation_FMS_B.result[55] = 0.0;
        Formation_FMS_B.result[70] = Formation_FMS_B.object[1].l_ad;
        Formation_FMS_B.result[13] = Formation_FMS_B.object[1].xf;
        Formation_FMS_B.result[28] = Formation_FMS_B.object[1].yf;
        Formation_FMS_B.result[43] = Formation_FMS_B.object[1].psi_f;
        Formation_FMS_B.result[58] = 0.0;
        Formation_FMS_B.result[73] = Formation_FMS_B.object[1]
          .l[Formation_FMS_B.d_i] + Formation_FMS_B.object[1].l_ad;
      }

      if (Formation_FMS_B.target == 3) {
        Formation_FMS_B.result[2] = Formation_FMS_B.object[2].xs;
        Formation_FMS_B.result[17] = Formation_FMS_B.object[2].ys;
        Formation_FMS_B.result[32] = Formation_FMS_B.object[2].psi_s;
        Formation_FMS_B.result[47] = Formation_FMS_B.object[2].r;
        Formation_FMS_B.d_i = (((static_cast<int32_T>(Formation_FMS_B.object[2].
          index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_B.object[2].index_dubins[0])) - 1;
        Formation_FMS_B.result[62] = Formation_FMS_B.object[2]
          .cs[Formation_FMS_B.d_i];
        Formation_FMS_B.result[5] = Formation_FMS_B.object[2]
          .xts[Formation_FMS_B.d_i];
        Formation_FMS_B.result[20] = Formation_FMS_B.object[2]
          .yts[Formation_FMS_B.d_i];
        Formation_FMS_B.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_B.object[2].xtf[Formation_FMS_B.d_i],
           Formation_FMS_B.object[2].ytf[Formation_FMS_B.d_i],
           Formation_FMS_B.object[2].xts[Formation_FMS_B.d_i],
           Formation_FMS_B.object[2].yts[Formation_FMS_B.d_i]) *
          57.295779513082323;
        Formation_FMS_B.result[35] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[50] = 0.0;
        Formation_FMS_B.result[65] = Formation_FMS_B.object[2]
          .lt[Formation_FMS_B.d_i];
        Formation_FMS_B.result[8] = Formation_FMS_B.object[2]
          .xtf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[23] = Formation_FMS_B.object[2]
          .ytf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[38] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[53] = Formation_FMS_B.object[2].r;
        Formation_FMS_B.result[68] = Formation_FMS_B.object[2]
          .cf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[11] = Formation_FMS_B.object[2].xm;
        Formation_FMS_B.result[26] = Formation_FMS_B.object[2].ym;
        Formation_FMS_B.result[41] = Formation_FMS_B.object[2].psi_f;
        Formation_FMS_B.result[56] = 0.0;
        Formation_FMS_B.result[71] = 0.0;
        Formation_FMS_B.result[14] = Formation_FMS_B.object[2].xf;
        Formation_FMS_B.result[29] = Formation_FMS_B.object[2].yf;
        Formation_FMS_B.result[44] = Formation_FMS_B.object[2].psi_f;
        Formation_FMS_B.result[59] = 0.0;
        Formation_FMS_B.result[74] = Formation_FMS_B.object[2]
          .l[Formation_FMS_B.d_i];
      } else {
        Formation_FMS_B.result[2] = Formation_FMS_B.object[2].xs;
        Formation_FMS_B.result[17] = Formation_FMS_B.object[2].ys;
        Formation_FMS_B.result[32] = Formation_FMS_B.object[2].psi_s;
        Formation_FMS_B.result[47] = Formation_FMS_B.object[2].r;
        Formation_FMS_B.d_i = (((static_cast<int32_T>(Formation_FMS_B.object[2].
          index_dubins[1]) - 1) << 1) + static_cast<int32_T>
          (Formation_FMS_B.object[2].index_dubins[0])) - 1;
        Formation_FMS_B.result[62] = Formation_FMS_B.object[2]
          .cs[Formation_FMS_B.d_i];
        Formation_FMS_B.l_ref = Formation_FMS_B.object[2]
          .xts[Formation_FMS_B.d_i];
        Formation_FMS_B.result[5] = Formation_FMS_B.l_ref;
        Formation_FMS_B.search_floor = Formation_FMS_B.object[2]
          .yts[Formation_FMS_B.d_i];
        Formation_FMS_B.result[20] = Formation_FMS_B.search_floor;
        Formation_FMS_B.search = Formation_FMS_B.object[2]
          .xtf[Formation_FMS_B.d_i];
        Formation_FMS_B.goal = Formation_FMS_B.object[2].ytf[Formation_FMS_B.d_i];
        Formation_FMS_B.l_ref = Formation_FMS_atan3_9FIHpp9F
          (Formation_FMS_B.search, Formation_FMS_B.goal, Formation_FMS_B.l_ref,
           Formation_FMS_B.search_floor) * 57.295779513082323;
        Formation_FMS_B.result[35] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[50] = 0.0;
        Formation_FMS_B.result[65] = Formation_FMS_B.object[2]
          .lt[Formation_FMS_B.d_i];
        Formation_FMS_B.result[8] = Formation_FMS_B.search;
        Formation_FMS_B.result[23] = Formation_FMS_B.goal;
        Formation_FMS_B.result[38] = Formation_FMS_B.l_ref;
        Formation_FMS_B.result[53] = Formation_FMS_B.object[2].r;
        Formation_FMS_B.result[68] = Formation_FMS_B.object[2]
          .cf[Formation_FMS_B.d_i];
        Formation_FMS_B.result[11] = Formation_FMS_B.object[2].xm;
        Formation_FMS_B.result[26] = Formation_FMS_B.object[2].ym;
        Formation_FMS_B.result[41] = Formation_FMS_B.object[2].psi_f;
        Formation_FMS_B.result[56] = 0.0;
        Formation_FMS_B.result[71] = Formation_FMS_B.object[2].l_ad;
        Formation_FMS_B.result[14] = Formation_FMS_B.object[2].xf;
        Formation_FMS_B.result[29] = Formation_FMS_B.object[2].yf;
        Formation_FMS_B.result[44] = Formation_FMS_B.object[2].psi_f;
        Formation_FMS_B.result[59] = 0.0;
        Formation_FMS_B.result[74] = Formation_FMS_B.object[2]
          .l[Formation_FMS_B.d_i] + Formation_FMS_B.object[2].l_ad;
      }

      std::memset(&Formation_FMS_B.Other_Mission_Data.x[0], 0, 24U * sizeof
                  (real32_T));
      std::memset(&Formation_FMS_B.Other_Mission_Data.y[0], 0, 24U * sizeof
                  (real32_T));
      std::memset(&Formation_FMS_B.Other_Mission_Data.z[0], 0, 24U * sizeof
                  (real32_T));
      std::memset(&Formation_FMS_B.Other_Mission_Data.heading[0], 0, 24U *
                  sizeof(real32_T));
      std::memset(&Formation_FMS_B.Other_Mission_Data.ext1[0], 0, 24U * sizeof
                  (real32_T));
      std::memset(&Formation_FMS_B.Other_Mission_Data.ext2[0], 0, 24U * sizeof
                  (real32_T));
      for (Formation_FMS_B.d_i = 0; Formation_FMS_B.d_i < 5; Formation_FMS_B.d_i
           ++) {
        Formation_FMS_B.Other_Mission_Data.x[3 * Formation_FMS_B.d_i] =
          static_cast<real32_T>(Formation_FMS_B.result[3 * Formation_FMS_B.d_i]);
        Formation_FMS_B.Other_Mission_Data.y[3 * Formation_FMS_B.d_i] =
          static_cast<real32_T>(Formation_FMS_B.result[3 * Formation_FMS_B.d_i +
          15]);
        i = 3 * Formation_FMS_B.d_i + 1;
        Formation_FMS_B.Other_Mission_Data.x[i] = static_cast<real32_T>
          (Formation_FMS_B.result[i]);
        Formation_FMS_B.Other_Mission_Data.y[i] = static_cast<real32_T>
          (Formation_FMS_B.result[3 * Formation_FMS_B.d_i + 16]);
        i = 3 * Formation_FMS_B.d_i + 2;
        Formation_FMS_B.Other_Mission_Data.x[i] = static_cast<real32_T>
          (Formation_FMS_B.result[i]);
        Formation_FMS_B.Other_Mission_Data.y[i] = static_cast<real32_T>
          (Formation_FMS_B.result[3 * Formation_FMS_B.d_i + 17]);
      }

      for (i = 0; i < 3; i++) {
        for (Formation_FMS_B.d_i = 0; Formation_FMS_B.d_i < 5;
             Formation_FMS_B.d_i++) {
          Formation_FMS_B.Other_Mission_Data.z[i + 3 * Formation_FMS_B.d_i] =
            BusConversion_InsertedFor_FMS_p->h_R[i];
        }
      }

      for (Formation_FMS_B.d_i = 0; Formation_FMS_B.d_i < 5; Formation_FMS_B.d_i
           ++) {
        Formation_FMS_B.Other_Mission_Data.heading[3 * Formation_FMS_B.d_i] =
          static_cast<real32_T>(Formation_FMS_B.result[3 * Formation_FMS_B.d_i +
          30]);
        Formation_FMS_B.Other_Mission_Data.ext1[3 * Formation_FMS_B.d_i] =
          static_cast<real32_T>(Formation_FMS_B.result[3 * Formation_FMS_B.d_i +
          45]);
        Formation_FMS_B.Other_Mission_Data.ext2[3 * Formation_FMS_B.d_i] =
          static_cast<real32_T>(Formation_FMS_B.result[3 * Formation_FMS_B.d_i +
          60]);
        i = 3 * Formation_FMS_B.d_i + 1;
        Formation_FMS_B.Other_Mission_Data.heading[i] = static_cast<real32_T>
          (Formation_FMS_B.result[3 * Formation_FMS_B.d_i + 31]);
        Formation_FMS_B.Other_Mission_Data.ext1[i] = static_cast<real32_T>
          (Formation_FMS_B.result[3 * Formation_FMS_B.d_i + 46]);
        Formation_FMS_B.Other_Mission_Data.ext2[i] = static_cast<real32_T>
          (Formation_FMS_B.result[3 * Formation_FMS_B.d_i + 61]);
        i = 3 * Formation_FMS_B.d_i + 2;
        Formation_FMS_B.Other_Mission_Data.heading[i] = static_cast<real32_T>
          (Formation_FMS_B.result[3 * Formation_FMS_B.d_i + 32]);
        Formation_FMS_B.Other_Mission_Data.ext1[i] = static_cast<real32_T>
          (Formation_FMS_B.result[3 * Formation_FMS_B.d_i + 47]);
        Formation_FMS_B.Other_Mission_Data.ext2[i] = static_cast<real32_T>
          (Formation_FMS_B.result[3 * Formation_FMS_B.d_i + 62]);
      }

      Formation_FMS_B.Other_Mission_Data.timestamp = 9999U;
      Formation_FMS_B.Other_Mission_Data.type[0] = 1U;
      Formation_FMS_B.Other_Mission_Data.valid_items[0] = 5U;
      Formation_FMS_B.Other_Mission_Data.type[1] = 1U;
      Formation_FMS_B.Other_Mission_Data.valid_items[1] = 5U;
      Formation_FMS_B.Other_Mission_Data.type[2] = 1U;
      Formation_FMS_B.Other_Mission_Data.valid_items[2] = 5U;

      // End of Outputs for SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPath' 
    }

    Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_WaitForUpdate;
    Formation_FMS_DW.temporalCounter_i1 = 0U;
    Formation_FMS_B.Cmd_In.cur_waypoint[0] =
      BusConversion_InsertedFor_FMS_c->x_R;
    Formation_FMS_B.Cmd_In.cur_waypoint[1] =
      BusConversion_InsertedFor_FMS_c->y_R;
    Formation_FMS_B.Cmd_In.cur_waypoint[2] =
      BusConversion_InsertedFor_FMS_c->h_R;
    Formation_FMS_B.state = VehicleState::FormHold;
  } else {
    boolean_T tmp;
    if (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormMission) {
      tmp = (Formation_FMS_B.Cmd_In.form_valid == 7U);
    } else {
      tmp = false;
    }

    if (tmp) {
      Formation_FMS_DW.is_Formation = Formation_FMS_IN_FormMission;
      Formation_FMS_B.Cmd_In.sp_waypoint[0] =
        BusConversion_InsertedFor_FMS_c->x_R;
      Formation_FMS_B.Cmd_In.sp_waypoint[1] =
        BusConversion_InsertedFor_FMS_c->y_R;
      Formation_FMS_B.Cmd_In.sp_waypoint[2] =
        BusConversion_InsertedFor_FMS_c->h_R;
      Formation_FMS_B.state = VehicleState::FormMission;
      Formation_FMS_DW.is_FormMission = Formation_FMS_IN_NextWP;
    } else if (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormDisband) {
      Formation_FMS_DW.is_Formation = Formation_FMS_IN_FormDisband;
      Formation_FMS_B.state = VehicleState::FormDisband;
    } else {
      Formation_FMS_DW.is_Formation = Formation_FMS_IN_InvalidMode;
    }
  }

  // End of Delay: '<S5>/Delay'
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
  Formation_FMS_B.Cmd_In.form_valid = 0U;
  Formation_FMS_B.Other_Mission_Data.timestamp = 0U;
  Formation_FMS_B.Cmd_In.sp_waypoint[0] = 0.0F;
  Formation_FMS_B.Cmd_In.cur_waypoint[0] = 0.0F;
  Formation_FMS_B.Other_Mission_Data.type[0] = 0U;
  Formation_FMS_B.Other_Mission_Data.valid_items[0] = 0U;
  Formation_FMS_B.Cmd_In.sp_waypoint[1] = 0.0F;
  Formation_FMS_B.Cmd_In.cur_waypoint[1] = 0.0F;
  Formation_FMS_B.Other_Mission_Data.type[1] = 0U;
  Formation_FMS_B.Other_Mission_Data.valid_items[1] = 0U;
  Formation_FMS_B.Cmd_In.sp_waypoint[2] = 0.0F;
  Formation_FMS_B.Cmd_In.cur_waypoint[2] = 0.0F;
  Formation_FMS_B.Other_Mission_Data.type[2] = 0U;
  Formation_FMS_B.Other_Mission_Data.valid_items[2] = 0U;
  for (int32_T i{0}; i < 24; i++) {
    Formation_FMS_B.Other_Mission_Data.x[i] = 0.0F;
    Formation_FMS_B.Other_Mission_Data.y[i] = 0.0F;
    Formation_FMS_B.Other_Mission_Data.z[i] = 0.0F;
    Formation_FMS_B.Other_Mission_Data.heading[i] = 0.0F;
    Formation_FMS_B.Other_Mission_Data.ext1[i] = 0.0F;
    Formation_FMS_B.Other_Mission_Data.ext2[i] = 0.0F;

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_x[i] = Formation_FMS_B.Other_Mission_Data.x[i];

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_y[i] = Formation_FMS_B.Other_Mission_Data.y[i];

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_z[i] = Formation_FMS_B.Other_Mission_Data.z[i];

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_heading[i] =
      Formation_FMS_B.Other_Mission_Data.heading[i];

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_ext1[i] = Formation_FMS_B.Other_Mission_Data.ext1[i];

    // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
    rty_Other_Mission_Data_ext2[i] = Formation_FMS_B.Other_Mission_Data.ext2[i];
  }

  // End of SystemInitialize for Chart: '<Root>/FMS State Machine'

  // SystemInitialize for IfAction SubSystem: '<S10>/Form_Subsystem'
  // Start for SwitchCase: '<S12>/Switch Case'
  Formation_FMS_DW.SwitchCase_ActiveSubsystem_c = -1;

  // SystemInitialize for IfAction SubSystem: '<S12>/FormAssemble'
  // SystemInitialize for Resettable SubSystem: '<S17>/Mission_SubSystem'
  // InitializeConditions for Delay: '<S26>/Delay'
  Formation_FMS_DW.icLoad_h = true;

  // End of SystemInitialize for SubSystem: '<S17>/Mission_SubSystem'
  // End of SystemInitialize for SubSystem: '<S12>/FormAssemble'

  // SystemInitialize for IfAction SubSystem: '<S12>/FormHold'
  // InitializeConditions for Delay: '<S68>/start_vel'
  Formation_FMS_DW.icLoad_l3 = true;

  // InitializeConditions for Delay: '<S64>/Delay'
  Formation_FMS_DW.icLoad_p = true;

  // End of SystemInitialize for SubSystem: '<S12>/FormHold'

  // SystemInitialize for IfAction SubSystem: '<S12>/FormMission'
  // SystemInitialize for Resettable SubSystem: '<S20>/FormMission_SubSystem'
  // InitializeConditions for Delay: '<S159>/Delay'
  Formation_FMS_DW.icLoad_k = true;

  // InitializeConditions for DiscreteIntegrator: '<S97>/Discrete-Time Integrator1' 
  Formation_FMS_DW.DiscreteTimeIntegrator1_IC_LOAD = 1U;

  // End of SystemInitialize for SubSystem: '<S20>/FormMission_SubSystem'
  // End of SystemInitialize for SubSystem: '<S12>/FormMission'

  // SystemInitialize for IfAction SubSystem: '<S12>/FormDisband'
  // InitializeConditions for Delay: '<S50>/start_vel'
  Formation_FMS_DW.icLoad_a = true;

  // InitializeConditions for Delay: '<S46>/Delay'
  Formation_FMS_DW.icLoad_l = true;

  // End of SystemInitialize for SubSystem: '<S12>/FormDisband'

  // SystemInitialize for IfAction SubSystem: '<S12>/Default'
  Formation_FMS_Default_Init(&Formation_FMS_DW.Default_d);

  // End of SystemInitialize for SubSystem: '<S12>/Default'
  // End of SystemInitialize for SubSystem: '<S10>/Form_Subsystem'

  // SystemInitialize for IfAction SubSystem: '<S10>/Hold'
  // InitializeConditions for Delay: '<S186>/start_vel'
  Formation_FMS_DW.icLoad = true;

  // InitializeConditions for Delay: '<S182>/Delay'
  Formation_FMS_DW.icLoad_j = true;

  // End of SystemInitialize for SubSystem: '<S10>/Hold'

  // SystemInitialize for IfAction SubSystem: '<S10>/Default'
  Formation_FMS_Default_Init(&Formation_FMS_DW.Default);

  // End of SystemInitialize for SubSystem: '<S10>/Default'

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_type[0] = Formation_FMS_B.Other_Mission_Data.type[0];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_valid_it[0] =
    Formation_FMS_B.Other_Mission_Data.valid_items[0];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_type[1] = Formation_FMS_B.Other_Mission_Data.type[1];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_valid_it[1] =
    Formation_FMS_B.Other_Mission_Data.valid_items[1];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_type[2] = Formation_FMS_B.Other_Mission_Data.type[2];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  rty_Other_Mission_Data_valid_it[2] =
    Formation_FMS_B.Other_Mission_Data.valid_items[2];

  // SystemInitialize for SignalConversion generated from: '<Root>/Other_Mission_Data' 
  *rty_Other_Mission_Data_timestam =
    Formation_FMS_B.Other_Mission_Data.timestamp;

  // SystemInitialize for Merge: '<S10>/Merge'
  std::memset(&Formation_FMS_B.Merge, 0, sizeof(FMS_Out_Bus));

  // SystemInitialize for SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_timestamp = Formation_FMS_B.Merge.timestamp;

  // SystemInitialize for SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_state = Formation_FMS_B.Merge.state;

  // SystemInitialize for SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_ax_cmd = Formation_FMS_B.Merge.ax_cmd;

  // SystemInitialize for SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_ay_cmd = Formation_FMS_B.Merge.ay_cmd;

  // SystemInitialize for SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_vh_cmd = Formation_FMS_B.Merge.vh_cmd;
}

// Disable for referenced model: 'Formation_FMS'
void Formation_FMS::disable(void)
{
  // Disable for SwitchCase: '<S10>/Switch Case'
  if (Formation_FMS_DW.SwitchCase_ActiveSubsystem == 0) {
    // Disable for SwitchCase: '<S12>/Switch Case'
    Formation_FMS_DW.SwitchCase_ActiveSubsystem_c = -1;
  }

  Formation_FMS_DW.SwitchCase_ActiveSubsystem = -1;

  // End of Disable for SwitchCase: '<S10>/Switch Case'
}

// Output and update for referenced model: 'Formation_FMS'
void Formation_FMS::step(const uint32_T *rtu_Pilot_Cmd_timestamp, const uint32_T
  *rtu_Pilot_Cmd_mode, const uint32_T *rtu_Mission_Data_timestamp, const
  uint32_T *rtu_Mission_Data_type, const uint8_T *rtu_Mission_Data_valid_items,
  const real32_T rtu_Mission_Data_x[8], const real32_T rtu_Mission_Data_y[8],
  const real32_T rtu_Mission_Data_z[8], const uint32_T *rtu_INS_Out_timestamp,
  const real32_T *rtu_INS_Out_phi, const real32_T *rtu_INS_Out_theta, const
  real32_T *rtu_INS_Out_psi, const real32_T *rtu_INS_Out_p, const real32_T
  *rtu_INS_Out_q, const real32_T *rtu_INS_Out_r, const real32_T
  rtu_INS_Out_quat[4], const real32_T *rtu_INS_Out_x_R, const real32_T
  *rtu_INS_Out_y_R, const real32_T *rtu_INS_Out_h_R, const real32_T
  *rtu_INS_Out_airspeed, const real32_T *rtu_INS_Out_ax, const real32_T
  *rtu_INS_Out_ay, const real32_T *rtu_INS_Out_az, const real32_T
  *rtu_INS_Out_vn, const real32_T *rtu_INS_Out_ve, const real32_T
  *rtu_INS_Out_vd, const uint32_T rtu_Formation_Cross_timestamp[3], const
  real32_T rtu_Formation_Cross_x_R[3], const real32_T rtu_Formation_Cross_y_R[3],
  const real32_T rtu_Formation_Cross_h_R[3], const real32_T
  rtu_Formation_Cross_vn[3], const real32_T rtu_Formation_Cross_ve[3], const
  real32_T rtu_Formation_Cross_vd[3], uint32_T *rty_FMS_Out_timestamp,
  VehicleState *rty_FMS_Out_state, real32_T *rty_FMS_Out_ax_cmd, real32_T
  *rty_FMS_Out_ay_cmd, real32_T *rty_FMS_Out_vh_cmd, uint32_T
  *rty_Other_Mission_Data_timestam, uint32_T rty_Other_Mission_Data_type[3],
  uint8_T rty_Other_Mission_Data_valid_it[3], real32_T rty_Other_Mission_Data_x
  [24], real32_T rty_Other_Mission_Data_y[24], real32_T
  rty_Other_Mission_Data_z[24], real32_T rty_Other_Mission_Data_heading[24],
  real32_T rty_Other_Mission_Data_ext1[24], real32_T
  rty_Other_Mission_Data_ext2[24])
{
  int8_T rtPrevAction;
  boolean_T x[3];
  boolean_T b_x[2];
  boolean_T exitg1;
  boolean_T rtb_FixPtRelationalOperator_c;

  // BusCreator generated from: '<Root>/FMS State Machine'
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.timestamp =
    *rtu_INS_Out_timestamp;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.phi = *rtu_INS_Out_phi;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.theta = *rtu_INS_Out_theta;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.psi = *rtu_INS_Out_psi;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.p = *rtu_INS_Out_p;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.q = *rtu_INS_Out_q;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.r = *rtu_INS_Out_r;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.quat[0] = rtu_INS_Out_quat[0];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.quat[1] = rtu_INS_Out_quat[1];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.quat[2] = rtu_INS_Out_quat[2];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.quat[3] = rtu_INS_Out_quat[3];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.x_R = *rtu_INS_Out_x_R;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.y_R = *rtu_INS_Out_y_R;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.h_R = *rtu_INS_Out_h_R;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.airspeed =
    *rtu_INS_Out_airspeed;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.ax = *rtu_INS_Out_ax;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.ay = *rtu_INS_Out_ay;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.az = *rtu_INS_Out_az;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.vn = *rtu_INS_Out_vn;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.ve = *rtu_INS_Out_ve;
  Formation_FMS_B.BusConversion_InsertedFor_FMS_c.vd = *rtu_INS_Out_vd;

  // BusCreator generated from: '<Root>/FMS State Machine'
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.timestamp[0] =
    rtu_Formation_Cross_timestamp[0];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.x_R[0] =
    rtu_Formation_Cross_x_R[0];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.y_R[0] =
    rtu_Formation_Cross_y_R[0];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.h_R[0] =
    rtu_Formation_Cross_h_R[0];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.vn[0] =
    rtu_Formation_Cross_vn[0];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.ve[0] =
    rtu_Formation_Cross_ve[0];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.vd[0] =
    rtu_Formation_Cross_vd[0];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.timestamp[1] =
    rtu_Formation_Cross_timestamp[1];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.x_R[1] =
    rtu_Formation_Cross_x_R[1];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.y_R[1] =
    rtu_Formation_Cross_y_R[1];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.h_R[1] =
    rtu_Formation_Cross_h_R[1];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.vn[1] =
    rtu_Formation_Cross_vn[1];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.ve[1] =
    rtu_Formation_Cross_ve[1];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.vd[1] =
    rtu_Formation_Cross_vd[1];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.timestamp[2] =
    rtu_Formation_Cross_timestamp[2];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.x_R[2] =
    rtu_Formation_Cross_x_R[2];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.y_R[2] =
    rtu_Formation_Cross_y_R[2];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.h_R[2] =
    rtu_Formation_Cross_h_R[2];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.vn[2] =
    rtu_Formation_Cross_vn[2];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.ve[2] =
    rtu_Formation_Cross_ve[2];
  Formation_FMS_B.BusConversion_InsertedFor_FMS_p.vd[2] =
    rtu_Formation_Cross_vd[2];

  // BusCreator generated from: '<Root>/FMS State Machine'
  Formation_FMS_B.BusConversion_InsertedFor_FMS_b = *rtu_Mission_Data_timestamp;
  Formation_FMS_B.BusConversion_InsertedFor_FM_pb = *rtu_Mission_Data_type;
  for (Formation_FMS_B.i = 0; Formation_FMS_B.i < 8; Formation_FMS_B.i++) {
    Formation_FMS_B.BusConversion_InsertedFor_FMSSt[Formation_FMS_B.i] =
      rtu_Mission_Data_x[Formation_FMS_B.i];
    Formation_FMS_B.BusConversion_InsertedFor_FM_cl[Formation_FMS_B.i] =
      rtu_Mission_Data_y[Formation_FMS_B.i];
    Formation_FMS_B.BusConversion_InsertedFor_FMS_k[Formation_FMS_B.i] =
      rtu_Mission_Data_z[Formation_FMS_B.i];
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
    Formation_FMS_DW.DiscreteTimeIntegrator1_DSTAT_l = 0.0F;
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
      (Formation_FMS_DW.DiscreteTimeIntegrator1_DSTAT_l < 0.5F)) {
    // Delay: '<S5>/Delay' incorporates:
    //   DataTypeConversion: '<S5>/Data Type Conversion2'

    Formation_FMS_DW.Delay_DSTATE_j = static_cast<PilotMode>(*rtu_Pilot_Cmd_mode);
  }

  // End of Switch: '<S5>/Switch'

  // Update for UnitDelay: '<S7>/Delay Input1'
  //
  //  Block description for '<S7>/Delay Input1':
  //
  //   Store in Global RAM

  Formation_FMS_DW.DelayInput1_DSTATE = *rtu_Pilot_Cmd_timestamp;

  // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
  Formation_FMS_DW.DiscreteTimeIntegrator1_DSTAT_l += 0.02F;

  // End of Outputs for SubSystem: '<Root>/CommandProcess'

  // Chart: '<Root>/FMS State Machine' incorporates:
  //   Constant: '<Root>/ACCEPT_R'
  //   Delay: '<S5>/Delay'
  //   MATLAB Function: '<S200>/MATLAB Function'

  if (Formation_FMS_DW.temporalCounter_i1 < 511U) {
    Formation_FMS_DW.temporalCounter_i1 = static_cast<uint16_T>
      (Formation_FMS_DW.temporalCounter_i1 + 1);
  }

  Formation_FMS_DW.Mission_Data_timestamp_prev =
    Formation_FMS_DW.Mission_Data_timestamp_start;
  Formation_FMS_DW.Mission_Data_timestamp_start =
    Formation_FMS_B.BusConversion_InsertedFor_FMS_b;
  Formation_FMS_DW.mode_prev = Formation_FMS_DW.mode_start;
  Formation_FMS_DW.mode_start = Formation_FMS_DW.Delay_DSTATE_j;
  if (Formation_FMS_DW.is_active_c3_Formation_FMS == 0U) {
    Formation_FMS_DW.Mission_Data_timestamp_prev =
      Formation_FMS_B.BusConversion_InsertedFor_FMS_b;
    Formation_FMS_DW.mode_prev = Formation_FMS_DW.Delay_DSTATE_j;
    Formation_FMS_DW.is_active_c3_Formation_FMS = 1U;
    x[0] = (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormAssemble);
    x[1] = (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormMission);
    x[2] = (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormDisband);
    rtb_FixPtRelationalOperator_c = false;
    Formation_FMS_B.i = 0;
    exitg1 = false;
    while ((!exitg1) && (Formation_FMS_B.i < 3)) {
      if (x[Formation_FMS_B.i]) {
        rtb_FixPtRelationalOperator_c = true;
        exitg1 = true;
      } else {
        Formation_FMS_B.i++;
      }
    }

    if (rtb_FixPtRelationalOperator_c) {
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Formation;
      Format_enter_internal_Formation
        (&Formation_FMS_B.BusConversion_InsertedFor_FMS_c,
         &Formation_FMS_B.BusConversion_InsertedFor_FMS_p);
    } else {
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Standby;
      Formation_FMS_B.Cmd_In.cur_waypoint[0] =
        Formation_FMS_B.BusConversion_InsertedFor_FMS_c.x_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[1] =
        Formation_FMS_B.BusConversion_InsertedFor_FMS_c.y_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[2] =
        Formation_FMS_B.BusConversion_InsertedFor_FMS_c.h_R;
      Formation_FMS_B.state = VehicleState::Hold;
    }
  } else if ((Formation_FMS_DW.mode_prev != Formation_FMS_DW.mode_start) &&
             (Formation_FMS_DW.Delay_DSTATE_j != PilotMode::None)) {
    x[0] = (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormAssemble);
    x[1] = (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormMission);
    x[2] = (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormDisband);
    rtb_FixPtRelationalOperator_c = false;
    Formation_FMS_B.i = 0;
    exitg1 = false;
    while ((!exitg1) && (Formation_FMS_B.i < 3)) {
      if (x[Formation_FMS_B.i]) {
        rtb_FixPtRelationalOperator_c = true;
        exitg1 = true;
      } else {
        Formation_FMS_B.i++;
      }
    }

    if (rtb_FixPtRelationalOperator_c) {
      Formation_exit_internal_Vehicle();
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Formation;
      Format_enter_internal_Formation
        (&Formation_FMS_B.BusConversion_InsertedFor_FMS_c,
         &Formation_FMS_B.BusConversion_InsertedFor_FMS_p);
    } else {
      Formation_exit_internal_Vehicle();
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Standby;
      Formation_FMS_B.Cmd_In.cur_waypoint[0] =
        Formation_FMS_B.BusConversion_InsertedFor_FMS_c.x_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[1] =
        Formation_FMS_B.BusConversion_InsertedFor_FMS_c.y_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[2] =
        Formation_FMS_B.BusConversion_InsertedFor_FMS_c.h_R;
      Formation_FMS_B.state = VehicleState::Hold;
    }
  } else if (Formation_FMS_DW.is_Vehicle == Formation_FMS_IN_Formation) {
    // Outputs for Function Call SubSystem: '<S3>/Vehicle.Formation.check_form_valid' 
    // MATLAB Function: '<S200>/MATLAB Function'
    Formation_FMS_B.BusConversion_InsertedFor_FMS_b = 0U;
    for (Formation_FMS_B.i = 0; Formation_FMS_B.i < 3; Formation_FMS_B.i++) {
      Formation_FMS_B.scale = 1.29246971E-26F;
      Formation_FMS_B.absxk = std::abs
        (Formation_FMS_B.BusConversion_InsertedFor_FMS_p.x_R[Formation_FMS_B.i]
         - Formation_FMS_B.BusConversion_InsertedFor_FMS_c.x_R);
      if (Formation_FMS_B.absxk > 1.29246971E-26F) {
        Formation_FMS_B.rtb_vn_idx_1 = 1.0F;
        Formation_FMS_B.scale = Formation_FMS_B.absxk;
      } else {
        Formation_FMS_B.t = Formation_FMS_B.absxk / 1.29246971E-26F;
        Formation_FMS_B.rtb_vn_idx_1 = Formation_FMS_B.t * Formation_FMS_B.t;
      }

      Formation_FMS_B.absxk = std::abs
        (Formation_FMS_B.BusConversion_InsertedFor_FMS_p.y_R[Formation_FMS_B.i]
         - Formation_FMS_B.BusConversion_InsertedFor_FMS_c.y_R);
      if (Formation_FMS_B.absxk > Formation_FMS_B.scale) {
        Formation_FMS_B.t = Formation_FMS_B.scale / Formation_FMS_B.absxk;
        Formation_FMS_B.rtb_vn_idx_1 = Formation_FMS_B.rtb_vn_idx_1 *
          Formation_FMS_B.t * Formation_FMS_B.t + 1.0F;
        Formation_FMS_B.scale = Formation_FMS_B.absxk;
      } else {
        Formation_FMS_B.t = Formation_FMS_B.absxk / Formation_FMS_B.scale;
        Formation_FMS_B.rtb_vn_idx_1 += Formation_FMS_B.t * Formation_FMS_B.t;
      }

      if (Formation_FMS_B.scale * std::sqrt(Formation_FMS_B.rtb_vn_idx_1) <=
          FORMATION_PARAM.FORM_RADIUS) {
        Formation_FMS_B.BusConversion_InsertedFor_FMS_b |= 1U <<
          Formation_FMS_B.i;
      } else {
        Formation_FMS_B.BusConversion_InsertedFor_FMS_b &= ~(1U <<
          Formation_FMS_B.i);
      }
    }

    Formation_FMS_B.Cmd_In.form_valid =
      Formation_FMS_B.BusConversion_InsertedFor_FMS_b;

    // End of Outputs for SubSystem: '<S3>/Vehicle.Formation.check_form_valid'
    switch (Formation_FMS_DW.is_Formation) {
     case Formation_FMS_IN_FormAssemble:
      switch (Formation_FMS_DW.is_FormAssemble) {
       case Formation_FMS_IN_Hold:
        Formation_FMS_B.state = VehicleState::FormHold;
        if (Formation_FMS_B.Cmd_In.form_valid == 7U) {
          Formation_FMS_DW.is_FormAssemble = Formation_FM_IN_NO_ACTIVE_CHILD;
          Formation_FMS_DW.is_Formation = Formation_FMS_IN_FormMission;
          Formation_FMS_B.Cmd_In.sp_waypoint[0] =
            Formation_FMS_B.BusConversion_InsertedFor_FMS_c.x_R;
          Formation_FMS_B.Cmd_In.sp_waypoint[1] =
            Formation_FMS_B.BusConversion_InsertedFor_FMS_c.y_R;
          Formation_FMS_B.Cmd_In.sp_waypoint[2] =
            Formation_FMS_B.BusConversion_InsertedFor_FMS_c.h_R;
          Formation_FMS_B.state = VehicleState::FormMission;
          Formation_FMS_DW.is_FormMission = Formation_FMS_IN_NextWP;
        }
        break;

       case Formation_FMS_IN_NextWP:
        Formation_FMS_B.state = VehicleState::FormAssemble;
        if (Formation_FMS_B.wp_index <= *rtu_Mission_Data_valid_items) {
          Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_Waypoint;
          Formation_FMS_B.Cmd_In.cur_waypoint[0] =
            Formation_FMS_B.Cmd_In.sp_waypoint[0];
          Formation_FMS_B.Cmd_In.cur_waypoint[1] =
            Formation_FMS_B.Cmd_In.sp_waypoint[1];
          Formation_FMS_B.Cmd_In.cur_waypoint[2] =
            Formation_FMS_B.Cmd_In.sp_waypoint[2];
          Formation_FMS_B.Cmd_In.sp_waypoint[0] =
            Formation_FMS_B.BusConversion_InsertedFor_FMSSt[Formation_FMS_B.wp_index
            - 1];
          Formation_FMS_B.Cmd_In.sp_waypoint[1] =
            Formation_FMS_B.BusConversion_InsertedFor_FM_cl[Formation_FMS_B.wp_index
            - 1];
          Formation_FMS_B.Cmd_In.sp_waypoint[2] =
            Formation_FMS_B.BusConversion_InsertedFor_FMS_k[Formation_FMS_B.wp_index
            - 1];
          b_x[0] = (Formation_FMS_B.Cmd_In.cur_waypoint[0] ==
                    Formation_FMS_B.Cmd_In.sp_waypoint[0]);
          b_x[1] = (Formation_FMS_B.Cmd_In.cur_waypoint[1] ==
                    Formation_FMS_B.Cmd_In.sp_waypoint[1]);
          rtb_FixPtRelationalOperator_c = true;
          Formation_FMS_B.i = 0;
          exitg1 = false;
          while ((!exitg1) && (Formation_FMS_B.i < 2)) {
            if (!b_x[Formation_FMS_B.i]) {
              rtb_FixPtRelationalOperator_c = false;
              exitg1 = true;
            } else {
              Formation_FMS_B.i++;
            }
          }

          if (rtb_FixPtRelationalOperator_c) {
            Formation_FMS_B.Cmd_In.sp_waypoint[0] += 0.01F;
            Formation_FMS_B.Cmd_In.sp_waypoint[1] += 0.01F;
          }
        } else {
          Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_Hold;
          Formation_FMS_B.Cmd_In.cur_waypoint[0] =
            Formation_FMS_B.Cmd_In.sp_waypoint[0];
          Formation_FMS_B.Cmd_In.cur_waypoint[1] =
            Formation_FMS_B.Cmd_In.sp_waypoint[1];
          Formation_FMS_B.Cmd_In.cur_waypoint[2] =
            Formation_FMS_B.Cmd_In.sp_waypoint[2];
          Formation_FMS_B.state = VehicleState::FormHold;
        }
        break;

       case Formation_FMS_IN_WaitForUpdate:
        Formation_FMS_B.state = VehicleState::FormHold;
        if ((Formation_FMS_DW.Mission_Data_timestamp_prev !=
             Formation_FMS_DW.Mission_Data_timestamp_start) &&
            (Formation_FMS_B.BusConversion_InsertedFor_FM_pb == 1U)) {
          Formation_FMS_B.wp_index = 1U;
          Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_NextWP;
          Formation_FMS_B.state = VehicleState::FormAssemble;
        } else if (Formation_FMS_DW.temporalCounter_i1 >= 500U) {
          Formation_FMS_DW.is_FormAssemble = Formation_FM_IN_NO_ACTIVE_CHILD;
          Formation_FMS_DW.is_Formation = Formation_FM_IN_NO_ACTIVE_CHILD;
          Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Standby;
          Formation_FMS_B.Cmd_In.cur_waypoint[0] =
            Formation_FMS_B.BusConversion_InsertedFor_FMS_c.x_R;
          Formation_FMS_B.Cmd_In.cur_waypoint[1] =
            Formation_FMS_B.BusConversion_InsertedFor_FMS_c.y_R;
          Formation_FMS_B.Cmd_In.cur_waypoint[2] =
            Formation_FMS_B.BusConversion_InsertedFor_FMS_c.h_R;
          Formation_FMS_B.state = VehicleState::Hold;
        }
        break;

       default:
        // case IN_Waypoint:
        Formation_FMS_B.P[0] =
          Formation_FMS_B.BusConversion_InsertedFor_FMS_c.x_R -
          Formation_FMS_B.Cmd_In.sp_waypoint[0];
        Formation_FMS_B.P[1] =
          Formation_FMS_B.BusConversion_InsertedFor_FMS_c.y_R -
          Formation_FMS_B.Cmd_In.sp_waypoint[1];
        if (norm_FqL2z8vo(Formation_FMS_B.P) <= FMS_PARAM.ACCEPT_R) {
          Formation_FMS_B.BusConversion_InsertedFor_FM_pb =
            Formation_FMS_B.wp_index + 1U;
          if (Formation_FMS_B.wp_index + 1U > 65535U) {
            Formation_FMS_B.BusConversion_InsertedFor_FM_pb = 65535U;
          }

          Formation_FMS_B.wp_index = static_cast<uint16_T>
            (Formation_FMS_B.BusConversion_InsertedFor_FM_pb);
          Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_NextWP;
          Formation_FMS_B.state = VehicleState::FormAssemble;
        }
        break;
      }
      break;

     case Formation_FMS_IN_FormDisband:
      Formation_FMS_B.state = VehicleState::FormDisband;
      break;

     case Formation_FMS_IN_FormMission:
      Formation_FMS_B.state = VehicleState::FormMission;
      if ((Formation_FMS_DW.Mission_Data_timestamp_prev !=
           Formation_FMS_DW.Mission_Data_timestamp_start) &&
          (Formation_FMS_B.BusConversion_InsertedFor_FM_pb == 3U)) {
        Formation_FMS_B.wp_index = 1U;
        Formation_FMS_DW.is_FormMission = Formation_FMS_IN_NextWP;
      } else {
        switch (Formation_FMS_DW.is_FormMission) {
         case Formation_FMS_IN_Follower:
          break;

         case Formation_FMS_IN_NextWP:
          if (FORMATION_PARAM.UAV_ID != 1U) {
            Formation_FMS_DW.is_FormMission = Formation_FMS_IN_Follower;
          } else if (Formation_FMS_B.wp_index <= *rtu_Mission_Data_valid_items)
          {
            Formation_FMS_DW.is_FormMission = Formation_FMS_IN_Waypoint_g;
            Formation_FMS_B.Cmd_In.cur_waypoint[0] =
              Formation_FMS_B.Cmd_In.sp_waypoint[0];
            Formation_FMS_B.Cmd_In.cur_waypoint[1] =
              Formation_FMS_B.Cmd_In.sp_waypoint[1];
            Formation_FMS_B.Cmd_In.cur_waypoint[2] =
              Formation_FMS_B.Cmd_In.sp_waypoint[2];
            Formation_FMS_B.Cmd_In.sp_waypoint[0] =
              Formation_FMS_B.BusConversion_InsertedFor_FMSSt[Formation_FMS_B.wp_index
              - 1];
            Formation_FMS_B.Cmd_In.sp_waypoint[1] =
              Formation_FMS_B.BusConversion_InsertedFor_FM_cl[Formation_FMS_B.wp_index
              - 1];
            Formation_FMS_B.Cmd_In.sp_waypoint[2] =
              Formation_FMS_B.BusConversion_InsertedFor_FMS_k[Formation_FMS_B.wp_index
              - 1];
          }
          break;

         default:
          // case IN_Waypoint:
          Formation_FMS_B.P[0] =
            Formation_FMS_B.BusConversion_InsertedFor_FMS_c.x_R -
            Formation_FMS_B.Cmd_In.sp_waypoint[0];
          Formation_FMS_B.P[1] =
            Formation_FMS_B.BusConversion_InsertedFor_FMS_c.y_R -
            Formation_FMS_B.Cmd_In.sp_waypoint[1];
          if (norm_FqL2z8vo(Formation_FMS_B.P) <= FMS_PARAM.ACCEPT_R) {
            Formation_FMS_B.BusConversion_InsertedFor_FM_pb =
              Formation_FMS_B.wp_index + 1U;
            if (Formation_FMS_B.wp_index + 1U > 65535U) {
              Formation_FMS_B.BusConversion_InsertedFor_FM_pb = 65535U;
            }

            Formation_FMS_B.wp_index = static_cast<uint16_T>
              (Formation_FMS_B.BusConversion_InsertedFor_FM_pb);
            Formation_FMS_DW.is_FormMission = Formation_FMS_IN_NextWP;
          }
          break;
        }
      }
      break;

     default:
      // case IN_InvalidMode:
      Formation_FMS_DW.is_Formation = Formation_FM_IN_NO_ACTIVE_CHILD;
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Standby;
      Formation_FMS_B.Cmd_In.cur_waypoint[0] =
        Formation_FMS_B.BusConversion_InsertedFor_FMS_c.x_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[1] =
        Formation_FMS_B.BusConversion_InsertedFor_FMS_c.y_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[2] =
        Formation_FMS_B.BusConversion_InsertedFor_FMS_c.h_R;
      Formation_FMS_B.state = VehicleState::Hold;
      break;
    }
  } else {
    // case IN_Standby:
    Formation_FMS_B.state = VehicleState::Hold;
  }

  // End of Chart: '<Root>/FMS State Machine'

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_x[0],
              &Formation_FMS_B.Other_Mission_Data.x[0], 24U * sizeof(real32_T));

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_y[0],
              &Formation_FMS_B.Other_Mission_Data.y[0], 24U * sizeof(real32_T));

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_z[0],
              &Formation_FMS_B.Other_Mission_Data.z[0], 24U * sizeof(real32_T));

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_heading[0],
              &Formation_FMS_B.Other_Mission_Data.heading[0], 24U * sizeof
              (real32_T));

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_ext1[0],
              &Formation_FMS_B.Other_Mission_Data.ext1[0], 24U * sizeof(real32_T));

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  std::memcpy(&rty_Other_Mission_Data_ext2[0],
              &Formation_FMS_B.Other_Mission_Data.ext2[0], 24U * sizeof(real32_T));

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.vd[0] = rtu_Formation_Cross_vd[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.ve[0] = rtu_Formation_Cross_ve[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.rtb_vn_idx_0 = rtu_Formation_Cross_vn[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.absxk = rtu_Formation_Cross_h_R[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.scale = rtu_Formation_Cross_y_R[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.rtb_x_R_idx_0 = rtu_Formation_Cross_x_R[0];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.vd[1] = rtu_Formation_Cross_vd[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.ve[1] = rtu_Formation_Cross_ve[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.rtb_vn_idx_1 = rtu_Formation_Cross_vn[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.t = rtu_Formation_Cross_h_R[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.rtb_y_R_idx_1 = rtu_Formation_Cross_y_R[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.rtb_x_R_idx_1 = rtu_Formation_Cross_x_R[1];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.vd[2] = rtu_Formation_Cross_vd[2];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.ve[2] = rtu_Formation_Cross_ve[2];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.rtb_vn_idx_2 = rtu_Formation_Cross_vn[2];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.Multiply1_f = rtu_Formation_Cross_h_R[2];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.rtb_y_R_idx_2 = rtu_Formation_Cross_y_R[2];

  // SignalConversion generated from: '<S9>/Signal Copy2'
  Formation_FMS_B.rtb_x_R_idx_2 = rtu_Formation_Cross_x_R[2];

  // SwitchCase: '<S10>/Switch Case' incorporates:
  //   Merge: '<S10>/Merge'
  //   Product: '<S196>/Divide'
  //   Product: '<S197>/Divide'

  rtPrevAction = Formation_FMS_DW.SwitchCase_ActiveSubsystem;
  switch (Formation_FMS_B.state) {
   case VehicleState::FormAssemble:
   case VehicleState::FormHold:
   case VehicleState::FormMission:
   case VehicleState::FormDisband:
    Formation_FMS_DW.SwitchCase_ActiveSubsystem = 0;
    break;

   case VehicleState::Hold:
    Formation_FMS_DW.SwitchCase_ActiveSubsystem = 1;
    break;

   default:
    Formation_FMS_DW.SwitchCase_ActiveSubsystem = 2;
    break;
  }

  if ((rtPrevAction != Formation_FMS_DW.SwitchCase_ActiveSubsystem) &&
      (rtPrevAction == 0)) {
    // SwitchCase: '<S12>/Switch Case'
    Formation_FMS_DW.SwitchCase_ActiveSubsystem_c = -1;
  }

  switch (Formation_FMS_DW.SwitchCase_ActiveSubsystem) {
   case 0:
    // Outputs for IfAction SubSystem: '<S10>/Form_Subsystem' incorporates:
    //   ActionPort: '<S12>/Action Port'

    // SwitchCase: '<S12>/Switch Case' incorporates:
    //   MATLAB Function: '<S86>/Calc_Position_Velocity_Setpoint'
    //   Merge: '<S10>/Merge'
    //   Product: '<S102>/Divide'
    //   Product: '<S43>/Divide'
    //   Product: '<S60>/Divide'
    //   Product: '<S61>/Divide'
    //   Product: '<S78>/Divide'
    //   Product: '<S79>/Divide'
    //   Product: '<S96>/Divide'
    //   Sum: '<S31>/Subtract'

    rtPrevAction = Formation_FMS_DW.SwitchCase_ActiveSubsystem_c;
    switch (Formation_FMS_B.state) {
     case VehicleState::FormAssemble:
      Formation_FMS_DW.SwitchCase_ActiveSubsystem_c = 0;
      break;

     case VehicleState::FormHold:
      Formation_FMS_DW.SwitchCase_ActiveSubsystem_c = 1;
      break;

     case VehicleState::FormMission:
      Formation_FMS_DW.SwitchCase_ActiveSubsystem_c = 2;
      break;

     case VehicleState::FormDisband:
      Formation_FMS_DW.SwitchCase_ActiveSubsystem_c = 3;
      break;

     default:
      Formation_FMS_DW.SwitchCase_ActiveSubsystem_c = 4;
      break;
    }

    switch (Formation_FMS_DW.SwitchCase_ActiveSubsystem_c) {
     case 0:
      // Outputs for IfAction SubSystem: '<S12>/FormAssemble' incorporates:
      //   ActionPort: '<S17>/Action Port'

      // RelationalOperator: '<S23>/FixPt Relational Operator' incorporates:
      //   UnitDelay: '<S23>/Delay Input1'
      //
      //  Block description for '<S23>/Delay Input1':
      //
      //   Store in Global RAM

      rtb_FixPtRelationalOperator_c = (Formation_FMS_B.wp_index !=
        Formation_FMS_DW.DelayInput1_DSTATE_h);

      // Outputs for Resettable SubSystem: '<S17>/Mission_SubSystem' incorporates:
      //   ResetPort: '<S24>/Reset'

      // InitializeConditions for Delay: '<S26>/Delay'
      Formation_FMS_DW.icLoad_h = ((rtb_FixPtRelationalOperator_c &&
        (Formation_FMS_PrevZCX.Mission_SubSystem_Reset_ZCE != POS_ZCSIG)) ||
        Formation_FMS_DW.icLoad_h);
      Formation_FMS_PrevZCX.Mission_SubSystem_Reset_ZCE =
        rtb_FixPtRelationalOperator_c;

      // SignalConversion generated from: '<S39>/Square'
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = *rtu_INS_Out_vn;
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = *rtu_INS_Out_ve;

      // Sum: '<S40>/Sum of Elements' incorporates:
      //   Math: '<S40>/Math Function'
      //   Sum: '<S39>/Sum of Elements'

      Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0] +
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1];

      // Math: '<S40>/Math Function1' incorporates:
      //   Sum: '<S40>/Sum of Elements'
      //
      //  About '<S40>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.absxk = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.absxk = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S40>/Math Function1'

      // Switch: '<S40>/Switch' incorporates:
      //   Constant: '<S40>/Constant'
      //   Product: '<S40>/Product'

      if (Formation_FMS_B.absxk > 0.0F) {
        Formation_FMS_B.vd[0] = *rtu_INS_Out_vn;
        Formation_FMS_B.vd[1] = *rtu_INS_Out_ve;
        Formation_FMS_B.vd[2] = Formation_FMS_B.absxk;
      } else {
        Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
          0.0F;
        Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
          0.0F;
        Formation_FMS_B.vd[2] = 1.0F;
      }

      // End of Switch: '<S40>/Switch'

      // Reshape: '<S29>/Reshape2'
      Formation_FMS_B.Reshape2_bq[0] = *rtu_INS_Out_x_R;
      Formation_FMS_B.Reshape2_bq[1] = *rtu_INS_Out_y_R;

      // MATLAB Function: '<S30>/NearbyRefWP' incorporates:
      //   Constant: '<S28>/L1'

      Formation_FMS_NearbyRefWP(&Formation_FMS_B.Cmd_In.sp_waypoint[0],
        Formation_FMS_B.Reshape2_bq, FMS_PARAM.L1,
        Formation_FMS_B.TmpSignalConversionAtSqua_c, &Formation_FMS_B.absxk);

      // MATLAB Function: '<S30>/SearchL1RefWP' incorporates:
      //   Constant: '<S28>/L1'

      Formation_FMS_SearchL1RefWP(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
        &Formation_FMS_B.Cmd_In.sp_waypoint[0], Formation_FMS_B.Reshape2_bq,
        FMS_PARAM.L1, Formation_FMS_B.P_d, &Formation_FMS_B.t);

      // MATLAB Function: '<S30>/OutRegionRegWP'
      Formation_FMS_OutRegionRegWP(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
        &Formation_FMS_B.Cmd_In.sp_waypoint[0], Formation_FMS_B.Reshape2_bq,
        Formation_FMS_B.P_i);

      // Switch: '<S30>/Switch1' incorporates:
      //   Constant: '<S32>/Constant'
      //   Constant: '<S33>/Constant'
      //   Product: '<S43>/Divide'
      //   RelationalOperator: '<S32>/Compare'
      //   RelationalOperator: '<S33>/Compare'
      //   Switch: '<S30>/Switch'

      if (Formation_FMS_B.absxk > 0.0F) {
        Formation_FMS_B.P_d[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
        Formation_FMS_B.P_d[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
      } else if (!(Formation_FMS_B.t >= 0.0F)) {
        // Product: '<S43>/Divide' incorporates:
        //   Switch: '<S30>/Switch'

        Formation_FMS_B.P_d[0] = Formation_FMS_B.P_i[0];
        Formation_FMS_B.P_d[1] = Formation_FMS_B.P_i[1];
      }

      // End of Switch: '<S30>/Switch1'

      // Sum: '<S31>/Subtract' incorporates:
      //   Product: '<S43>/Divide'
      //   Reshape: '<S29>/Reshape2'

      Formation_FMS_B.Multiply1_f = Formation_FMS_B.P_d[0] -
        Formation_FMS_B.Reshape2_bq[0];

      // Math: '<S41>/Math Function'
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] =
        Formation_FMS_B.Multiply1_f * Formation_FMS_B.Multiply1_f;
      Formation_FMS_B.P_d[0] = Formation_FMS_B.Multiply1_f;

      // Sum: '<S31>/Subtract' incorporates:
      //   Product: '<S43>/Divide'
      //   Reshape: '<S29>/Reshape2'

      Formation_FMS_B.Multiply1_f = Formation_FMS_B.P_d[1] -
        Formation_FMS_B.Reshape2_bq[1];

      // Sum: '<S41>/Sum of Elements' incorporates:
      //   Math: '<S41>/Math Function'

      Formation_FMS_B.absxk = Formation_FMS_B.Multiply1_f *
        Formation_FMS_B.Multiply1_f +
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

      // Math: '<S41>/Math Function1' incorporates:
      //   Sum: '<S41>/Sum of Elements'
      //
      //  About '<S41>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.absxk < 0.0F) {
        Formation_FMS_B.absxk = -std::sqrt(std::abs(Formation_FMS_B.absxk));
      } else {
        Formation_FMS_B.absxk = std::sqrt(Formation_FMS_B.absxk);
      }

      // End of Math: '<S41>/Math Function1'

      // Switch: '<S41>/Switch' incorporates:
      //   Constant: '<S41>/Constant'
      //   Product: '<S41>/Product'
      //   Sum: '<S31>/Subtract'
      //   Switch: '<S44>/Switch'

      if (Formation_FMS_B.absxk > 0.0F) {
        Formation_FMS_B.ve[0] = Formation_FMS_B.P_d[0];
        Formation_FMS_B.ve[1] = Formation_FMS_B.Multiply1_f;
        Formation_FMS_B.ve[2] = Formation_FMS_B.absxk;
      } else {
        Formation_FMS_B.ve[0] = Formation_FMS_B.P_d[0] * 0.0F;
        Formation_FMS_B.ve[1] = Formation_FMS_B.Multiply1_f * 0.0F;
        Formation_FMS_B.ve[2] = 1.0F;
      }

      // End of Switch: '<S41>/Switch'

      // Product: '<S40>/Divide'
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.vd[0] /
        Formation_FMS_B.vd[2];
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.vd[1] /
        Formation_FMS_B.vd[2];

      // Sum: '<S43>/Sum of Elements' incorporates:
      //   Math: '<S43>/Math Function'
      //   SignalConversion generated from: '<S43>/Math Function'

      Formation_FMS_B.absxk = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1] +
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

      // Math: '<S43>/Math Function1' incorporates:
      //   Sum: '<S43>/Sum of Elements'
      //
      //  About '<S43>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.absxk < 0.0F) {
        Formation_FMS_B.absxk = -std::sqrt(std::abs(Formation_FMS_B.absxk));
      } else {
        Formation_FMS_B.absxk = std::sqrt(Formation_FMS_B.absxk);
      }

      // End of Math: '<S43>/Math Function1'

      // Switch: '<S43>/Switch' incorporates:
      //   Constant: '<S43>/Constant'
      //   Product: '<S43>/Product'
      //   SignalConversion generated from: '<S43>/Math Function'

      if (Formation_FMS_B.absxk > 0.0F) {
        Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
        Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
        Formation_FMS_B.vd[2] = Formation_FMS_B.absxk;
      } else {
        Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
          0.0F;
        Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
          0.0F;
        Formation_FMS_B.vd[2] = 1.0F;
      }

      // End of Switch: '<S43>/Switch'

      // Product: '<S41>/Divide' incorporates:
      //   Product: '<S44>/Divide'

      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.ve[0] /
        Formation_FMS_B.ve[2];
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.ve[1] /
        Formation_FMS_B.ve[2];

      // Sum: '<S44>/Sum of Elements' incorporates:
      //   Math: '<S44>/Math Function'
      //   SignalConversion generated from: '<S44>/Math Function'

      Formation_FMS_B.absxk = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1] +
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

      // Math: '<S44>/Math Function1' incorporates:
      //   Sum: '<S44>/Sum of Elements'
      //
      //  About '<S44>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.absxk < 0.0F) {
        Formation_FMS_B.absxk = -std::sqrt(std::abs(Formation_FMS_B.absxk));
      } else {
        Formation_FMS_B.absxk = std::sqrt(Formation_FMS_B.absxk);
      }

      // End of Math: '<S44>/Math Function1'

      // Switch: '<S44>/Switch' incorporates:
      //   Constant: '<S44>/Constant'
      //   Product: '<S44>/Product'
      //   SignalConversion generated from: '<S44>/Math Function'

      if (Formation_FMS_B.absxk > 0.0F) {
        Formation_FMS_B.ve[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
        Formation_FMS_B.ve[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
        Formation_FMS_B.ve[2] = Formation_FMS_B.absxk;
      } else {
        Formation_FMS_B.ve[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
          0.0F;
        Formation_FMS_B.ve[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
          0.0F;
        Formation_FMS_B.ve[2] = 1.0F;
      }

      // End of Switch: '<S44>/Switch'

      // Product: '<S44>/Divide'
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.ve[0] /
        Formation_FMS_B.ve[2];

      // Product: '<S43>/Divide'
      Formation_FMS_B.P_d[0] = Formation_FMS_B.vd[0] / Formation_FMS_B.vd[2];

      // Product: '<S44>/Divide'
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.ve[1] /
        Formation_FMS_B.ve[2];

      // Product: '<S43>/Divide'
      Formation_FMS_B.P_d[1] = Formation_FMS_B.vd[1] / Formation_FMS_B.vd[2];

      // Sqrt: '<S39>/Sqrt'
      Formation_FMS_B.absxk = std::sqrt(Formation_FMS_B.scale);

      // Math: '<S37>/Square'
      Formation_FMS_B.scale = Formation_FMS_B.absxk * Formation_FMS_B.absxk;

      // Sum: '<S42>/Subtract' incorporates:
      //   Product: '<S42>/Multiply'
      //   Product: '<S42>/Multiply1'

      Formation_FMS_B.t = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.P_d[1] - Formation_FMS_B.P_d[0] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1];

      // Signum: '<S38>/Sign1'
      if (std::isnan(Formation_FMS_B.t)) {
        Formation_FMS_B.absxk = (rtNaNF);
      } else if (Formation_FMS_B.t < 0.0F) {
        Formation_FMS_B.absxk = -1.0F;
      } else {
        Formation_FMS_B.absxk = (Formation_FMS_B.t > 0.0F);
      }

      // End of Signum: '<S38>/Sign1'

      // Switch: '<S38>/Switch2' incorporates:
      //   Constant: '<S38>/Constant4'

      if (Formation_FMS_B.absxk != 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = Formation_FMS_B.absxk;
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = 1.0F;
      }

      // End of Switch: '<S38>/Switch2'

      // Sum: '<S25>/Sum' incorporates:
      //   Constant: '<S25>/Constant'

      Formation_FMS_B.absxk = FMS_PARAM.FW_AIRSPD_TRIM - *rtu_INS_Out_airspeed;

      // Delay: '<S26>/Delay' incorporates:
      //   Constant: '<S26>/Constant'

      if (Formation_FMS_DW.icLoad_h) {
        Formation_FMS_DW.Delay_DSTATE_l = FMS_PARAM.FW_HEIGHT_TRIM;
      }

      // Sum: '<S26>/Sum' incorporates:
      //   Delay: '<S26>/Delay'

      Formation_FMS_B.t = Formation_FMS_DW.Delay_DSTATE_l - *rtu_INS_Out_h_R;

      // End of Outputs for SubSystem: '<S17>/Mission_SubSystem'
      // End of Outputs for SubSystem: '<S12>/FormAssemble'
      std::memset(&Formation_FMS_B.Merge, 0, sizeof(FMS_Out_Bus));

      // Outputs for IfAction SubSystem: '<S12>/FormAssemble' incorporates:
      //   ActionPort: '<S17>/Action Port'

      // Outputs for Resettable SubSystem: '<S17>/Mission_SubSystem' incorporates:
      //   ResetPort: '<S24>/Reset'

      // BusAssignment: '<S24>/Bus Assignment' incorporates:
      //   Constant: '<S24>/Constant1'
      //   Merge: '<S10>/Merge'

      Formation_FMS_B.Merge.state = VehicleState::FormAssemble;
      Formation_FMS_B.Merge.ax_cmd = Formation_FMS_B.absxk;

      // DotProduct: '<S38>/Dot Product'
      Formation_FMS_B.Multiply1_f = Formation_FMS_B.P_d[0] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0] + Formation_FMS_B.P_d[1] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1];

      // Trigonometry: '<S38>/Acos' incorporates:
      //   DotProduct: '<S38>/Dot Product'

      if (Formation_FMS_B.Multiply1_f > 1.0F) {
        Formation_FMS_B.Multiply1_f = 1.0F;
      } else if (Formation_FMS_B.Multiply1_f < -1.0F) {
        Formation_FMS_B.Multiply1_f = -1.0F;
      }

      // Product: '<S38>/Multiply' incorporates:
      //   Trigonometry: '<S38>/Acos'

      Formation_FMS_B.Multiply1_f = std::acos(Formation_FMS_B.Multiply1_f) *
        Formation_FMS_B.rtb_vn_idx_1;

      // Saturate: '<S37>/Saturation'
      if (Formation_FMS_B.Multiply1_f > 1.57079637F) {
        Formation_FMS_B.Multiply1_f = 1.57079637F;
      } else if (Formation_FMS_B.Multiply1_f < -1.57079637F) {
        Formation_FMS_B.Multiply1_f = -1.57079637F;
      }

      // Product: '<S37>/Divide' incorporates:
      //   Constant: '<S28>/L1'
      //   Gain: '<S37>/Gain'
      //   Product: '<S37>/Multiply1'
      //   Saturate: '<S37>/Saturation'
      //   Trigonometry: '<S37>/Sin'

      Formation_FMS_B.Multiply1_f = 2.0F * Formation_FMS_B.scale * std::sin
        (Formation_FMS_B.Multiply1_f) / FMS_PARAM.L1;

      // Saturate: '<S28>/Saturation1'
      if (Formation_FMS_B.Multiply1_f > FMS_PARAM.ACC_Y_LIM) {
        // BusAssignment: '<S24>/Bus Assignment'
        Formation_FMS_B.Merge.ay_cmd = FMS_PARAM.ACC_Y_LIM;
      } else if (Formation_FMS_B.Multiply1_f < -FMS_PARAM.ACC_Y_LIM) {
        // BusAssignment: '<S24>/Bus Assignment'
        Formation_FMS_B.Merge.ay_cmd = -FMS_PARAM.ACC_Y_LIM;
      } else {
        // BusAssignment: '<S24>/Bus Assignment'
        Formation_FMS_B.Merge.ay_cmd = Formation_FMS_B.Multiply1_f;
      }

      // End of Saturate: '<S28>/Saturation1'

      // Gain: '<S26>/Gain2'
      Formation_FMS_B.Multiply1_f = FMS_PARAM.Z_P * Formation_FMS_B.t;

      // Saturate: '<S26>/Saturation'
      if (Formation_FMS_B.Multiply1_f > CONTROL_PARAM.FW_T_CLMB_MAX) {
        // BusAssignment: '<S24>/Bus Assignment'
        Formation_FMS_B.Merge.vh_cmd = CONTROL_PARAM.FW_T_CLMB_MAX;
      } else if (Formation_FMS_B.Multiply1_f < -CONTROL_PARAM.FW_T_SINK_MAX) {
        // BusAssignment: '<S24>/Bus Assignment'
        Formation_FMS_B.Merge.vh_cmd = -CONTROL_PARAM.FW_T_SINK_MAX;
      } else {
        // BusAssignment: '<S24>/Bus Assignment'
        Formation_FMS_B.Merge.vh_cmd = Formation_FMS_B.Multiply1_f;
      }

      // End of Saturate: '<S26>/Saturation'

      // Update for Delay: '<S26>/Delay'
      Formation_FMS_DW.icLoad_h = false;

      // End of Outputs for SubSystem: '<S17>/Mission_SubSystem'

      // Update for UnitDelay: '<S23>/Delay Input1'
      //
      //  Block description for '<S23>/Delay Input1':
      //
      //   Store in Global RAM

      Formation_FMS_DW.DelayInput1_DSTATE_h = Formation_FMS_B.wp_index;

      // End of Outputs for SubSystem: '<S12>/FormAssemble'
      break;

     case 1:
      if (Formation_FMS_DW.SwitchCase_ActiveSubsystem_c != rtPrevAction) {
        // InitializeConditions for IfAction SubSystem: '<S12>/FormHold' incorporates:
        //   ActionPort: '<S19>/Action Port'

        // InitializeConditions for SwitchCase: '<S12>/Switch Case' incorporates:
        //   Delay: '<S64>/Delay'
        //   Delay: '<S68>/start_vel'

        Formation_FMS_DW.icLoad_l3 = true;
        Formation_FMS_DW.icLoad_p = true;

        // End of InitializeConditions for SubSystem: '<S12>/FormHold'
      }

      // Outputs for IfAction SubSystem: '<S12>/FormHold' incorporates:
      //   ActionPort: '<S19>/Action Port'

      // SignalConversion generated from: '<S74>/Square'
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = *rtu_INS_Out_vn;
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = *rtu_INS_Out_ve;

      // Math: '<S75>/Math Function' incorporates:
      //   Math: '<S74>/Square'

      Formation_FMS_B.absxk = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
      Formation_FMS_B.t = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1];

      // Sum: '<S75>/Sum of Elements' incorporates:
      //   Math: '<S75>/Math Function'

      Formation_FMS_B.scale = Formation_FMS_B.absxk + Formation_FMS_B.t;

      // Math: '<S75>/Math Function1' incorporates:
      //   Sum: '<S75>/Sum of Elements'
      //
      //  About '<S75>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S75>/Math Function1'

      // Switch: '<S75>/Switch' incorporates:
      //   Constant: '<S75>/Constant'
      //   Product: '<S75>/Product'

      if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
        Formation_FMS_B.vd[0] = *rtu_INS_Out_vn;
        Formation_FMS_B.vd[1] = *rtu_INS_Out_ve;
        Formation_FMS_B.vd[2] = Formation_FMS_B.rtb_vn_idx_1;
      } else {
        Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
          0.0F;
        Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
          0.0F;
        Formation_FMS_B.vd[2] = 1.0F;
      }

      // End of Switch: '<S75>/Switch'

      // Delay: '<S68>/start_vel'
      if (Formation_FMS_DW.icLoad_l3) {
        Formation_FMS_DW.start_vel_DSTATE_n[0] =
          Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
        Formation_FMS_DW.start_vel_DSTATE_n[1] =
          Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
      }

      // Math: '<S80>/Math Function' incorporates:
      //   Delay: '<S68>/start_vel'

      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] =
        Formation_FMS_DW.start_vel_DSTATE_n[0] *
        Formation_FMS_DW.start_vel_DSTATE_n[0];
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] =
        Formation_FMS_DW.start_vel_DSTATE_n[1] *
        Formation_FMS_DW.start_vel_DSTATE_n[1];

      // Sum: '<S80>/Sum of Elements'
      Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] +
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1];

      // Math: '<S80>/Math Function1' incorporates:
      //   Sum: '<S80>/Sum of Elements'
      //
      //  About '<S80>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S80>/Math Function1'

      // Switch: '<S80>/Switch' incorporates:
      //   Constant: '<S80>/Constant'
      //   Delay: '<S68>/start_vel'
      //   Product: '<S80>/Product'

      if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
        Formation_FMS_B.ve[0] = Formation_FMS_DW.start_vel_DSTATE_n[0];
        Formation_FMS_B.ve[1] = Formation_FMS_DW.start_vel_DSTATE_n[1];
        Formation_FMS_B.ve[2] = Formation_FMS_B.rtb_vn_idx_1;
      } else {
        Formation_FMS_B.ve[0] = Formation_FMS_DW.start_vel_DSTATE_n[0] * 0.0F;
        Formation_FMS_B.ve[1] = Formation_FMS_DW.start_vel_DSTATE_n[1] * 0.0F;
        Formation_FMS_B.ve[2] = 1.0F;
      }

      // End of Switch: '<S80>/Switch'

      // Product: '<S75>/Divide'
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.vd[0] /
        Formation_FMS_B.vd[2];
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.vd[1] /
        Formation_FMS_B.vd[2];

      // SignalConversion generated from: '<S78>/Math Function'
      Formation_FMS_B.P_d[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
      Formation_FMS_B.P_d[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

      // Sum: '<S78>/Sum of Elements' incorporates:
      //   Math: '<S78>/Math Function'
      //   SignalConversion generated from: '<S78>/Math Function'

      Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1] +
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

      // Math: '<S78>/Math Function1' incorporates:
      //   Sum: '<S78>/Sum of Elements'
      //
      //  About '<S78>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S78>/Math Function1'

      // Switch: '<S78>/Switch' incorporates:
      //   Constant: '<S78>/Constant'
      //   Product: '<S78>/Product'
      //   SignalConversion generated from: '<S78>/Math Function'

      if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
        Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
        Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
        Formation_FMS_B.vd[2] = Formation_FMS_B.rtb_vn_idx_1;
      } else {
        Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
          0.0F;
        Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
          0.0F;
        Formation_FMS_B.vd[2] = 1.0F;
      }

      // End of Switch: '<S78>/Switch'

      // MinMax: '<S66>/Max' incorporates:
      //   Constant: '<S65>/L1'
      //   Constant: '<S65>/R'
      //   Gain: '<S66>/Gain'

      Formation_FMS_B.scale = std::fmax(FMS_PARAM.LOITER_R, 0.5F * FMS_PARAM.L1);

      // Reshape: '<S66>/Reshape2'
      Formation_FMS_B.Reshape2_bq[0] = *rtu_INS_Out_x_R;
      Formation_FMS_B.Reshape2_bq[1] = *rtu_INS_Out_y_R;

      // MATLAB Function: '<S66>/SearchL1RefWP' incorporates:
      //   Constant: '<S65>/L1'

      Formation_FMS_SearchL1RefWP_i(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
        Formation_FMS_B.Reshape2_bq, Formation_FMS_B.scale, FMS_PARAM.L1,
        Formation_FMS_B.TmpSignalConversionAtSqua_c, &Formation_FMS_B.n_j);

      // RelationalOperator: '<S69>/Compare' incorporates:
      //   Constant: '<S69>/Constant'

      rtb_FixPtRelationalOperator_c = (Formation_FMS_B.n_j > 0.0);

      // Product: '<S80>/Divide'
      Formation_FMS_B.P_i[0] = Formation_FMS_B.ve[0] / Formation_FMS_B.ve[2];
      Formation_FMS_B.P_i[1] = Formation_FMS_B.ve[1] / Formation_FMS_B.ve[2];

      // MATLAB Function: '<S66>/OutRegionRegWP' incorporates:
      //   Constant: '<S65>/L1'

      Formation_FMS_OutRegionRegWP_o(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
        Formation_FMS_B.Reshape2_bq, Formation_FMS_B.scale, FMS_PARAM.L1,
        Formation_FMS_B.P_i, Formation_FMS_B.P_d);

      // Switch: '<S66>/Switch'
      if (rtb_FixPtRelationalOperator_c) {
        Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
      } else {
        Formation_FMS_B.scale = Formation_FMS_B.P_d[0];
      }

      // Sum: '<S67>/Subtract' incorporates:
      //   Switch: '<S66>/Switch'

      Formation_FMS_B.Reshape2_bq[0] = Formation_FMS_B.scale - *rtu_INS_Out_x_R;

      // Switch: '<S66>/Switch'
      if (rtb_FixPtRelationalOperator_c) {
        Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
      } else {
        Formation_FMS_B.scale = Formation_FMS_B.P_d[1];
      }

      // Sum: '<S67>/Subtract' incorporates:
      //   Switch: '<S66>/Switch'

      Formation_FMS_B.Reshape2_bq[1] = Formation_FMS_B.scale - *rtu_INS_Out_y_R;

      // Sum: '<S76>/Sum of Elements' incorporates:
      //   Math: '<S76>/Math Function'
      //   Sum: '<S67>/Subtract'

      Formation_FMS_B.scale = Formation_FMS_B.Reshape2_bq[0] *
        Formation_FMS_B.Reshape2_bq[0] + Formation_FMS_B.Reshape2_bq[1] *
        Formation_FMS_B.Reshape2_bq[1];

      // Math: '<S76>/Math Function1' incorporates:
      //   Sum: '<S76>/Sum of Elements'
      //
      //  About '<S76>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S76>/Math Function1'

      // Switch: '<S76>/Switch' incorporates:
      //   Constant: '<S76>/Constant'
      //   Product: '<S76>/Product'
      //   Sum: '<S67>/Subtract'
      //   Switch: '<S79>/Switch'

      if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
        Formation_FMS_B.ve[0] = Formation_FMS_B.Reshape2_bq[0];
        Formation_FMS_B.ve[1] = Formation_FMS_B.Reshape2_bq[1];
        Formation_FMS_B.ve[2] = Formation_FMS_B.rtb_vn_idx_1;
      } else {
        Formation_FMS_B.ve[0] = Formation_FMS_B.Reshape2_bq[0] * 0.0F;
        Formation_FMS_B.ve[1] = Formation_FMS_B.Reshape2_bq[1] * 0.0F;
        Formation_FMS_B.ve[2] = 1.0F;
      }

      // End of Switch: '<S76>/Switch'

      // Product: '<S76>/Divide' incorporates:
      //   Product: '<S79>/Divide'

      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.ve[0] /
        Formation_FMS_B.ve[2];
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.ve[1] /
        Formation_FMS_B.ve[2];

      // Sum: '<S79>/Sum of Elements' incorporates:
      //   Math: '<S79>/Math Function'
      //   SignalConversion generated from: '<S79>/Math Function'

      Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1] +
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

      // Math: '<S79>/Math Function1' incorporates:
      //   Sum: '<S79>/Sum of Elements'
      //
      //  About '<S79>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S79>/Math Function1'

      // Switch: '<S79>/Switch' incorporates:
      //   Constant: '<S79>/Constant'
      //   Product: '<S79>/Product'
      //   SignalConversion generated from: '<S79>/Math Function'

      if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
        Formation_FMS_B.ve[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
        Formation_FMS_B.ve[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
        Formation_FMS_B.ve[2] = Formation_FMS_B.rtb_vn_idx_1;
      } else {
        Formation_FMS_B.ve[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
          0.0F;
        Formation_FMS_B.ve[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
          0.0F;
        Formation_FMS_B.ve[2] = 1.0F;
      }

      // End of Switch: '<S79>/Switch'

      // Product: '<S79>/Divide'
      Formation_FMS_B.rtb_x_R_idx_0 = Formation_FMS_B.ve[0] /
        Formation_FMS_B.ve[2];

      // Product: '<S78>/Divide'
      Formation_FMS_B.Multiply1_f = Formation_FMS_B.vd[0] / Formation_FMS_B.vd[2];

      // DotProduct: '<S73>/Dot Product'
      Formation_FMS_B.scale = Formation_FMS_B.Multiply1_f *
        Formation_FMS_B.rtb_x_R_idx_0;
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] =
        Formation_FMS_B.rtb_x_R_idx_0;
      Formation_FMS_B.P_d[0] = Formation_FMS_B.Multiply1_f;

      // Product: '<S79>/Divide' incorporates:
      //   Product: '<S78>/Divide'

      Formation_FMS_B.rtb_x_R_idx_0 = Formation_FMS_B.ve[1] /
        Formation_FMS_B.ve[2];

      // Product: '<S78>/Divide'
      Formation_FMS_B.Multiply1_f = Formation_FMS_B.vd[1] / Formation_FMS_B.vd[2];

      // DotProduct: '<S73>/Dot Product'
      Formation_FMS_B.scale += Formation_FMS_B.Multiply1_f *
        Formation_FMS_B.rtb_x_R_idx_0;

      // Sqrt: '<S74>/Sqrt' incorporates:
      //   Math: '<S74>/Square'
      //   Sum: '<S74>/Sum of Elements'

      Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.absxk +
        Formation_FMS_B.t);

      // Math: '<S72>/Square'
      Formation_FMS_B.absxk = Formation_FMS_B.rtb_vn_idx_1 *
        Formation_FMS_B.rtb_vn_idx_1;

      // Sum: '<S77>/Subtract' incorporates:
      //   Product: '<S77>/Multiply'
      //   Product: '<S77>/Multiply1'

      Formation_FMS_B.t = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.Multiply1_f - Formation_FMS_B.P_d[0] *
        Formation_FMS_B.rtb_x_R_idx_0;

      // Signum: '<S73>/Sign1'
      if (std::isnan(Formation_FMS_B.t)) {
        Formation_FMS_B.rtb_vn_idx_1 = (rtNaNF);
      } else if (Formation_FMS_B.t < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -1.0F;
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = (Formation_FMS_B.t > 0.0F);
      }

      // End of Signum: '<S73>/Sign1'

      // Trigonometry: '<S73>/Acos' incorporates:
      //   DotProduct: '<S73>/Dot Product'

      if (Formation_FMS_B.scale > 1.0F) {
        Formation_FMS_B.scale = 1.0F;
      } else if (Formation_FMS_B.scale < -1.0F) {
        Formation_FMS_B.scale = -1.0F;
      }

      // Switch: '<S73>/Switch2' incorporates:
      //   Constant: '<S73>/Constant4'

      if (!(Formation_FMS_B.rtb_vn_idx_1 != 0.0F)) {
        Formation_FMS_B.rtb_vn_idx_1 = 1.0F;
      }

      // Product: '<S73>/Multiply' incorporates:
      //   Switch: '<S73>/Switch2'
      //   Trigonometry: '<S73>/Acos'

      Formation_FMS_B.Multiply1_f = std::acos(Formation_FMS_B.scale) *
        Formation_FMS_B.rtb_vn_idx_1;

      // Sum: '<S63>/Sum' incorporates:
      //   Constant: '<S63>/Constant'

      Formation_FMS_B.rtb_vn_idx_1 = FMS_PARAM.FW_AIRSPD_TRIM -
        *rtu_INS_Out_airspeed;

      // Delay: '<S64>/Delay' incorporates:
      //   Constant: '<S64>/Constant'

      if (Formation_FMS_DW.icLoad_p) {
        Formation_FMS_DW.Delay_DSTATE_a = FMS_PARAM.FW_HEIGHT_TRIM;
      }

      // Sum: '<S64>/Sum' incorporates:
      //   Delay: '<S64>/Delay'

      Formation_FMS_B.scale = Formation_FMS_DW.Delay_DSTATE_a - *rtu_INS_Out_h_R;

      // End of Outputs for SubSystem: '<S12>/FormHold'
      std::memset(&Formation_FMS_B.Merge, 0, sizeof(FMS_Out_Bus));

      // Outputs for IfAction SubSystem: '<S12>/FormHold' incorporates:
      //   ActionPort: '<S19>/Action Port'

      // BusAssignment: '<S19>/Bus Assignment' incorporates:
      //   Constant: '<S19>/Constant1'
      //   Merge: '<S10>/Merge'

      Formation_FMS_B.Merge.state = VehicleState::FormHold;
      Formation_FMS_B.Merge.ax_cmd = Formation_FMS_B.rtb_vn_idx_1;

      // Saturate: '<S72>/Saturation'
      if (Formation_FMS_B.Multiply1_f > 1.57079637F) {
        Formation_FMS_B.Multiply1_f = 1.57079637F;
      } else if (Formation_FMS_B.Multiply1_f < -1.57079637F) {
        Formation_FMS_B.Multiply1_f = -1.57079637F;
      }

      // BusAssignment: '<S19>/Bus Assignment' incorporates:
      //   Constant: '<S65>/L1'
      //   Gain: '<S72>/Gain'
      //   Product: '<S72>/Divide'
      //   Product: '<S72>/Multiply1'
      //   Saturate: '<S72>/Saturation'
      //   Trigonometry: '<S72>/Sin'

      Formation_FMS_B.Merge.ay_cmd = 2.0F * Formation_FMS_B.absxk * std::sin
        (Formation_FMS_B.Multiply1_f) / FMS_PARAM.L1;

      // Gain: '<S64>/Gain2'
      Formation_FMS_B.Multiply1_f = FMS_PARAM.Z_P * Formation_FMS_B.scale;

      // Saturate: '<S64>/Saturation'
      if (Formation_FMS_B.Multiply1_f > CONTROL_PARAM.FW_T_CLMB_MAX) {
        // BusAssignment: '<S19>/Bus Assignment'
        Formation_FMS_B.Merge.vh_cmd = CONTROL_PARAM.FW_T_CLMB_MAX;
      } else if (Formation_FMS_B.Multiply1_f < -CONTROL_PARAM.FW_T_SINK_MAX) {
        // BusAssignment: '<S19>/Bus Assignment'
        Formation_FMS_B.Merge.vh_cmd = -CONTROL_PARAM.FW_T_SINK_MAX;
      } else {
        // BusAssignment: '<S19>/Bus Assignment'
        Formation_FMS_B.Merge.vh_cmd = Formation_FMS_B.Multiply1_f;
      }

      // End of Saturate: '<S64>/Saturation'

      // Update for Delay: '<S68>/start_vel'
      Formation_FMS_DW.icLoad_l3 = false;

      // Update for Delay: '<S64>/Delay'
      Formation_FMS_DW.icLoad_p = false;

      // End of Outputs for SubSystem: '<S12>/FormHold'
      break;

     case 2:
      // Outputs for IfAction SubSystem: '<S12>/FormMission' incorporates:
      //   ActionPort: '<S20>/Action Port'

      // RelationalOperator: '<S81>/FixPt Relational Operator' incorporates:
      //   UnitDelay: '<S81>/Delay Input1'
      //
      //  Block description for '<S81>/Delay Input1':
      //
      //   Store in Global RAM

      rtb_FixPtRelationalOperator_c = (Formation_FMS_B.wp_index !=
        Formation_FMS_DW.DelayInput1_DSTATE_d);

      // Outputs for Resettable SubSystem: '<S20>/FormMission_SubSystem' incorporates:
      //   ResetPort: '<S82>/Reset'

      if (rtb_FixPtRelationalOperator_c &&
          (Formation_FMS_PrevZCX.FormMission_SubSystem_Reset_ZCE != POS_ZCSIG))
      {
        // InitializeConditions for Delay: '<S159>/Delay'
        Formation_FMS_DW.icLoad_k = true;

        // InitializeConditions for DiscreteIntegrator: '<S97>/Discrete-Time Integrator1' 
        Formation_FMS_DW.DiscreteTimeIntegrator1_PrevRes = 0;
        Formation_FMS_DW.DiscreteTimeIntegrator1_IC_LOAD = 1U;

        // InitializeConditions for DiscreteIntegrator: '<S141>/Integrator'
        Formation_FMS_DW.Integrator_DSTATE = 0.0F;
      }

      Formation_FMS_PrevZCX.FormMission_SubSystem_Reset_ZCE =
        rtb_FixPtRelationalOperator_c;

      // SignalConversion generated from: '<S84>/Vector Concatenate'
      Formation_FMS_B.xyz_O_nx3[0] = Formation_FMS_B.rtb_x_R_idx_0;

      // SignalConversion generated from: '<S84>/Vector Concatenate'
      Formation_FMS_B.xyz_O_nx3[3] = Formation_FMS_B.scale;

      // SignalConversion generated from: '<S84>/Vector Concatenate'
      Formation_FMS_B.xyz_O_nx3[6] = Formation_FMS_B.absxk;

      // SignalConversion generated from: '<S84>/Vector Concatenate1'
      Formation_FMS_B.vNED_O_nx3[0] = Formation_FMS_B.rtb_vn_idx_0;

      // SignalConversion generated from: '<S84>/Vector Concatenate1'
      Formation_FMS_B.vNED_O_nx3[3] = Formation_FMS_B.ve[0];

      // SignalConversion generated from: '<S84>/Vector Concatenate1'
      Formation_FMS_B.vNED_O_nx3[6] = Formation_FMS_B.vd[0];
      Formation_FMS_B.ve[0] = 0.0F;
      Formation_FMS_B.vd[0] = 0.0F;

      // SignalConversion generated from: '<S84>/Vector Concatenate' incorporates:
      //   MATLAB Function: '<S86>/Calc_Position_Velocity_Setpoint'

      Formation_FMS_B.xyz_O_nx3[1] = Formation_FMS_B.rtb_x_R_idx_1;

      // SignalConversion generated from: '<S84>/Vector Concatenate'
      Formation_FMS_B.xyz_O_nx3[4] = Formation_FMS_B.rtb_y_R_idx_1;

      // SignalConversion generated from: '<S84>/Vector Concatenate'
      Formation_FMS_B.xyz_O_nx3[7] = Formation_FMS_B.t;

      // SignalConversion generated from: '<S84>/Vector Concatenate1'
      Formation_FMS_B.vNED_O_nx3[1] = Formation_FMS_B.rtb_vn_idx_1;

      // SignalConversion generated from: '<S84>/Vector Concatenate1'
      Formation_FMS_B.vNED_O_nx3[4] = Formation_FMS_B.ve[1];

      // SignalConversion generated from: '<S84>/Vector Concatenate1'
      Formation_FMS_B.vNED_O_nx3[7] = Formation_FMS_B.vd[1];
      Formation_FMS_B.ve[1] = 0.0F;
      Formation_FMS_B.vd[1] = 0.0F;

      // SignalConversion generated from: '<S84>/Vector Concatenate' incorporates:
      //   MATLAB Function: '<S86>/Calc_Position_Velocity_Setpoint'

      Formation_FMS_B.xyz_O_nx3[2] = Formation_FMS_B.rtb_x_R_idx_2;

      // SignalConversion generated from: '<S84>/Vector Concatenate'
      Formation_FMS_B.xyz_O_nx3[5] = Formation_FMS_B.rtb_y_R_idx_2;

      // SignalConversion generated from: '<S84>/Vector Concatenate'
      Formation_FMS_B.xyz_O_nx3[8] = Formation_FMS_B.Multiply1_f;

      // SignalConversion generated from: '<S84>/Vector Concatenate1'
      Formation_FMS_B.vNED_O_nx3[2] = Formation_FMS_B.rtb_vn_idx_2;

      // SignalConversion generated from: '<S84>/Vector Concatenate1'
      Formation_FMS_B.vNED_O_nx3[5] = Formation_FMS_B.ve[2];

      // SignalConversion generated from: '<S84>/Vector Concatenate1'
      Formation_FMS_B.vNED_O_nx3[8] = Formation_FMS_B.vd[2];
      Formation_FMS_B.ve[2] = 0.0F;
      Formation_FMS_B.vd[2] = 0.0F;

      // MATLAB Function: '<S86>/Calc_Position_Velocity_Setpoint' incorporates:
      //   Concatenate: '<S84>/Vector Concatenate'
      //   Concatenate: '<S84>/Vector Concatenate1'

      Formation_FMS_B.scale = 0.0F;
      for (Formation_FMS_B.i = 0; Formation_FMS_B.i < 3; Formation_FMS_B.i++) {
        if (static_cast<uint32_T>(Formation_FMS_B.i + 1) !=
            FORMATION_PARAM.UAV_ID) {
          Formation_FMS_B.idx = (3 * Formation_FMS_B.i + static_cast<int32_T>
            (FORMATION_PARAM.UAV_ID)) - 1;
          Formation_FMS_B.n_j = FORMATION_PARAM.ADJ_MARTIX[Formation_FMS_B.idx];
          if (!(Formation_FMS_B.n_j == 0.0)) {
            Formation_FMS_B.t = rt_atan2f_snf
              (Formation_FMS_B.vNED_O_nx3[Formation_FMS_B.i + 3],
               Formation_FMS_B.vNED_O_nx3[Formation_FMS_B.i]);
            Formation_FMS_B.absxk = std::sin(Formation_FMS_B.t);
            Formation_FMS_B.t = std::cos(Formation_FMS_B.t);
            Formation_FMS_B.rtb_pos_err_tmp[0] = Formation_FMS_B.t;
            Formation_FMS_B.rtb_pos_err_tmp[3] = -Formation_FMS_B.absxk;
            Formation_FMS_B.rtb_pos_err_tmp[6] = 0.0F;
            Formation_FMS_B.rtb_pos_err_tmp[1] = Formation_FMS_B.absxk;
            Formation_FMS_B.rtb_pos_err_tmp[4] = Formation_FMS_B.t;
            Formation_FMS_B.rtb_pos_err_tmp[7] = 0.0F;
            Formation_FMS_B.rtb_pos_err_tmp[2] = 0.0F;
            Formation_FMS_B.rtb_pos_err_tmp[5] = 0.0F;
            Formation_FMS_B.rtb_pos_err_tmp[8] = 1.0F;
            Formation_FMS_B.absxk = static_cast<real32_T>
              (FORMATION_PARAM.REL_X_MATRIX[Formation_FMS_B.idx]);
            Formation_FMS_B.t = static_cast<real32_T>
              (FORMATION_PARAM.REL_Y_MATRIX[Formation_FMS_B.idx]);
            Formation_FMS_B.rtb_vn_idx_1 = static_cast<real32_T>
              (FORMATION_PARAM.REL_Z_MATRIX[Formation_FMS_B.idx]);
            for (Formation_FMS_B.idx = 0; Formation_FMS_B.idx < 3;
                 Formation_FMS_B.idx++) {
              Formation_FMS_B.rtb_vd_tmp = 3 * Formation_FMS_B.idx +
                Formation_FMS_B.i;
              Formation_FMS_B.vd[Formation_FMS_B.idx] +=
                (((Formation_FMS_B.rtb_pos_err_tmp[Formation_FMS_B.idx + 3] *
                   Formation_FMS_B.t +
                   Formation_FMS_B.rtb_pos_err_tmp[Formation_FMS_B.idx] *
                   Formation_FMS_B.absxk) +
                  Formation_FMS_B.rtb_pos_err_tmp[Formation_FMS_B.idx + 6] *
                  Formation_FMS_B.rtb_vn_idx_1) +
                 Formation_FMS_B.xyz_O_nx3[Formation_FMS_B.rtb_vd_tmp]) *
                static_cast<real32_T>(Formation_FMS_B.n_j);
              Formation_FMS_B.ve[Formation_FMS_B.idx] +=
                Formation_FMS_B.vNED_O_nx3[Formation_FMS_B.rtb_vd_tmp] *
                static_cast<real32_T>(Formation_FMS_B.n_j);
            }

            Formation_FMS_B.scale++;
          }
        }
      }

      if (Formation_FMS_B.scale != 0.0F) {
        Formation_FMS_B.vd[0] = Formation_FMS_B.vd[0] / Formation_FMS_B.scale -
          Formation_FMS_B.xyz_O_nx3[static_cast<int32_T>(FORMATION_PARAM.UAV_ID)
          - 1];
        Formation_FMS_B.ve[0] /= Formation_FMS_B.scale;
        Formation_FMS_B.vd[1] = Formation_FMS_B.vd[1] / Formation_FMS_B.scale -
          Formation_FMS_B.xyz_O_nx3[static_cast<int32_T>(FORMATION_PARAM.UAV_ID)
          + 2];
        Formation_FMS_B.ve[1] /= Formation_FMS_B.scale;
        Formation_FMS_B.vd[2] = Formation_FMS_B.vd[2] / Formation_FMS_B.scale -
          Formation_FMS_B.xyz_O_nx3[static_cast<int32_T>(FORMATION_PARAM.UAV_ID)
          + 5];
      } else {
        Formation_FMS_B.ve[0] = Formation_FMS_B.vNED_O_nx3[static_cast<int32_T>
          (FORMATION_PARAM.UAV_ID) - 1];
        Formation_FMS_B.ve[1] = Formation_FMS_B.vNED_O_nx3[static_cast<int32_T>
          (FORMATION_PARAM.UAV_ID) + 2];
      }

      // Sum: '<S96>/Sum of Elements' incorporates:
      //   Math: '<S96>/Math Function'
      //   Sum: '<S102>/Sum of Elements'
      //   Sum: '<S94>/Sum of Elements'
      //   Switch: '<S82>/Switch'

      Formation_FMS_B.scale = Formation_FMS_B.ve[0] * Formation_FMS_B.ve[0] +
        Formation_FMS_B.ve[1] * Formation_FMS_B.ve[1];

      // Math: '<S96>/Math Function1' incorporates:
      //   Sum: '<S96>/Sum of Elements'
      //
      //  About '<S96>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.Multiply1_f = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.Multiply1_f = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S96>/Math Function1'

      // Switch: '<S96>/Switch' incorporates:
      //   Constant: '<S96>/Constant'
      //   Product: '<S96>/Product'

      if (Formation_FMS_B.Multiply1_f > 0.0F) {
        Formation_FMS_B.rtb_vn_idx_0 = Formation_FMS_B.ve[0];
        Formation_FMS_B.rtb_vn_idx_1 = Formation_FMS_B.ve[1];
        Formation_FMS_B.rtb_vn_idx_2 = Formation_FMS_B.Multiply1_f;
      } else {
        Formation_FMS_B.rtb_vn_idx_0 = Formation_FMS_B.ve[0] * 0.0F;
        Formation_FMS_B.rtb_vn_idx_1 = Formation_FMS_B.ve[1] * 0.0F;
        Formation_FMS_B.rtb_vn_idx_2 = 1.0F;
      }

      // End of Switch: '<S96>/Switch'

      // Math: '<S102>/Math Function1'
      //
      //  About '<S102>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.Multiply1_f = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.Multiply1_f = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S102>/Math Function1'

      // Switch: '<S102>/Switch' incorporates:
      //   Constant: '<S102>/Constant'
      //   Product: '<S102>/Product'
      //   Switch: '<S82>/Switch'

      if (Formation_FMS_B.Multiply1_f > 0.0F) {
        Formation_FMS_B.absxk = Formation_FMS_B.ve[0];
        Formation_FMS_B.t = Formation_FMS_B.ve[1];
      } else {
        Formation_FMS_B.absxk = Formation_FMS_B.ve[0] * 0.0F;
        Formation_FMS_B.t = Formation_FMS_B.ve[1] * 0.0F;
        Formation_FMS_B.Multiply1_f = 1.0F;
      }

      // End of Switch: '<S102>/Switch'

      // SignalConversion generated from: '<S95>/Square'
      Formation_FMS_B.Reshape2_bq[0] = *rtu_INS_Out_vn;
      Formation_FMS_B.Reshape2_bq[1] = *rtu_INS_Out_ve;

      // Reshape: '<S165>/Reshape2'
      Formation_FMS_B.P_i[0] = *rtu_INS_Out_x_R;
      Formation_FMS_B.P_i[1] = *rtu_INS_Out_y_R;

      // MATLAB Function: '<S166>/NearbyRefWP' incorporates:
      //   Constant: '<S164>/L1'

      Formation_FMS_NearbyRefWP(&Formation_FMS_B.Cmd_In.sp_waypoint[0],
        Formation_FMS_B.P_i, FMS_PARAM.L1,
        Formation_FMS_B.TmpSignalConversionAtSqua_c,
        &Formation_FMS_B.rtb_x_R_idx_0);

      // MATLAB Function: '<S166>/SearchL1RefWP' incorporates:
      //   Constant: '<S164>/L1'

      Formation_FMS_SearchL1RefWP(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
        &Formation_FMS_B.Cmd_In.sp_waypoint[0], Formation_FMS_B.P_i,
        FMS_PARAM.L1, Formation_FMS_B.P, &Formation_FMS_B.rtb_y_R_idx_1);

      // MATLAB Function: '<S166>/OutRegionRegWP'
      Formation_FMS_OutRegionRegWP(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
        &Formation_FMS_B.Cmd_In.sp_waypoint[0], Formation_FMS_B.P_i,
        Formation_FMS_B.P_b);

      // MATLAB Function: '<S160>/min_radius'
      if (!std::isnan(FORMATION_PARAM.REL_Y_MATRIX[0])) {
        Formation_FMS_B.idx = 1;
      } else {
        Formation_FMS_B.idx = 0;
        Formation_FMS_B.i = 2;
        exitg1 = false;
        while ((!exitg1) && (Formation_FMS_B.i < 4)) {
          if (!std::isnan(FORMATION_PARAM.REL_Y_MATRIX[(Formation_FMS_B.i - 1) *
                          3])) {
            Formation_FMS_B.idx = Formation_FMS_B.i;
            exitg1 = true;
          } else {
            Formation_FMS_B.i++;
          }
        }
      }

      if (Formation_FMS_B.idx == 0) {
        Formation_FMS_B.ex = FORMATION_PARAM.REL_Y_MATRIX[0];
      } else {
        Formation_FMS_B.ex = FORMATION_PARAM.REL_Y_MATRIX[(Formation_FMS_B.idx -
          1) * 3];
        for (Formation_FMS_B.i = Formation_FMS_B.idx + 1; Formation_FMS_B.i < 4;
             Formation_FMS_B.i++) {
          Formation_FMS_B.n_j = FORMATION_PARAM.REL_Y_MATRIX[(Formation_FMS_B.i
            - 1) * 3];
          if (Formation_FMS_B.ex < Formation_FMS_B.n_j) {
            Formation_FMS_B.ex = Formation_FMS_B.n_j;
          }
        }
      }

      // Delay: '<S159>/Delay' incorporates:
      //   Constant: '<S159>/Constant'

      if (Formation_FMS_DW.icLoad_k) {
        Formation_FMS_DW.Delay_DSTATE_o = FMS_PARAM.FW_HEIGHT_TRIM;
      }

      // Product: '<S96>/Divide'
      Formation_FMS_B.rtb_x_R_idx_1 = Formation_FMS_B.rtb_vn_idx_0 /
        Formation_FMS_B.rtb_vn_idx_2;

      // DotProduct: '<S90>/Dot Product'
      Formation_FMS_B.rtb_y_R_idx_2 = Formation_FMS_B.vd[0] *
        Formation_FMS_B.rtb_x_R_idx_1;
      Formation_FMS_B.rtb_vn_idx_0 = Formation_FMS_B.rtb_x_R_idx_1;

      // Product: '<S96>/Divide' incorporates:
      //   Product: '<S102>/Divide'

      Formation_FMS_B.rtb_x_R_idx_1 = Formation_FMS_B.rtb_vn_idx_1 /
        Formation_FMS_B.rtb_vn_idx_2;

      // Sum: '<S90>/Add' incorporates:
      //   Abs: '<S90>/Abs'
      //   DotProduct: '<S90>/Dot Product'
      //   Product: '<S92>/Multiply'
      //   Product: '<S92>/Multiply1'
      //   Sum: '<S92>/Subtract'

      Formation_FMS_B.rtb_vn_idx_2 = std::abs(Formation_FMS_B.vd[0] *
        Formation_FMS_B.rtb_x_R_idx_1 - Formation_FMS_B.rtb_vn_idx_0 *
        Formation_FMS_B.vd[1]) + (Formation_FMS_B.vd[1] *
        Formation_FMS_B.rtb_x_R_idx_1 + Formation_FMS_B.rtb_y_R_idx_2);

      // Gain: '<S93>/Pos_D'
      Formation_FMS_B.rtb_vn_idx_1 = FORMATION_PARAM.FORM_POS_KD *
        Formation_FMS_B.rtb_vn_idx_2;

      // DiscreteIntegrator: '<S97>/Discrete-Time Integrator1'
      if (Formation_FMS_DW.DiscreteTimeIntegrator1_IC_LOAD != 0) {
        Formation_FMS_DW.DiscreteTimeIntegrator1_DSTATE =
          Formation_FMS_B.rtb_vn_idx_1;
      }

      if (Formation_FMS_DW.DiscreteTimeIntegrator1_PrevRes != 0) {
        Formation_FMS_DW.DiscreteTimeIntegrator1_DSTATE =
          Formation_FMS_B.rtb_vn_idx_1;
      }

      // Gain: '<S97>/Gain' incorporates:
      //   DiscreteIntegrator: '<S97>/Discrete-Time Integrator1'
      //   Sum: '<S97>/Sum5'

      Formation_FMS_B.rtb_vn_idx_1 = (Formation_FMS_B.rtb_vn_idx_1 -
        Formation_FMS_DW.DiscreteTimeIntegrator1_DSTATE) * 62.831852F;

      // Product: '<S102>/Divide'
      Formation_FMS_B.rtb_vn_idx_0 = Formation_FMS_B.absxk /
        Formation_FMS_B.Multiply1_f;

      // Math: '<S100>/Square' incorporates:
      //   Math: '<S107>/Square'
      //   Math: '<S175>/Square'
      //   Math: '<S176>/Math Function'
      //   Math: '<S95>/Square'
      //   Switch: '<S101>/Switch'
      //   Switch: '<S82>/Switch'

      Formation_FMS_B.absxk = Formation_FMS_B.Reshape2_bq[0] *
        Formation_FMS_B.Reshape2_bq[0];

      // Product: '<S102>/Divide'
      Formation_FMS_B.rtb_y_R_idx_2 = Formation_FMS_B.t /
        Formation_FMS_B.Multiply1_f;

      // Math: '<S100>/Square' incorporates:
      //   Math: '<S107>/Square'
      //   Math: '<S175>/Square'
      //   Math: '<S176>/Math Function'
      //   Math: '<S95>/Square'
      //   Switch: '<S101>/Switch'
      //   Switch: '<S82>/Switch'

      Formation_FMS_B.t = Formation_FMS_B.Reshape2_bq[1] *
        Formation_FMS_B.Reshape2_bq[1];

      // Sum: '<S98>/Subtract' incorporates:
      //   Product: '<S98>/Multiply'
      //   Product: '<S98>/Multiply1'

      Formation_FMS_B.Subtract_b = Formation_FMS_B.vd[0] *
        Formation_FMS_B.rtb_y_R_idx_2 - Formation_FMS_B.rtb_vn_idx_0 *
        Formation_FMS_B.vd[1];

      // Sum: '<S100>/Sum of Elements' incorporates:
      //   Math: '<S100>/Square'
      //   Sum: '<S107>/Sum of Elements'
      //   Sum: '<S176>/Sum of Elements'
      //   Switch: '<S101>/Switch'
      //   Switch: '<S82>/Switch'

      Formation_FMS_B.rtb_x_R_idx_1 = Formation_FMS_B.absxk + Formation_FMS_B.t;

      // Product: '<S100>/Divide' incorporates:
      //   Abs: '<S100>/Abs'
      //   Bias: '<S100>/Bias'
      //   Constant: '<S100>/Ts//2'
      //   Product: '<S100>/Product'
      //   Sum: '<S100>/Sum of Elements'

      Formation_FMS_B.Multiply1_f = std::abs(Formation_FMS_B.Subtract_b) /
        (FORMATION_PARAM.LATERAL_DAMP * FORMATION_PARAM.LATERAL_PERIOD * 0.5F *
         (Formation_FMS_B.rtb_x_R_idx_1 + 1.0F));

      // Saturate: '<S100>/normalized_track_error'
      if (Formation_FMS_B.Multiply1_f > 1.0F) {
        Formation_FMS_B.Multiply1_f = 1.0F;
      } else if (Formation_FMS_B.Multiply1_f < 0.0F) {
        Formation_FMS_B.Multiply1_f = 0.0F;
      }

      // End of Saturate: '<S100>/normalized_track_error'

      // Gain: '<S104>/Gain1' incorporates:
      //   Bias: '<S104>/Bias1'
      //   Math: '<S104>/Square1'

      Formation_FMS_B.rtb_x_R_idx_2 = (Formation_FMS_B.Multiply1_f - 1.0F) *
        (Formation_FMS_B.Multiply1_f - 1.0F) * 1.57079637F;

      // Trigonometry: '<S99>/Sin'
      Formation_FMS_B.Sin = std::sin(Formation_FMS_B.rtb_x_R_idx_2);

      // Trigonometry: '<S99>/Cos'
      Formation_FMS_B.rtb_x_R_idx_2 = std::cos(Formation_FMS_B.rtb_x_R_idx_2);

      // MATLAB Function: '<S99>/signNoZero'
      Formation_FMS_signNoZero(Formation_FMS_B.Subtract_b,
        &Formation_FMS_B.Multiply1_f);

      // Sum: '<S99>/Add' incorporates:
      //   Gain: '<S99>/Gain'
      //   Gain: '<S99>/Gain1'
      //   Product: '<S102>/Divide'
      //   Product: '<S99>/Product'
      //   Product: '<S99>/Product1'
      //   Product: '<S99>/unit_track_error'

      Formation_FMS_B.Subtract_b = -Formation_FMS_B.rtb_y_R_idx_2 *
        -Formation_FMS_B.Multiply1_f * Formation_FMS_B.rtb_x_R_idx_2 +
        Formation_FMS_B.rtb_vn_idx_0 * Formation_FMS_B.Sin;
      Formation_FMS_B.rtb_vn_idx_0 = Formation_FMS_B.rtb_vn_idx_0 *
        -Formation_FMS_B.Multiply1_f * Formation_FMS_B.rtb_x_R_idx_2 +
        Formation_FMS_B.rtb_y_R_idx_2 * Formation_FMS_B.Sin;

      // Product: '<S105>/Multiply'
      Formation_FMS_B.rtb_x_R_idx_2 = *rtu_INS_Out_vn *
        Formation_FMS_B.rtb_vn_idx_0;

      // Product: '<S105>/Multiply1'
      Formation_FMS_B.Multiply1_f = *rtu_INS_Out_ve * Formation_FMS_B.Subtract_b;

      // Sum: '<S105>/Subtract'
      Formation_FMS_B.Multiply1_f = Formation_FMS_B.rtb_x_R_idx_2 -
        Formation_FMS_B.Multiply1_f;

      // MATLAB Function: '<S101>/signNoZero'
      Formation_FMS_signNoZero(Formation_FMS_B.Multiply1_f,
        &Formation_FMS_B.rtb_x_R_idx_2);

      // Switch: '<S82>/Switch' incorporates:
      //   Constant: '<S82>/Constant2'
      //   Constant: '<S83>/Constant'
      //   DiscreteIntegrator: '<S141>/Integrator'
      //   DotProduct: '<S101>/Dot Product'
      //   Gain: '<S101>/Gain'
      //   Gain: '<S146>/Proportional Gain'
      //   Gain: '<S158>/Gain'
      //   Product: '<S179>/Divide'
      //   RelationalOperator: '<S83>/Compare'
      //   Sum: '<S150>/Sum'
      //   Sum: '<S99>/Add'
      //   Switch: '<S101>/Switch'

      if (FORMATION_PARAM.UAV_ID == 1U) {
        // Switch: '<S166>/Switch1' incorporates:
        //   Constant: '<S169>/Constant'
        //   RelationalOperator: '<S169>/Compare'

        if (!(Formation_FMS_B.rtb_x_R_idx_0 > 0.0F)) {
          // Switch: '<S166>/Switch' incorporates:
          //   Constant: '<S168>/Constant'
          //   RelationalOperator: '<S168>/Compare'
          //   Switch: '<S166>/Switch1'

          if (Formation_FMS_B.rtb_y_R_idx_1 >= 0.0F) {
            Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.P[0];
            Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.P[1];
          } else {
            Formation_FMS_B.TmpSignalConversionAtSqua_c[0] =
              Formation_FMS_B.P_b[0];
            Formation_FMS_B.TmpSignalConversionAtSqua_c[1] =
              Formation_FMS_B.P_b[1];
          }

          // End of Switch: '<S166>/Switch'
        }

        // End of Switch: '<S166>/Switch1'

        // Sum: '<S167>/Subtract' incorporates:
        //   Reshape: '<S165>/Reshape2'
        //   Switch: '<S166>/Switch1'

        Formation_FMS_B.Multiply1_f =
          Formation_FMS_B.TmpSignalConversionAtSqua_c[0] - Formation_FMS_B.P_i[0];
        Formation_FMS_B.rtb_x_R_idx_0 =
          Formation_FMS_B.TmpSignalConversionAtSqua_c[1] - Formation_FMS_B.P_i[1];

        // Math: '<S176>/Math Function1'
        //
        //  About '<S176>/Math Function1':
        //   Operator: sqrt

        if (Formation_FMS_B.rtb_x_R_idx_1 < 0.0F) {
          Formation_FMS_B.scale = -std::sqrt(std::abs
            (Formation_FMS_B.rtb_x_R_idx_1));
        } else {
          Formation_FMS_B.scale = std::sqrt(Formation_FMS_B.rtb_x_R_idx_1);
        }

        // End of Math: '<S176>/Math Function1'

        // Switch: '<S176>/Switch' incorporates:
        //   Constant: '<S176>/Constant'
        //   Product: '<S176>/Product'

        if (Formation_FMS_B.scale > 0.0F) {
          Formation_FMS_B.ve[0] = *rtu_INS_Out_vn;
          Formation_FMS_B.ve[1] = *rtu_INS_Out_ve;
          Formation_FMS_B.ve[2] = Formation_FMS_B.scale;
        } else {
          Formation_FMS_B.ve[0] = Formation_FMS_B.Reshape2_bq[0] * 0.0F;
          Formation_FMS_B.ve[1] = Formation_FMS_B.Reshape2_bq[1] * 0.0F;
          Formation_FMS_B.ve[2] = 1.0F;
        }

        // End of Switch: '<S176>/Switch'

        // Product: '<S176>/Divide'
        Formation_FMS_B.P_d[0] = Formation_FMS_B.ve[0] / Formation_FMS_B.ve[2];
        Formation_FMS_B.P_d[1] = Formation_FMS_B.ve[1] / Formation_FMS_B.ve[2];

        // Sum: '<S177>/Sum of Elements' incorporates:
        //   Math: '<S177>/Math Function'

        Formation_FMS_B.scale = Formation_FMS_B.Multiply1_f *
          Formation_FMS_B.Multiply1_f + Formation_FMS_B.rtb_x_R_idx_0 *
          Formation_FMS_B.rtb_x_R_idx_0;

        // Math: '<S177>/Math Function1' incorporates:
        //   Sum: '<S177>/Sum of Elements'
        //
        //  About '<S177>/Math Function1':
        //   Operator: sqrt

        if (Formation_FMS_B.scale < 0.0F) {
          Formation_FMS_B.scale = -std::sqrt(std::abs(Formation_FMS_B.scale));
        } else {
          Formation_FMS_B.scale = std::sqrt(Formation_FMS_B.scale);
        }

        // End of Math: '<S177>/Math Function1'

        // Switch: '<S177>/Switch' incorporates:
        //   Constant: '<S177>/Constant'
        //   Product: '<S177>/Product'
        //   Sum: '<S167>/Subtract'
        //   Switch: '<S179>/Switch'

        if (Formation_FMS_B.scale > 0.0F) {
          Formation_FMS_B.ve[0] = Formation_FMS_B.Multiply1_f;
          Formation_FMS_B.ve[1] = Formation_FMS_B.rtb_x_R_idx_0;
          Formation_FMS_B.ve[2] = Formation_FMS_B.scale;
        } else {
          Formation_FMS_B.ve[0] = Formation_FMS_B.Multiply1_f * 0.0F;
          Formation_FMS_B.ve[1] = Formation_FMS_B.rtb_x_R_idx_0 * 0.0F;
          Formation_FMS_B.ve[2] = 1.0F;
        }

        // End of Switch: '<S177>/Switch'

        // Sum: '<S158>/Sum' incorporates:
        //   Constant: '<S158>/Constant'

        Formation_FMS_B.rtb_x_R_idx_0 = FMS_PARAM.FW_AIRSPD_TRIM -
          *rtu_INS_Out_airspeed;

        // Product: '<S160>/Divide' incorporates:
        //   Constant: '<S160>/v^2'
        //   Gain: '<S160>/Satefy'
        //   MATLAB Function: '<S160>/min_radius'

        Formation_FMS_B.rtb_y_R_idx_1 = CONTROL_PARAM.FW_AIRSPD_TRIM *
          CONTROL_PARAM.FW_AIRSPD_TRIM / (static_cast<real32_T>
          (Formation_FMS_B.ex) * CONTROL_PARAM.FW_AIRSPD_TRIM / std::fmin
          (CONTROL_PARAM.FW_AIRSPD_MAX - CONTROL_PARAM.FW_AIRSPD_TRIM,
           CONTROL_PARAM.FW_AIRSPD_TRIM - CONTROL_PARAM.FW_AIRSPD_MIN) *
          FMS_PARAM.FW_RADIUS_RATIO);

        // Product: '<S177>/Divide' incorporates:
        //   Product: '<S180>/Divide'

        Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.ve[0] /
          Formation_FMS_B.ve[2];
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.ve[1] /
          Formation_FMS_B.ve[2];

        // Sqrt: '<S175>/Sqrt' incorporates:
        //   Math: '<S175>/Square'
        //   Sum: '<S175>/Sum of Elements'

        Formation_FMS_B.scale = std::sqrt(Formation_FMS_B.absxk +
          Formation_FMS_B.t);

        // Math: '<S173>/Square'
        Formation_FMS_B.absxk = Formation_FMS_B.scale * Formation_FMS_B.scale;

        // Sum: '<S180>/Sum of Elements' incorporates:
        //   Math: '<S180>/Math Function'
        //   SignalConversion generated from: '<S180>/Math Function'

        Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
          Formation_FMS_B.TmpSignalConversionAtSqua_c[1] +
          Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
          Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

        // Math: '<S180>/Math Function1' incorporates:
        //   Sum: '<S180>/Sum of Elements'
        //
        //  About '<S180>/Math Function1':
        //   Operator: sqrt

        if (Formation_FMS_B.scale < 0.0F) {
          Formation_FMS_B.scale = -std::sqrt(std::abs(Formation_FMS_B.scale));
        } else {
          Formation_FMS_B.scale = std::sqrt(Formation_FMS_B.scale);
        }

        // End of Math: '<S180>/Math Function1'

        // Switch: '<S180>/Switch' incorporates:
        //   Constant: '<S180>/Constant'
        //   Product: '<S180>/Product'
        //   SignalConversion generated from: '<S180>/Math Function'

        if (Formation_FMS_B.scale > 0.0F) {
          Formation_FMS_B.ve[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
          Formation_FMS_B.ve[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
          Formation_FMS_B.ve[2] = Formation_FMS_B.scale;
        } else {
          Formation_FMS_B.ve[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1]
            * 0.0F;
          Formation_FMS_B.ve[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0]
            * 0.0F;
          Formation_FMS_B.ve[2] = 1.0F;
        }

        // End of Switch: '<S180>/Switch'

        // Product: '<S180>/Divide'
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.ve[0] /
          Formation_FMS_B.ve[2];
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.ve[1] /
          Formation_FMS_B.ve[2];

        // Sum: '<S179>/Sum of Elements' incorporates:
        //   Math: '<S179>/Math Function'
        //   SignalConversion generated from: '<S179>/Math Function'

        Formation_FMS_B.scale = Formation_FMS_B.P_d[1] * Formation_FMS_B.P_d[1]
          + Formation_FMS_B.P_d[0] * Formation_FMS_B.P_d[0];

        // Math: '<S179>/Math Function1' incorporates:
        //   Sum: '<S179>/Sum of Elements'
        //
        //  About '<S179>/Math Function1':
        //   Operator: sqrt

        if (Formation_FMS_B.scale < 0.0F) {
          Formation_FMS_B.scale = -std::sqrt(std::abs(Formation_FMS_B.scale));
        } else {
          Formation_FMS_B.scale = std::sqrt(Formation_FMS_B.scale);
        }

        // End of Math: '<S179>/Math Function1'

        // Switch: '<S179>/Switch' incorporates:
        //   Constant: '<S179>/Constant'
        //   Product: '<S179>/Product'
        //   SignalConversion generated from: '<S179>/Math Function'

        if (Formation_FMS_B.scale > 0.0F) {
          Formation_FMS_B.ve[0] = Formation_FMS_B.P_d[1];
          Formation_FMS_B.ve[1] = Formation_FMS_B.P_d[0];
          Formation_FMS_B.ve[2] = Formation_FMS_B.scale;
        } else {
          Formation_FMS_B.ve[0] = Formation_FMS_B.P_d[1] * 0.0F;
          Formation_FMS_B.ve[1] = Formation_FMS_B.P_d[0] * 0.0F;
          Formation_FMS_B.ve[2] = 1.0F;
        }

        // End of Switch: '<S179>/Switch'

        // Product: '<S179>/Divide'
        Formation_FMS_B.Multiply1_f = Formation_FMS_B.ve[0] /
          Formation_FMS_B.ve[2];

        // DotProduct: '<S174>/Dot Product'
        Formation_FMS_B.scale = Formation_FMS_B.Multiply1_f *
          Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
        Formation_FMS_B.P_d[0] = Formation_FMS_B.Multiply1_f;

        // Product: '<S179>/Divide'
        Formation_FMS_B.Multiply1_f = Formation_FMS_B.ve[1] /
          Formation_FMS_B.ve[2];

        // DotProduct: '<S174>/Dot Product'
        Formation_FMS_B.scale += Formation_FMS_B.Multiply1_f *
          Formation_FMS_B.TmpSignalConversionAtSqua_c[1];

        // Sum: '<S178>/Subtract' incorporates:
        //   Product: '<S178>/Multiply'
        //   Product: '<S178>/Multiply1'

        Formation_FMS_B.t = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
          Formation_FMS_B.Multiply1_f - Formation_FMS_B.P_d[0] *
          Formation_FMS_B.TmpSignalConversionAtSqua_c[1];

        // Signum: '<S174>/Sign1'
        if (std::isnan(Formation_FMS_B.t)) {
          Formation_FMS_B.t = (rtNaNF);
        } else if (Formation_FMS_B.t < 0.0F) {
          Formation_FMS_B.t = -1.0F;
        } else {
          Formation_FMS_B.t = (Formation_FMS_B.t > 0.0F);
        }

        // End of Signum: '<S174>/Sign1'

        // Trigonometry: '<S174>/Acos' incorporates:
        //   DotProduct: '<S174>/Dot Product'

        if (Formation_FMS_B.scale > 1.0F) {
          Formation_FMS_B.scale = 1.0F;
        } else if (Formation_FMS_B.scale < -1.0F) {
          Formation_FMS_B.scale = -1.0F;
        }

        // Switch: '<S174>/Switch2' incorporates:
        //   Constant: '<S174>/Constant4'

        if (!(Formation_FMS_B.t != 0.0F)) {
          Formation_FMS_B.t = 1.0F;
        }

        // Product: '<S174>/Multiply' incorporates:
        //   Switch: '<S174>/Switch2'
        //   Trigonometry: '<S174>/Acos'

        Formation_FMS_B.Multiply1_f = std::acos(Formation_FMS_B.scale) *
          Formation_FMS_B.t;

        // Saturate: '<S173>/Saturation'
        if (Formation_FMS_B.Multiply1_f > 1.57079637F) {
          Formation_FMS_B.Multiply1_f = 1.57079637F;
        } else if (Formation_FMS_B.Multiply1_f < -1.57079637F) {
          Formation_FMS_B.Multiply1_f = -1.57079637F;
        }

        // Product: '<S173>/Divide' incorporates:
        //   Constant: '<S164>/L1'
        //   Gain: '<S173>/Gain'
        //   Product: '<S173>/Multiply1'
        //   Saturate: '<S173>/Saturation'
        //   Trigonometry: '<S173>/Sin'

        Formation_FMS_B.t = 2.0F * Formation_FMS_B.absxk * std::sin
          (Formation_FMS_B.Multiply1_f) / FMS_PARAM.L1;

        // Saturate: '<S164>/Saturation1'
        if (Formation_FMS_B.t > FMS_PARAM.ACC_Y_LIM) {
          Formation_FMS_B.t = FMS_PARAM.ACC_Y_LIM;
        } else if (Formation_FMS_B.t < -FMS_PARAM.ACC_Y_LIM) {
          Formation_FMS_B.t = -FMS_PARAM.ACC_Y_LIM;
        }

        // End of Saturate: '<S164>/Saturation1'

        // Switch: '<S162>/Switch2' incorporates:
        //   Gain: '<S160>/Gain'
        //   RelationalOperator: '<S162>/LowerRelop1'
        //   RelationalOperator: '<S162>/UpperRelop'
        //   Switch: '<S162>/Switch'

        if (Formation_FMS_B.t > Formation_FMS_B.rtb_y_R_idx_1) {
          Formation_FMS_B.t = Formation_FMS_B.rtb_y_R_idx_1;
        } else if (Formation_FMS_B.t < -Formation_FMS_B.rtb_y_R_idx_1) {
          // Switch: '<S162>/Switch' incorporates:
          //   Gain: '<S160>/Gain'

          Formation_FMS_B.t = -Formation_FMS_B.rtb_y_R_idx_1;
        }

        // End of Switch: '<S162>/Switch2'

        // Sum: '<S159>/Sum' incorporates:
        //   Delay: '<S159>/Delay'

        Formation_FMS_B.scale = Formation_FMS_DW.Delay_DSTATE_o -
          *rtu_INS_Out_h_R;
        Formation_FMS_B.absxk = FMS_PARAM.AIRSPD_P *
          Formation_FMS_B.rtb_x_R_idx_0;

        // Gain: '<S159>/Gain2' incorporates:
        //   Gain: '<S158>/Gain'

        Formation_FMS_B.Multiply1_f = FMS_PARAM.Z_P * Formation_FMS_B.scale;

        // Saturate: '<S159>/Saturation'
        if (Formation_FMS_B.Multiply1_f > CONTROL_PARAM.FW_T_CLMB_MAX) {
          Formation_FMS_B.Multiply1_f = CONTROL_PARAM.FW_T_CLMB_MAX;
        } else if (Formation_FMS_B.Multiply1_f < -CONTROL_PARAM.FW_T_SINK_MAX) {
          Formation_FMS_B.Multiply1_f = -CONTROL_PARAM.FW_T_SINK_MAX;
        }

        // End of Saturate: '<S159>/Saturation'
      } else {
        if (Formation_FMS_B.Reshape2_bq[0] * Formation_FMS_B.Subtract_b +
            Formation_FMS_B.Reshape2_bq[1] * Formation_FMS_B.rtb_vn_idx_0 >=
            0.0F) {
          // Switch: '<S101>/Switch' incorporates:
          //   Math: '<S106>/Square'
          //   Product: '<S101>/Divide'
          //   Sqrt: '<S106>/Sqrt'
          //   Sum: '<S106>/Sum of Elements'
          //   Sum: '<S99>/Add'

          Formation_FMS_B.rtb_x_R_idx_0 = Formation_FMS_B.Multiply1_f / std::
            sqrt(Formation_FMS_B.Subtract_b * Formation_FMS_B.Subtract_b +
                 Formation_FMS_B.rtb_vn_idx_0 * Formation_FMS_B.rtb_vn_idx_0);
        } else {
          // Switch: '<S101>/Switch' incorporates:
          //   Product: '<S101>/Product'
          //   Sqrt: '<S107>/Sqrt'

          Formation_FMS_B.rtb_x_R_idx_0 = std::sqrt
            (Formation_FMS_B.rtb_x_R_idx_1) * Formation_FMS_B.rtb_x_R_idx_2;
        }

        // Sum: '<S93>/Add' incorporates:
        //   Gain: '<S93>/Pos_P'
        //   Switch: '<S97>/Switch'

        Formation_FMS_B.Multiply1_f = FORMATION_PARAM.FORM_POS_KP *
          Formation_FMS_B.rtb_vn_idx_2 + Formation_FMS_B.rtb_vn_idx_1;

        // Saturate: '<S93>/Saturation'
        Formation_FMS_B.rtb_y_R_idx_1 = CONTROL_PARAM.FW_AIRSPD_MIN -
          CONTROL_PARAM.FW_AIRSPD_TRIM;
        Formation_FMS_B.rtb_vn_idx_0 = CONTROL_PARAM.FW_AIRSPD_MAX -
          CONTROL_PARAM.FW_AIRSPD_TRIM;
        if (Formation_FMS_B.Multiply1_f > Formation_FMS_B.rtb_vn_idx_0) {
          Formation_FMS_B.Multiply1_f = Formation_FMS_B.rtb_vn_idx_0;
        } else if (Formation_FMS_B.Multiply1_f < Formation_FMS_B.rtb_y_R_idx_1)
        {
          Formation_FMS_B.Multiply1_f = Formation_FMS_B.rtb_y_R_idx_1;
        }

        // Gain: '<S90>/Vel_Kp' incorporates:
        //   Math: '<S95>/Square'
        //   Saturate: '<S93>/Saturation'
        //   Sqrt: '<S94>/Sqrt'
        //   Sqrt: '<S95>/Sqrt'
        //   Sum: '<S90>/Sum'
        //   Sum: '<S90>/Sum1'
        //   Sum: '<S95>/Sum of Elements'

        Formation_FMS_B.absxk = ((std::sqrt(Formation_FMS_B.scale) +
          Formation_FMS_B.Multiply1_f) - std::sqrt(Formation_FMS_B.absxk +
          Formation_FMS_B.t)) * FORMATION_PARAM.FORM_VEL_KP;

        // Saturate: '<S90>/Saturation1'
        if (Formation_FMS_B.absxk > 10.0F) {
          Formation_FMS_B.absxk = 10.0F;
        } else if (Formation_FMS_B.absxk < -10.0F) {
          Formation_FMS_B.absxk = -10.0F;
        }

        // End of Saturate: '<S90>/Saturation1'
        Formation_FMS_B.t = 12.566371F * FORMATION_PARAM.LATERAL_DAMP /
          FORMATION_PARAM.LATERAL_PERIOD * Formation_FMS_B.rtb_x_R_idx_0;
        Formation_FMS_B.Multiply1_f = 0.1F * Formation_FMS_B.vd[2] +
          Formation_FMS_DW.Integrator_DSTATE;
      }

      // End of Outputs for SubSystem: '<S20>/FormMission_SubSystem'
      // End of Outputs for SubSystem: '<S12>/FormMission'
      std::memset(&Formation_FMS_B.Merge, 0, sizeof(FMS_Out_Bus));

      // Outputs for IfAction SubSystem: '<S12>/FormMission' incorporates:
      //   ActionPort: '<S20>/Action Port'

      // Outputs for Resettable SubSystem: '<S20>/FormMission_SubSystem' incorporates:
      //   ResetPort: '<S82>/Reset'

      // BusAssignment: '<S82>/Bus Assignment' incorporates:
      //   Constant: '<S82>/Constant1'
      //   Merge: '<S10>/Merge'

      Formation_FMS_B.Merge.state = VehicleState::FormMission;
      Formation_FMS_B.Merge.ax_cmd = Formation_FMS_B.absxk;
      Formation_FMS_B.Merge.ay_cmd = Formation_FMS_B.t;
      Formation_FMS_B.Merge.vh_cmd = Formation_FMS_B.Multiply1_f;

      // Update for Delay: '<S159>/Delay'
      Formation_FMS_DW.icLoad_k = false;

      // Update for DiscreteIntegrator: '<S97>/Discrete-Time Integrator1'
      Formation_FMS_DW.DiscreteTimeIntegrator1_IC_LOAD = 0U;
      Formation_FMS_DW.DiscreteTimeIntegrator1_DSTATE += 0.02F *
        Formation_FMS_B.rtb_vn_idx_1;
      Formation_FMS_DW.DiscreteTimeIntegrator1_PrevRes = 0;

      // Update for DiscreteIntegrator: '<S141>/Integrator' incorporates:
      //   Gain: '<S138>/Integral Gain'

      Formation_FMS_DW.Integrator_DSTATE += 0.0F * Formation_FMS_B.vd[2] * 0.02F;

      // End of Outputs for SubSystem: '<S20>/FormMission_SubSystem'

      // Update for UnitDelay: '<S81>/Delay Input1'
      //
      //  Block description for '<S81>/Delay Input1':
      //
      //   Store in Global RAM

      Formation_FMS_DW.DelayInput1_DSTATE_d = Formation_FMS_B.wp_index;

      // End of Outputs for SubSystem: '<S12>/FormMission'
      break;

     case 3:
      if (Formation_FMS_DW.SwitchCase_ActiveSubsystem_c != rtPrevAction) {
        // InitializeConditions for IfAction SubSystem: '<S12>/FormDisband' incorporates:
        //   ActionPort: '<S18>/Action Port'

        // InitializeConditions for SwitchCase: '<S12>/Switch Case' incorporates:
        //   Delay: '<S46>/Delay'
        //   Delay: '<S50>/start_vel'

        Formation_FMS_DW.icLoad_a = true;
        Formation_FMS_DW.icLoad_l = true;

        // End of InitializeConditions for SubSystem: '<S12>/FormDisband'
      }

      // Outputs for IfAction SubSystem: '<S12>/FormDisband' incorporates:
      //   ActionPort: '<S18>/Action Port'

      // SignalConversion generated from: '<S56>/Square'
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = *rtu_INS_Out_vn;
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = *rtu_INS_Out_ve;

      // Math: '<S57>/Math Function' incorporates:
      //   Math: '<S56>/Square'

      Formation_FMS_B.absxk = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
      Formation_FMS_B.t = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1];

      // Sum: '<S57>/Sum of Elements' incorporates:
      //   Math: '<S57>/Math Function'

      Formation_FMS_B.scale = Formation_FMS_B.absxk + Formation_FMS_B.t;

      // Math: '<S57>/Math Function1' incorporates:
      //   Sum: '<S57>/Sum of Elements'
      //
      //  About '<S57>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S57>/Math Function1'

      // Switch: '<S57>/Switch' incorporates:
      //   Constant: '<S57>/Constant'
      //   Product: '<S57>/Product'

      if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
        Formation_FMS_B.vd[0] = *rtu_INS_Out_vn;
        Formation_FMS_B.vd[1] = *rtu_INS_Out_ve;
        Formation_FMS_B.vd[2] = Formation_FMS_B.rtb_vn_idx_1;
      } else {
        Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
          0.0F;
        Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
          0.0F;
        Formation_FMS_B.vd[2] = 1.0F;
      }

      // End of Switch: '<S57>/Switch'

      // Delay: '<S50>/start_vel'
      if (Formation_FMS_DW.icLoad_a) {
        Formation_FMS_DW.start_vel_DSTATE_m[0] =
          Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
        Formation_FMS_DW.start_vel_DSTATE_m[1] =
          Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
      }

      // Math: '<S62>/Math Function' incorporates:
      //   Delay: '<S50>/start_vel'

      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] =
        Formation_FMS_DW.start_vel_DSTATE_m[0] *
        Formation_FMS_DW.start_vel_DSTATE_m[0];
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] =
        Formation_FMS_DW.start_vel_DSTATE_m[1] *
        Formation_FMS_DW.start_vel_DSTATE_m[1];

      // Sum: '<S62>/Sum of Elements'
      Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] +
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1];

      // Math: '<S62>/Math Function1' incorporates:
      //   Sum: '<S62>/Sum of Elements'
      //
      //  About '<S62>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S62>/Math Function1'

      // Switch: '<S62>/Switch' incorporates:
      //   Constant: '<S62>/Constant'
      //   Delay: '<S50>/start_vel'
      //   Product: '<S62>/Product'

      if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
        Formation_FMS_B.ve[0] = Formation_FMS_DW.start_vel_DSTATE_m[0];
        Formation_FMS_B.ve[1] = Formation_FMS_DW.start_vel_DSTATE_m[1];
        Formation_FMS_B.ve[2] = Formation_FMS_B.rtb_vn_idx_1;
      } else {
        Formation_FMS_B.ve[0] = Formation_FMS_DW.start_vel_DSTATE_m[0] * 0.0F;
        Formation_FMS_B.ve[1] = Formation_FMS_DW.start_vel_DSTATE_m[1] * 0.0F;
        Formation_FMS_B.ve[2] = 1.0F;
      }

      // End of Switch: '<S62>/Switch'

      // Product: '<S57>/Divide'
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.vd[0] /
        Formation_FMS_B.vd[2];
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.vd[1] /
        Formation_FMS_B.vd[2];

      // SignalConversion generated from: '<S60>/Math Function'
      Formation_FMS_B.P_d[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
      Formation_FMS_B.P_d[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

      // Sum: '<S60>/Sum of Elements' incorporates:
      //   Math: '<S60>/Math Function'
      //   SignalConversion generated from: '<S60>/Math Function'

      Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1] +
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

      // Math: '<S60>/Math Function1' incorporates:
      //   Sum: '<S60>/Sum of Elements'
      //
      //  About '<S60>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S60>/Math Function1'

      // Switch: '<S60>/Switch' incorporates:
      //   Constant: '<S60>/Constant'
      //   Product: '<S60>/Product'
      //   SignalConversion generated from: '<S60>/Math Function'

      if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
        Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
        Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
        Formation_FMS_B.vd[2] = Formation_FMS_B.rtb_vn_idx_1;
      } else {
        Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
          0.0F;
        Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
          0.0F;
        Formation_FMS_B.vd[2] = 1.0F;
      }

      // End of Switch: '<S60>/Switch'

      // MinMax: '<S48>/Max' incorporates:
      //   Constant: '<S47>/L1'
      //   Constant: '<S47>/R'
      //   Gain: '<S48>/Gain'

      Formation_FMS_B.scale = std::fmax(FMS_PARAM.LOITER_R, 0.5F * FMS_PARAM.L1);

      // Reshape: '<S48>/Reshape2'
      Formation_FMS_B.Reshape2_bq[0] = *rtu_INS_Out_x_R;
      Formation_FMS_B.Reshape2_bq[1] = *rtu_INS_Out_y_R;

      // MATLAB Function: '<S48>/SearchL1RefWP' incorporates:
      //   Constant: '<S47>/L1'

      Formation_FMS_SearchL1RefWP_i(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
        Formation_FMS_B.Reshape2_bq, Formation_FMS_B.scale, FMS_PARAM.L1,
        Formation_FMS_B.TmpSignalConversionAtSqua_c, &Formation_FMS_B.n_j);

      // RelationalOperator: '<S51>/Compare' incorporates:
      //   Constant: '<S51>/Constant'

      rtb_FixPtRelationalOperator_c = (Formation_FMS_B.n_j > 0.0);

      // Product: '<S62>/Divide'
      Formation_FMS_B.P_i[0] = Formation_FMS_B.ve[0] / Formation_FMS_B.ve[2];
      Formation_FMS_B.P_i[1] = Formation_FMS_B.ve[1] / Formation_FMS_B.ve[2];

      // MATLAB Function: '<S48>/OutRegionRegWP' incorporates:
      //   Constant: '<S47>/L1'

      Formation_FMS_OutRegionRegWP_o(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
        Formation_FMS_B.Reshape2_bq, Formation_FMS_B.scale, FMS_PARAM.L1,
        Formation_FMS_B.P_i, Formation_FMS_B.P_d);

      // Switch: '<S48>/Switch'
      if (rtb_FixPtRelationalOperator_c) {
        Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
      } else {
        Formation_FMS_B.scale = Formation_FMS_B.P_d[0];
      }

      // Sum: '<S49>/Subtract' incorporates:
      //   Switch: '<S48>/Switch'

      Formation_FMS_B.Reshape2_bq[0] = Formation_FMS_B.scale - *rtu_INS_Out_x_R;

      // Switch: '<S48>/Switch'
      if (rtb_FixPtRelationalOperator_c) {
        Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
      } else {
        Formation_FMS_B.scale = Formation_FMS_B.P_d[1];
      }

      // Sum: '<S49>/Subtract' incorporates:
      //   Switch: '<S48>/Switch'

      Formation_FMS_B.Reshape2_bq[1] = Formation_FMS_B.scale - *rtu_INS_Out_y_R;

      // Sum: '<S58>/Sum of Elements' incorporates:
      //   Math: '<S58>/Math Function'
      //   Sum: '<S49>/Subtract'

      Formation_FMS_B.scale = Formation_FMS_B.Reshape2_bq[0] *
        Formation_FMS_B.Reshape2_bq[0] + Formation_FMS_B.Reshape2_bq[1] *
        Formation_FMS_B.Reshape2_bq[1];

      // Math: '<S58>/Math Function1' incorporates:
      //   Sum: '<S58>/Sum of Elements'
      //
      //  About '<S58>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S58>/Math Function1'

      // Switch: '<S58>/Switch' incorporates:
      //   Constant: '<S58>/Constant'
      //   Product: '<S58>/Product'
      //   Sum: '<S49>/Subtract'
      //   Switch: '<S61>/Switch'

      if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
        Formation_FMS_B.ve[0] = Formation_FMS_B.Reshape2_bq[0];
        Formation_FMS_B.ve[1] = Formation_FMS_B.Reshape2_bq[1];
        Formation_FMS_B.ve[2] = Formation_FMS_B.rtb_vn_idx_1;
      } else {
        Formation_FMS_B.ve[0] = Formation_FMS_B.Reshape2_bq[0] * 0.0F;
        Formation_FMS_B.ve[1] = Formation_FMS_B.Reshape2_bq[1] * 0.0F;
        Formation_FMS_B.ve[2] = 1.0F;
      }

      // End of Switch: '<S58>/Switch'

      // Product: '<S58>/Divide' incorporates:
      //   Product: '<S61>/Divide'

      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.ve[0] /
        Formation_FMS_B.ve[2];
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.ve[1] /
        Formation_FMS_B.ve[2];

      // Sum: '<S61>/Sum of Elements' incorporates:
      //   Math: '<S61>/Math Function'
      //   SignalConversion generated from: '<S61>/Math Function'

      Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1] +
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

      // Math: '<S61>/Math Function1' incorporates:
      //   Sum: '<S61>/Sum of Elements'
      //
      //  About '<S61>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.scale < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
      }

      // End of Math: '<S61>/Math Function1'

      // Switch: '<S61>/Switch' incorporates:
      //   Constant: '<S61>/Constant'
      //   Product: '<S61>/Product'
      //   SignalConversion generated from: '<S61>/Math Function'

      if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
        Formation_FMS_B.ve[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
        Formation_FMS_B.ve[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
        Formation_FMS_B.ve[2] = Formation_FMS_B.rtb_vn_idx_1;
      } else {
        Formation_FMS_B.ve[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
          0.0F;
        Formation_FMS_B.ve[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
          0.0F;
        Formation_FMS_B.ve[2] = 1.0F;
      }

      // End of Switch: '<S61>/Switch'

      // Product: '<S61>/Divide'
      Formation_FMS_B.rtb_x_R_idx_0 = Formation_FMS_B.ve[0] /
        Formation_FMS_B.ve[2];

      // Product: '<S60>/Divide'
      Formation_FMS_B.Multiply1_f = Formation_FMS_B.vd[0] / Formation_FMS_B.vd[2];

      // DotProduct: '<S55>/Dot Product'
      Formation_FMS_B.scale = Formation_FMS_B.Multiply1_f *
        Formation_FMS_B.rtb_x_R_idx_0;
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] =
        Formation_FMS_B.rtb_x_R_idx_0;
      Formation_FMS_B.P_d[0] = Formation_FMS_B.Multiply1_f;

      // Product: '<S61>/Divide' incorporates:
      //   Product: '<S60>/Divide'

      Formation_FMS_B.rtb_x_R_idx_0 = Formation_FMS_B.ve[1] /
        Formation_FMS_B.ve[2];

      // Product: '<S60>/Divide'
      Formation_FMS_B.Multiply1_f = Formation_FMS_B.vd[1] / Formation_FMS_B.vd[2];

      // DotProduct: '<S55>/Dot Product'
      Formation_FMS_B.scale += Formation_FMS_B.Multiply1_f *
        Formation_FMS_B.rtb_x_R_idx_0;

      // Sqrt: '<S56>/Sqrt' incorporates:
      //   Math: '<S56>/Square'
      //   Sum: '<S56>/Sum of Elements'

      Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.absxk +
        Formation_FMS_B.t);

      // Math: '<S54>/Square'
      Formation_FMS_B.absxk = Formation_FMS_B.rtb_vn_idx_1 *
        Formation_FMS_B.rtb_vn_idx_1;

      // Sum: '<S59>/Subtract' incorporates:
      //   Product: '<S59>/Multiply'
      //   Product: '<S59>/Multiply1'

      Formation_FMS_B.t = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        Formation_FMS_B.Multiply1_f - Formation_FMS_B.P_d[0] *
        Formation_FMS_B.rtb_x_R_idx_0;

      // Signum: '<S55>/Sign1'
      if (std::isnan(Formation_FMS_B.t)) {
        Formation_FMS_B.rtb_vn_idx_1 = (rtNaNF);
      } else if (Formation_FMS_B.t < 0.0F) {
        Formation_FMS_B.rtb_vn_idx_1 = -1.0F;
      } else {
        Formation_FMS_B.rtb_vn_idx_1 = (Formation_FMS_B.t > 0.0F);
      }

      // End of Signum: '<S55>/Sign1'

      // Trigonometry: '<S55>/Acos' incorporates:
      //   DotProduct: '<S55>/Dot Product'

      if (Formation_FMS_B.scale > 1.0F) {
        Formation_FMS_B.scale = 1.0F;
      } else if (Formation_FMS_B.scale < -1.0F) {
        Formation_FMS_B.scale = -1.0F;
      }

      // Switch: '<S55>/Switch2' incorporates:
      //   Constant: '<S55>/Constant4'

      if (!(Formation_FMS_B.rtb_vn_idx_1 != 0.0F)) {
        Formation_FMS_B.rtb_vn_idx_1 = 1.0F;
      }

      // Product: '<S55>/Multiply' incorporates:
      //   Switch: '<S55>/Switch2'
      //   Trigonometry: '<S55>/Acos'

      Formation_FMS_B.Multiply1_f = std::acos(Formation_FMS_B.scale) *
        Formation_FMS_B.rtb_vn_idx_1;

      // Sum: '<S45>/Sum' incorporates:
      //   Constant: '<S45>/Constant'

      Formation_FMS_B.rtb_vn_idx_1 = FMS_PARAM.FW_AIRSPD_TRIM -
        *rtu_INS_Out_airspeed;

      // Delay: '<S46>/Delay' incorporates:
      //   Constant: '<S46>/Constant'

      if (Formation_FMS_DW.icLoad_l) {
        Formation_FMS_DW.Delay_DSTATE_i = FMS_PARAM.FW_HEIGHT_TRIM;
      }

      // Sum: '<S46>/Sum' incorporates:
      //   Delay: '<S46>/Delay'

      Formation_FMS_B.scale = Formation_FMS_DW.Delay_DSTATE_i - *rtu_INS_Out_h_R;

      // End of Outputs for SubSystem: '<S12>/FormDisband'
      std::memset(&Formation_FMS_B.Merge, 0, sizeof(FMS_Out_Bus));

      // Outputs for IfAction SubSystem: '<S12>/FormDisband' incorporates:
      //   ActionPort: '<S18>/Action Port'

      // BusAssignment: '<S18>/Bus Assignment' incorporates:
      //   Constant: '<S18>/Constant1'
      //   Merge: '<S10>/Merge'

      Formation_FMS_B.Merge.state = VehicleState::FormDisband;
      Formation_FMS_B.Merge.ax_cmd = Formation_FMS_B.rtb_vn_idx_1;

      // Saturate: '<S54>/Saturation'
      if (Formation_FMS_B.Multiply1_f > 1.57079637F) {
        Formation_FMS_B.Multiply1_f = 1.57079637F;
      } else if (Formation_FMS_B.Multiply1_f < -1.57079637F) {
        Formation_FMS_B.Multiply1_f = -1.57079637F;
      }

      // BusAssignment: '<S18>/Bus Assignment' incorporates:
      //   Constant: '<S47>/L1'
      //   Gain: '<S54>/Gain'
      //   Product: '<S54>/Divide'
      //   Product: '<S54>/Multiply1'
      //   Saturate: '<S54>/Saturation'
      //   Trigonometry: '<S54>/Sin'

      Formation_FMS_B.Merge.ay_cmd = 2.0F * Formation_FMS_B.absxk * std::sin
        (Formation_FMS_B.Multiply1_f) / FMS_PARAM.L1;

      // Gain: '<S46>/Gain2'
      Formation_FMS_B.Multiply1_f = FMS_PARAM.Z_P * Formation_FMS_B.scale;

      // Saturate: '<S46>/Saturation'
      if (Formation_FMS_B.Multiply1_f > CONTROL_PARAM.FW_T_CLMB_MAX) {
        // BusAssignment: '<S18>/Bus Assignment'
        Formation_FMS_B.Merge.vh_cmd = CONTROL_PARAM.FW_T_CLMB_MAX;
      } else if (Formation_FMS_B.Multiply1_f < -CONTROL_PARAM.FW_T_SINK_MAX) {
        // BusAssignment: '<S18>/Bus Assignment'
        Formation_FMS_B.Merge.vh_cmd = -CONTROL_PARAM.FW_T_SINK_MAX;
      } else {
        // BusAssignment: '<S18>/Bus Assignment'
        Formation_FMS_B.Merge.vh_cmd = Formation_FMS_B.Multiply1_f;
      }

      // End of Saturate: '<S46>/Saturation'

      // Update for Delay: '<S50>/start_vel'
      Formation_FMS_DW.icLoad_a = false;

      // Update for Delay: '<S46>/Delay'
      Formation_FMS_DW.icLoad_l = false;

      // End of Outputs for SubSystem: '<S12>/FormDisband'
      break;

     default:
      if (Formation_FMS_DW.SwitchCase_ActiveSubsystem_c != rtPrevAction) {
        // SystemReset for IfAction SubSystem: '<S12>/Default' incorporates:
        //   ActionPort: '<S16>/Action Port'

        // SystemReset for SwitchCase: '<S12>/Switch Case'
        Formation_FMS_Default_Reset(&Formation_FMS_DW.Default_d);

        // End of SystemReset for SubSystem: '<S12>/Default'
      }

      // Outputs for IfAction SubSystem: '<S12>/Default' incorporates:
      //   ActionPort: '<S16>/Action Port'

      Formation_FMS_Default(rtu_INS_Out_airspeed, rtu_INS_Out_h_R,
                            &Formation_FMS_B.Merge, &Formation_FMS_DW.Default_d);

      // End of Outputs for SubSystem: '<S12>/Default'
      break;
    }

    // End of Outputs for SubSystem: '<S10>/Form_Subsystem'
    break;

   case 1:
    if (Formation_FMS_DW.SwitchCase_ActiveSubsystem != rtPrevAction) {
      // InitializeConditions for IfAction SubSystem: '<S10>/Hold' incorporates:
      //   ActionPort: '<S13>/Action Port'

      // InitializeConditions for SwitchCase: '<S10>/Switch Case' incorporates:
      //   Delay: '<S182>/Delay'
      //   Delay: '<S186>/start_vel'

      Formation_FMS_DW.icLoad = true;
      Formation_FMS_DW.icLoad_j = true;

      // End of InitializeConditions for SubSystem: '<S10>/Hold'
    }

    // Outputs for IfAction SubSystem: '<S10>/Hold' incorporates:
    //   ActionPort: '<S13>/Action Port'

    // SignalConversion generated from: '<S192>/Square'
    Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = *rtu_INS_Out_vn;
    Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = *rtu_INS_Out_ve;

    // Math: '<S193>/Math Function' incorporates:
    //   Math: '<S192>/Square'

    Formation_FMS_B.absxk = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
    Formation_FMS_B.t = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1];

    // Sum: '<S193>/Sum of Elements' incorporates:
    //   Math: '<S193>/Math Function'

    Formation_FMS_B.scale = Formation_FMS_B.absxk + Formation_FMS_B.t;

    // Math: '<S193>/Math Function1' incorporates:
    //   Sum: '<S193>/Sum of Elements'
    //
    //  About '<S193>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.scale < 0.0F) {
      Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
    } else {
      Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
    }

    // End of Math: '<S193>/Math Function1'

    // Switch: '<S193>/Switch' incorporates:
    //   Constant: '<S193>/Constant'
    //   Product: '<S193>/Product'

    if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
      Formation_FMS_B.vd[0] = *rtu_INS_Out_vn;
      Formation_FMS_B.vd[1] = *rtu_INS_Out_ve;
      Formation_FMS_B.vd[2] = Formation_FMS_B.rtb_vn_idx_1;
    } else {
      Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        0.0F;
      Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        0.0F;
      Formation_FMS_B.vd[2] = 1.0F;
    }

    // End of Switch: '<S193>/Switch'

    // Delay: '<S186>/start_vel'
    if (Formation_FMS_DW.icLoad) {
      Formation_FMS_DW.start_vel_DSTATE[0] =
        Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
      Formation_FMS_DW.start_vel_DSTATE[1] =
        Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
    }

    // Math: '<S198>/Math Function' incorporates:
    //   Delay: '<S186>/start_vel'

    Formation_FMS_B.TmpSignalConversionAtSqua_c[0] =
      Formation_FMS_DW.start_vel_DSTATE[0] * Formation_FMS_DW.start_vel_DSTATE[0];
    Formation_FMS_B.TmpSignalConversionAtSqua_c[1] =
      Formation_FMS_DW.start_vel_DSTATE[1] * Formation_FMS_DW.start_vel_DSTATE[1];

    // Sum: '<S198>/Sum of Elements'
    Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] +
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1];

    // Math: '<S198>/Math Function1' incorporates:
    //   Sum: '<S198>/Sum of Elements'
    //
    //  About '<S198>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.scale < 0.0F) {
      Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
    } else {
      Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
    }

    // End of Math: '<S198>/Math Function1'

    // Switch: '<S198>/Switch' incorporates:
    //   Constant: '<S198>/Constant'
    //   Delay: '<S186>/start_vel'
    //   Product: '<S198>/Product'

    if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
      Formation_FMS_B.ve[0] = Formation_FMS_DW.start_vel_DSTATE[0];
      Formation_FMS_B.ve[1] = Formation_FMS_DW.start_vel_DSTATE[1];
      Formation_FMS_B.ve[2] = Formation_FMS_B.rtb_vn_idx_1;
    } else {
      Formation_FMS_B.ve[0] = Formation_FMS_DW.start_vel_DSTATE[0] * 0.0F;
      Formation_FMS_B.ve[1] = Formation_FMS_DW.start_vel_DSTATE[1] * 0.0F;
      Formation_FMS_B.ve[2] = 1.0F;
    }

    // End of Switch: '<S198>/Switch'

    // Product: '<S193>/Divide'
    Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.vd[0] /
      Formation_FMS_B.vd[2];
    Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.vd[1] /
      Formation_FMS_B.vd[2];

    // SignalConversion generated from: '<S196>/Math Function'
    Formation_FMS_B.P_d[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
    Formation_FMS_B.P_d[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

    // Sum: '<S196>/Sum of Elements' incorporates:
    //   Math: '<S196>/Math Function'
    //   SignalConversion generated from: '<S196>/Math Function'

    Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] +
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

    // Math: '<S196>/Math Function1' incorporates:
    //   Sum: '<S196>/Sum of Elements'
    //
    //  About '<S196>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.scale < 0.0F) {
      Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
    } else {
      Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
    }

    // End of Math: '<S196>/Math Function1'

    // Switch: '<S196>/Switch' incorporates:
    //   Constant: '<S196>/Constant'
    //   Product: '<S196>/Product'
    //   SignalConversion generated from: '<S196>/Math Function'

    if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
      Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
      Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
      Formation_FMS_B.vd[2] = Formation_FMS_B.rtb_vn_idx_1;
    } else {
      Formation_FMS_B.vd[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        0.0F;
      Formation_FMS_B.vd[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        0.0F;
      Formation_FMS_B.vd[2] = 1.0F;
    }

    // End of Switch: '<S196>/Switch'

    // MinMax: '<S184>/Max' incorporates:
    //   Constant: '<S183>/L1'
    //   Constant: '<S183>/R'
    //   Gain: '<S184>/Gain'

    Formation_FMS_B.scale = std::fmax(FMS_PARAM.LOITER_R, 0.5F * FMS_PARAM.L1);

    // Reshape: '<S184>/Reshape2'
    Formation_FMS_B.Reshape2_bq[0] = *rtu_INS_Out_x_R;
    Formation_FMS_B.Reshape2_bq[1] = *rtu_INS_Out_y_R;

    // MATLAB Function: '<S184>/SearchL1RefWP' incorporates:
    //   Constant: '<S183>/L1'

    Formation_FMS_SearchL1RefWP_i(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
      Formation_FMS_B.Reshape2_bq, Formation_FMS_B.scale, FMS_PARAM.L1,
      Formation_FMS_B.TmpSignalConversionAtSqua_c, &Formation_FMS_B.n_j);

    // RelationalOperator: '<S187>/Compare' incorporates:
    //   Constant: '<S187>/Constant'

    rtb_FixPtRelationalOperator_c = (Formation_FMS_B.n_j > 0.0);

    // Product: '<S198>/Divide'
    Formation_FMS_B.P_i[0] = Formation_FMS_B.ve[0] / Formation_FMS_B.ve[2];
    Formation_FMS_B.P_i[1] = Formation_FMS_B.ve[1] / Formation_FMS_B.ve[2];

    // MATLAB Function: '<S184>/OutRegionRegWP' incorporates:
    //   Constant: '<S183>/L1'

    Formation_FMS_OutRegionRegWP_o(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
      Formation_FMS_B.Reshape2_bq, Formation_FMS_B.scale, FMS_PARAM.L1,
      Formation_FMS_B.P_i, Formation_FMS_B.P_d);

    // Switch: '<S184>/Switch'
    if (rtb_FixPtRelationalOperator_c) {
      Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
    } else {
      Formation_FMS_B.scale = Formation_FMS_B.P_d[0];
    }

    // Sum: '<S185>/Subtract' incorporates:
    //   Switch: '<S184>/Switch'

    Formation_FMS_B.Reshape2_bq[0] = Formation_FMS_B.scale - *rtu_INS_Out_x_R;

    // Switch: '<S184>/Switch'
    if (rtb_FixPtRelationalOperator_c) {
      Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
    } else {
      Formation_FMS_B.scale = Formation_FMS_B.P_d[1];
    }

    // Sum: '<S185>/Subtract' incorporates:
    //   Switch: '<S184>/Switch'

    Formation_FMS_B.Reshape2_bq[1] = Formation_FMS_B.scale - *rtu_INS_Out_y_R;

    // Sum: '<S194>/Sum of Elements' incorporates:
    //   Math: '<S194>/Math Function'
    //   Sum: '<S185>/Subtract'

    Formation_FMS_B.scale = Formation_FMS_B.Reshape2_bq[0] *
      Formation_FMS_B.Reshape2_bq[0] + Formation_FMS_B.Reshape2_bq[1] *
      Formation_FMS_B.Reshape2_bq[1];

    // Math: '<S194>/Math Function1' incorporates:
    //   Sum: '<S194>/Sum of Elements'
    //
    //  About '<S194>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.scale < 0.0F) {
      Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
    } else {
      Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
    }

    // End of Math: '<S194>/Math Function1'

    // Switch: '<S194>/Switch' incorporates:
    //   Constant: '<S194>/Constant'
    //   Product: '<S194>/Product'
    //   Sum: '<S185>/Subtract'
    //   Switch: '<S197>/Switch'

    if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
      Formation_FMS_B.ve[0] = Formation_FMS_B.Reshape2_bq[0];
      Formation_FMS_B.ve[1] = Formation_FMS_B.Reshape2_bq[1];
      Formation_FMS_B.ve[2] = Formation_FMS_B.rtb_vn_idx_1;
    } else {
      Formation_FMS_B.ve[0] = Formation_FMS_B.Reshape2_bq[0] * 0.0F;
      Formation_FMS_B.ve[1] = Formation_FMS_B.Reshape2_bq[1] * 0.0F;
      Formation_FMS_B.ve[2] = 1.0F;
    }

    // End of Switch: '<S194>/Switch'

    // Product: '<S194>/Divide' incorporates:
    //   Product: '<S197>/Divide'

    Formation_FMS_B.TmpSignalConversionAtSqua_c[0] = Formation_FMS_B.ve[0] /
      Formation_FMS_B.ve[2];
    Formation_FMS_B.TmpSignalConversionAtSqua_c[1] = Formation_FMS_B.ve[1] /
      Formation_FMS_B.ve[2];

    // Sum: '<S197>/Sum of Elements' incorporates:
    //   Math: '<S197>/Math Function'
    //   SignalConversion generated from: '<S197>/Math Function'

    Formation_FMS_B.scale = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
      Formation_FMS_B.TmpSignalConversionAtSqua_c[1] +
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
      Formation_FMS_B.TmpSignalConversionAtSqua_c[0];

    // Math: '<S197>/Math Function1' incorporates:
    //   Sum: '<S197>/Sum of Elements'
    //
    //  About '<S197>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.scale < 0.0F) {
      Formation_FMS_B.rtb_vn_idx_1 = -std::sqrt(std::abs(Formation_FMS_B.scale));
    } else {
      Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.scale);
    }

    // End of Math: '<S197>/Math Function1'

    // Switch: '<S197>/Switch' incorporates:
    //   Constant: '<S197>/Constant'
    //   Product: '<S197>/Product'
    //   SignalConversion generated from: '<S197>/Math Function'

    if (Formation_FMS_B.rtb_vn_idx_1 > 0.0F) {
      Formation_FMS_B.ve[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1];
      Formation_FMS_B.ve[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0];
      Formation_FMS_B.ve[2] = Formation_FMS_B.rtb_vn_idx_1;
    } else {
      Formation_FMS_B.ve[0] = Formation_FMS_B.TmpSignalConversionAtSqua_c[1] *
        0.0F;
      Formation_FMS_B.ve[1] = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
        0.0F;
      Formation_FMS_B.ve[2] = 1.0F;
    }

    // End of Switch: '<S197>/Switch'

    // Product: '<S197>/Divide'
    Formation_FMS_B.rtb_x_R_idx_0 = Formation_FMS_B.ve[0] / Formation_FMS_B.ve[2];

    // Product: '<S196>/Divide'
    Formation_FMS_B.Multiply1_f = Formation_FMS_B.vd[0] / Formation_FMS_B.vd[2];

    // DotProduct: '<S191>/Dot Product'
    Formation_FMS_B.scale = Formation_FMS_B.Multiply1_f *
      Formation_FMS_B.rtb_x_R_idx_0;
    Formation_FMS_B.TmpSignalConversionAtSqua_c[0] =
      Formation_FMS_B.rtb_x_R_idx_0;
    Formation_FMS_B.P_d[0] = Formation_FMS_B.Multiply1_f;

    // Product: '<S197>/Divide' incorporates:
    //   Product: '<S196>/Divide'

    Formation_FMS_B.rtb_x_R_idx_0 = Formation_FMS_B.ve[1] / Formation_FMS_B.ve[2];

    // Product: '<S196>/Divide'
    Formation_FMS_B.Multiply1_f = Formation_FMS_B.vd[1] / Formation_FMS_B.vd[2];

    // DotProduct: '<S191>/Dot Product'
    Formation_FMS_B.scale += Formation_FMS_B.Multiply1_f *
      Formation_FMS_B.rtb_x_R_idx_0;

    // Sqrt: '<S192>/Sqrt' incorporates:
    //   Math: '<S192>/Square'
    //   Sum: '<S192>/Sum of Elements'

    Formation_FMS_B.rtb_vn_idx_1 = std::sqrt(Formation_FMS_B.absxk +
      Formation_FMS_B.t);

    // Math: '<S190>/Square'
    Formation_FMS_B.absxk = Formation_FMS_B.rtb_vn_idx_1 *
      Formation_FMS_B.rtb_vn_idx_1;

    // Sum: '<S195>/Subtract' incorporates:
    //   Product: '<S195>/Multiply'
    //   Product: '<S195>/Multiply1'

    Formation_FMS_B.t = Formation_FMS_B.TmpSignalConversionAtSqua_c[0] *
      Formation_FMS_B.Multiply1_f - Formation_FMS_B.P_d[0] *
      Formation_FMS_B.rtb_x_R_idx_0;

    // Signum: '<S191>/Sign1'
    if (std::isnan(Formation_FMS_B.t)) {
      Formation_FMS_B.rtb_vn_idx_1 = (rtNaNF);
    } else if (Formation_FMS_B.t < 0.0F) {
      Formation_FMS_B.rtb_vn_idx_1 = -1.0F;
    } else {
      Formation_FMS_B.rtb_vn_idx_1 = (Formation_FMS_B.t > 0.0F);
    }

    // End of Signum: '<S191>/Sign1'

    // Trigonometry: '<S191>/Acos' incorporates:
    //   DotProduct: '<S191>/Dot Product'

    if (Formation_FMS_B.scale > 1.0F) {
      Formation_FMS_B.scale = 1.0F;
    } else if (Formation_FMS_B.scale < -1.0F) {
      Formation_FMS_B.scale = -1.0F;
    }

    // Switch: '<S191>/Switch2' incorporates:
    //   Constant: '<S191>/Constant4'

    if (!(Formation_FMS_B.rtb_vn_idx_1 != 0.0F)) {
      Formation_FMS_B.rtb_vn_idx_1 = 1.0F;
    }

    // Product: '<S191>/Multiply' incorporates:
    //   Switch: '<S191>/Switch2'
    //   Trigonometry: '<S191>/Acos'

    Formation_FMS_B.Multiply1_f = std::acos(Formation_FMS_B.scale) *
      Formation_FMS_B.rtb_vn_idx_1;

    // Sum: '<S181>/Sum' incorporates:
    //   Constant: '<S181>/Constant'

    Formation_FMS_B.rtb_vn_idx_1 = FMS_PARAM.FW_AIRSPD_TRIM -
      *rtu_INS_Out_airspeed;

    // Delay: '<S182>/Delay' incorporates:
    //   Constant: '<S182>/Constant'

    if (Formation_FMS_DW.icLoad_j) {
      Formation_FMS_DW.Delay_DSTATE = FMS_PARAM.FW_HEIGHT_TRIM;
    }

    // Sum: '<S182>/Sum' incorporates:
    //   Delay: '<S182>/Delay'

    Formation_FMS_B.scale = Formation_FMS_DW.Delay_DSTATE - *rtu_INS_Out_h_R;

    // End of Outputs for SubSystem: '<S10>/Hold'
    std::memset(&Formation_FMS_B.Merge, 0, sizeof(FMS_Out_Bus));

    // Outputs for IfAction SubSystem: '<S10>/Hold' incorporates:
    //   ActionPort: '<S13>/Action Port'

    // BusAssignment: '<S13>/Bus Assignment' incorporates:
    //   Constant: '<S13>/Constant1'
    //   Merge: '<S10>/Merge'

    Formation_FMS_B.Merge.state = VehicleState::Hold;
    Formation_FMS_B.Merge.ax_cmd = Formation_FMS_B.rtb_vn_idx_1;

    // Saturate: '<S190>/Saturation'
    if (Formation_FMS_B.Multiply1_f > 1.57079637F) {
      Formation_FMS_B.Multiply1_f = 1.57079637F;
    } else if (Formation_FMS_B.Multiply1_f < -1.57079637F) {
      Formation_FMS_B.Multiply1_f = -1.57079637F;
    }

    // BusAssignment: '<S13>/Bus Assignment' incorporates:
    //   Constant: '<S183>/L1'
    //   Gain: '<S190>/Gain'
    //   Product: '<S190>/Divide'
    //   Product: '<S190>/Multiply1'
    //   Saturate: '<S190>/Saturation'
    //   Trigonometry: '<S190>/Sin'

    Formation_FMS_B.Merge.ay_cmd = 2.0F * Formation_FMS_B.absxk * std::sin
      (Formation_FMS_B.Multiply1_f) / FMS_PARAM.L1;

    // Gain: '<S182>/Gain2'
    Formation_FMS_B.Multiply1_f = FMS_PARAM.Z_P * Formation_FMS_B.scale;

    // Saturate: '<S182>/Saturation'
    if (Formation_FMS_B.Multiply1_f > CONTROL_PARAM.FW_T_CLMB_MAX) {
      // BusAssignment: '<S13>/Bus Assignment'
      Formation_FMS_B.Merge.vh_cmd = CONTROL_PARAM.FW_T_CLMB_MAX;
    } else if (Formation_FMS_B.Multiply1_f < -CONTROL_PARAM.FW_T_SINK_MAX) {
      // BusAssignment: '<S13>/Bus Assignment'
      Formation_FMS_B.Merge.vh_cmd = -CONTROL_PARAM.FW_T_SINK_MAX;
    } else {
      // BusAssignment: '<S13>/Bus Assignment'
      Formation_FMS_B.Merge.vh_cmd = Formation_FMS_B.Multiply1_f;
    }

    // End of Saturate: '<S182>/Saturation'

    // Update for Delay: '<S186>/start_vel'
    Formation_FMS_DW.icLoad = false;

    // Update for Delay: '<S182>/Delay'
    Formation_FMS_DW.icLoad_j = false;

    // End of Outputs for SubSystem: '<S10>/Hold'
    break;

   default:
    if (Formation_FMS_DW.SwitchCase_ActiveSubsystem != rtPrevAction) {
      // SystemReset for IfAction SubSystem: '<S10>/Default' incorporates:
      //   ActionPort: '<S11>/Action Port'

      // SystemReset for SwitchCase: '<S10>/Switch Case'
      Formation_FMS_Default_Reset(&Formation_FMS_DW.Default);

      // End of SystemReset for SubSystem: '<S10>/Default'
    }

    // Outputs for IfAction SubSystem: '<S10>/Default' incorporates:
    //   ActionPort: '<S11>/Action Port'

    Formation_FMS_Default(rtu_INS_Out_airspeed, rtu_INS_Out_h_R,
                          &Formation_FMS_B.Merge, &Formation_FMS_DW.Default);

    // End of Outputs for SubSystem: '<S10>/Default'
    break;
  }

  // End of SwitchCase: '<S10>/Switch Case'

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_type[0] = Formation_FMS_B.Other_Mission_Data.type[0];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_valid_it[0] =
    Formation_FMS_B.Other_Mission_Data.valid_items[0];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_type[1] = Formation_FMS_B.Other_Mission_Data.type[1];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_valid_it[1] =
    Formation_FMS_B.Other_Mission_Data.valid_items[1];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_type[2] = Formation_FMS_B.Other_Mission_Data.type[2];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  rty_Other_Mission_Data_valid_it[2] =
    Formation_FMS_B.Other_Mission_Data.valid_items[2];

  // SignalConversion generated from: '<Root>/Other_Mission_Data'
  *rty_Other_Mission_Data_timestam =
    Formation_FMS_B.Other_Mission_Data.timestamp;

  // SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_timestamp = Formation_FMS_B.Merge.timestamp;

  // SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_state = Formation_FMS_B.Merge.state;

  // SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_ax_cmd = Formation_FMS_B.Merge.ax_cmd;

  // SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_ay_cmd = Formation_FMS_B.Merge.ay_cmd;

  // SignalConversion generated from: '<Root>/FMS_Out'
  *rty_FMS_Out_vh_cmd = Formation_FMS_B.Merge.vh_cmd;
}

// Model initialize function
void Formation_FMS::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  Formation_FMS_PrevZCX.Mission_SubSystem_Reset_ZCE = POS_ZCSIG;
  Formation_FMS_PrevZCX.FormMission_SubSystem_Reset_ZCE = POS_ZCSIG;
}

// Constructor
Formation_FMS::Formation_FMS() :
  Formation_FMS_B(),
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
