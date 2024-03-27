//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Formation_FMS.cpp
//
// Code generated for Simulink model 'Formation_FMS'.
//
// Model version                  : 1.121
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Wed Mar 27 20:14:25 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "Formation_FMS.h"
#include "rtwtypes.h"
#include "Formation_FMS_types.h"
#include <cmath>
#include <cstring>
#include <xmmintrin.h>
#include "rt_defines.h"
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

const uint8_T Formation_FMS_IN_Loiter{ 1U };

const uint8_T Formation_FMS_IN_Mission{ 2U };

const uint8_T Formation_FMS_IN_NextWP{ 1U };

const uint8_T Formation_FMS_IN_NextWP_d{ 3U };

const uint8_T Formation_FMS_IN_NextWP_dp{ 2U };

const uint8_T Formation_FMS_IN_Standby{ 3U };

const uint8_T Formation_FMS_IN_WaitForUpdate{ 2U };

const uint8_T Formation_FMS_IN_Waypoint{ 3U };

const uint8_T Formation_FMS_IN_Waypoint_g{ 4U };

const uint8_T Formation_FM_IN_NO_ACTIVE_CHILD{ 0U };

// Exported block parameters
struct_FebwIpiU9Ih55vl7WG22GB CONTROL_PARAM{
  7.0F,
  7.0F,
  0.1F,
  0.2F,
  0.15F,
  0.1F,
  0.1F,
  0.2F,
  -0.1F,
  0.1F,
  2.10256686e-16F,
  -0.011449079F,
  -2.56444572e-16F,
  0.0479616486F,
  10.0F,
  30.0F,
  25.0F,
  7.0F,
  0,
  1,
  5.0F,
  0.1F,
  0.05F,
  0.1F,
  1.0F,
  10.0F,
  2.0F,
  8.0F,
  5.0F,
  5.0F,
  0.52359879F,
  -0.52359879F,
  0.87266463F,
  7.0F,
  5.0F,
  0.3F,
  15.0F,
  0.5F,
  0.5F,
  0.3F,
  1.22173047F,
  1.04719758F,
  0.87266463F,
  1.0F,
  0.0F,
  0.349944651F,
  1.0F,
  0.1F
} ;                                    // Variable: CONTROL_PARAM
                                          //  Referenced by:
                                          //    '<S15>/Constant'
                                          //    '<S16>/Saturation'
                                          //    '<S64>/Constant'
                                          //    '<S65>/Saturation'
                                          //    '<S19>/Constant'
                                          //    '<S20>/Saturation'
                                          //    '<S42>/Constant'
                                          //    '<S43>/Saturation'


struct_9QCb8LDOYrZ6XTvfIWkyaC FMS_PARAM{
  0.15F,
  0.15F,
  0.1F,
  0.1F,
  0.5F,
  1.0F,
  2.5F,
  2.5F,
  1.04719758F,
  0.52359879F,
  50.0F,
  100.0F,
  100.0F,
  0.95F,
  8.0F
} ;                                    // Variable: FMS_PARAM
                                          //  Referenced by:
                                          //    '<Root>/ACCEPT_R'
                                          //    '<S16>/Gain2'
                                          //    '<S65>/Gain2'
                                          //    '<S66>/L1'
                                          //    '<S66>/R'
                                          //    '<S20>/Gain2'
                                          //    '<S42>/Gain'
                                          //    '<S43>/Gain2'
                                          //    '<S23>/L1'
                                          //    '<S23>/Saturation1'
                                          //    '<S47>/L1'
                                          //    '<S47>/Saturation1'


//
// Output and update for atomic system:
//    '<S49>/NearbyRefWP'
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
//    '<S49>/OutRegionRegWP'
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
//    '<S49>/SearchL1RefWP'
//    '<S25>/SearchL1RefWP'
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

// Function for MATLAB Function: '<S83>/MATLAB Function'
real_T Formation_FMS::Formation_FMS_atan3(real_T x, real_T y, real_T x0, real_T
  b_y0)
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

// Function for MATLAB Function: '<S83>/MATLAB Function'
void Formation_FMS::Formation_FMS_Dubins(const captured_var_Formation_FMS_T
  *PhiMaximum, const captured_var_Formation_FMS_T *rad2deg, real_T xs, real_T ys,
  real_T psi_s, real_T xf, real_T yf, real_T psi_f, real_T v, real_T xts[4],
  real_T yts[4], real_T xtf[4], real_T ytf[4], real_T cs[4], real_T cf[4],
  real_T lt[4], real_T l[4], real_T pos[4], real_T pof[4], real_T *r, real_T
  m_data[], int32_T *m_size, real_T n_data[], int32_T *n_size,
  B_VehicleFormationFormAssembl_T *localB)
{
  real_T lt_tmp;
  int32_T idx;
  int32_T ii;
  int32_T jj;
  int8_T j_data[4];
  boolean_T exitg1;
  *r = v * v / 9.81 / std::tan(PhiMaximum->contents / rad2deg->contents);
  localB->l_best = psi_s / rad2deg->contents;
  localB->pos_tmp = std::cos(localB->l_best) * *r;
  pos[0] = localB->pos_tmp + xs;
  localB->l_best = std::sin(localB->l_best) * *r;
  pos[2] = ys - localB->l_best;
  pos[1] = xs - localB->pos_tmp;
  pos[3] = localB->l_best + ys;
  localB->l_best = psi_f / rad2deg->contents;
  localB->pos_tmp = std::cos(localB->l_best) * *r;
  pof[0] = localB->pos_tmp + xf;
  localB->l_best = std::sin(localB->l_best) * *r;
  pof[2] = yf - localB->l_best;
  pof[1] = xf - localB->pos_tmp;
  pof[3] = localB->l_best + yf;
  localB->pos_tmp = Formation_FMS_atan3(pof[0], pof[2], pos[0], pos[2]);
  localB->xts_tmp = *r * std::sin(localB->pos_tmp);
  localB->l_best = pos[0] - localB->xts_tmp;
  localB->yts_tmp = *r * std::cos(localB->pos_tmp);
  localB->pos_tmp = localB->yts_tmp + pos[2];
  localB->xts_tmp = pof[0] - localB->xts_tmp;
  localB->yts_tmp += pof[2];
  localB->cs_tmp = xs - localB->l_best;
  localB->cs_tmp_m = ys - localB->pos_tmp;
  localB->cs_tmp = std::asin(std::sqrt(localB->cs_tmp * localB->cs_tmp +
    localB->cs_tmp_m * localB->cs_tmp_m) / 2.0 / *r) * (*r * 2.0);
  localB->cs_tmp_m = xf - localB->xts_tmp;
  localB->cf_tmp = yf - localB->yts_tmp;
  localB->cs_tmp_m = std::asin(std::sqrt(localB->cs_tmp_m * localB->cs_tmp_m +
    localB->cf_tmp * localB->cf_tmp) / 2.0 / *r) * (*r * 2.0);
  localB->cf_tmp = localB->xts_tmp - localB->l_best;
  lt_tmp = localB->yts_tmp - localB->pos_tmp;
  localB->cf_tmp = std::sqrt(localB->cf_tmp * localB->cf_tmp + lt_tmp * lt_tmp);
  l[0] = (localB->cs_tmp + localB->cs_tmp_m) + localB->cf_tmp;
  xts[0] = localB->l_best;
  yts[0] = localB->pos_tmp;
  xtf[0] = localB->xts_tmp;
  ytf[0] = localB->yts_tmp;
  cs[0] = localB->cs_tmp;
  cf[0] = localB->cs_tmp_m;
  lt[0] = localB->cf_tmp;
  localB->l_best = pof[3] - pos[2];
  localB->pos_tmp = pof[1] - pos[0];
  localB->pos_tmp = std::acos(*r * 2.0 / std::sqrt(localB->l_best *
    localB->l_best + localB->pos_tmp * localB->pos_tmp)) + Formation_FMS_atan3
    (pof[1], pof[3], pos[0], pos[2]);
  localB->xts_tmp = *r * std::cos(localB->pos_tmp);
  localB->l_best = localB->xts_tmp + pos[0];
  localB->yts_tmp = *r * std::sin(localB->pos_tmp);
  localB->pos_tmp = localB->yts_tmp + pos[2];
  localB->xts_tmp = pof[1] - localB->xts_tmp;
  localB->yts_tmp = pof[3] - localB->yts_tmp;
  localB->cs_tmp = xs - localB->l_best;
  localB->cs_tmp_m = ys - localB->pos_tmp;
  localB->cs_tmp = std::asin(std::sqrt(localB->cs_tmp * localB->cs_tmp +
    localB->cs_tmp_m * localB->cs_tmp_m) / 2.0 / *r) * (*r * 2.0);
  localB->cs_tmp_m = xf - localB->xts_tmp;
  localB->cf_tmp = yf - localB->yts_tmp;
  localB->cs_tmp_m = std::asin(std::sqrt(localB->cs_tmp_m * localB->cs_tmp_m +
    localB->cf_tmp * localB->cf_tmp) / 2.0 / *r) * (*r * 2.0);
  localB->cf_tmp = localB->xts_tmp - localB->l_best;
  lt_tmp = localB->yts_tmp - localB->pos_tmp;
  localB->cf_tmp = std::sqrt(localB->cf_tmp * localB->cf_tmp + lt_tmp * lt_tmp);
  l[2] = (localB->cs_tmp + localB->cs_tmp_m) + localB->cf_tmp;
  xts[2] = localB->l_best;
  yts[2] = localB->pos_tmp;
  xtf[2] = localB->xts_tmp;
  ytf[2] = localB->yts_tmp;
  cs[2] = localB->cs_tmp;
  cf[2] = localB->cs_tmp_m;
  lt[2] = localB->cf_tmp;
  localB->l_best = pof[2] - pos[3];
  localB->pos_tmp = pof[0] - pos[1];
  localB->pos_tmp = Formation_FMS_atan3(pof[0], pof[2], pos[1], pos[3]) - std::
    acos(*r * 2.0 / std::sqrt(localB->l_best * localB->l_best + localB->pos_tmp *
          localB->pos_tmp));
  localB->xts_tmp = *r * std::cos(localB->pos_tmp);
  localB->l_best = localB->xts_tmp + pos[1];
  localB->yts_tmp = *r * std::sin(localB->pos_tmp);
  localB->pos_tmp = localB->yts_tmp + pos[3];
  localB->xts_tmp = pof[0] - localB->xts_tmp;
  localB->yts_tmp = pof[2] - localB->yts_tmp;
  localB->cs_tmp = xs - localB->l_best;
  localB->cs_tmp_m = ys - localB->pos_tmp;
  localB->cs_tmp = std::asin(std::sqrt(localB->cs_tmp * localB->cs_tmp +
    localB->cs_tmp_m * localB->cs_tmp_m) / 2.0 / *r) * (*r * 2.0);
  localB->cs_tmp_m = xf - localB->xts_tmp;
  localB->cf_tmp = yf - localB->yts_tmp;
  localB->cs_tmp_m = std::asin(std::sqrt(localB->cs_tmp_m * localB->cs_tmp_m +
    localB->cf_tmp * localB->cf_tmp) / 2.0 / *r) * (*r * 2.0);
  localB->cf_tmp = localB->xts_tmp - localB->l_best;
  lt_tmp = localB->yts_tmp - localB->pos_tmp;
  localB->cf_tmp = std::sqrt(localB->cf_tmp * localB->cf_tmp + lt_tmp * lt_tmp);
  l[1] = (localB->cs_tmp + localB->cs_tmp_m) + localB->cf_tmp;
  xts[1] = localB->l_best;
  yts[1] = localB->pos_tmp;
  xtf[1] = localB->xts_tmp;
  ytf[1] = localB->yts_tmp;
  cs[1] = localB->cs_tmp;
  cf[1] = localB->cs_tmp_m;
  lt[1] = localB->cf_tmp;
  localB->pos_tmp = Formation_FMS_atan3(pof[1], pof[3], pos[1], pos[3]);
  localB->xts_tmp = *r * std::sin(localB->pos_tmp);
  localB->l_best = localB->xts_tmp + pos[1];
  localB->yts_tmp = *r * std::cos(localB->pos_tmp);
  localB->pos_tmp = pos[3] - localB->yts_tmp;
  localB->xts_tmp += pof[1];
  localB->yts_tmp = pof[3] - localB->yts_tmp;
  localB->cs_tmp = xs - localB->l_best;
  localB->cs_tmp_m = ys - localB->pos_tmp;
  localB->cs_tmp = std::asin(std::sqrt(localB->cs_tmp * localB->cs_tmp +
    localB->cs_tmp_m * localB->cs_tmp_m) / 2.0 / *r) * (*r * 2.0);
  localB->cs_tmp_m = xf - localB->xts_tmp;
  localB->cf_tmp = yf - localB->yts_tmp;
  localB->cs_tmp_m = std::asin(std::sqrt(localB->cs_tmp_m * localB->cs_tmp_m +
    localB->cf_tmp * localB->cf_tmp) / 2.0 / *r) * (*r * 2.0);
  localB->cf_tmp = localB->xts_tmp - localB->l_best;
  lt_tmp = localB->yts_tmp - localB->pos_tmp;
  localB->cf_tmp = std::sqrt(localB->cf_tmp * localB->cf_tmp + lt_tmp * lt_tmp);
  l[3] = (localB->cs_tmp + localB->cs_tmp_m) + localB->cf_tmp;
  xts[3] = localB->l_best;
  yts[3] = localB->pos_tmp;
  xtf[3] = localB->xts_tmp;
  ytf[3] = localB->yts_tmp;
  cs[3] = localB->cs_tmp;
  cf[3] = localB->cs_tmp_m;
  lt[3] = localB->cf_tmp;
  localB->l_best = (rtInf);
  if ((l[0] >= 0.0) && (l[0] < (rtInf))) {
    localB->l_best = l[0];
  }

  if ((l[1] >= 0.0) && (l[1] < localB->l_best)) {
    localB->l_best = l[1];
  }

  if ((l[2] >= 0.0) && (l[2] < localB->l_best)) {
    localB->l_best = l[2];
  }

  if ((l[3] >= 0.0) && (l[3] < localB->l_best)) {
    localB->l_best = l[3];
  }

  idx = -1;
  ii = 1;
  jj = 1;
  exitg1 = false;
  while ((!exitg1) && (jj <= 2)) {
    boolean_T guard1;
    guard1 = false;
    if (l[(((jj - 1) << 1) + ii) - 1] == localB->l_best) {
      idx++;
      localB->i_data[idx] = ii;
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
    m_data[ii] = localB->i_data[ii];
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

// Output and update for function-call system: '<S3>/Vehicle.Formation.FormAssemble.dubinsPath'
void Formation_FMS::VehicleFormationFormAssembledub(const Formation_Cross_Bus
  *rtu_Formation_Cross, Other_Mission_Data_Bus *rty_Other_Mission_Data,
  B_VehicleFormationFormAssembl_T *localB)
{
  static const real_T d[8]{ 1000.0, 100.0, 10.0, 1.0, 0.1, 0.01, 0.001, 0.0001 };

  int32_T b_size;
  int32_T c_size;
  int32_T i;
  int32_T target;

  // MATLAB Function: '<S83>/MATLAB Function'
  localB->PhiMaximum.contents = 40.0;
  localB->rad2deg.contents = 57.295779513082323;
  localB->obj.xs = 0.0;
  localB->obj.ys = 0.0;
  localB->obj.psi_s = 0.0;
  localB->obj.xf = 0.0;
  localB->obj.yf = 0.0;
  localB->obj.psi_f = 0.0;
  localB->obj.v = 0.0;
  localB->obj.r = 0.0;
  localB->obj.pos[0] = 0.0;
  localB->obj.pof[0] = 0.0;
  localB->obj.xts[0] = 0.0;
  localB->obj.yts[0] = 0.0;
  localB->obj.xtf[0] = 0.0;
  localB->obj.ytf[0] = 0.0;
  localB->obj.cs[0] = 0.0;
  localB->obj.cf[0] = 0.0;
  localB->obj.lt[0] = 0.0;
  localB->obj.l[0] = 0.0;
  localB->obj.pos[1] = 0.0;
  localB->obj.pof[1] = 0.0;
  localB->obj.xts[1] = 0.0;
  localB->obj.yts[1] = 0.0;
  localB->obj.xtf[1] = 0.0;
  localB->obj.ytf[1] = 0.0;
  localB->obj.cs[1] = 0.0;
  localB->obj.cf[1] = 0.0;
  localB->obj.lt[1] = 0.0;
  localB->obj.l[1] = 0.0;
  localB->obj.pos[2] = 0.0;
  localB->obj.pof[2] = 0.0;
  localB->obj.xts[2] = 0.0;
  localB->obj.yts[2] = 0.0;
  localB->obj.xtf[2] = 0.0;
  localB->obj.ytf[2] = 0.0;
  localB->obj.cs[2] = 0.0;
  localB->obj.cf[2] = 0.0;
  localB->obj.lt[2] = 0.0;
  localB->obj.l[2] = 0.0;
  localB->obj.pos[3] = 0.0;
  localB->obj.pof[3] = 0.0;
  localB->obj.xts[3] = 0.0;
  localB->obj.yts[3] = 0.0;
  localB->obj.xtf[3] = 0.0;
  localB->obj.ytf[3] = 0.0;
  localB->obj.cs[3] = 0.0;
  localB->obj.cf[3] = 0.0;
  localB->obj.lt[3] = 0.0;
  localB->obj.l[3] = 0.0;
  localB->obj.index_dubins[0] = 0.0;
  localB->obj.index_dubins[1] = 0.0;
  localB->obj.l_ad = 0.0;
  localB->obj.precision_flag = 0.0;
  localB->obj.xm = 0.0;
  localB->obj.ym = 0.0;
  localB->object[0] = localB->obj;
  localB->object[1] = localB->obj;
  localB->object[2] = localB->obj;
  localB->object[0].xs = rtu_Formation_Cross->x_R[0];
  localB->object[0].ys = rtu_Formation_Cross->y_R[0];
  localB->object[0].psi_s = rtu_Formation_Cross->psi[0];
  localB->object[0].xf = 0.0;
  localB->object[0].yf = 1000.0;
  localB->object[0].psi_f = 0.0;
  localB->object[0].v = 25.0;
  localB->object[1].xs = rtu_Formation_Cross->x_R[1];
  localB->object[1].ys = rtu_Formation_Cross->y_R[1];
  localB->object[1].psi_s = rtu_Formation_Cross->psi[1];
  localB->object[1].xf = 50.0;
  localB->object[1].yf = 1000.0;
  localB->object[1].psi_f = 0.0;
  localB->object[1].v = 25.0;
  localB->object[2].xs = rtu_Formation_Cross->x_R[2];
  localB->object[2].ys = rtu_Formation_Cross->y_R[2];
  localB->object[2].psi_s = rtu_Formation_Cross->psi[2];
  localB->object[2].xf = -50.0;
  localB->object[2].yf = 1000.0;
  localB->object[2].psi_f = 0.0;
  localB->object[2].v = 25.0;
  target = -1;
  localB->l_ref = -1.0;
  localB->obj = localB->object[0];
  Formation_FMS_Dubins(&localB->PhiMaximum, &localB->rad2deg, static_cast<real_T>
                       (rtu_Formation_Cross->x_R[0]), static_cast<real_T>
                       (rtu_Formation_Cross->y_R[0]), static_cast<real_T>
                       (rtu_Formation_Cross->psi[0]), 0.0, 1000.0, 0.0, 25.0,
                       localB->obj.xts, localB->obj.yts, localB->obj.xtf,
                       localB->obj.ytf, localB->obj.cs, localB->obj.cf,
                       localB->obj.lt, localB->obj.l, localB->obj.pos,
                       localB->obj.pof, &localB->obj.r, localB->b_data, &b_size,
                       localB->c_data, &c_size, localB);
  localB->obj.index_dubins[0] = localB->b_data[0];
  localB->obj.index_dubins[1] = localB->c_data[0];
  localB->search_floor = localB->obj.l[(((static_cast<int32_T>(localB->c_data[0])
    - 1) << 1) + static_cast<int32_T>(localB->b_data[0])) - 1];
  if (localB->search_floor > -1.0) {
    localB->l_ref = localB->search_floor;
    target = 1;
  }

  localB->object[0] = localB->obj;
  localB->obj = localB->object[1];
  Formation_FMS_Dubins(&localB->PhiMaximum, &localB->rad2deg, static_cast<real_T>
                       (rtu_Formation_Cross->x_R[1]), static_cast<real_T>
                       (rtu_Formation_Cross->y_R[1]), static_cast<real_T>
                       (rtu_Formation_Cross->psi[1]), 50.0, 1000.0, 0.0, 25.0,
                       localB->obj.xts, localB->obj.yts, localB->obj.xtf,
                       localB->obj.ytf, localB->obj.cs, localB->obj.cf,
                       localB->obj.lt, localB->obj.l, localB->obj.pos,
                       localB->obj.pof, &localB->obj.r, localB->b_data, &b_size,
                       localB->c_data, &c_size, localB);
  localB->obj.index_dubins[0] = localB->b_data[0];
  localB->obj.index_dubins[1] = localB->c_data[0];
  localB->search_floor = localB->obj.l[(((static_cast<int32_T>(localB->c_data[0])
    - 1) << 1) + static_cast<int32_T>(localB->b_data[0])) - 1];
  if (localB->search_floor > localB->l_ref) {
    localB->l_ref = localB->search_floor;
    target = 2;
  }

  localB->object[1] = localB->obj;
  localB->obj = localB->object[2];
  Formation_FMS_Dubins(&localB->PhiMaximum, &localB->rad2deg, static_cast<real_T>
                       (rtu_Formation_Cross->x_R[2]), static_cast<real_T>
                       (rtu_Formation_Cross->y_R[2]), static_cast<real_T>
                       (rtu_Formation_Cross->psi[2]), -50.0, 1000.0, 0.0, 25.0,
                       localB->obj.xts, localB->obj.yts, localB->obj.xtf,
                       localB->obj.ytf, localB->obj.cs, localB->obj.cf,
                       localB->obj.lt, localB->obj.l, localB->obj.pos,
                       localB->obj.pof, &localB->obj.r, localB->b_data, &b_size,
                       localB->c_data, &c_size, localB);
  localB->obj.index_dubins[0] = localB->b_data[0];
  localB->obj.index_dubins[1] = localB->c_data[0];
  localB->search_floor = localB->obj.l[(((static_cast<int32_T>(localB->c_data[0])
    - 1) << 1) + static_cast<int32_T>(localB->b_data[0])) - 1];
  if (localB->search_floor > localB->l_ref) {
    localB->l_ref = localB->search_floor;
    target = 3;
  }

  localB->object[2] = localB->obj;
  for (i = 0; i < 3; i++) {
    if (i + 1 != target) {
      int32_T stop_flag;
      localB->search_floor = 0.0;
      localB->search = 0.0;
      stop_flag = 1;
      for (int32_T j{0}; j < 7; j++) {
        boolean_T exitg1;
        exitg1 = false;
        while ((!exitg1) && (stop_flag != 0)) {
          localB->search += d[j];
          localB->object[i].xm = localB->object[i].xf - localB->search * 0.0;
          localB->object[i].ym = localB->object[i].yf - localB->search;
          Formation_FMS_Dubins(&localB->PhiMaximum, &localB->rad2deg,
                               localB->object[i].xs, localB->object[i].ys,
                               localB->object[i].psi_s, localB->object[i].xm,
                               localB->object[i].ym, 0.0, localB->object[i].v,
                               localB->object[i].xts, localB->object[i].yts,
                               localB->object[i].xtf, localB->object[i].ytf,
                               localB->object[i].cs, localB->object[i].cf,
                               localB->object[i].lt, localB->object[i].l,
                               localB->object[i].pos, localB->object[i].pof,
                               &localB->goal, localB->b_data, &b_size,
                               localB->c_data, &c_size, localB);
          localB->object[i].index_dubins[0] = localB->b_data[0];
          localB->object[i].index_dubins[1] = localB->c_data[0];
          localB->goal = (localB->object[i].l[(((static_cast<int32_T>
            (localB->object[i].index_dubins[1]) - 1) << 1) + static_cast<int32_T>
            (localB->object[i].index_dubins[0])) - 1] + localB->search) -
            localB->l_ref;
          if (localB->goal > 0.0) {
            localB->object[i].l_ad = localB->search_floor;
            localB->object[i].precision_flag = d[j];
            localB->search = localB->search_floor;
            exitg1 = true;
          } else if (localB->goal < 0.0) {
            localB->search_floor = localB->search;
          } else {
            localB->object[i].l_ad = localB->search;
            localB->object[i].precision_flag = 0.0;
            stop_flag = 0;
          }
        }
      }
    } else {
      localB->object[i].xm = localB->object[i].xf;
      localB->object[i].ym = localB->object[i].yf;
    }
  }

  rty_Other_Mission_Data->timestamp = 9999U;
  if (target == 1) {
    localB->result[0] = localB->object[0].xs;
    localB->result[15] = localB->object[0].ys;
    localB->result[30] = localB->object[0].psi_s;
    localB->result[45] = localB->object[0].r;
    i = (((static_cast<int32_T>(localB->object[0].index_dubins[1]) - 1) << 1) +
         static_cast<int32_T>(localB->object[0].index_dubins[0])) - 1;
    localB->result[60] = localB->object[0].cs[i];
    localB->result[3] = localB->object[0].xts[i];
    localB->result[18] = localB->object[0].yts[i];
    localB->l_ref = Formation_FMS_atan3(localB->object[0].xtf[i], localB->
      object[0].ytf[i], localB->object[0].xts[i], localB->object[0].yts[i]) *
      57.295779513082323;
    localB->result[33] = localB->l_ref;
    localB->result[48] = 0.0;
    localB->result[63] = localB->object[0].lt[i];
    localB->result[6] = localB->object[0].xtf[i];
    localB->result[21] = localB->object[0].ytf[i];
    localB->result[36] = localB->l_ref;
    localB->result[51] = localB->object[0].r;
    localB->result[66] = localB->object[0].cf[i];
    localB->result[9] = localB->object[0].xm;
    localB->result[24] = localB->object[0].ym;
    localB->result[39] = 0.0;
    localB->result[54] = 0.0;
    localB->result[69] = 0.0;
    localB->result[12] = localB->object[0].xf;
    localB->result[27] = localB->object[0].yf;
    localB->result[42] = 0.0;
    localB->result[57] = 0.0;
    localB->result[72] = localB->object[0].l[i];
  } else {
    localB->result[0] = localB->object[0].xs;
    localB->result[15] = localB->object[0].ys;
    localB->result[30] = localB->object[0].psi_s;
    localB->result[45] = localB->object[0].r;
    i = (((static_cast<int32_T>(localB->object[0].index_dubins[1]) - 1) << 1) +
         static_cast<int32_T>(localB->object[0].index_dubins[0])) - 1;
    localB->result[60] = localB->object[0].cs[i];
    localB->l_ref = localB->object[0].xts[i];
    localB->result[3] = localB->l_ref;
    localB->search_floor = localB->object[0].yts[i];
    localB->result[18] = localB->search_floor;
    localB->search = localB->object[0].xtf[i];
    localB->goal = localB->object[0].ytf[i];
    localB->l_ref = Formation_FMS_atan3(localB->search, localB->goal,
      localB->l_ref, localB->search_floor) * 57.295779513082323;
    localB->result[33] = localB->l_ref;
    localB->result[48] = 0.0;
    localB->result[63] = localB->object[0].lt[i];
    localB->result[6] = localB->search;
    localB->result[21] = localB->goal;
    localB->result[36] = localB->l_ref;
    localB->result[51] = localB->object[0].r;
    localB->result[66] = localB->object[0].cf[i];
    localB->result[9] = localB->object[0].xm;
    localB->result[24] = localB->object[0].ym;
    localB->result[39] = 0.0;
    localB->result[54] = 0.0;
    localB->result[69] = localB->object[0].l_ad;
    localB->result[12] = localB->object[0].xf;
    localB->result[27] = localB->object[0].yf;
    localB->result[42] = 0.0;
    localB->result[57] = 0.0;
    localB->result[72] = localB->object[0].l[i] + localB->object[0].l_ad;
  }

  rty_Other_Mission_Data->type[0] = 1U;
  rty_Other_Mission_Data->valid_items[0] = 5U;
  if (target == 2) {
    localB->result[1] = localB->object[1].xs;
    localB->result[16] = localB->object[1].ys;
    localB->result[31] = localB->object[1].psi_s;
    localB->result[46] = localB->object[1].r;
    i = (((static_cast<int32_T>(localB->object[1].index_dubins[1]) - 1) << 1) +
         static_cast<int32_T>(localB->object[1].index_dubins[0])) - 1;
    localB->result[61] = localB->object[1].cs[i];
    localB->result[4] = localB->object[1].xts[i];
    localB->result[19] = localB->object[1].yts[i];
    localB->l_ref = Formation_FMS_atan3(localB->object[1].xtf[i], localB->
      object[1].ytf[i], localB->object[1].xts[i], localB->object[1].yts[i]) *
      57.295779513082323;
    localB->result[34] = localB->l_ref;
    localB->result[49] = 0.0;
    localB->result[64] = localB->object[1].lt[i];
    localB->result[7] = localB->object[1].xtf[i];
    localB->result[22] = localB->object[1].ytf[i];
    localB->result[37] = localB->l_ref;
    localB->result[52] = localB->object[1].r;
    localB->result[67] = localB->object[1].cf[i];
    localB->result[10] = localB->object[1].xm;
    localB->result[25] = localB->object[1].ym;
    localB->result[40] = 0.0;
    localB->result[55] = 0.0;
    localB->result[70] = 0.0;
    localB->result[13] = localB->object[1].xf;
    localB->result[28] = localB->object[1].yf;
    localB->result[43] = 0.0;
    localB->result[58] = 0.0;
    localB->result[73] = localB->object[1].l[i];
  } else {
    localB->result[1] = localB->object[1].xs;
    localB->result[16] = localB->object[1].ys;
    localB->result[31] = localB->object[1].psi_s;
    localB->result[46] = localB->object[1].r;
    i = (((static_cast<int32_T>(localB->object[1].index_dubins[1]) - 1) << 1) +
         static_cast<int32_T>(localB->object[1].index_dubins[0])) - 1;
    localB->result[61] = localB->object[1].cs[i];
    localB->l_ref = localB->object[1].xts[i];
    localB->result[4] = localB->l_ref;
    localB->search_floor = localB->object[1].yts[i];
    localB->result[19] = localB->search_floor;
    localB->search = localB->object[1].xtf[i];
    localB->goal = localB->object[1].ytf[i];
    localB->l_ref = Formation_FMS_atan3(localB->search, localB->goal,
      localB->l_ref, localB->search_floor) * 57.295779513082323;
    localB->result[34] = localB->l_ref;
    localB->result[49] = 0.0;
    localB->result[64] = localB->object[1].lt[i];
    localB->result[7] = localB->search;
    localB->result[22] = localB->goal;
    localB->result[37] = localB->l_ref;
    localB->result[52] = localB->object[1].r;
    localB->result[67] = localB->object[1].cf[i];
    localB->result[10] = localB->object[1].xm;
    localB->result[25] = localB->object[1].ym;
    localB->result[40] = 0.0;
    localB->result[55] = 0.0;
    localB->result[70] = localB->object[1].l_ad;
    localB->result[13] = localB->object[1].xf;
    localB->result[28] = localB->object[1].yf;
    localB->result[43] = 0.0;
    localB->result[58] = 0.0;
    localB->result[73] = localB->object[1].l[i] + localB->object[1].l_ad;
  }

  rty_Other_Mission_Data->type[1] = 1U;
  rty_Other_Mission_Data->valid_items[1] = 5U;
  if (target == 3) {
    localB->result[2] = localB->object[2].xs;
    localB->result[17] = localB->object[2].ys;
    localB->result[32] = localB->object[2].psi_s;
    localB->result[47] = localB->object[2].r;
    i = (((static_cast<int32_T>(localB->object[2].index_dubins[1]) - 1) << 1) +
         static_cast<int32_T>(localB->object[2].index_dubins[0])) - 1;
    localB->result[62] = localB->object[2].cs[i];
    localB->result[5] = localB->object[2].xts[i];
    localB->result[20] = localB->object[2].yts[i];
    localB->l_ref = Formation_FMS_atan3(localB->object[2].xtf[i], localB->
      object[2].ytf[i], localB->object[2].xts[i], localB->object[2].yts[i]) *
      57.295779513082323;
    localB->result[35] = localB->l_ref;
    localB->result[50] = 0.0;
    localB->result[65] = localB->object[2].lt[i];
    localB->result[8] = localB->object[2].xtf[i];
    localB->result[23] = localB->object[2].ytf[i];
    localB->result[38] = localB->l_ref;
    localB->result[53] = localB->object[2].r;
    localB->result[68] = localB->object[2].cf[i];
    localB->result[11] = localB->object[2].xm;
    localB->result[26] = localB->object[2].ym;
    localB->result[41] = 0.0;
    localB->result[56] = 0.0;
    localB->result[71] = 0.0;
    localB->result[14] = localB->object[2].xf;
    localB->result[29] = localB->object[2].yf;
    localB->result[44] = 0.0;
    localB->result[59] = 0.0;
    localB->result[74] = localB->object[2].l[i];
  } else {
    localB->result[2] = localB->object[2].xs;
    localB->result[17] = localB->object[2].ys;
    localB->result[32] = localB->object[2].psi_s;
    localB->result[47] = localB->object[2].r;
    i = (((static_cast<int32_T>(localB->object[2].index_dubins[1]) - 1) << 1) +
         static_cast<int32_T>(localB->object[2].index_dubins[0])) - 1;
    localB->result[62] = localB->object[2].cs[i];
    localB->l_ref = localB->object[2].xts[i];
    localB->result[5] = localB->l_ref;
    localB->search_floor = localB->object[2].yts[i];
    localB->result[20] = localB->search_floor;
    localB->search = localB->object[2].xtf[i];
    localB->goal = localB->object[2].ytf[i];
    localB->l_ref = Formation_FMS_atan3(localB->search, localB->goal,
      localB->l_ref, localB->search_floor) * 57.295779513082323;
    localB->result[35] = localB->l_ref;
    localB->result[50] = 0.0;
    localB->result[65] = localB->object[2].lt[i];
    localB->result[8] = localB->search;
    localB->result[23] = localB->goal;
    localB->result[38] = localB->l_ref;
    localB->result[53] = localB->object[2].r;
    localB->result[68] = localB->object[2].cf[i];
    localB->result[11] = localB->object[2].xm;
    localB->result[26] = localB->object[2].ym;
    localB->result[41] = 0.0;
    localB->result[56] = 0.0;
    localB->result[71] = localB->object[2].l_ad;
    localB->result[14] = localB->object[2].xf;
    localB->result[29] = localB->object[2].yf;
    localB->result[44] = 0.0;
    localB->result[59] = 0.0;
    localB->result[74] = localB->object[2].l[i] + localB->object[2].l_ad;
  }

  rty_Other_Mission_Data->type[2] = 1U;
  rty_Other_Mission_Data->valid_items[2] = 5U;
  std::memset(&rty_Other_Mission_Data->x[0], 0, 24U * sizeof(real32_T));
  std::memset(&rty_Other_Mission_Data->y[0], 0, 24U * sizeof(real32_T));
  std::memset(&rty_Other_Mission_Data->z[0], 0, 24U * sizeof(real32_T));
  std::memset(&rty_Other_Mission_Data->heading[0], 0, 24U * sizeof(real32_T));
  std::memset(&rty_Other_Mission_Data->ext1[0], 0, 24U * sizeof(real32_T));
  std::memset(&rty_Other_Mission_Data->ext2[0], 0, 24U * sizeof(real32_T));
  for (i = 0; i < 3; i++) {
    for (int32_T j{0}; j < 5; j++) {
      target = 3 * j + i;
      rty_Other_Mission_Data->x[target] = static_cast<real32_T>(localB->
        result[target]);
      rty_Other_Mission_Data->y[target] = static_cast<real32_T>(localB->
        result[target + 15]);
      rty_Other_Mission_Data->z[target] = rtu_Formation_Cross->h_R[i];
      rty_Other_Mission_Data->heading[target] = static_cast<real32_T>
        (localB->result[target + 30]);
      rty_Other_Mission_Data->ext1[target] = static_cast<real32_T>
        (localB->result[target + 45]);
      rty_Other_Mission_Data->ext2[target] = static_cast<real32_T>
        (localB->result[target + 60]);
    }
  }

  // End of MATLAB Function: '<S83>/MATLAB Function'
}

// Function for MATLAB Function: '<S84>/Dubins Closest Point'
real32_T Formation_FMS::Formation_FMS_norm(const real32_T x[2])
{
  real32_T y;
  Formation_FMS_B.scale_c = 1.29246971E-26F;
  Formation_FMS_B.absxk_b = std::abs(x[0]);
  if (Formation_FMS_B.absxk_b > 1.29246971E-26F) {
    y = 1.0F;
    Formation_FMS_B.scale_c = Formation_FMS_B.absxk_b;
  } else {
    Formation_FMS_B.t_p = Formation_FMS_B.absxk_b / 1.29246971E-26F;
    y = Formation_FMS_B.t_p * Formation_FMS_B.t_p;
  }

  Formation_FMS_B.absxk_b = std::abs(x[1]);
  if (Formation_FMS_B.absxk_b > Formation_FMS_B.scale_c) {
    Formation_FMS_B.t_p = Formation_FMS_B.scale_c / Formation_FMS_B.absxk_b;
    y = y * Formation_FMS_B.t_p * Formation_FMS_B.t_p + 1.0F;
    Formation_FMS_B.scale_c = Formation_FMS_B.absxk_b;
  } else {
    Formation_FMS_B.t_p = Formation_FMS_B.absxk_b / Formation_FMS_B.scale_c;
    y += Formation_FMS_B.t_p * Formation_FMS_B.t_p;
  }

  return Formation_FMS_B.scale_c * std::sqrt(y);
}

real32_T Formation_FMS::Formation_FMS_rt_atan2f_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaNF);
  } else if (std::isinf(u0) && std::isinf(u1)) {
    if (u0 > 0.0F) {
      Formation_FMS_B.i_c = 1;
    } else {
      Formation_FMS_B.i_c = -1;
    }

    if (u1 > 0.0F) {
      Formation_FMS_B.i1 = 1;
    } else {
      Formation_FMS_B.i1 = -1;
    }

    y = std::atan2(static_cast<real32_T>(Formation_FMS_B.i_c),
                   static_cast<real32_T>(Formation_FMS_B.i1));
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = std::atan2(u0, u1);
  }

  return y;
}

// Function for MATLAB Function: '<S84>/Dubins Closest Point'
real32_T Formation_FMS::Formation_FMS_mod(real32_T x)
{
  real32_T r;
  if (std::isnan(x)) {
    r = (rtNaNF);
  } else if (std::isinf(x)) {
    r = (rtNaNF);
  } else if (x == 0.0F) {
    r = 0.0F;
  } else {
    r = std::fmod(x, 6.28318548F);
    Formation_FMS_B.rEQ0 = (r == 0.0F);
    if (!Formation_FMS_B.rEQ0) {
      Formation_FMS_B.q = std::abs(x / 6.28318548F);
      Formation_FMS_B.rEQ0 = !(std::abs(Formation_FMS_B.q - std::floor
        (Formation_FMS_B.q + 0.5F)) > 1.1920929E-7F * Formation_FMS_B.q);
    }

    if (Formation_FMS_B.rEQ0) {
      r = 0.0F;
    } else if (x < 0.0F) {
      r += 6.28318548F;
    }
  }

  return r;
}

// Function for MATLAB Function: '<S84>/Dubins Closest Point'
void Formation_FMS::Formati_getMinDistanceAtSegment(const real32_T waypoints[25],
  const real32_T pose[3], uint16_T segment, real32_T *dist, real32_T *ratio)
{
  if (segment >= 5) {
    *dist = (rtInfF);
    *ratio = 0.0F;
  } else {
    Formation_FMS_B.unit_point_to_next_tmp = waypoints[segment - 1];
    Formation_FMS_B.unit_point_to_next_tmp_k = waypoints[segment];
    Formation_FMS_B.unit_point_to_next[0] =
      Formation_FMS_B.unit_point_to_next_tmp_k -
      Formation_FMS_B.unit_point_to_next_tmp;
    Formation_FMS_B.unit_centre_to_pose_idx_0 = waypoints[segment + 4];
    Formation_FMS_B.dotProduct = waypoints[segment + 5];
    Formation_FMS_B.unit_point_to_next[1] = Formation_FMS_B.dotProduct -
      Formation_FMS_B.unit_centre_to_pose_idx_0;
    Formation_FMS_B.nearest_cross = Formation_FMS_norm
      (Formation_FMS_B.unit_point_to_next);
    Formation_FMS_B.project_line = waypoints[segment + 9];
    Formation_FMS_B.nearest_cross_tmp = std::cos(Formation_FMS_B.project_line);
    Formation_FMS_B.nearest_cross_tmp_c = std::sin(Formation_FMS_B.project_line);
    Formation_FMS_B.nearest_cross = Formation_FMS_B.unit_point_to_next[1] /
      Formation_FMS_B.nearest_cross * Formation_FMS_B.nearest_cross_tmp -
      Formation_FMS_B.unit_point_to_next[0] / Formation_FMS_B.nearest_cross *
      Formation_FMS_B.nearest_cross_tmp_c;
    if (std::abs(Formation_FMS_B.nearest_cross) < 0.017452406437283512) {
      Formation_FMS_B.nearest_cross = pose[0] -
        Formation_FMS_B.unit_point_to_next_tmp;
      Formation_FMS_B.project_line = Formation_FMS_B.nearest_cross *
        Formation_FMS_B.nearest_cross_tmp;
      Formation_FMS_B.unit_point_to_next[0] = Formation_FMS_B.nearest_cross;
      Formation_FMS_B.nearest_cross = pose[1] -
        Formation_FMS_B.unit_centre_to_pose_idx_0;
      Formation_FMS_B.project_line += Formation_FMS_B.nearest_cross *
        Formation_FMS_B.nearest_cross_tmp_c;
      Formation_FMS_B.unit_point_to_next[0] -= Formation_FMS_B.project_line *
        Formation_FMS_B.nearest_cross_tmp;
      Formation_FMS_B.unit_point_to_next[1] = Formation_FMS_B.nearest_cross -
        Formation_FMS_B.project_line * Formation_FMS_B.nearest_cross_tmp_c;
      *dist = Formation_FMS_norm(Formation_FMS_B.unit_point_to_next);
      Formation_FMS_B.unit_point_to_next[0] =
        Formation_FMS_B.unit_point_to_next_tmp -
        Formation_FMS_B.unit_point_to_next_tmp_k;
      Formation_FMS_B.unit_point_to_next[1] =
        Formation_FMS_B.unit_centre_to_pose_idx_0 - Formation_FMS_B.dotProduct;
      *ratio = Formation_FMS_B.project_line / Formation_FMS_norm
        (Formation_FMS_B.unit_point_to_next);
    } else if (Formation_FMS_B.nearest_cross > 0.017452406437283512) {
      Formation_FMS_B.unit_point_to_next_tmp_k = waypoints[segment + 14];
      Formation_FMS_B.unit_point_to_next[0] = pose[0] -
        (Formation_FMS_B.unit_point_to_next_tmp_k *
         -Formation_FMS_B.nearest_cross_tmp_c +
         Formation_FMS_B.unit_point_to_next_tmp);
      Formation_FMS_B.unit_point_to_next[1] = pose[1] -
        (Formation_FMS_B.unit_point_to_next_tmp_k *
         Formation_FMS_B.nearest_cross_tmp +
         Formation_FMS_B.unit_centre_to_pose_idx_0);
      Formation_FMS_B.nearest_cross = Formation_FMS_norm
        (Formation_FMS_B.unit_point_to_next);
      Formation_FMS_B.unit_point_to_next_tmp =
        Formation_FMS_B.unit_point_to_next[0] / Formation_FMS_B.nearest_cross;
      Formation_FMS_B.dotProduct = Formation_FMS_B.nearest_cross_tmp_c *
        Formation_FMS_B.unit_point_to_next_tmp;
      Formation_FMS_B.unit_centre_to_pose_idx_0 =
        Formation_FMS_B.unit_point_to_next_tmp;
      Formation_FMS_B.unit_point_to_next_tmp =
        Formation_FMS_B.unit_point_to_next[1] / Formation_FMS_B.nearest_cross;
      Formation_FMS_B.dotProduct = Formation_FMS_rt_atan2f_snf
        (Formation_FMS_B.nearest_cross_tmp_c *
         Formation_FMS_B.unit_point_to_next_tmp -
         Formation_FMS_B.unit_centre_to_pose_idx_0 *
         -Formation_FMS_B.nearest_cross_tmp, -Formation_FMS_B.nearest_cross_tmp *
         Formation_FMS_B.unit_point_to_next_tmp + Formation_FMS_B.dotProduct);
      if (Formation_FMS_B.dotProduct < 0.0F) {
        Formation_FMS_B.dotProduct += ((0.0F - Formation_FMS_B.dotProduct) /
          6.28318548F + 1.0F) * 6.28318548F;
      }

      *dist = Formation_FMS_B.nearest_cross -
        Formation_FMS_B.unit_point_to_next_tmp_k;
      Formation_FMS_B.unit_point_to_next_tmp_k = waypoints[segment + 10];
      Formation_FMS_B.project_line = (Formation_FMS_B.unit_point_to_next_tmp_k +
        6.28318548F) - Formation_FMS_B.project_line;
      if (Formation_FMS_B.project_line < 0.0F) {
        Formation_FMS_B.project_line += ((0.0F - Formation_FMS_B.project_line) /
          6.28318548F + 1.0F) * 6.28318548F;
      }

      *ratio = Formation_FMS_mod(Formation_FMS_B.dotProduct) / Formation_FMS_mod
        (Formation_FMS_B.project_line);
      if (*ratio > 1.0F) {
        Formation_FMS_B.unit_point_to_next[0] =
          Formation_FMS_B.unit_centre_to_pose_idx_0 -
          Formation_FMS_B.nearest_cross_tmp_c;
        Formation_FMS_B.unit_point_to_next[1] =
          Formation_FMS_B.unit_point_to_next_tmp +
          Formation_FMS_B.nearest_cross_tmp;
        Formation_FMS_B.unit_centre_to_pose[0] = -std::sin
          (Formation_FMS_B.unit_point_to_next_tmp_k) +
          Formation_FMS_B.unit_centre_to_pose_idx_0;
        Formation_FMS_B.unit_centre_to_pose[1] = std::cos
          (Formation_FMS_B.unit_point_to_next_tmp_k) +
          Formation_FMS_B.unit_point_to_next_tmp;
        *ratio = static_cast<real32_T>(!(Formation_FMS_norm
          (Formation_FMS_B.unit_point_to_next) < Formation_FMS_norm
          (Formation_FMS_B.unit_centre_to_pose)));
      }
    } else {
      Formation_FMS_B.unit_point_to_next_tmp_k = waypoints[segment + 14];
      Formation_FMS_B.unit_point_to_next[0] = pose[0] -
        (Formation_FMS_B.unit_point_to_next_tmp_k *
         Formation_FMS_B.nearest_cross_tmp_c +
         Formation_FMS_B.unit_point_to_next_tmp);
      Formation_FMS_B.unit_point_to_next[1] = pose[1] -
        (Formation_FMS_B.unit_point_to_next_tmp_k *
         -Formation_FMS_B.nearest_cross_tmp +
         Formation_FMS_B.unit_centre_to_pose_idx_0);
      Formation_FMS_B.nearest_cross = Formation_FMS_norm
        (Formation_FMS_B.unit_point_to_next);
      Formation_FMS_B.unit_point_to_next_tmp =
        Formation_FMS_B.unit_point_to_next[0] / Formation_FMS_B.nearest_cross;
      Formation_FMS_B.dotProduct = Formation_FMS_B.unit_point_to_next_tmp *
        -Formation_FMS_B.nearest_cross_tmp_c;
      Formation_FMS_B.unit_centre_to_pose_idx_0 =
        Formation_FMS_B.unit_point_to_next_tmp;
      Formation_FMS_B.unit_point_to_next_tmp =
        Formation_FMS_B.unit_point_to_next[1] / Formation_FMS_B.nearest_cross;
      Formation_FMS_B.dotProduct = Formation_FMS_rt_atan2f_snf
        (Formation_FMS_B.unit_centre_to_pose_idx_0 *
         Formation_FMS_B.nearest_cross_tmp -
         -Formation_FMS_B.nearest_cross_tmp_c *
         Formation_FMS_B.unit_point_to_next_tmp,
         Formation_FMS_B.unit_point_to_next_tmp *
         Formation_FMS_B.nearest_cross_tmp + Formation_FMS_B.dotProduct);
      if (Formation_FMS_B.dotProduct < 0.0F) {
        Formation_FMS_B.dotProduct += ((0.0F - Formation_FMS_B.dotProduct) /
          6.28318548F + 1.0F) * 6.28318548F;
      }

      *dist = Formation_FMS_B.nearest_cross -
        Formation_FMS_B.unit_point_to_next_tmp_k;
      Formation_FMS_B.unit_point_to_next_tmp_k = waypoints[segment + 10];
      Formation_FMS_B.project_line += 6.28318548F -
        Formation_FMS_B.unit_point_to_next_tmp_k;
      if (Formation_FMS_B.project_line < 0.0F) {
        Formation_FMS_B.project_line += ((0.0F - Formation_FMS_B.project_line) /
          6.28318548F + 1.0F) * 6.28318548F;
      }

      *ratio = Formation_FMS_mod(Formation_FMS_B.dotProduct) / Formation_FMS_mod
        (Formation_FMS_B.project_line);
      if (*ratio > 1.0F) {
        Formation_FMS_B.unit_point_to_next[0] =
          Formation_FMS_B.unit_centre_to_pose_idx_0 +
          Formation_FMS_B.nearest_cross_tmp_c;
        Formation_FMS_B.unit_point_to_next[1] =
          Formation_FMS_B.unit_point_to_next_tmp -
          Formation_FMS_B.nearest_cross_tmp;
        Formation_FMS_B.unit_centre_to_pose[0] = std::sin
          (Formation_FMS_B.unit_point_to_next_tmp_k) +
          Formation_FMS_B.unit_centre_to_pose_idx_0;
        Formation_FMS_B.unit_centre_to_pose[1] = -std::cos
          (Formation_FMS_B.unit_point_to_next_tmp_k) +
          Formation_FMS_B.unit_point_to_next_tmp;
        *ratio = static_cast<real32_T>(!(Formation_FMS_norm
          (Formation_FMS_B.unit_point_to_next) < Formation_FMS_norm
          (Formation_FMS_B.unit_centre_to_pose)));
      }
    }
  }
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
    Formation_FMS_DW.is_Mission = Formation_FM_IN_NO_ACTIVE_CHILD;
    Formation_FMS_DW.is_Vehicle = Formation_FM_IN_NO_ACTIVE_CHILD;
  }
}

// Function for Chart: '<Root>/FMS State Machine'
void Formation_FMS::Formation_FMS_Vehicle(const INS_Out_Bus
  *BusConversion_InsertedFor_FMS_c, const Formation_Cross_Bus
  *BusConversion_InsertedFor_FMS_p, const Mission_Data_Bus
  *BusConversion_InsertedFor_FMSSt, const uint32_T *Mission_Data_timestamp_prev,
  const PilotMode *mode_prev, Formation_Cross_Bus *Formation_Cross_d)
{
  // Delay: '<S5>/Delay' incorporates:
  //   Constant: '<Root>/ACCEPT_R'
  //   MATLAB Function: '<S85>/MATLAB Function'
  //   Outport: '<Root>/Form_Single'
  //   Outport: '<Root>/Other_Mission_Data'
  //   SignalConversion generated from: '<S82>/Output'

  if ((*mode_prev != Formation_FMS_DW.mode_start) &&
      (Formation_FMS_DW.Delay_DSTATE_j != PilotMode::None)) {
    boolean_T exitg1;
    Formation_FMS_B.b_x[0] = (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::
      FormAssemble);
    Formation_FMS_B.b_x[1] = (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::
      FormDisband);
    Formation_FMS_B.c_y = false;
    Formation_FMS_B.i = 0;
    exitg1 = false;
    while ((!exitg1) && (Formation_FMS_B.i < 2)) {
      if (Formation_FMS_B.b_x[Formation_FMS_B.i]) {
        Formation_FMS_B.c_y = true;
        exitg1 = true;
      } else {
        Formation_FMS_B.i++;
      }
    }

    if (Formation_FMS_B.c_y) {
      Formation_exit_internal_Vehicle();
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Formation;
      if (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormAssemble) {
        Formation_FMS_DW.is_Formation = Formation_FMS_IN_FormAssemble;
        Formation_FMS_B.Cmd_In.sp_waypoint[0] =
          BusConversion_InsertedFor_FMS_c->x_R;
        Formation_FMS_B.Cmd_In.sp_waypoint[1] =
          BusConversion_InsertedFor_FMS_c->y_R;
        Formation_FMS_B.Cmd_In.sp_waypoint[2] =
          BusConversion_InsertedFor_FMS_c->h_R;
        *Formation_Cross_d = *BusConversion_InsertedFor_FMS_p;

        // Outputs for Function Call SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPath' 
        VehicleFormationFormAssembledub(Formation_Cross_d,
          &Formation_FMS_B.mission,
          &Formation_FMS_B.VehicleFormationFormAssembled_o);

        // End of Outputs for SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPath' 
        Formation_FMS_Y.Other_Mission_Data = Formation_FMS_B.mission;
        Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_WaitForUpdate;
        Formation_FMS_B.state = VehicleState::None;
      } else {
        Formation_FMS_DW.is_Formation = Formation_FMS_IN_InvalidMode;
      }
    } else if (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::Mission) {
      Formation_FMS_B.wp_index = 1U;
      Formation_FMS_B.Cmd_In.cur_waypoint[0] =
        BusConversion_InsertedFor_FMS_c->x_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[1] =
        BusConversion_InsertedFor_FMS_c->y_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[2] =
        BusConversion_InsertedFor_FMS_c->h_R;
      Formation_exit_internal_Vehicle();
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Mission;
      Formation_FMS_B.Cmd_In.sp_waypoint[0] =
        BusConversion_InsertedFor_FMS_c->x_R;
      Formation_FMS_B.Cmd_In.sp_waypoint[1] =
        BusConversion_InsertedFor_FMS_c->y_R;
      Formation_FMS_B.Cmd_In.sp_waypoint[2] =
        BusConversion_InsertedFor_FMS_c->h_R;
      Formation_FMS_DW.is_Mission = Formation_FMS_IN_NextWP_dp;
      Formation_FMS_B.state = VehicleState::None;
    } else {
      Formation_exit_internal_Vehicle();
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Standby;
      Formation_FMS_B.Cmd_In.cur_waypoint[0] =
        BusConversion_InsertedFor_FMS_c->x_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[1] =
        BusConversion_InsertedFor_FMS_c->y_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[2] =
        BusConversion_InsertedFor_FMS_c->h_R;
      Formation_FMS_B.state = VehicleState::Hold;
    }
  } else {
    switch (Formation_FMS_DW.is_Vehicle) {
     case Formation_FMS_IN_Formation:
      {
        // Outputs for Function Call SubSystem: '<S3>/Vehicle.Formation.check_form_valid' 
        // MATLAB Function: '<S85>/MATLAB Function'
        Formation_FMS_B.VehicleFormationFormAssembleWay = 0U;
        for (Formation_FMS_B.i = 0; Formation_FMS_B.i < 3; Formation_FMS_B.i++)
        {
          if (Formation_FMS_B.i + 1 != 1) {
            Formation_FMS_B.scale = 1.29246971E-26F;
            Formation_FMS_B.absxk = std::abs
              (BusConversion_InsertedFor_FMS_p->x_R[Formation_FMS_B.i] -
               BusConversion_InsertedFor_FMS_c->x_R);
            if (Formation_FMS_B.absxk > 1.29246971E-26F) {
              Formation_FMS_B.y = 1.0F;
              Formation_FMS_B.scale = Formation_FMS_B.absxk;
            } else {
              Formation_FMS_B.t = Formation_FMS_B.absxk / 1.29246971E-26F;
              Formation_FMS_B.y = Formation_FMS_B.t * Formation_FMS_B.t;
            }

            Formation_FMS_B.absxk = std::abs
              (BusConversion_InsertedFor_FMS_p->y_R[Formation_FMS_B.i] -
               BusConversion_InsertedFor_FMS_c->y_R);
            if (Formation_FMS_B.absxk > Formation_FMS_B.scale) {
              Formation_FMS_B.t = Formation_FMS_B.scale / Formation_FMS_B.absxk;
              Formation_FMS_B.y = Formation_FMS_B.y * Formation_FMS_B.t *
                Formation_FMS_B.t + 1.0F;
              Formation_FMS_B.scale = Formation_FMS_B.absxk;
            } else {
              Formation_FMS_B.t = Formation_FMS_B.absxk / Formation_FMS_B.scale;
              Formation_FMS_B.y += Formation_FMS_B.t * Formation_FMS_B.t;
            }

            if (Formation_FMS_B.scale * std::sqrt(Formation_FMS_B.y) <= 100.0F)
            {
              Formation_FMS_B.VehicleFormationFormAssembleWay |= 1U <<
                Formation_FMS_B.i;
            } else {
              Formation_FMS_B.VehicleFormationFormAssembleWay &= ~(1U <<
                Formation_FMS_B.i);
            }
          }
        }

        Formation_FMS_B.Cmd_In.form_valid =
          Formation_FMS_B.VehicleFormationFormAssembleWay;

        // End of Outputs for SubSystem: '<S3>/Vehicle.Formation.check_form_valid' 
        switch (Formation_FMS_DW.is_Formation) {
         case Formation_FMS_IN_FormAssemble:
          {
            switch (Formation_FMS_DW.is_FormAssemble) {
             case Formation_FMS_IN_NextWP:
              {
                Formation_FMS_B.state = VehicleState::FormAssemble;
                if (Formation_FMS_B.wp_index <=
                    BusConversion_InsertedFor_FMSSt->valid_items) {
                  boolean_T exitg1;
                  Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_Waypoint;

                  // Enable for Function Call SubSystem: '<S3>/Vehicle.Formation.FormAssemble.Waypoint.LPF' 
                  Formation_FMS_DW.VehicleFormationFormAssembleW_o = true;

                  // Enable for DiscreteIntegrator: '<S86>/Discrete-Time Integrator5' 
                  Formation_FMS_DW.DiscreteTimeIntegrator5_SYSTEM_ = 1U;

                  // End of Enable for SubSystem: '<S3>/Vehicle.Formation.FormAssemble.Waypoint.LPF' 
                  Formation_FMS_B.Cmd_In.cur_waypoint[0] =
                    Formation_FMS_B.Cmd_In.sp_waypoint[0];
                  Formation_FMS_B.Cmd_In.cur_waypoint[1] =
                    Formation_FMS_B.Cmd_In.sp_waypoint[1];
                  Formation_FMS_B.Cmd_In.cur_waypoint[2] =
                    Formation_FMS_B.Cmd_In.sp_waypoint[2];
                  Formation_FMS_B.Cmd_In.sp_waypoint[0] =
                    BusConversion_InsertedFor_FMSSt->x[Formation_FMS_B.wp_index
                    - 1];
                  Formation_FMS_B.Cmd_In.sp_waypoint[1] =
                    BusConversion_InsertedFor_FMSSt->y[Formation_FMS_B.wp_index
                    - 1];
                  Formation_FMS_B.Cmd_In.sp_waypoint[2] =
                    BusConversion_InsertedFor_FMSSt->z[Formation_FMS_B.wp_index
                    - 1];
                  Formation_FMS_B.b_x[0] = (Formation_FMS_B.Cmd_In.cur_waypoint
                    [0] == Formation_FMS_B.Cmd_In.sp_waypoint[0]);
                  Formation_FMS_B.b_x[1] = (Formation_FMS_B.Cmd_In.cur_waypoint
                    [1] == Formation_FMS_B.Cmd_In.sp_waypoint[1]);
                  Formation_FMS_B.c_y = true;
                  Formation_FMS_B.i = 0;
                  exitg1 = false;
                  while ((!exitg1) && (Formation_FMS_B.i < 2)) {
                    if (!Formation_FMS_B.b_x[Formation_FMS_B.i]) {
                      Formation_FMS_B.c_y = false;
                      exitg1 = true;
                    } else {
                      Formation_FMS_B.i++;
                    }
                  }

                  if (Formation_FMS_B.c_y) {
                    Formation_FMS_B.Cmd_In.sp_waypoint[0] += 0.01F;
                    Formation_FMS_B.Cmd_In.sp_waypoint[1] += 0.01F;
                  }

                  for (Formation_FMS_B.i = 0; Formation_FMS_B.i <= 0;
                       Formation_FMS_B.i += 4) {
                    __m128 tmp;
                    tmp = _mm_loadu_ps(&BusConversion_InsertedFor_FMSSt->
                                       x[Formation_FMS_B.i]);
                    _mm_storeu_ps(&Formation_FMS_DW.waypoints[Formation_FMS_B.i],
                                  tmp);
                    tmp = _mm_loadu_ps(&BusConversion_InsertedFor_FMSSt->
                                       y[Formation_FMS_B.i]);
                    _mm_storeu_ps(&Formation_FMS_DW.waypoints[Formation_FMS_B.i
                                  + 5], tmp);
                    tmp = _mm_loadu_ps(&BusConversion_InsertedFor_FMSSt->
                                       heading[Formation_FMS_B.i]);
                    _mm_storeu_ps(&Formation_FMS_DW.waypoints[Formation_FMS_B.i
                                  + 10], _mm_mul_ps(_mm_set1_ps(0.0174532924F),
                      tmp));
                    tmp = _mm_loadu_ps(&BusConversion_InsertedFor_FMSSt->
                                       ext1[Formation_FMS_B.i]);
                    _mm_storeu_ps(&Formation_FMS_DW.waypoints[Formation_FMS_B.i
                                  + 15], tmp);
                    tmp = _mm_loadu_ps(&BusConversion_InsertedFor_FMSSt->
                                       ext2[Formation_FMS_B.i]);
                    _mm_storeu_ps(&Formation_FMS_DW.waypoints[Formation_FMS_B.i
                                  + 20], tmp);
                  }

                  for (Formation_FMS_B.i = 4; Formation_FMS_B.i < 5;
                       Formation_FMS_B.i++) {
                    Formation_FMS_DW.waypoints[Formation_FMS_B.i] =
                      BusConversion_InsertedFor_FMSSt->x[Formation_FMS_B.i];
                    Formation_FMS_DW.waypoints[Formation_FMS_B.i + 5] =
                      BusConversion_InsertedFor_FMSSt->y[Formation_FMS_B.i];
                    Formation_FMS_DW.waypoints[Formation_FMS_B.i + 10] =
                      0.0174532924F * BusConversion_InsertedFor_FMSSt->
                      heading[Formation_FMS_B.i];
                    Formation_FMS_DW.waypoints[Formation_FMS_B.i + 15] =
                      BusConversion_InsertedFor_FMSSt->ext1[Formation_FMS_B.i];
                    Formation_FMS_DW.waypoints[Formation_FMS_B.i + 20] =
                      BusConversion_InsertedFor_FMSSt->ext2[Formation_FMS_B.i];
                  }
                } else {
                  Formation_FMS_DW.is_FormAssemble =
                    Formation_FM_IN_NO_ACTIVE_CHILD;
                  Formation_FMS_DW.is_Formation = Formation_FMS_IN_FormMission;
                  Formation_FMS_B.Cmd_In.sp_waypoint[0] =
                    BusConversion_InsertedFor_FMS_c->x_R;
                  Formation_FMS_B.Cmd_In.sp_waypoint[1] =
                    BusConversion_InsertedFor_FMS_c->y_R;
                  Formation_FMS_B.Cmd_In.sp_waypoint[2] =
                    BusConversion_InsertedFor_FMS_c->h_R;
                  Formation_FMS_B.state = VehicleState::FormMission;
                  Formation_FMS_DW.is_FormMission = Formation_FMS_IN_NextWP_d;
                }
              }
              break;

             case Formation_FMS_IN_WaitForUpdate:
              if ((*Mission_Data_timestamp_prev !=
                   Formation_FMS_DW.Mission_Data_timestamp_start) &&
                  (BusConversion_InsertedFor_FMSSt->type == 1U)) {
                Formation_FMS_B.wp_index = 1U;
                Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_NextWP;
                Formation_FMS_B.state = VehicleState::FormAssemble;
              } else {
                Formation_FMS_DW.is_FormAssemble =
                  Formation_FMS_IN_WaitForUpdate;
                Formation_FMS_B.state = VehicleState::None;
              }
              break;

             default:
              // case IN_Waypoint:
              Formation_FMS_B.BusConversion_InsertedFor_FMS_c[0] =
                BusConversion_InsertedFor_FMS_c->x_R -
                Formation_FMS_B.Cmd_In.sp_waypoint[0];
              Formation_FMS_B.BusConversion_InsertedFor_FMS_c[1] =
                BusConversion_InsertedFor_FMS_c->y_R -
                Formation_FMS_B.Cmd_In.sp_waypoint[1];
              if (Formation_FMS_norm
                  (Formation_FMS_B.BusConversion_InsertedFor_FMS_c) <=
                  FMS_PARAM.ACCEPT_R) {
                Formation_FMS_B.VehicleFormationFormAssembleWay =
                  Formation_FMS_B.wp_index + 1U;
                if (Formation_FMS_B.wp_index + 1U > 65535U) {
                  Formation_FMS_B.VehicleFormationFormAssembleWay = 65535U;
                }

                Formation_FMS_B.wp_index = static_cast<uint16_T>
                  (Formation_FMS_B.VehicleFormationFormAssembleWay);
                Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_NextWP;
                Formation_FMS_B.state = VehicleState::FormAssemble;
              } else {
                Formation_FMS_B.VehicleFormationFormAssembleWay =
                  Formation_FMS_B.wp_index - /*MW:OvSatOk*/ 1U;
                if (Formation_FMS_B.wp_index - 1U > Formation_FMS_B.wp_index) {
                  Formation_FMS_B.VehicleFormationFormAssembleWay = 0U;
                }

                if (static_cast<uint16_T>
                    (Formation_FMS_B.VehicleFormationFormAssembleWay) < 1) {
                  Formation_FMS_B.wp_index_f = 1U;
                } else {
                  Formation_FMS_B.wp_index_f = static_cast<uint16_T>
                    (Formation_FMS_B.VehicleFormationFormAssembleWay);
                }

                Formation_FMS_B.pose[0] = BusConversion_InsertedFor_FMS_c->x_R;
                Formation_FMS_B.pose[1] = BusConversion_InsertedFor_FMS_c->y_R;
                Formation_FMS_B.pose[2] = BusConversion_InsertedFor_FMS_c->psi;

                // Outputs for Function Call SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPathRatio' 
                // MATLAB Function: '<S84>/Dubins Closest Point'
                Formati_getMinDistanceAtSegment(Formation_FMS_DW.waypoints,
                  Formation_FMS_B.pose, Formation_FMS_B.wp_index_f,
                  &Formation_FMS_B.t, &Formation_FMS_B.scale);
                Formation_FMS_B.VehicleFormationFormAssembleWay =
                  Formation_FMS_B.wp_index_f + 1U;
                if (Formation_FMS_B.wp_index_f + 1U > 65535U) {
                  Formation_FMS_B.VehicleFormationFormAssembleWay = 65535U;
                }

                Formati_getMinDistanceAtSegment(Formation_FMS_DW.waypoints,
                  Formation_FMS_B.pose, static_cast<uint16_T>
                  (Formation_FMS_B.VehicleFormationFormAssembleWay),
                  &Formation_FMS_B.y, &Formation_FMS_B.absxk);
                if (Formation_FMS_B.t <= Formation_FMS_B.y) {
                  Formation_FMS_B.i = static_cast<int32_T>
                    (Formation_FMS_B.wp_index_f - /*MW:OvSatOk*/ 1U);
                  if (Formation_FMS_B.wp_index_f - 1U >
                      Formation_FMS_B.wp_index_f) {
                    Formation_FMS_B.i = 0;
                  }

                  if (static_cast<uint16_T>(Formation_FMS_B.i) < 1) {
                    Formation_FMS_B.t = 0.0F;
                  } else {
                    Formation_FMS_B.b_vlen = static_cast<uint16_T>
                      (Formation_FMS_B.i);
                    Formation_FMS_B.t = Formation_FMS_DW.waypoints[20];
                    for (Formation_FMS_B.i = 2; Formation_FMS_B.i <=
                         Formation_FMS_B.b_vlen; Formation_FMS_B.i++) {
                      Formation_FMS_B.t +=
                        Formation_FMS_DW.waypoints[Formation_FMS_B.i + 19];
                    }
                  }

                  Formation_FMS_B.scale =
                    (Formation_FMS_DW.waypoints[Formation_FMS_B.wp_index_f + 19]
                     * Formation_FMS_B.scale + Formation_FMS_B.t) /
                    Formation_FMS_DW.waypoints[24];
                } else {
                  Formation_FMS_B.b_vlen = Formation_FMS_B.wp_index_f;
                  Formation_FMS_B.t = Formation_FMS_DW.waypoints[20];
                  for (Formation_FMS_B.i = 2; Formation_FMS_B.i <=
                       Formation_FMS_B.b_vlen; Formation_FMS_B.i++) {
                    Formation_FMS_B.t +=
                      Formation_FMS_DW.waypoints[Formation_FMS_B.i + 19];
                  }

                  Formation_FMS_B.VehicleFormationFormAssembleWay =
                    Formation_FMS_B.wp_index_f + 1U;
                  if (Formation_FMS_B.wp_index_f + 1U > 65535U) {
                    Formation_FMS_B.VehicleFormationFormAssembleWay = 65535U;
                  }

                  Formation_FMS_B.scale = (Formation_FMS_DW.waypoints[
                    static_cast<int32_T>
                    (Formation_FMS_B.VehicleFormationFormAssembleWay) + 19] *
                    Formation_FMS_B.absxk + Formation_FMS_B.t) /
                    Formation_FMS_DW.waypoints[24];
                }

                // End of MATLAB Function: '<S84>/Dubins Closest Point'
                // End of Outputs for SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPathRatio' 

                // Outputs for Function Call SubSystem: '<S3>/Vehicle.Formation.FormAssemble.Waypoint.LPF' 
                if (Formation_FMS_DW.VehicleFormationFormAssembleW_o) {
                  Formation_FMS_B.VehicleFormationFormAssembleWay = 0U;
                } else {
                  Formation_FMS_B.VehicleFormationFormAssembleWay =
                    (&Formation_FMS_M)->Timing.clockTick0 -
                    Formation_FMS_DW.VehicleFormationFormAssembleW_m;
                }

                Formation_FMS_DW.VehicleFormationFormAssembleW_m =
                  (&Formation_FMS_M)->Timing.clockTick0;
                Formation_FMS_DW.VehicleFormationFormAssembleW_o = false;

                // DiscreteIntegrator: '<S86>/Discrete-Time Integrator5'
                if (Formation_FMS_DW.DiscreteTimeIntegrator5_SYSTEM_ != 0) {
                  if (Formation_FMS_DW.DiscreteTimeIntegrator5_IC_LOAD != 0) {
                    Formation_FMS_DW.DiscreteTimeIntegrator5_DSTATE =
                      Formation_FMS_B.scale;
                  }
                } else {
                  // DiscreteIntegrator: '<S86>/Discrete-Time Integrator5'
                  Formation_FMS_DW.DiscreteTimeIntegrator5_DSTATE += 0.2F *
                    static_cast<real32_T>
                    (Formation_FMS_B.VehicleFormationFormAssembleWay) *
                    Formation_FMS_DW.DiscreteTimeIntegrator5_PREV_U;
                }

                // End of DiscreteIntegrator: '<S86>/Discrete-Time Integrator5'

                // Update for DiscreteIntegrator: '<S86>/Discrete-Time Integrator5' incorporates:
                //   Gain: '<S86>/Gain'
                //   Sum: '<S86>/Sum5'

                Formation_FMS_DW.DiscreteTimeIntegrator5_SYSTEM_ = 0U;
                Formation_FMS_DW.DiscreteTimeIntegrator5_IC_LOAD = 0U;
                Formation_FMS_DW.DiscreteTimeIntegrator5_PREV_U =
                  (Formation_FMS_B.scale -
                   Formation_FMS_DW.DiscreteTimeIntegrator5_DSTATE) * 62.831852F;

                // End of Outputs for SubSystem: '<S3>/Vehicle.Formation.FormAssemble.Waypoint.LPF' 
                Formation_FMS_B.scale = 1.29246971E-26F;
                Formation_FMS_B.absxk = std::abs
                  (BusConversion_InsertedFor_FMS_c->vn);
                if (Formation_FMS_B.absxk > 1.29246971E-26F) {
                  Formation_FMS_B.y = 1.0F;
                  Formation_FMS_B.scale = Formation_FMS_B.absxk;
                } else {
                  Formation_FMS_B.t = Formation_FMS_B.absxk / 1.29246971E-26F;
                  Formation_FMS_B.y = Formation_FMS_B.t * Formation_FMS_B.t;
                }

                Formation_FMS_B.absxk = std::abs
                  (BusConversion_InsertedFor_FMS_c->ve);
                if (Formation_FMS_B.absxk > Formation_FMS_B.scale) {
                  Formation_FMS_B.t = Formation_FMS_B.scale /
                    Formation_FMS_B.absxk;
                  Formation_FMS_B.y = Formation_FMS_B.y * Formation_FMS_B.t *
                    Formation_FMS_B.t + 1.0F;
                  Formation_FMS_B.scale = Formation_FMS_B.absxk;
                } else {
                  Formation_FMS_B.t = Formation_FMS_B.absxk /
                    Formation_FMS_B.scale;
                  Formation_FMS_B.y += Formation_FMS_B.t * Formation_FMS_B.t;
                }

                // Outputs for Function Call SubSystem: '<S3>/Vehicle.Formation.FormAssemble.Waypoint.LPF' 
                Formation_FMS_Y.Form_Single = (1.0F -
                  Formation_FMS_DW.DiscreteTimeIntegrator5_DSTATE) *
                  BusConversion_InsertedFor_FMSSt->ext2[4] /
                  (Formation_FMS_B.scale * std::sqrt(Formation_FMS_B.y));

                // End of Outputs for SubSystem: '<S3>/Vehicle.Formation.FormAssemble.Waypoint.LPF' 
              }
              break;
            }
          }
          break;

         case Formation_FMS_IN_FormDisband:
          Formation_FMS_B.state = VehicleState::FormDisband;
          break;

         case Formation_FMS_IN_FormMission:
          Formation_FMS_B.state = VehicleState::FormMission;
          if (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormDisband) {
            Formation_FMS_DW.is_FormMission = Formation_FM_IN_NO_ACTIVE_CHILD;
            Formation_FMS_DW.is_Formation = Formation_FMS_IN_FormDisband;
            Formation_FMS_B.state = VehicleState::FormDisband;
          } else if ((*Mission_Data_timestamp_prev !=
                      Formation_FMS_DW.Mission_Data_timestamp_start) &&
                     (BusConversion_InsertedFor_FMSSt->type == 3U)) {
            Formation_FMS_B.wp_index = 1U;
            Formation_FMS_DW.is_FormMission = Formation_FMS_IN_NextWP_d;
          } else {
            switch (Formation_FMS_DW.is_FormMission) {
             case Formation_FMS_IN_Follower:
             case Formation_FMS_IN_Forward:
              break;

             case Formation_FMS_IN_NextWP_d:
              if (Formation_FMS_B.wp_index <=
                  BusConversion_InsertedFor_FMSSt->valid_items) {
                Formation_FMS_DW.is_FormMission = Formation_FMS_IN_Waypoint_g;
                Formation_FMS_B.Cmd_In.cur_waypoint[0] =
                  Formation_FMS_B.Cmd_In.sp_waypoint[0];
                Formation_FMS_B.Cmd_In.cur_waypoint[1] =
                  Formation_FMS_B.Cmd_In.sp_waypoint[1];
                Formation_FMS_B.Cmd_In.cur_waypoint[2] =
                  Formation_FMS_B.Cmd_In.sp_waypoint[2];
                Formation_FMS_B.Cmd_In.sp_waypoint[0] =
                  BusConversion_InsertedFor_FMSSt->x[Formation_FMS_B.wp_index -
                  1];
                Formation_FMS_B.Cmd_In.sp_waypoint[1] =
                  BusConversion_InsertedFor_FMSSt->y[Formation_FMS_B.wp_index -
                  1];
                Formation_FMS_B.Cmd_In.sp_waypoint[2] =
                  BusConversion_InsertedFor_FMSSt->z[Formation_FMS_B.wp_index -
                  1];
                Formation_FMS_B.Cmd_In.l1_enable = true;
              } else {
                Formation_FMS_DW.is_FormMission = Formation_FMS_IN_Forward;
                Formation_FMS_B.Cmd_In.l1_enable = false;
              }
              break;

             default:
              // case IN_Waypoint:
              Formation_FMS_B.BusConversion_InsertedFor_FMS_c[0] =
                BusConversion_InsertedFor_FMS_c->x_R -
                Formation_FMS_B.Cmd_In.sp_waypoint[0];
              Formation_FMS_B.BusConversion_InsertedFor_FMS_c[1] =
                BusConversion_InsertedFor_FMS_c->y_R -
                Formation_FMS_B.Cmd_In.sp_waypoint[1];
              if (Formation_FMS_norm
                  (Formation_FMS_B.BusConversion_InsertedFor_FMS_c) <=
                  FMS_PARAM.ACCEPT_R) {
                Formation_FMS_B.VehicleFormationFormAssembleWay =
                  Formation_FMS_B.wp_index + 1U;
                if (Formation_FMS_B.wp_index + 1U > 65535U) {
                  Formation_FMS_B.VehicleFormationFormAssembleWay = 65535U;
                }

                Formation_FMS_B.wp_index = static_cast<uint16_T>
                  (Formation_FMS_B.VehicleFormationFormAssembleWay);
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
          Formation_FMS_B.Cmd_In.cur_waypoint[0] =
            BusConversion_InsertedFor_FMS_c->x_R;
          Formation_FMS_B.Cmd_In.cur_waypoint[1] =
            BusConversion_InsertedFor_FMS_c->y_R;
          Formation_FMS_B.Cmd_In.cur_waypoint[2] =
            BusConversion_InsertedFor_FMS_c->h_R;
          Formation_FMS_B.state = VehicleState::Hold;
          break;
        }
      }
      break;

     case Formation_FMS_IN_Mission:
      if (*Mission_Data_timestamp_prev !=
          Formation_FMS_DW.Mission_Data_timestamp_start) {
        Formation_FMS_B.wp_index = 1U;
        Formation_FMS_DW.is_Mission = Formation_FMS_IN_NextWP_dp;
        Formation_FMS_B.state = VehicleState::None;
      } else {
        switch (Formation_FMS_DW.is_Mission) {
         case Formation_FMS_IN_Loiter:
          Formation_FMS_B.state = VehicleState::Hold;
          break;

         case Formation_FMS_IN_NextWP_dp:
          Formation_FMS_B.state = VehicleState::None;
          if (Formation_FMS_B.wp_index <=
              BusConversion_InsertedFor_FMSSt->valid_items) {
            Formation_FMS_DW.is_Mission = Formation_FMS_IN_Waypoint;
            Formation_FMS_B.Cmd_In.cur_waypoint[0] =
              Formation_FMS_B.Cmd_In.sp_waypoint[0];
            Formation_FMS_B.Cmd_In.cur_waypoint[1] =
              Formation_FMS_B.Cmd_In.sp_waypoint[1];
            Formation_FMS_B.Cmd_In.cur_waypoint[2] =
              Formation_FMS_B.Cmd_In.sp_waypoint[2];
            Formation_FMS_B.Cmd_In.sp_waypoint[0] =
              BusConversion_InsertedFor_FMSSt->x[Formation_FMS_B.wp_index - 1];
            Formation_FMS_B.Cmd_In.sp_waypoint[1] =
              BusConversion_InsertedFor_FMSSt->y[Formation_FMS_B.wp_index - 1];
            Formation_FMS_B.Cmd_In.sp_waypoint[2] =
              BusConversion_InsertedFor_FMSSt->z[Formation_FMS_B.wp_index - 1];
            Formation_FMS_B.state = VehicleState::Mission;
          } else if (Formation_FMS_B.wp_index >
                     BusConversion_InsertedFor_FMSSt->valid_items) {
            Formation_FMS_DW.is_Mission = Formation_FMS_IN_Loiter;
            Formation_FMS_B.Cmd_In.cur_waypoint[0] =
              Formation_FMS_B.Cmd_In.sp_waypoint[0];
            Formation_FMS_B.Cmd_In.cur_waypoint[1] =
              Formation_FMS_B.Cmd_In.sp_waypoint[1];
            Formation_FMS_B.Cmd_In.cur_waypoint[2] =
              Formation_FMS_B.Cmd_In.sp_waypoint[2];
            Formation_FMS_B.state = VehicleState::Hold;
          }
          break;

         default:
          // case IN_Waypoint:
          Formation_FMS_B.state = VehicleState::Mission;
          Formation_FMS_B.BusConversion_InsertedFor_FMS_c[0] =
            BusConversion_InsertedFor_FMS_c->x_R -
            Formation_FMS_B.Cmd_In.sp_waypoint[0];
          Formation_FMS_B.BusConversion_InsertedFor_FMS_c[1] =
            BusConversion_InsertedFor_FMS_c->y_R -
            Formation_FMS_B.Cmd_In.sp_waypoint[1];
          if (Formation_FMS_norm(Formation_FMS_B.BusConversion_InsertedFor_FMS_c)
              <= FMS_PARAM.ACCEPT_R) {
            Formation_FMS_B.VehicleFormationFormAssembleWay =
              Formation_FMS_B.wp_index + 1U;
            if (Formation_FMS_B.wp_index + 1U > 65535U) {
              Formation_FMS_B.VehicleFormationFormAssembleWay = 65535U;
            }

            Formation_FMS_B.wp_index = static_cast<uint16_T>
              (Formation_FMS_B.VehicleFormationFormAssembleWay);
            Formation_FMS_DW.is_Mission = Formation_FMS_IN_NextWP_dp;
            Formation_FMS_B.state = VehicleState::None;
          }
          break;
        }
      }
      break;

     default:
      // case IN_Standby:
      Formation_FMS_B.state = VehicleState::Hold;
      break;
    }
  }

  // End of Delay: '<S5>/Delay'
}

// Model step function
void Formation_FMS::step()
{
  // Outputs for Atomic SubSystem: '<Root>/CommandProcess'
  // DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' incorporates:
  //   Inport: '<Root>/Pilot_Cmd'
  //   RelationalOperator: '<S7>/FixPt Relational Operator'
  //   UnitDelay: '<S7>/Delay Input1'
  //
  //  Block description for '<S7>/Delay Input1':
  //
  //   Store in Global RAM

  if (Formation_FMS_U.Pilot_Cmd.timestamp != Formation_FMS_DW.DelayInput1_DSTATE)
  {
    Formation_FMS_DW.DiscreteTimeIntegrator1_DSTATE = 0.0F;
  }

  // Switch: '<S5>/Switch' incorporates:
  //   Constant: '<S6>/Constant'
  //   Constant: '<S8>/Constant'
  //   DataTypeConversion: '<S5>/Data Type Conversion2'
  //   Delay: '<S5>/Delay'
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
  //   Inport: '<Root>/Pilot_Cmd'
  //   Logic: '<S5>/Logical Operator1'
  //   RelationalOperator: '<S6>/Compare'
  //   RelationalOperator: '<S8>/Compare'

  if ((Formation_FMS_U.Pilot_Cmd.mode != 0U) &&
      (Formation_FMS_DW.DiscreteTimeIntegrator1_DSTATE < 0.5F)) {
    Formation_FMS_DW.Delay_DSTATE_j = static_cast<PilotMode>
      (Formation_FMS_U.Pilot_Cmd.mode);
  }

  // End of Switch: '<S5>/Switch'

  // Update for UnitDelay: '<S7>/Delay Input1' incorporates:
  //   Inport: '<Root>/Pilot_Cmd'
  //
  //  Block description for '<S7>/Delay Input1':
  //
  //   Store in Global RAM

  Formation_FMS_DW.DelayInput1_DSTATE = Formation_FMS_U.Pilot_Cmd.timestamp;

  // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
  Formation_FMS_DW.DiscreteTimeIntegrator1_DSTATE += 0.2F;

  // End of Outputs for SubSystem: '<Root>/CommandProcess'

  // Chart: '<Root>/FMS State Machine' incorporates:
  //   Delay: '<S5>/Delay'
  //   Inport: '<Root>/Formation_Cross'
  //   Inport: '<Root>/INS_Out'
  //   Inport: '<Root>/Mission_Data'

  Formation_FMS_B.Mission_Data_timestamp_prev =
    Formation_FMS_DW.Mission_Data_timestamp_start;
  Formation_FMS_DW.Mission_Data_timestamp_start =
    Formation_FMS_U.Mission_Data.timestamp;
  Formation_FMS_B.mode_prev = Formation_FMS_DW.mode_start;
  Formation_FMS_DW.mode_start = Formation_FMS_DW.Delay_DSTATE_j;
  if (Formation_FMS_DW.is_active_c3_Formation_FMS == 0U) {
    boolean_T exitg1;
    Formation_FMS_DW.Mission_Data_timestamp_start =
      Formation_FMS_U.Mission_Data.timestamp;
    Formation_FMS_DW.is_active_c3_Formation_FMS = 1U;
    Formation_FMS_B.x[0] = (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::
      FormAssemble);
    Formation_FMS_B.x[1] = (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::
      FormDisband);
    Formation_FMS_B.FixPtRelationalOperator_m = false;
    Formation_FMS_B.n = 0;
    exitg1 = false;
    while ((!exitg1) && (Formation_FMS_B.n < 2)) {
      if (Formation_FMS_B.x[Formation_FMS_B.n]) {
        Formation_FMS_B.FixPtRelationalOperator_m = true;
        exitg1 = true;
      } else {
        Formation_FMS_B.n++;
      }
    }

    if (Formation_FMS_B.FixPtRelationalOperator_m) {
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Formation;
      if (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::FormAssemble) {
        Formation_FMS_DW.is_Formation = Formation_FMS_IN_FormAssemble;
        Formation_FMS_B.Cmd_In.sp_waypoint[0] = Formation_FMS_U.INS_Out.x_R;
        Formation_FMS_B.Cmd_In.sp_waypoint[1] = Formation_FMS_U.INS_Out.y_R;
        Formation_FMS_B.Cmd_In.sp_waypoint[2] = Formation_FMS_U.INS_Out.h_R;

        // Outputs for Function Call SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPath' 
        VehicleFormationFormAssembledub(&Formation_FMS_U.Formation_Cross,
          &Formation_FMS_B.mission,
          &Formation_FMS_B.VehicleFormationFormAssembled_o);

        // End of Outputs for SubSystem: '<S3>/Vehicle.Formation.FormAssemble.dubinsPath' 

        // Outport: '<Root>/Other_Mission_Data' incorporates:
        //   Inport: '<Root>/Formation_Cross'
        //   Inport: '<Root>/INS_Out'

        Formation_FMS_Y.Other_Mission_Data = Formation_FMS_B.mission;
        Formation_FMS_DW.is_FormAssemble = Formation_FMS_IN_WaitForUpdate;
        Formation_FMS_B.state = VehicleState::None;
      } else {
        Formation_FMS_DW.is_Formation = Formation_FMS_IN_InvalidMode;
      }
    } else if (Formation_FMS_DW.Delay_DSTATE_j == PilotMode::Mission) {
      Formation_FMS_B.wp_index = 1U;
      Formation_FMS_B.Cmd_In.cur_waypoint[0] = Formation_FMS_U.INS_Out.x_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[1] = Formation_FMS_U.INS_Out.y_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[2] = Formation_FMS_U.INS_Out.h_R;
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Mission;
      Formation_FMS_B.Cmd_In.sp_waypoint[0] = Formation_FMS_U.INS_Out.x_R;
      Formation_FMS_B.Cmd_In.sp_waypoint[1] = Formation_FMS_U.INS_Out.y_R;
      Formation_FMS_B.Cmd_In.sp_waypoint[2] = Formation_FMS_U.INS_Out.h_R;
      Formation_FMS_DW.is_Mission = Formation_FMS_IN_NextWP_dp;
      Formation_FMS_B.state = VehicleState::None;
    } else {
      Formation_FMS_DW.is_Vehicle = Formation_FMS_IN_Standby;
      Formation_FMS_B.Cmd_In.cur_waypoint[0] = Formation_FMS_U.INS_Out.x_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[1] = Formation_FMS_U.INS_Out.y_R;
      Formation_FMS_B.Cmd_In.cur_waypoint[2] = Formation_FMS_U.INS_Out.h_R;
      Formation_FMS_B.state = VehicleState::Hold;
    }
  } else {
    Formation_FMS_Vehicle(&Formation_FMS_U.INS_Out,
                          &Formation_FMS_U.Formation_Cross,
                          &Formation_FMS_U.Mission_Data,
                          &Formation_FMS_B.Mission_Data_timestamp_prev,
                          &Formation_FMS_B.mode_prev,
                          &Formation_FMS_B.Formation_Cross_d);
  }

  // End of Chart: '<Root>/FMS State Machine'

  // SwitchCase: '<S10>/Switch Case' incorporates:
  //   Outport: '<Root>/FMS_Out'
  //   Product: '<S38>/Divide'
  //   Product: '<S62>/Divide'
  //   Product: '<S63>/Divide'
  //   Sum: '<S26>/Subtract'
  //   Sum: '<S50>/Subtract'

  Formation_FMS_B.rtPrevAction = Formation_FMS_DW.SwitchCase_ActiveSubsystem;
  switch (Formation_FMS_B.state) {
   case VehicleState::FormMission:
    Formation_FMS_DW.SwitchCase_ActiveSubsystem = 0;
    break;

   case VehicleState::FormAssemble:
    Formation_FMS_DW.SwitchCase_ActiveSubsystem = 1;
    break;

   case VehicleState::Hold:
    Formation_FMS_DW.SwitchCase_ActiveSubsystem = 2;
    break;

   default:
    Formation_FMS_DW.SwitchCase_ActiveSubsystem = 3;
    break;
  }

  switch (Formation_FMS_DW.SwitchCase_ActiveSubsystem) {
   case 0:
    // Outputs for IfAction SubSystem: '<S10>/FormMission' incorporates:
    //   ActionPort: '<S13>/Action Port'

    // RelationalOperator: '<S40>/FixPt Relational Operator' incorporates:
    //   UnitDelay: '<S40>/Delay Input1'
    //
    //  Block description for '<S40>/Delay Input1':
    //
    //   Store in Global RAM

    Formation_FMS_B.FixPtRelationalOperator_m = (Formation_FMS_B.wp_index !=
      Formation_FMS_DW.DelayInput1_DSTATE_d);

    // Outputs for Resettable SubSystem: '<S13>/FormMission_SubSystem' incorporates:
    //   ResetPort: '<S41>/Reset'

    // InitializeConditions for Delay: '<S43>/Delay'
    Formation_FMS_DW.icLoad_n = ((Formation_FMS_B.FixPtRelationalOperator_m &&
      (Formation_FMS_PrevZCX.FormMission_SubSystem_Reset_ZCE != POS_ZCSIG)) ||
      Formation_FMS_DW.icLoad_n);
    Formation_FMS_PrevZCX.FormMission_SubSystem_Reset_ZCE =
      Formation_FMS_B.FixPtRelationalOperator_m;

    // SignalConversion generated from: '<S44>/Vector Concatenate' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.xyz_O_nx3[0] = Formation_FMS_U.Formation_Cross.x_R[0];

    // SignalConversion generated from: '<S44>/Vector Concatenate' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.xyz_O_nx3[3] = Formation_FMS_U.Formation_Cross.y_R[0];

    // SignalConversion generated from: '<S44>/Vector Concatenate' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.xyz_O_nx3[6] = Formation_FMS_U.Formation_Cross.h_R[0];

    // SignalConversion generated from: '<S44>/Vector Concatenate1' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.vNED_O_nx3[0] = Formation_FMS_U.Formation_Cross.vn[0];

    // SignalConversion generated from: '<S44>/Vector Concatenate1' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.vNED_O_nx3[3] = Formation_FMS_U.Formation_Cross.ve[0];

    // SignalConversion generated from: '<S44>/Vector Concatenate1' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.vNED_O_nx3[6] = Formation_FMS_U.Formation_Cross.vd[0];

    // SignalConversion generated from: '<S44>/Vector Concatenate' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.xyz_O_nx3[1] = Formation_FMS_U.Formation_Cross.x_R[1];

    // SignalConversion generated from: '<S44>/Vector Concatenate' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.xyz_O_nx3[4] = Formation_FMS_U.Formation_Cross.y_R[1];

    // SignalConversion generated from: '<S44>/Vector Concatenate' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.xyz_O_nx3[7] = Formation_FMS_U.Formation_Cross.h_R[1];

    // SignalConversion generated from: '<S44>/Vector Concatenate1' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.vNED_O_nx3[1] = Formation_FMS_U.Formation_Cross.vn[1];

    // SignalConversion generated from: '<S44>/Vector Concatenate1' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.vNED_O_nx3[4] = Formation_FMS_U.Formation_Cross.ve[1];

    // SignalConversion generated from: '<S44>/Vector Concatenate1' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.vNED_O_nx3[7] = Formation_FMS_U.Formation_Cross.vd[1];

    // SignalConversion generated from: '<S44>/Vector Concatenate' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.xyz_O_nx3[2] = Formation_FMS_U.Formation_Cross.x_R[2];

    // SignalConversion generated from: '<S44>/Vector Concatenate' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.xyz_O_nx3[5] = Formation_FMS_U.Formation_Cross.y_R[2];

    // SignalConversion generated from: '<S44>/Vector Concatenate' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.xyz_O_nx3[8] = Formation_FMS_U.Formation_Cross.h_R[2];

    // SignalConversion generated from: '<S44>/Vector Concatenate1' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.vNED_O_nx3[2] = Formation_FMS_U.Formation_Cross.vn[2];

    // SignalConversion generated from: '<S44>/Vector Concatenate1' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.vNED_O_nx3[5] = Formation_FMS_U.Formation_Cross.ve[2];

    // SignalConversion generated from: '<S44>/Vector Concatenate1' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.vNED_O_nx3[8] = Formation_FMS_U.Formation_Cross.vd[2];

    // MATLAB Function: '<S44>/Consensus Controller' incorporates:
    //   Concatenate: '<S44>/Vector Concatenate'
    //   Concatenate: '<S44>/Vector Concatenate1'
    //   Inport: '<Root>/Formation_Cross'
    //   SignalConversion generated from: '<S9>/Signal Copy2'

    Formation_FMS_B.Sum1_e = 0.0F;
    Formation_FMS_B.u = 0.0F;
    Formation_FMS_B.a = 0.0F;
    Formation_FMS_B.psi = Formation_FMS_rt_atan2f_snf
      (Formation_FMS_U.Formation_Cross.ve[0],
       Formation_FMS_U.Formation_Cross.vn[0]);
    Formation_FMS_B.new_pos_err_idx_0 = std::sin(Formation_FMS_B.psi);
    Formation_FMS_B.new_pos_err_idx_1 = std::cos(Formation_FMS_B.psi);
    for (Formation_FMS_B.n = 0; Formation_FMS_B.n < 3; Formation_FMS_B.n++) {
      if ((1U << Formation_FMS_B.n & Formation_FMS_B.Cmd_In.form_valid) != 0U) {
        Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.xyz_O_nx3[0] -
          Formation_FMS_B.xyz_O_nx3[Formation_FMS_B.n];
        Formation_FMS_B.psi = Formation_FMS_B.xyz_O_nx3[3] -
          Formation_FMS_B.xyz_O_nx3[Formation_FMS_B.n + 3];
        Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.vNED_O_nx3[0] -
          Formation_FMS_B.vNED_O_nx3[Formation_FMS_B.n];
        Formation_FMS_B.pos_err_idx_2 = Formation_FMS_B.vNED_O_nx3[3] -
          Formation_FMS_B.vNED_O_nx3[Formation_FMS_B.n + 3];
        Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.new_pos_err_idx_1 *
          Formation_FMS_B.l1_a_cmd_m;
        Formation_FMS_B.new_vel_err[1] = -Formation_FMS_B.new_pos_err_idx_0 *
          Formation_FMS_B.l1_a_cmd_m;
        Formation_FMS_B.l1_a_cmd_m = static_cast<real32_T>
          (Formation_FMS_ConstP.ConsensusController_adj_matrix[3 *
           Formation_FMS_B.n]);
        Formation_FMS_B.Sum1_e -= (((Formation_FMS_B.new_pos_err_idx_1 *
          Formation_FMS_B.pos_err_idx_0 + Formation_FMS_B.new_pos_err_idx_0 *
          Formation_FMS_B.psi) - static_cast<real32_T>
          (Formation_FMS_ConstP.ConsensusController_rel_x[3 * Formation_FMS_B.n]))
          + (Formation_FMS_B.new_pos_err_idx_0 * Formation_FMS_B.pos_err_idx_2 +
             Formation_FMS_B.new_vel_err[0])) * Formation_FMS_B.l1_a_cmd_m;
        Formation_FMS_B.u -= (((-Formation_FMS_B.new_pos_err_idx_0 *
          Formation_FMS_B.pos_err_idx_0 + Formation_FMS_B.new_pos_err_idx_1 *
          Formation_FMS_B.psi) - static_cast<real32_T>
          (Formation_FMS_ConstP.ConsensusController_rel_y[3 * Formation_FMS_B.n]))
                              + (Formation_FMS_B.new_pos_err_idx_1 *
          Formation_FMS_B.pos_err_idx_2 + Formation_FMS_B.new_vel_err[1])) *
          Formation_FMS_B.l1_a_cmd_m;
        Formation_FMS_B.a -= (Formation_FMS_B.xyz_O_nx3[6] -
                              Formation_FMS_B.xyz_O_nx3[Formation_FMS_B.n + 6]) *
          Formation_FMS_B.l1_a_cmd_m;
      }
    }

    // Outputs for Enabled SubSystem: '<S41>/Position Command' incorporates:
    //   EnablePort: '<S45>/Enable'

    if (Formation_FMS_B.Cmd_In.l1_enable) {
      // SignalConversion generated from: '<S58>/Square' incorporates:
      //   Inport: '<Root>/INS_Out'

      Formation_FMS_B.new_vel_err[0] = Formation_FMS_U.INS_Out.vn;
      Formation_FMS_B.new_vel_err[1] = Formation_FMS_U.INS_Out.ve;

      // Math: '<S59>/Math Function' incorporates:
      //   Inport: '<Root>/INS_Out'
      //   Math: '<S58>/Square'
      //   SignalConversion generated from: '<S58>/Square'

      Formation_FMS_B.new_pos_err_idx_0 = Formation_FMS_U.INS_Out.vn *
        Formation_FMS_U.INS_Out.vn;
      Formation_FMS_B.new_pos_err_idx_1 = Formation_FMS_U.INS_Out.ve *
        Formation_FMS_U.INS_Out.ve;

      // Sum: '<S59>/Sum of Elements' incorporates:
      //   Math: '<S59>/Math Function'

      Formation_FMS_B.Saturation_g = Formation_FMS_B.new_pos_err_idx_0 +
        Formation_FMS_B.new_pos_err_idx_1;

      // Math: '<S59>/Math Function1' incorporates:
      //   Sum: '<S59>/Sum of Elements'
      //
      //  About '<S59>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.Saturation_g < 0.0F) {
        Formation_FMS_B.Saturation_g = -std::sqrt(std::abs
          (Formation_FMS_B.Saturation_g));
      } else {
        Formation_FMS_B.Saturation_g = std::sqrt(Formation_FMS_B.Saturation_g);
      }

      // End of Math: '<S59>/Math Function1'

      // Switch: '<S59>/Switch' incorporates:
      //   Constant: '<S59>/Constant'
      //   Inport: '<Root>/INS_Out'
      //   Product: '<S59>/Product'
      //   SignalConversion generated from: '<S58>/Square'

      if (Formation_FMS_B.Saturation_g > 0.0F) {
        Formation_FMS_B.pos_err_idx_0 = Formation_FMS_U.INS_Out.vn;
        Formation_FMS_B.psi = Formation_FMS_U.INS_Out.ve;
        Formation_FMS_B.pos_err_idx_2 = Formation_FMS_B.Saturation_g;
      } else {
        Formation_FMS_B.pos_err_idx_0 = Formation_FMS_U.INS_Out.vn * 0.0F;
        Formation_FMS_B.psi = Formation_FMS_U.INS_Out.ve * 0.0F;
        Formation_FMS_B.pos_err_idx_2 = 1.0F;
      }

      // End of Switch: '<S59>/Switch'

      // Reshape: '<S48>/Reshape2' incorporates:
      //   Inport: '<Root>/INS_Out'

      Formation_FMS_B.Reshape2_bi[0] = Formation_FMS_U.INS_Out.x_R;
      Formation_FMS_B.Reshape2_bi[1] = Formation_FMS_U.INS_Out.y_R;

      // MATLAB Function: '<S49>/NearbyRefWP' incorporates:
      //   Constant: '<S47>/L1'

      Formation_FMS_NearbyRefWP(&Formation_FMS_B.Cmd_In.sp_waypoint[0],
        Formation_FMS_B.Reshape2_bi, FMS_PARAM.L1, Formation_FMS_B.new_vel_err,
        &Formation_FMS_B.l1_a_cmd_m);

      // MATLAB Function: '<S49>/SearchL1RefWP' incorporates:
      //   Constant: '<S47>/L1'

      Formation_FMS_SearchL1RefWP(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
        &Formation_FMS_B.Cmd_In.sp_waypoint[0], Formation_FMS_B.Reshape2_bi,
        FMS_PARAM.L1, Formation_FMS_B.P_mr, &Formation_FMS_B.u_e);

      // MATLAB Function: '<S49>/OutRegionRegWP'
      Formation_FMS_OutRegionRegWP(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
        &Formation_FMS_B.Cmd_In.sp_waypoint[0], Formation_FMS_B.Reshape2_bi,
        Formation_FMS_B.P_b);

      // Switch: '<S49>/Switch1' incorporates:
      //   Constant: '<S51>/Constant'
      //   Constant: '<S52>/Constant'
      //   Product: '<S62>/Divide'
      //   RelationalOperator: '<S51>/Compare'
      //   RelationalOperator: '<S52>/Compare'
      //   Switch: '<S49>/Switch'

      if (Formation_FMS_B.l1_a_cmd_m > 0.0F) {
        Formation_FMS_B.P_mr[0] = Formation_FMS_B.new_vel_err[0];
        Formation_FMS_B.P_mr[1] = Formation_FMS_B.new_vel_err[1];
      } else if (!(Formation_FMS_B.u_e >= 0.0F)) {
        // Product: '<S62>/Divide' incorporates:
        //   Switch: '<S49>/Switch'

        Formation_FMS_B.P_mr[0] = Formation_FMS_B.P_b[0];
        Formation_FMS_B.P_mr[1] = Formation_FMS_B.P_b[1];
      }

      // End of Switch: '<S49>/Switch1'

      // Sum: '<S50>/Subtract' incorporates:
      //   Inport: '<Root>/INS_Out'
      //   Product: '<S62>/Divide'
      //   Reshape: '<S48>/Reshape2'

      Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.P_mr[0] -
        Formation_FMS_U.INS_Out.x_R;

      // Math: '<S60>/Math Function'
      Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.l1_a_cmd_m *
        Formation_FMS_B.l1_a_cmd_m;
      Formation_FMS_B.P_mr[0] = Formation_FMS_B.l1_a_cmd_m;

      // Sum: '<S50>/Subtract' incorporates:
      //   Inport: '<Root>/INS_Out'
      //   Product: '<S62>/Divide'
      //   Reshape: '<S48>/Reshape2'

      Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.P_mr[1] -
        Formation_FMS_U.INS_Out.y_R;

      // Sum: '<S60>/Sum of Elements' incorporates:
      //   Math: '<S60>/Math Function'

      Formation_FMS_B.Saturation_g = Formation_FMS_B.l1_a_cmd_m *
        Formation_FMS_B.l1_a_cmd_m + Formation_FMS_B.new_vel_err[0];

      // Math: '<S60>/Math Function1' incorporates:
      //   Sum: '<S60>/Sum of Elements'
      //
      //  About '<S60>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.Saturation_g < 0.0F) {
        Formation_FMS_B.Saturation_g = -std::sqrt(std::abs
          (Formation_FMS_B.Saturation_g));
      } else {
        Formation_FMS_B.Saturation_g = std::sqrt(Formation_FMS_B.Saturation_g);
      }

      // End of Math: '<S60>/Math Function1'

      // Switch: '<S60>/Switch' incorporates:
      //   Constant: '<S60>/Constant'
      //   Product: '<S60>/Product'
      //   Sum: '<S50>/Subtract'
      //   Switch: '<S63>/Switch'

      if (Formation_FMS_B.Saturation_g > 0.0F) {
        Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.P_mr[0];
        Formation_FMS_B.u_e = Formation_FMS_B.Saturation_g;
      } else {
        Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.P_mr[0] * 0.0F;
        Formation_FMS_B.l1_a_cmd_m *= 0.0F;
        Formation_FMS_B.u_e = 1.0F;
      }

      // End of Switch: '<S60>/Switch'

      // Product: '<S59>/Divide'
      Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.pos_err_idx_0 /
        Formation_FMS_B.pos_err_idx_2;
      Formation_FMS_B.new_vel_err[1] = Formation_FMS_B.psi /
        Formation_FMS_B.pos_err_idx_2;

      // Sum: '<S62>/Sum of Elements' incorporates:
      //   Math: '<S62>/Math Function'
      //   SignalConversion generated from: '<S62>/Math Function'

      Formation_FMS_B.Saturation_g = Formation_FMS_B.new_vel_err[1] *
        Formation_FMS_B.new_vel_err[1] + Formation_FMS_B.new_vel_err[0] *
        Formation_FMS_B.new_vel_err[0];

      // Math: '<S62>/Math Function1' incorporates:
      //   Sum: '<S62>/Sum of Elements'
      //
      //  About '<S62>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.Saturation_g < 0.0F) {
        Formation_FMS_B.Saturation_g = -std::sqrt(std::abs
          (Formation_FMS_B.Saturation_g));
      } else {
        Formation_FMS_B.Saturation_g = std::sqrt(Formation_FMS_B.Saturation_g);
      }

      // End of Math: '<S62>/Math Function1'

      // Switch: '<S62>/Switch' incorporates:
      //   Constant: '<S62>/Constant'
      //   Product: '<S62>/Product'
      //   SignalConversion generated from: '<S62>/Math Function'

      if (Formation_FMS_B.Saturation_g > 0.0F) {
        Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.new_vel_err[1];
        Formation_FMS_B.psi = Formation_FMS_B.new_vel_err[0];
        Formation_FMS_B.pos_err_idx_2 = Formation_FMS_B.Saturation_g;
      } else {
        Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.new_vel_err[1] * 0.0F;
        Formation_FMS_B.psi = Formation_FMS_B.new_vel_err[0] * 0.0F;
        Formation_FMS_B.pos_err_idx_2 = 1.0F;
      }

      // End of Switch: '<S62>/Switch'

      // Product: '<S60>/Divide' incorporates:
      //   Product: '<S63>/Divide'

      Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.rtb_Switch_i_idx_0 /
        Formation_FMS_B.u_e;
      Formation_FMS_B.new_vel_err[1] = Formation_FMS_B.l1_a_cmd_m /
        Formation_FMS_B.u_e;

      // Sum: '<S63>/Sum of Elements' incorporates:
      //   Math: '<S63>/Math Function'
      //   SignalConversion generated from: '<S63>/Math Function'

      Formation_FMS_B.Saturation_g = Formation_FMS_B.new_vel_err[1] *
        Formation_FMS_B.new_vel_err[1] + Formation_FMS_B.new_vel_err[0] *
        Formation_FMS_B.new_vel_err[0];

      // Math: '<S63>/Math Function1' incorporates:
      //   Sum: '<S63>/Sum of Elements'
      //
      //  About '<S63>/Math Function1':
      //   Operator: sqrt

      if (Formation_FMS_B.Saturation_g < 0.0F) {
        Formation_FMS_B.Saturation_g = -std::sqrt(std::abs
          (Formation_FMS_B.Saturation_g));
      } else {
        Formation_FMS_B.Saturation_g = std::sqrt(Formation_FMS_B.Saturation_g);
      }

      // End of Math: '<S63>/Math Function1'

      // Switch: '<S63>/Switch' incorporates:
      //   Constant: '<S63>/Constant'
      //   Product: '<S63>/Product'
      //   SignalConversion generated from: '<S63>/Math Function'

      if (Formation_FMS_B.Saturation_g > 0.0F) {
        Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.new_vel_err[1];
        Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.new_vel_err[0];
        Formation_FMS_B.u_e = Formation_FMS_B.Saturation_g;
      } else {
        Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.new_vel_err[1] *
          0.0F;
        Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.new_vel_err[0] * 0.0F;
        Formation_FMS_B.u_e = 1.0F;
      }

      // End of Switch: '<S63>/Switch'

      // Product: '<S63>/Divide'
      Formation_FMS_B.rtb_Switch_i_idx_0 /= Formation_FMS_B.u_e;

      // Product: '<S62>/Divide'
      Formation_FMS_B.pos_err_idx_0 /= Formation_FMS_B.pos_err_idx_2;

      // DotProduct: '<S57>/Dot Product'
      Formation_FMS_B.rtb_P_mr_m = Formation_FMS_B.pos_err_idx_0 *
        Formation_FMS_B.rtb_Switch_i_idx_0;
      Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.rtb_Switch_i_idx_0;
      Formation_FMS_B.P_mr[0] = Formation_FMS_B.pos_err_idx_0;

      // Product: '<S63>/Divide' incorporates:
      //   Product: '<S62>/Divide'

      Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.l1_a_cmd_m /
        Formation_FMS_B.u_e;

      // Product: '<S62>/Divide'
      Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.psi /
        Formation_FMS_B.pos_err_idx_2;

      // DotProduct: '<S57>/Dot Product'
      Formation_FMS_B.rtb_P_mr_m += Formation_FMS_B.pos_err_idx_0 *
        Formation_FMS_B.rtb_Switch_i_idx_0;

      // Sqrt: '<S58>/Sqrt' incorporates:
      //   Math: '<S58>/Square'
      //   Sum: '<S58>/Sum of Elements'

      Formation_FMS_B.Saturation_g = std::sqrt(Formation_FMS_B.new_pos_err_idx_0
        + Formation_FMS_B.new_pos_err_idx_1);

      // Math: '<S56>/Square'
      Formation_FMS_B.psi = Formation_FMS_B.Saturation_g *
        Formation_FMS_B.Saturation_g;

      // Sum: '<S61>/Subtract' incorporates:
      //   Product: '<S61>/Multiply'
      //   Product: '<S61>/Multiply1'

      Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.new_vel_err[0] *
        Formation_FMS_B.pos_err_idx_0 - Formation_FMS_B.P_mr[0] *
        Formation_FMS_B.rtb_Switch_i_idx_0;

      // Signum: '<S57>/Sign1'
      if (std::isnan(Formation_FMS_B.pos_err_idx_0)) {
        Formation_FMS_B.Saturation_g = (rtNaNF);
      } else if (Formation_FMS_B.pos_err_idx_0 < 0.0F) {
        Formation_FMS_B.Saturation_g = -1.0F;
      } else {
        Formation_FMS_B.Saturation_g = (Formation_FMS_B.pos_err_idx_0 > 0.0F);
      }

      // End of Signum: '<S57>/Sign1'

      // Trigonometry: '<S57>/Acos' incorporates:
      //   DotProduct: '<S57>/Dot Product'

      if (Formation_FMS_B.rtb_P_mr_m > 1.0F) {
        Formation_FMS_B.rtb_P_mr_m = 1.0F;
      } else if (Formation_FMS_B.rtb_P_mr_m < -1.0F) {
        Formation_FMS_B.rtb_P_mr_m = -1.0F;
      }

      // Switch: '<S57>/Switch2' incorporates:
      //   Constant: '<S57>/Constant4'

      if (!(Formation_FMS_B.Saturation_g != 0.0F)) {
        Formation_FMS_B.Saturation_g = 1.0F;
      }

      // Product: '<S57>/Multiply' incorporates:
      //   Switch: '<S57>/Switch2'
      //   Trigonometry: '<S57>/Acos'

      Formation_FMS_B.pos_err_idx_0 = std::acos(Formation_FMS_B.rtb_P_mr_m) *
        Formation_FMS_B.Saturation_g;

      // Saturate: '<S56>/Saturation'
      if (Formation_FMS_B.pos_err_idx_0 > 1.57079637F) {
        Formation_FMS_B.pos_err_idx_0 = 1.57079637F;
      } else if (Formation_FMS_B.pos_err_idx_0 < -1.57079637F) {
        Formation_FMS_B.pos_err_idx_0 = -1.57079637F;
      }

      // Product: '<S56>/Divide' incorporates:
      //   Constant: '<S47>/L1'
      //   Gain: '<S56>/Gain'
      //   Product: '<S56>/Multiply1'
      //   Saturate: '<S56>/Saturation'
      //   Trigonometry: '<S56>/Sin'

      Formation_FMS_B.Saturation1 = 2.0F * Formation_FMS_B.psi * std::sin
        (Formation_FMS_B.pos_err_idx_0) / FMS_PARAM.L1;

      // Saturate: '<S47>/Saturation1'
      if (Formation_FMS_B.Saturation1 > FMS_PARAM.ACC_Y_LIM) {
        // Product: '<S56>/Divide' incorporates:
        //   Saturate: '<S47>/Saturation1'

        Formation_FMS_B.Saturation1 = FMS_PARAM.ACC_Y_LIM;
      } else if (Formation_FMS_B.Saturation1 < -FMS_PARAM.ACC_Y_LIM) {
        // Product: '<S56>/Divide' incorporates:
        //   Saturate: '<S47>/Saturation1'

        Formation_FMS_B.Saturation1 = -FMS_PARAM.ACC_Y_LIM;
      }

      // End of Saturate: '<S47>/Saturation1'
    }

    // End of Outputs for SubSystem: '<S41>/Position Command'

    // Delay: '<S43>/Delay' incorporates:
    //   Constant: '<S43>/Constant'
    //   Product: '<S62>/Divide'
    //   Product: '<S63>/Divide'
    //   Sum: '<S50>/Subtract'

    if (Formation_FMS_DW.icLoad_n) {
      Formation_FMS_DW.Delay_DSTATE_c = 1000.0;
    }

    // End of Outputs for SubSystem: '<S13>/FormMission_SubSystem'
    // End of Outputs for SubSystem: '<S10>/FormMission'
    std::memset(&Formation_FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

    // Outputs for IfAction SubSystem: '<S10>/FormMission' incorporates:
    //   ActionPort: '<S13>/Action Port'

    // Outputs for Resettable SubSystem: '<S13>/FormMission_SubSystem' incorporates:
    //   ResetPort: '<S41>/Reset'

    // BusAssignment: '<S41>/Bus Assignment' incorporates:
    //   Constant: '<S42>/Constant'
    //   Gain: '<S42>/Gain'
    //   Inport: '<Root>/INS_Out'
    //   MATLAB Function: '<S44>/Consensus Controller'
    //   Outport: '<Root>/FMS_Out'
    //   Sum: '<S41>/Sum'
    //   Sum: '<S41>/Sum1'
    //   Sum: '<S42>/Sum'

    Formation_FMS_Y.FMS_Out.ax_cmd = (CONTROL_PARAM.FW_AIRSPD_TRIM -
      Formation_FMS_U.INS_Out.airspeed) * FMS_PARAM.AIRSPD_P +
      Formation_FMS_B.Sum1_e;
    Formation_FMS_Y.FMS_Out.ay_cmd = Formation_FMS_B.Saturation1 +
      Formation_FMS_B.u;

    // Gain: '<S43>/Gain2' incorporates:
    //   Delay: '<S43>/Delay'
    //   Inport: '<Root>/INS_Out'
    //   Sum: '<S43>/Sum'

    Formation_FMS_B.pos_err_idx_0 = static_cast<real32_T>
      ((Formation_FMS_DW.Delay_DSTATE_c - Formation_FMS_U.INS_Out.h_R) *
       FMS_PARAM.Z_P);

    // Saturate: '<S43>/Saturation'
    if (Formation_FMS_B.pos_err_idx_0 > CONTROL_PARAM.FW_T_CLMB_MAX) {
      Formation_FMS_B.pos_err_idx_0 = CONTROL_PARAM.FW_T_CLMB_MAX;
    } else if (Formation_FMS_B.pos_err_idx_0 < -CONTROL_PARAM.FW_T_SINK_MAX) {
      Formation_FMS_B.pos_err_idx_0 = -CONTROL_PARAM.FW_T_SINK_MAX;
    }

    // BusAssignment: '<S41>/Bus Assignment' incorporates:
    //   MATLAB Function: '<S44>/Consensus Controller'
    //   Outport: '<Root>/FMS_Out'
    //   Saturate: '<S43>/Saturation'
    //   Sum: '<S41>/Sum2'

    Formation_FMS_Y.FMS_Out.vh_cmd = Formation_FMS_B.pos_err_idx_0 +
      Formation_FMS_B.a;

    // Update for Delay: '<S43>/Delay'
    Formation_FMS_DW.icLoad_n = false;

    // End of Outputs for SubSystem: '<S13>/FormMission_SubSystem'

    // Update for UnitDelay: '<S40>/Delay Input1'
    //
    //  Block description for '<S40>/Delay Input1':
    //
    //   Store in Global RAM

    Formation_FMS_DW.DelayInput1_DSTATE_d = Formation_FMS_B.wp_index;

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

    Formation_FMS_B.FixPtRelationalOperator_m = (Formation_FMS_B.wp_index !=
      Formation_FMS_DW.DelayInput1_DSTATE_h);

    // Outputs for Resettable SubSystem: '<S12>/Mission_SubSystem' incorporates:
    //   ResetPort: '<S18>/Reset'

    // InitializeConditions for Delay: '<S20>/Delay'
    Formation_FMS_DW.icLoad_h = ((Formation_FMS_B.FixPtRelationalOperator_m &&
      (Formation_FMS_PrevZCX.Mission_SubSystem_Reset_ZCE != POS_ZCSIG)) ||
      Formation_FMS_DW.icLoad_h);
    Formation_FMS_PrevZCX.Mission_SubSystem_Reset_ZCE =
      Formation_FMS_B.FixPtRelationalOperator_m;

    // SignalConversion generated from: '<S34>/Square' incorporates:
    //   Inport: '<Root>/INS_Out'

    Formation_FMS_B.new_vel_err[0] = Formation_FMS_U.INS_Out.vn;
    Formation_FMS_B.new_vel_err[1] = Formation_FMS_U.INS_Out.ve;

    // Math: '<S35>/Math Function' incorporates:
    //   Inport: '<Root>/INS_Out'
    //   Math: '<S34>/Square'
    //   SignalConversion generated from: '<S34>/Square'

    Formation_FMS_B.new_pos_err_idx_0 = Formation_FMS_U.INS_Out.vn *
      Formation_FMS_U.INS_Out.vn;
    Formation_FMS_B.new_pos_err_idx_1 = Formation_FMS_U.INS_Out.ve *
      Formation_FMS_U.INS_Out.ve;

    // Sum: '<S35>/Sum of Elements' incorporates:
    //   Math: '<S35>/Math Function'

    Formation_FMS_B.Saturation_g = Formation_FMS_B.new_pos_err_idx_0 +
      Formation_FMS_B.new_pos_err_idx_1;

    // Math: '<S35>/Math Function1' incorporates:
    //   Sum: '<S35>/Sum of Elements'
    //
    //  About '<S35>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.Saturation_g < 0.0F) {
      Formation_FMS_B.Sum1_e = -std::sqrt(std::abs(Formation_FMS_B.Saturation_g));
    } else {
      Formation_FMS_B.Sum1_e = std::sqrt(Formation_FMS_B.Saturation_g);
    }

    // End of Math: '<S35>/Math Function1'

    // Switch: '<S35>/Switch' incorporates:
    //   Constant: '<S35>/Constant'
    //   Inport: '<Root>/INS_Out'
    //   Product: '<S35>/Product'
    //   SignalConversion generated from: '<S34>/Square'

    if (Formation_FMS_B.Sum1_e > 0.0F) {
      Formation_FMS_B.pos_err_idx_0 = Formation_FMS_U.INS_Out.vn;
      Formation_FMS_B.psi = Formation_FMS_U.INS_Out.ve;
      Formation_FMS_B.pos_err_idx_2 = Formation_FMS_B.Sum1_e;
    } else {
      Formation_FMS_B.pos_err_idx_0 = Formation_FMS_U.INS_Out.vn * 0.0F;
      Formation_FMS_B.psi = Formation_FMS_U.INS_Out.ve * 0.0F;
      Formation_FMS_B.pos_err_idx_2 = 1.0F;
    }

    // End of Switch: '<S35>/Switch'

    // Reshape: '<S24>/Reshape2' incorporates:
    //   Inport: '<Root>/INS_Out'

    Formation_FMS_B.Reshape2_bi[0] = Formation_FMS_U.INS_Out.x_R;
    Formation_FMS_B.Reshape2_bi[1] = Formation_FMS_U.INS_Out.y_R;

    // MATLAB Function: '<S25>/NearbyRefWP' incorporates:
    //   Constant: '<S23>/L1'

    Formation_FMS_NearbyRefWP(&Formation_FMS_B.Cmd_In.sp_waypoint[0],
      Formation_FMS_B.Reshape2_bi, FMS_PARAM.L1, Formation_FMS_B.new_vel_err,
      &Formation_FMS_B.Sum1_e);

    // MATLAB Function: '<S25>/SearchL1RefWP' incorporates:
    //   Constant: '<S23>/L1'

    Formation_FMS_SearchL1RefWP(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
      &Formation_FMS_B.Cmd_In.sp_waypoint[0], Formation_FMS_B.Reshape2_bi,
      FMS_PARAM.L1, Formation_FMS_B.P_mr, &Formation_FMS_B.u);

    // MATLAB Function: '<S25>/OutRegionRegWP'
    Formation_FMS_OutRegionRegWP(&Formation_FMS_B.Cmd_In.cur_waypoint[0],
      &Formation_FMS_B.Cmd_In.sp_waypoint[0], Formation_FMS_B.Reshape2_bi,
      Formation_FMS_B.P_b);

    // Switch: '<S25>/Switch1' incorporates:
    //   Constant: '<S27>/Constant'
    //   Constant: '<S28>/Constant'
    //   Product: '<S38>/Divide'
    //   RelationalOperator: '<S27>/Compare'
    //   RelationalOperator: '<S28>/Compare'
    //   Switch: '<S25>/Switch'

    if (Formation_FMS_B.Sum1_e > 0.0F) {
      Formation_FMS_B.P_mr[0] = Formation_FMS_B.new_vel_err[0];
      Formation_FMS_B.P_mr[1] = Formation_FMS_B.new_vel_err[1];
    } else if (!(Formation_FMS_B.u >= 0.0F)) {
      // Product: '<S38>/Divide' incorporates:
      //   Switch: '<S25>/Switch'

      Formation_FMS_B.P_mr[0] = Formation_FMS_B.P_b[0];
      Formation_FMS_B.P_mr[1] = Formation_FMS_B.P_b[1];
    }

    // End of Switch: '<S25>/Switch1'

    // Sum: '<S26>/Subtract' incorporates:
    //   Inport: '<Root>/INS_Out'
    //   Product: '<S38>/Divide'
    //   Reshape: '<S24>/Reshape2'

    Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.P_mr[0] -
      Formation_FMS_U.INS_Out.x_R;

    // Math: '<S36>/Math Function'
    Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.l1_a_cmd_m *
      Formation_FMS_B.l1_a_cmd_m;
    Formation_FMS_B.P_mr[0] = Formation_FMS_B.l1_a_cmd_m;

    // Sum: '<S26>/Subtract' incorporates:
    //   Inport: '<Root>/INS_Out'
    //   Product: '<S38>/Divide'
    //   Reshape: '<S24>/Reshape2'

    Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.P_mr[1] -
      Formation_FMS_U.INS_Out.y_R;

    // Sum: '<S36>/Sum of Elements' incorporates:
    //   Math: '<S36>/Math Function'

    Formation_FMS_B.Saturation_g = Formation_FMS_B.l1_a_cmd_m *
      Formation_FMS_B.l1_a_cmd_m + Formation_FMS_B.new_vel_err[0];

    // Math: '<S36>/Math Function1' incorporates:
    //   Sum: '<S36>/Sum of Elements'
    //
    //  About '<S36>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.Saturation_g < 0.0F) {
      Formation_FMS_B.Sum1_e = -std::sqrt(std::abs(Formation_FMS_B.Saturation_g));
    } else {
      Formation_FMS_B.Sum1_e = std::sqrt(Formation_FMS_B.Saturation_g);
    }

    // End of Math: '<S36>/Math Function1'

    // Switch: '<S36>/Switch' incorporates:
    //   Constant: '<S36>/Constant'
    //   Product: '<S36>/Product'
    //   Sum: '<S26>/Subtract'
    //   Switch: '<S39>/Switch'

    if (Formation_FMS_B.Sum1_e > 0.0F) {
      Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.P_mr[0];
      Formation_FMS_B.u_e = Formation_FMS_B.Sum1_e;
    } else {
      Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.P_mr[0] * 0.0F;
      Formation_FMS_B.l1_a_cmd_m *= 0.0F;
      Formation_FMS_B.u_e = 1.0F;
    }

    // End of Switch: '<S36>/Switch'

    // Product: '<S35>/Divide'
    Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.pos_err_idx_0 /
      Formation_FMS_B.pos_err_idx_2;
    Formation_FMS_B.new_vel_err[1] = Formation_FMS_B.psi /
      Formation_FMS_B.pos_err_idx_2;

    // Sum: '<S38>/Sum of Elements' incorporates:
    //   Math: '<S38>/Math Function'
    //   SignalConversion generated from: '<S38>/Math Function'

    Formation_FMS_B.Saturation_g = Formation_FMS_B.new_vel_err[1] *
      Formation_FMS_B.new_vel_err[1] + Formation_FMS_B.new_vel_err[0] *
      Formation_FMS_B.new_vel_err[0];

    // Math: '<S38>/Math Function1' incorporates:
    //   Sum: '<S38>/Sum of Elements'
    //
    //  About '<S38>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.Saturation_g < 0.0F) {
      Formation_FMS_B.Sum1_e = -std::sqrt(std::abs(Formation_FMS_B.Saturation_g));
    } else {
      Formation_FMS_B.Sum1_e = std::sqrt(Formation_FMS_B.Saturation_g);
    }

    // End of Math: '<S38>/Math Function1'

    // Switch: '<S38>/Switch' incorporates:
    //   Constant: '<S38>/Constant'
    //   Product: '<S38>/Product'
    //   SignalConversion generated from: '<S38>/Math Function'

    if (Formation_FMS_B.Sum1_e > 0.0F) {
      Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.new_vel_err[1];
      Formation_FMS_B.psi = Formation_FMS_B.new_vel_err[0];
      Formation_FMS_B.pos_err_idx_2 = Formation_FMS_B.Sum1_e;
    } else {
      Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.new_vel_err[1] * 0.0F;
      Formation_FMS_B.psi = Formation_FMS_B.new_vel_err[0] * 0.0F;
      Formation_FMS_B.pos_err_idx_2 = 1.0F;
    }

    // End of Switch: '<S38>/Switch'

    // Product: '<S36>/Divide' incorporates:
    //   Product: '<S39>/Divide'

    Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.rtb_Switch_i_idx_0 /
      Formation_FMS_B.u_e;
    Formation_FMS_B.new_vel_err[1] = Formation_FMS_B.l1_a_cmd_m /
      Formation_FMS_B.u_e;

    // Sum: '<S39>/Sum of Elements' incorporates:
    //   Math: '<S39>/Math Function'
    //   SignalConversion generated from: '<S39>/Math Function'

    Formation_FMS_B.Saturation_g = Formation_FMS_B.new_vel_err[1] *
      Formation_FMS_B.new_vel_err[1] + Formation_FMS_B.new_vel_err[0] *
      Formation_FMS_B.new_vel_err[0];

    // Math: '<S39>/Math Function1' incorporates:
    //   Sum: '<S39>/Sum of Elements'
    //
    //  About '<S39>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.Saturation_g < 0.0F) {
      Formation_FMS_B.Sum1_e = -std::sqrt(std::abs(Formation_FMS_B.Saturation_g));
    } else {
      Formation_FMS_B.Sum1_e = std::sqrt(Formation_FMS_B.Saturation_g);
    }

    // End of Math: '<S39>/Math Function1'

    // Switch: '<S39>/Switch' incorporates:
    //   Constant: '<S39>/Constant'
    //   Product: '<S39>/Product'
    //   SignalConversion generated from: '<S39>/Math Function'

    if (Formation_FMS_B.Sum1_e > 0.0F) {
      Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.new_vel_err[1];
      Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.new_vel_err[0];
      Formation_FMS_B.u_e = Formation_FMS_B.Sum1_e;
    } else {
      Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.new_vel_err[1] * 0.0F;
      Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.new_vel_err[0] * 0.0F;
      Formation_FMS_B.u_e = 1.0F;
    }

    // End of Switch: '<S39>/Switch'

    // Product: '<S39>/Divide'
    Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.rtb_Switch_i_idx_0 /
      Formation_FMS_B.u_e;

    // Product: '<S38>/Divide'
    Formation_FMS_B.P_mr[0] = Formation_FMS_B.pos_err_idx_0 /
      Formation_FMS_B.pos_err_idx_2;

    // Product: '<S39>/Divide'
    Formation_FMS_B.new_vel_err[1] = Formation_FMS_B.l1_a_cmd_m /
      Formation_FMS_B.u_e;

    // Product: '<S38>/Divide'
    Formation_FMS_B.P_mr[1] = Formation_FMS_B.psi /
      Formation_FMS_B.pos_err_idx_2;

    // Sqrt: '<S34>/Sqrt' incorporates:
    //   Math: '<S34>/Square'
    //   Sum: '<S34>/Sum of Elements'

    Formation_FMS_B.Sum1_e = std::sqrt(Formation_FMS_B.new_pos_err_idx_0 +
      Formation_FMS_B.new_pos_err_idx_1);

    // Math: '<S32>/Square'
    Formation_FMS_B.psi = Formation_FMS_B.Sum1_e * Formation_FMS_B.Sum1_e;

    // Sum: '<S37>/Subtract' incorporates:
    //   Product: '<S37>/Multiply'
    //   Product: '<S37>/Multiply1'

    Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.new_vel_err[0] *
      Formation_FMS_B.P_mr[1] - Formation_FMS_B.P_mr[0] *
      Formation_FMS_B.new_vel_err[1];

    // Signum: '<S33>/Sign1'
    if (std::isnan(Formation_FMS_B.pos_err_idx_0)) {
      Formation_FMS_B.Sum1_e = (rtNaNF);
    } else if (Formation_FMS_B.pos_err_idx_0 < 0.0F) {
      Formation_FMS_B.Sum1_e = -1.0F;
    } else {
      Formation_FMS_B.Sum1_e = (Formation_FMS_B.pos_err_idx_0 > 0.0F);
    }

    // End of Signum: '<S33>/Sign1'

    // Delay: '<S20>/Delay' incorporates:
    //   Constant: '<S20>/Constant'

    if (Formation_FMS_DW.icLoad_h) {
      Formation_FMS_DW.Delay_DSTATE_l = 1000.0;
    }

    // End of Outputs for SubSystem: '<S12>/Mission_SubSystem'
    // End of Outputs for SubSystem: '<S10>/FormAssemble'
    std::memset(&Formation_FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

    // Outputs for IfAction SubSystem: '<S10>/FormAssemble' incorporates:
    //   ActionPort: '<S12>/Action Port'

    // Outputs for Resettable SubSystem: '<S12>/Mission_SubSystem' incorporates:
    //   ResetPort: '<S18>/Reset'

    // BusAssignment: '<S18>/Bus Assignment' incorporates:
    //   Constant: '<S19>/Constant'
    //   Gain: '<S19>/Gain1'
    //   Inport: '<Root>/Formation_Cross'
    //   Inport: '<Root>/INS_Out'
    //   MATLAB Function: '<S19>/Time Consensus Controller'
    //   Outport: '<Root>/FMS_Out'
    //   Sum: '<S19>/Sum'
    //   Sum: '<S19>/Sum1'

    Formation_FMS_Y.FMS_Out.ax_cmd =
      (((Formation_FMS_U.Formation_Cross.left_time[0] -
         Formation_FMS_U.Formation_Cross.left_time[0]) * 0.0F +
        (Formation_FMS_U.Formation_Cross.left_time[0] -
         Formation_FMS_U.Formation_Cross.left_time[1]) * 0.2F) +
       (Formation_FMS_U.Formation_Cross.left_time[0] -
        Formation_FMS_U.Formation_Cross.left_time[2]) * 0.2F) * 5.0F +
      (CONTROL_PARAM.FW_AIRSPD_TRIM - Formation_FMS_U.INS_Out.airspeed);

    // DotProduct: '<S33>/Dot Product'
    Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.P_mr[0] *
      Formation_FMS_B.new_vel_err[0] + Formation_FMS_B.P_mr[1] *
      Formation_FMS_B.new_vel_err[1];

    // Trigonometry: '<S33>/Acos' incorporates:
    //   DotProduct: '<S33>/Dot Product'

    if (Formation_FMS_B.pos_err_idx_0 > 1.0F) {
      Formation_FMS_B.pos_err_idx_0 = 1.0F;
    } else if (Formation_FMS_B.pos_err_idx_0 < -1.0F) {
      Formation_FMS_B.pos_err_idx_0 = -1.0F;
    }

    // Switch: '<S33>/Switch2' incorporates:
    //   Constant: '<S33>/Constant4'

    if (!(Formation_FMS_B.Sum1_e != 0.0F)) {
      Formation_FMS_B.Sum1_e = 1.0F;
    }

    // Product: '<S33>/Multiply' incorporates:
    //   Switch: '<S33>/Switch2'
    //   Trigonometry: '<S33>/Acos'

    Formation_FMS_B.pos_err_idx_0 = std::acos(Formation_FMS_B.pos_err_idx_0) *
      Formation_FMS_B.Sum1_e;

    // Saturate: '<S32>/Saturation'
    if (Formation_FMS_B.pos_err_idx_0 > 1.57079637F) {
      Formation_FMS_B.pos_err_idx_0 = 1.57079637F;
    } else if (Formation_FMS_B.pos_err_idx_0 < -1.57079637F) {
      Formation_FMS_B.pos_err_idx_0 = -1.57079637F;
    }

    // Product: '<S32>/Divide' incorporates:
    //   Constant: '<S23>/L1'
    //   Gain: '<S32>/Gain'
    //   Product: '<S32>/Multiply1'
    //   Saturate: '<S32>/Saturation'
    //   Trigonometry: '<S32>/Sin'

    Formation_FMS_B.pos_err_idx_0 = 2.0F * Formation_FMS_B.psi * std::sin
      (Formation_FMS_B.pos_err_idx_0) / FMS_PARAM.L1;

    // Saturate: '<S23>/Saturation1'
    if (Formation_FMS_B.pos_err_idx_0 > FMS_PARAM.ACC_Y_LIM) {
      // BusAssignment: '<S18>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.ay_cmd = FMS_PARAM.ACC_Y_LIM;
    } else if (Formation_FMS_B.pos_err_idx_0 < -FMS_PARAM.ACC_Y_LIM) {
      // BusAssignment: '<S18>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.ay_cmd = -FMS_PARAM.ACC_Y_LIM;
    } else {
      // BusAssignment: '<S18>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.ay_cmd = Formation_FMS_B.pos_err_idx_0;
    }

    // End of Saturate: '<S23>/Saturation1'

    // Gain: '<S20>/Gain2' incorporates:
    //   Delay: '<S20>/Delay'
    //   Inport: '<Root>/INS_Out'
    //   Sum: '<S20>/Sum'

    Formation_FMS_B.pos_err_idx_0 = static_cast<real32_T>
      ((Formation_FMS_DW.Delay_DSTATE_l - Formation_FMS_U.INS_Out.h_R) *
       FMS_PARAM.Z_P);

    // Saturate: '<S20>/Saturation'
    if (Formation_FMS_B.pos_err_idx_0 > CONTROL_PARAM.FW_T_CLMB_MAX) {
      // BusAssignment: '<S18>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.vh_cmd = CONTROL_PARAM.FW_T_CLMB_MAX;
    } else if (Formation_FMS_B.pos_err_idx_0 < -CONTROL_PARAM.FW_T_SINK_MAX) {
      // BusAssignment: '<S18>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.vh_cmd = -CONTROL_PARAM.FW_T_SINK_MAX;
    } else {
      // BusAssignment: '<S18>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.vh_cmd = Formation_FMS_B.pos_err_idx_0;
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

    Formation_FMS_DW.DelayInput1_DSTATE_h = Formation_FMS_B.wp_index;

    // End of Outputs for SubSystem: '<S10>/FormAssemble'
    break;

   case 2:
    if (Formation_FMS_DW.SwitchCase_ActiveSubsystem !=
        Formation_FMS_B.rtPrevAction) {
      // InitializeConditions for IfAction SubSystem: '<S10>/Hold' incorporates:
      //   ActionPort: '<S14>/Action Port'

      // InitializeConditions for SwitchCase: '<S10>/Switch Case' incorporates:
      //   Delay: '<S65>/Delay'
      //   Delay: '<S69>/start_vel'

      Formation_FMS_DW.icLoad_c = true;
      Formation_FMS_DW.icLoad_m = true;

      // End of InitializeConditions for SubSystem: '<S10>/Hold'
    }

    // Outputs for IfAction SubSystem: '<S10>/Hold' incorporates:
    //   ActionPort: '<S14>/Action Port'

    // Math: '<S76>/Math Function' incorporates:
    //   Inport: '<Root>/INS_Out'
    //   Math: '<S75>/Square'
    //   SignalConversion generated from: '<S75>/Square'

    Formation_FMS_B.new_pos_err_idx_0 = Formation_FMS_U.INS_Out.vn *
      Formation_FMS_U.INS_Out.vn;
    Formation_FMS_B.new_pos_err_idx_1 = Formation_FMS_U.INS_Out.ve *
      Formation_FMS_U.INS_Out.ve;

    // Sum: '<S76>/Sum of Elements' incorporates:
    //   Math: '<S76>/Math Function'

    Formation_FMS_B.Saturation_g = Formation_FMS_B.new_pos_err_idx_0 +
      Formation_FMS_B.new_pos_err_idx_1;

    // Math: '<S76>/Math Function1' incorporates:
    //   Sum: '<S76>/Sum of Elements'
    //
    //  About '<S76>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.Saturation_g < 0.0F) {
      Formation_FMS_B.Sum1_e = -std::sqrt(std::abs(Formation_FMS_B.Saturation_g));
    } else {
      Formation_FMS_B.Sum1_e = std::sqrt(Formation_FMS_B.Saturation_g);
    }

    // End of Math: '<S76>/Math Function1'

    // Switch: '<S76>/Switch' incorporates:
    //   Constant: '<S76>/Constant'
    //   Inport: '<Root>/INS_Out'
    //   Product: '<S76>/Product'
    //   SignalConversion generated from: '<S75>/Square'

    if (Formation_FMS_B.Sum1_e > 0.0F) {
      Formation_FMS_B.pos_err_idx_0 = Formation_FMS_U.INS_Out.vn;
      Formation_FMS_B.psi = Formation_FMS_U.INS_Out.ve;
      Formation_FMS_B.pos_err_idx_2 = Formation_FMS_B.Sum1_e;
    } else {
      Formation_FMS_B.pos_err_idx_0 = Formation_FMS_U.INS_Out.vn * 0.0F;
      Formation_FMS_B.psi = Formation_FMS_U.INS_Out.ve * 0.0F;
      Formation_FMS_B.pos_err_idx_2 = 1.0F;
    }

    // End of Switch: '<S76>/Switch'

    // Delay: '<S69>/start_vel' incorporates:
    //   Inport: '<Root>/INS_Out'
    //   SignalConversion generated from: '<S75>/Square'

    if (Formation_FMS_DW.icLoad_c) {
      Formation_FMS_DW.start_vel_DSTATE[0] = Formation_FMS_U.INS_Out.vn;
      Formation_FMS_DW.start_vel_DSTATE[1] = Formation_FMS_U.INS_Out.ve;
    }

    // Sum: '<S81>/Sum of Elements' incorporates:
    //   Delay: '<S69>/start_vel'
    //   Math: '<S81>/Math Function'

    Formation_FMS_B.Saturation_g = Formation_FMS_DW.start_vel_DSTATE[0] *
      Formation_FMS_DW.start_vel_DSTATE[0] + Formation_FMS_DW.start_vel_DSTATE[1]
      * Formation_FMS_DW.start_vel_DSTATE[1];

    // Math: '<S81>/Math Function1' incorporates:
    //   Sum: '<S81>/Sum of Elements'
    //
    //  About '<S81>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.Saturation_g < 0.0F) {
      Formation_FMS_B.Sum1_e = -std::sqrt(std::abs(Formation_FMS_B.Saturation_g));
    } else {
      Formation_FMS_B.Sum1_e = std::sqrt(Formation_FMS_B.Saturation_g);
    }

    // End of Math: '<S81>/Math Function1'

    // Switch: '<S81>/Switch' incorporates:
    //   Constant: '<S81>/Constant'
    //   Delay: '<S69>/start_vel'
    //   Product: '<S81>/Product'

    if (Formation_FMS_B.Sum1_e > 0.0F) {
      Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_DW.start_vel_DSTATE[0];
      Formation_FMS_B.l1_a_cmd_m = Formation_FMS_DW.start_vel_DSTATE[1];
      Formation_FMS_B.u_e = Formation_FMS_B.Sum1_e;
    } else {
      Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_DW.start_vel_DSTATE[0] *
        0.0F;
      Formation_FMS_B.l1_a_cmd_m = Formation_FMS_DW.start_vel_DSTATE[1] * 0.0F;
      Formation_FMS_B.u_e = 1.0F;
    }

    // End of Switch: '<S81>/Switch'

    // Product: '<S76>/Divide'
    Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.pos_err_idx_0 /
      Formation_FMS_B.pos_err_idx_2;
    Formation_FMS_B.new_vel_err[1] = Formation_FMS_B.psi /
      Formation_FMS_B.pos_err_idx_2;

    // Sum: '<S79>/Sum of Elements' incorporates:
    //   Math: '<S79>/Math Function'
    //   SignalConversion generated from: '<S79>/Math Function'

    Formation_FMS_B.Saturation_g = Formation_FMS_B.new_vel_err[1] *
      Formation_FMS_B.new_vel_err[1] + Formation_FMS_B.new_vel_err[0] *
      Formation_FMS_B.new_vel_err[0];

    // Math: '<S79>/Math Function1' incorporates:
    //   Sum: '<S79>/Sum of Elements'
    //
    //  About '<S79>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.Saturation_g < 0.0F) {
      Formation_FMS_B.Sum1_e = -std::sqrt(std::abs(Formation_FMS_B.Saturation_g));
    } else {
      Formation_FMS_B.Sum1_e = std::sqrt(Formation_FMS_B.Saturation_g);
    }

    // End of Math: '<S79>/Math Function1'

    // Switch: '<S79>/Switch' incorporates:
    //   Constant: '<S79>/Constant'
    //   Product: '<S79>/Product'
    //   SignalConversion generated from: '<S79>/Math Function'

    if (Formation_FMS_B.Sum1_e > 0.0F) {
      Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.new_vel_err[1];
      Formation_FMS_B.psi = Formation_FMS_B.new_vel_err[0];
      Formation_FMS_B.pos_err_idx_2 = Formation_FMS_B.Sum1_e;
    } else {
      Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.new_vel_err[1] * 0.0F;
      Formation_FMS_B.psi = Formation_FMS_B.new_vel_err[0] * 0.0F;
      Formation_FMS_B.pos_err_idx_2 = 1.0F;
    }

    // End of Switch: '<S79>/Switch'

    // MinMax: '<S67>/Max' incorporates:
    //   Constant: '<S66>/L1'
    //   Constant: '<S66>/R'
    //   Gain: '<S67>/Gain'

    Formation_FMS_B.Sum1_e = std::fmax(FMS_PARAM.LOITER_R, 0.5F * FMS_PARAM.L1);

    // MATLAB Function: '<S67>/SearchL1RefWP' incorporates:
    //   Constant: '<S66>/L1'
    //   Inport: '<Root>/INS_Out'
    //   Reshape: '<S67>/Reshape2'

    Formation_FMS_B.P_mr[0] = 0.0F;
    Formation_FMS_B.P_mr[1] = 0.0F;
    if ((Formation_FMS_U.INS_Out.x_R == Formation_FMS_B.Cmd_In.cur_waypoint[0]) &&
        (Formation_FMS_U.INS_Out.y_R == Formation_FMS_B.Cmd_In.cur_waypoint[1]) &&
        (Formation_FMS_B.Sum1_e == FMS_PARAM.L1)) {
      Formation_FMS_B.n = 0;
    } else {
      Formation_FMS_B.u = Formation_FMS_B.Cmd_In.cur_waypoint[0] -
        Formation_FMS_U.INS_Out.x_R;
      Formation_FMS_B.Reshape2_bi[0] = Formation_FMS_B.u * Formation_FMS_B.u;
      Formation_FMS_B.P_b[0] = Formation_FMS_B.u;
      Formation_FMS_B.u = Formation_FMS_B.Cmd_In.cur_waypoint[1] -
        Formation_FMS_U.INS_Out.y_R;
      Formation_FMS_B.Saturation_g = std::sqrt(Formation_FMS_B.u *
        Formation_FMS_B.u + Formation_FMS_B.Reshape2_bi[0]);
      Formation_FMS_B.a_tmp = FMS_PARAM.L1 * FMS_PARAM.L1;
      Formation_FMS_B.a = ((Formation_FMS_B.Saturation_g *
                            Formation_FMS_B.Saturation_g + Formation_FMS_B.a_tmp)
                           - Formation_FMS_B.Sum1_e * Formation_FMS_B.Sum1_e) /
        (2.0F * Formation_FMS_B.Saturation_g);
      Formation_FMS_B.rtb_P_mr_m = Formation_FMS_B.P_b[0] /
        Formation_FMS_B.Saturation_g;
      Formation_FMS_B.u /= Formation_FMS_B.Saturation_g;
      Formation_FMS_B.Saturation_g = Formation_FMS_B.a * Formation_FMS_B.a;
      if (Formation_FMS_B.Saturation_g > Formation_FMS_B.a_tmp) {
        Formation_FMS_B.n = 0;
      } else if (Formation_FMS_B.Saturation_g == Formation_FMS_B.a_tmp) {
        Formation_FMS_B.n = 1;
        Formation_FMS_B.P_mr[0] = Formation_FMS_B.a * Formation_FMS_B.rtb_P_mr_m
          + Formation_FMS_U.INS_Out.x_R;
        Formation_FMS_B.P_mr[1] = Formation_FMS_B.a * Formation_FMS_B.u +
          Formation_FMS_U.INS_Out.y_R;
      } else {
        Formation_FMS_B.n = 2;
        Formation_FMS_B.Saturation_g = std::sqrt(Formation_FMS_B.a_tmp -
          Formation_FMS_B.Saturation_g);
        Formation_FMS_B.P_mr[0] = (0.0F * Formation_FMS_B.rtb_P_mr_m -
          Formation_FMS_B.u) * Formation_FMS_B.Saturation_g + (Formation_FMS_B.a
          * Formation_FMS_B.rtb_P_mr_m + Formation_FMS_U.INS_Out.x_R);
        Formation_FMS_B.P_mr[1] = (0.0F * Formation_FMS_B.u +
          Formation_FMS_B.rtb_P_mr_m) * Formation_FMS_B.Saturation_g +
          (Formation_FMS_B.a * Formation_FMS_B.u + Formation_FMS_U.INS_Out.y_R);
      }
    }

    // End of MATLAB Function: '<S67>/SearchL1RefWP'

    // RelationalOperator: '<S70>/Compare' incorporates:
    //   Constant: '<S70>/Constant'

    Formation_FMS_B.FixPtRelationalOperator_m = (Formation_FMS_B.n > 0);

    // MATLAB Function: '<S67>/OutRegionRegWP' incorporates:
    //   Inport: '<Root>/INS_Out'
    //   Reshape: '<S67>/Reshape2'

    Formation_FMS_B.u = Formation_FMS_U.INS_Out.x_R -
      Formation_FMS_B.Cmd_In.cur_waypoint[0];
    Formation_FMS_B.Reshape2_bi[0] = Formation_FMS_B.u * Formation_FMS_B.u;
    Formation_FMS_B.u = Formation_FMS_U.INS_Out.y_R -
      Formation_FMS_B.Cmd_In.cur_waypoint[1];
    Formation_FMS_B.Reshape2_bi[1] = Formation_FMS_B.u * Formation_FMS_B.u;

    // Switch: '<S67>/Switch' incorporates:
    //   Constant: '<S66>/L1'
    //   Inport: '<Root>/INS_Out'
    //   MATLAB Function: '<S67>/OutRegionRegWP'
    //   Product: '<S81>/Divide'
    //   Reshape: '<S67>/Reshape2'

    if (Formation_FMS_B.FixPtRelationalOperator_m) {
      Formation_FMS_B.Saturation_g = Formation_FMS_B.P_mr[0];
    } else if (Formation_FMS_B.Reshape2_bi[0] + Formation_FMS_B.Reshape2_bi[1] >
               Formation_FMS_B.Sum1_e * Formation_FMS_B.Sum1_e) {
      // MATLAB Function: '<S67>/OutRegionRegWP'
      Formation_FMS_B.Saturation_g = Formation_FMS_B.Cmd_In.cur_waypoint[0];
    } else {
      Formation_FMS_B.Saturation_g = Formation_FMS_B.rtb_Switch_i_idx_0 /
        Formation_FMS_B.u_e * FMS_PARAM.L1 + Formation_FMS_U.INS_Out.x_R;
    }

    // Sum: '<S68>/Subtract' incorporates:
    //   Inport: '<Root>/INS_Out'
    //   Switch: '<S67>/Switch'

    Formation_FMS_B.P_b[0] = Formation_FMS_B.Saturation_g -
      Formation_FMS_U.INS_Out.x_R;

    // Switch: '<S67>/Switch' incorporates:
    //   Constant: '<S66>/L1'
    //   Inport: '<Root>/INS_Out'
    //   MATLAB Function: '<S67>/OutRegionRegWP'
    //   Product: '<S81>/Divide'
    //   Reshape: '<S67>/Reshape2'

    if (Formation_FMS_B.FixPtRelationalOperator_m) {
      Formation_FMS_B.Saturation_g = Formation_FMS_B.P_mr[1];
    } else if (Formation_FMS_B.Reshape2_bi[0] + Formation_FMS_B.Reshape2_bi[1] >
               Formation_FMS_B.Sum1_e * Formation_FMS_B.Sum1_e) {
      // MATLAB Function: '<S67>/OutRegionRegWP'
      Formation_FMS_B.Saturation_g = Formation_FMS_B.Cmd_In.cur_waypoint[1];
    } else {
      Formation_FMS_B.Saturation_g = Formation_FMS_B.l1_a_cmd_m /
        Formation_FMS_B.u_e * FMS_PARAM.L1 + Formation_FMS_U.INS_Out.y_R;
    }

    // Sum: '<S68>/Subtract' incorporates:
    //   Inport: '<Root>/INS_Out'
    //   Switch: '<S67>/Switch'

    Formation_FMS_B.P_b[1] = Formation_FMS_B.Saturation_g -
      Formation_FMS_U.INS_Out.y_R;

    // Sum: '<S77>/Sum of Elements' incorporates:
    //   Math: '<S77>/Math Function'
    //   Sum: '<S68>/Subtract'

    Formation_FMS_B.Saturation_g = Formation_FMS_B.P_b[0] * Formation_FMS_B.P_b
      [0] + Formation_FMS_B.P_b[1] * Formation_FMS_B.P_b[1];

    // Math: '<S77>/Math Function1' incorporates:
    //   Sum: '<S77>/Sum of Elements'
    //
    //  About '<S77>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.Saturation_g < 0.0F) {
      Formation_FMS_B.Sum1_e = -std::sqrt(std::abs(Formation_FMS_B.Saturation_g));
    } else {
      Formation_FMS_B.Sum1_e = std::sqrt(Formation_FMS_B.Saturation_g);
    }

    // End of Math: '<S77>/Math Function1'

    // Switch: '<S77>/Switch' incorporates:
    //   Constant: '<S77>/Constant'
    //   Product: '<S77>/Product'
    //   Sum: '<S68>/Subtract'
    //   Switch: '<S80>/Switch'

    if (Formation_FMS_B.Sum1_e > 0.0F) {
      Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.P_b[0];
      Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.P_b[1];
      Formation_FMS_B.u_e = Formation_FMS_B.Sum1_e;
    } else {
      Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.P_b[0] * 0.0F;
      Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.P_b[1] * 0.0F;
      Formation_FMS_B.u_e = 1.0F;
    }

    // End of Switch: '<S77>/Switch'

    // Product: '<S77>/Divide' incorporates:
    //   Product: '<S80>/Divide'

    Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.rtb_Switch_i_idx_0 /
      Formation_FMS_B.u_e;
    Formation_FMS_B.new_vel_err[1] = Formation_FMS_B.l1_a_cmd_m /
      Formation_FMS_B.u_e;

    // Sum: '<S80>/Sum of Elements' incorporates:
    //   Math: '<S80>/Math Function'
    //   SignalConversion generated from: '<S80>/Math Function'

    Formation_FMS_B.Saturation_g = Formation_FMS_B.new_vel_err[1] *
      Formation_FMS_B.new_vel_err[1] + Formation_FMS_B.new_vel_err[0] *
      Formation_FMS_B.new_vel_err[0];

    // Math: '<S80>/Math Function1' incorporates:
    //   Sum: '<S80>/Sum of Elements'
    //
    //  About '<S80>/Math Function1':
    //   Operator: sqrt

    if (Formation_FMS_B.Saturation_g < 0.0F) {
      Formation_FMS_B.Sum1_e = -std::sqrt(std::abs(Formation_FMS_B.Saturation_g));
    } else {
      Formation_FMS_B.Sum1_e = std::sqrt(Formation_FMS_B.Saturation_g);
    }

    // End of Math: '<S80>/Math Function1'

    // Switch: '<S80>/Switch' incorporates:
    //   Constant: '<S80>/Constant'
    //   Product: '<S80>/Product'
    //   SignalConversion generated from: '<S80>/Math Function'

    if (Formation_FMS_B.Sum1_e > 0.0F) {
      Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.new_vel_err[1];
      Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.new_vel_err[0];
      Formation_FMS_B.u_e = Formation_FMS_B.Sum1_e;
    } else {
      Formation_FMS_B.rtb_Switch_i_idx_0 = Formation_FMS_B.new_vel_err[1] * 0.0F;
      Formation_FMS_B.l1_a_cmd_m = Formation_FMS_B.new_vel_err[0] * 0.0F;
      Formation_FMS_B.u_e = 1.0F;
    }

    // End of Switch: '<S80>/Switch'

    // Product: '<S80>/Divide'
    Formation_FMS_B.new_vel_err[0] = Formation_FMS_B.rtb_Switch_i_idx_0 /
      Formation_FMS_B.u_e;

    // Product: '<S79>/Divide'
    Formation_FMS_B.P_mr[0] = Formation_FMS_B.pos_err_idx_0 /
      Formation_FMS_B.pos_err_idx_2;

    // Product: '<S80>/Divide'
    Formation_FMS_B.new_vel_err[1] = Formation_FMS_B.l1_a_cmd_m /
      Formation_FMS_B.u_e;

    // Product: '<S79>/Divide'
    Formation_FMS_B.P_mr[1] = Formation_FMS_B.psi /
      Formation_FMS_B.pos_err_idx_2;

    // Sqrt: '<S75>/Sqrt' incorporates:
    //   Math: '<S75>/Square'
    //   Sum: '<S75>/Sum of Elements'

    Formation_FMS_B.Sum1_e = std::sqrt(Formation_FMS_B.new_pos_err_idx_0 +
      Formation_FMS_B.new_pos_err_idx_1);

    // Math: '<S73>/Square'
    Formation_FMS_B.psi = Formation_FMS_B.Sum1_e * Formation_FMS_B.Sum1_e;

    // Sum: '<S78>/Subtract' incorporates:
    //   Product: '<S78>/Multiply'
    //   Product: '<S78>/Multiply1'

    Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.new_vel_err[0] *
      Formation_FMS_B.P_mr[1] - Formation_FMS_B.P_mr[0] *
      Formation_FMS_B.new_vel_err[1];

    // Signum: '<S74>/Sign1'
    if (std::isnan(Formation_FMS_B.pos_err_idx_0)) {
      Formation_FMS_B.Sum1_e = (rtNaNF);
    } else if (Formation_FMS_B.pos_err_idx_0 < 0.0F) {
      Formation_FMS_B.Sum1_e = -1.0F;
    } else {
      Formation_FMS_B.Sum1_e = (Formation_FMS_B.pos_err_idx_0 > 0.0F);
    }

    // End of Signum: '<S74>/Sign1'

    // Delay: '<S65>/Delay' incorporates:
    //   Constant: '<S65>/Constant'

    if (Formation_FMS_DW.icLoad_m) {
      Formation_FMS_DW.Delay_DSTATE = 1000.0;
    }

    // End of Outputs for SubSystem: '<S10>/Hold'
    std::memset(&Formation_FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

    // Outputs for IfAction SubSystem: '<S10>/Hold' incorporates:
    //   ActionPort: '<S14>/Action Port'

    // BusAssignment: '<S14>/Bus Assignment' incorporates:
    //   Constant: '<S64>/Constant'
    //   Inport: '<Root>/INS_Out'
    //   Outport: '<Root>/FMS_Out'
    //   Sum: '<S64>/Sum'

    Formation_FMS_Y.FMS_Out.ax_cmd = CONTROL_PARAM.FW_AIRSPD_TRIM -
      Formation_FMS_U.INS_Out.airspeed;

    // DotProduct: '<S74>/Dot Product'
    Formation_FMS_B.pos_err_idx_0 = Formation_FMS_B.P_mr[0] *
      Formation_FMS_B.new_vel_err[0] + Formation_FMS_B.P_mr[1] *
      Formation_FMS_B.new_vel_err[1];

    // Trigonometry: '<S74>/Acos' incorporates:
    //   DotProduct: '<S74>/Dot Product'

    if (Formation_FMS_B.pos_err_idx_0 > 1.0F) {
      Formation_FMS_B.pos_err_idx_0 = 1.0F;
    } else if (Formation_FMS_B.pos_err_idx_0 < -1.0F) {
      Formation_FMS_B.pos_err_idx_0 = -1.0F;
    }

    // Switch: '<S74>/Switch2' incorporates:
    //   Constant: '<S74>/Constant4'

    if (!(Formation_FMS_B.Sum1_e != 0.0F)) {
      Formation_FMS_B.Sum1_e = 1.0F;
    }

    // Product: '<S74>/Multiply' incorporates:
    //   Switch: '<S74>/Switch2'
    //   Trigonometry: '<S74>/Acos'

    Formation_FMS_B.pos_err_idx_0 = std::acos(Formation_FMS_B.pos_err_idx_0) *
      Formation_FMS_B.Sum1_e;

    // Saturate: '<S73>/Saturation'
    if (Formation_FMS_B.pos_err_idx_0 > 1.57079637F) {
      Formation_FMS_B.pos_err_idx_0 = 1.57079637F;
    } else if (Formation_FMS_B.pos_err_idx_0 < -1.57079637F) {
      Formation_FMS_B.pos_err_idx_0 = -1.57079637F;
    }

    // BusAssignment: '<S14>/Bus Assignment' incorporates:
    //   Constant: '<S66>/L1'
    //   Gain: '<S73>/Gain'
    //   Outport: '<Root>/FMS_Out'
    //   Product: '<S73>/Divide'
    //   Product: '<S73>/Multiply1'
    //   Saturate: '<S73>/Saturation'
    //   Trigonometry: '<S73>/Sin'

    Formation_FMS_Y.FMS_Out.ay_cmd = 2.0F * Formation_FMS_B.psi * std::sin
      (Formation_FMS_B.pos_err_idx_0) / FMS_PARAM.L1;

    // Gain: '<S65>/Gain2' incorporates:
    //   Delay: '<S65>/Delay'
    //   Inport: '<Root>/INS_Out'
    //   Sum: '<S65>/Sum'

    Formation_FMS_B.pos_err_idx_0 = static_cast<real32_T>
      ((Formation_FMS_DW.Delay_DSTATE - Formation_FMS_U.INS_Out.h_R) *
       FMS_PARAM.Z_P);

    // Saturate: '<S65>/Saturation'
    if (Formation_FMS_B.pos_err_idx_0 > CONTROL_PARAM.FW_T_CLMB_MAX) {
      // BusAssignment: '<S14>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.vh_cmd = CONTROL_PARAM.FW_T_CLMB_MAX;
    } else if (Formation_FMS_B.pos_err_idx_0 < -CONTROL_PARAM.FW_T_SINK_MAX) {
      // BusAssignment: '<S14>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.vh_cmd = -CONTROL_PARAM.FW_T_SINK_MAX;
    } else {
      // BusAssignment: '<S14>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.vh_cmd = Formation_FMS_B.pos_err_idx_0;
    }

    // End of Saturate: '<S65>/Saturation'

    // Update for Delay: '<S69>/start_vel'
    Formation_FMS_DW.icLoad_c = false;

    // Update for Delay: '<S65>/Delay'
    Formation_FMS_DW.icLoad_m = false;

    // End of Outputs for SubSystem: '<S10>/Hold'
    break;

   default:
    // InitializeConditions for IfAction SubSystem: '<S10>/Default' incorporates:
    //   ActionPort: '<S11>/Action Port'

    // InitializeConditions for SwitchCase: '<S10>/Switch Case' incorporates:
    //   Delay: '<S16>/Delay'

    Formation_FMS_DW.icLoad = ((Formation_FMS_DW.SwitchCase_ActiveSubsystem !=
      Formation_FMS_B.rtPrevAction) || Formation_FMS_DW.icLoad);

    // End of InitializeConditions for SubSystem: '<S10>/Default'

    // Outputs for IfAction SubSystem: '<S10>/Default' incorporates:
    //   ActionPort: '<S11>/Action Port'

    // Delay: '<S16>/Delay' incorporates:
    //   Inport: '<Root>/INS_Out'

    if (Formation_FMS_DW.icLoad) {
      Formation_FMS_DW.Delay_DSTATE_p = Formation_FMS_U.INS_Out.h_R;
    }

    // End of Outputs for SubSystem: '<S10>/Default'
    std::memset(&Formation_FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

    // Outputs for IfAction SubSystem: '<S10>/Default' incorporates:
    //   ActionPort: '<S11>/Action Port'

    // BusAssignment: '<S11>/Bus Assignment' incorporates:
    //   Constant: '<S15>/Constant'
    //   Inport: '<Root>/INS_Out'
    //   Outport: '<Root>/FMS_Out'
    //   Sum: '<S15>/Sum'

    Formation_FMS_Y.FMS_Out.ax_cmd = CONTROL_PARAM.FW_AIRSPD_TRIM -
      Formation_FMS_U.INS_Out.airspeed;
    Formation_FMS_Y.FMS_Out.ay_cmd = 0.0F;

    // Gain: '<S16>/Gain2' incorporates:
    //   Delay: '<S16>/Delay'
    //   Inport: '<Root>/INS_Out'
    //   Sum: '<S16>/Sum'

    Formation_FMS_B.pos_err_idx_0 = (Formation_FMS_DW.Delay_DSTATE_p -
      Formation_FMS_U.INS_Out.h_R) * FMS_PARAM.Z_P;

    // Saturate: '<S16>/Saturation'
    if (Formation_FMS_B.pos_err_idx_0 > CONTROL_PARAM.FW_T_CLMB_MAX) {
      // BusAssignment: '<S11>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.vh_cmd = CONTROL_PARAM.FW_T_CLMB_MAX;
    } else if (Formation_FMS_B.pos_err_idx_0 < -CONTROL_PARAM.FW_T_SINK_MAX) {
      // BusAssignment: '<S11>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.vh_cmd = -CONTROL_PARAM.FW_T_SINK_MAX;
    } else {
      // BusAssignment: '<S11>/Bus Assignment' incorporates:
      //   Outport: '<Root>/FMS_Out'

      Formation_FMS_Y.FMS_Out.vh_cmd = Formation_FMS_B.pos_err_idx_0;
    }

    // End of Saturate: '<S16>/Saturation'

    // Update for Delay: '<S16>/Delay'
    Formation_FMS_DW.icLoad = false;

    // End of Outputs for SubSystem: '<S10>/Default'
    break;
  }

  // End of SwitchCase: '<S10>/Switch Case'

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.2, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  (&Formation_FMS_M)->Timing.clockTick0++;
}

// Model initialize function
void Formation_FMS::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // Start for SwitchCase: '<S10>/Switch Case'
  Formation_FMS_DW.SwitchCase_ActiveSubsystem = -1;
  Formation_FMS_PrevZCX.FormMission_SubSystem_Reset_ZCE = POS_ZCSIG;
  Formation_FMS_PrevZCX.Mission_SubSystem_Reset_ZCE = POS_ZCSIG;
  Formation_FMS_B.Cmd_In.form_valid = 0U;
  Formation_FMS_B.Cmd_In.l1_enable = false;

  // SystemInitialize for Outport: '<Root>/Other_Mission_Data'
  Formation_FMS_Y.Other_Mission_Data.timestamp = 0U;
  Formation_FMS_B.Cmd_In.sp_waypoint[0] = 0.0F;
  Formation_FMS_B.Cmd_In.cur_waypoint[0] = 0.0F;

  // SystemInitialize for Outport: '<Root>/Other_Mission_Data'
  Formation_FMS_Y.Other_Mission_Data.type[0] = 0U;
  Formation_FMS_Y.Other_Mission_Data.valid_items[0] = 0U;
  Formation_FMS_B.Cmd_In.sp_waypoint[1] = 0.0F;
  Formation_FMS_B.Cmd_In.cur_waypoint[1] = 0.0F;

  // SystemInitialize for Outport: '<Root>/Other_Mission_Data'
  Formation_FMS_Y.Other_Mission_Data.type[1] = 0U;
  Formation_FMS_Y.Other_Mission_Data.valid_items[1] = 0U;
  Formation_FMS_B.Cmd_In.sp_waypoint[2] = 0.0F;
  Formation_FMS_B.Cmd_In.cur_waypoint[2] = 0.0F;

  // SystemInitialize for Outport: '<Root>/Other_Mission_Data'
  Formation_FMS_Y.Other_Mission_Data.type[2] = 0U;
  Formation_FMS_Y.Other_Mission_Data.valid_items[2] = 0U;
  std::memset(&Formation_FMS_Y.Other_Mission_Data.x[0], 0, 24U * sizeof(real32_T));
  std::memset(&Formation_FMS_Y.Other_Mission_Data.y[0], 0, 24U * sizeof(real32_T));
  std::memset(&Formation_FMS_Y.Other_Mission_Data.z[0], 0, 24U * sizeof(real32_T));
  std::memset(&Formation_FMS_Y.Other_Mission_Data.heading[0], 0, 24U * sizeof
              (real32_T));
  std::memset(&Formation_FMS_Y.Other_Mission_Data.ext1[0], 0, 24U * sizeof
              (real32_T));
  std::memset(&Formation_FMS_Y.Other_Mission_Data.ext2[0], 0, 24U * sizeof
              (real32_T));

  // SystemInitialize for Chart: '<Root>/FMS State Machine' incorporates:
  //   SubSystem: '<S3>/Vehicle.Formation.FormAssemble.Waypoint.LPF'

  // InitializeConditions for DiscreteIntegrator: '<S86>/Discrete-Time Integrator5' 
  Formation_FMS_DW.DiscreteTimeIntegrator5_IC_LOAD = 1U;

  // SystemInitialize for IfAction SubSystem: '<S10>/FormMission'
  // SystemInitialize for Resettable SubSystem: '<S13>/FormMission_SubSystem'
  // InitializeConditions for Delay: '<S43>/Delay'
  Formation_FMS_DW.icLoad_n = true;

  // End of SystemInitialize for SubSystem: '<S13>/FormMission_SubSystem'
  // End of SystemInitialize for SubSystem: '<S10>/FormMission'

  // SystemInitialize for IfAction SubSystem: '<S10>/FormAssemble'
  // SystemInitialize for Resettable SubSystem: '<S12>/Mission_SubSystem'
  // InitializeConditions for Delay: '<S20>/Delay'
  Formation_FMS_DW.icLoad_h = true;

  // End of SystemInitialize for SubSystem: '<S12>/Mission_SubSystem'
  // End of SystemInitialize for SubSystem: '<S10>/FormAssemble'

  // SystemInitialize for IfAction SubSystem: '<S10>/Hold'
  // InitializeConditions for Delay: '<S69>/start_vel'
  Formation_FMS_DW.icLoad_c = true;

  // InitializeConditions for Delay: '<S65>/Delay'
  Formation_FMS_DW.icLoad_m = true;

  // End of SystemInitialize for SubSystem: '<S10>/Hold'

  // SystemInitialize for IfAction SubSystem: '<S10>/Default'
  // InitializeConditions for Delay: '<S16>/Delay'
  Formation_FMS_DW.icLoad = true;

  // End of SystemInitialize for SubSystem: '<S10>/Default'
}

// Model terminate function
void Formation_FMS::terminate()
{
  // (no terminate code required)
}

// Constructor
Formation_FMS::Formation_FMS() :
  Formation_FMS_U(),
  Formation_FMS_Y(),
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

//
// File trailer for generated code.
//
// [EOF]
//
