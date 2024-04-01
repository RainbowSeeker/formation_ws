//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: FMS_TECS_types.h
//
// Code generated for Simulink model 'FMS_TECS'.
//
// Model version                  : 1.27
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Mon Apr  1 20:58:12 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_FMS_TECS_types_h_
#define RTW_HEADER_FMS_TECS_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_Pilot_Cmd_Bus_
#define DEFINED_TYPEDEF_FOR_Pilot_Cmd_Bus_

struct Pilot_Cmd_Bus
{
  uint32_T timestamp;
  uint32_T mode;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Mission_Data_Bus_
#define DEFINED_TYPEDEF_FOR_Mission_Data_Bus_

struct Mission_Data_Bus
{
  uint32_T timestamp;

  // FormAssemble(1),
  // FormDisband(2),
  // FormMission(3),
  // Mission(4),
  uint32_T type;
  uint8_T valid_items;
  real32_T x[8];
  real32_T y[8];
  real32_T z[8];
  real32_T heading[8];
  real32_T ext1[8];
  real32_T ext2[8];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_INS_Out_Bus_
#define DEFINED_TYPEDEF_FOR_INS_Out_Bus_

struct INS_Out_Bus
{
  uint32_T timestamp;
  real32_T phi;
  real32_T theta;
  real32_T psi;
  real32_T p;
  real32_T q;
  real32_T r;

  // Quaternion
  real32_T quat[4];
  real32_T x_R;
  real32_T y_R;
  real32_T h_R;
  real32_T airspeed;
  real32_T ax;
  real32_T ay;
  real32_T az;
  real32_T vn;
  real32_T ve;
  real32_T vd;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Formation_Cross_Bus_
#define DEFINED_TYPEDEF_FOR_Formation_Cross_Bus_

// Supports up to 3 drone.
struct Formation_Cross_Bus
{
  uint32_T timestamp[3];
  real32_T x_R[3];
  real32_T y_R[3];
  real32_T h_R[3];
  real32_T vn[3];
  real32_T ve[3];
  real32_T vd[3];

  // rad
  real32_T psi[3];
  real32_T left_time[3];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_FMS_Out_Bus_
#define DEFINED_TYPEDEF_FOR_FMS_Out_Bus_

struct FMS_Out_Bus
{
  uint32_T timestamp;
  real32_T ax_cmd;
  real32_T ay_cmd;
  real32_T vh_cmd;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Other_Mission_Data_Bus_
#define DEFINED_TYPEDEF_FOR_Other_Mission_Data_Bus_

struct Other_Mission_Data_Bus
{
  uint32_T timestamp;

  // FormAssemble(1),
  // FormDisband(2),
  // FormMission(3),
  // Mission(4),
  uint32_T type[3];
  uint8_T valid_items[3];
  real32_T x[24];
  real32_T y[24];
  real32_T z[24];
  real32_T heading[24];
  real32_T ext1[24];
  real32_T ext2[24];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_FebwIpiU9Ih55vl7WG22GB_
#define DEFINED_TYPEDEF_FOR_struct_FebwIpiU9Ih55vl7WG22GB_

struct struct_FebwIpiU9Ih55vl7WG22GB
{
  real32_T ROLL_P;
  real32_T PITCH_P;
  real32_T ROLL_RATE_P;
  real32_T PITCH_RATE_P;
  real32_T YAW_RATE_P;
  real32_T ROLL_RATE_I;
  real32_T PITCH_RATE_I;
  real32_T YAW_RATE_I;
  real32_T RATE_I_MIN;
  real32_T RATE_I_MAX;
  real32_T TRIM_ROLL;
  real32_T TRIM_PITCH;
  real32_T TRIM_YAW;
  real32_T FW_PSP_OFF;
  real32_T FW_AIRSPD_MIN;
  real32_T FW_AIRSPD_MAX;
  real32_T FW_AIRSPD_TRIM;
  real32_T FW_AIRSPD_STALL;
  int32_T FW_ARSP_MODE;
  int32_T FW_ARSP_SCALE_EN;
  real32_T FW_T_TAS_TC;
  real32_T FW_T_I_GAIN_PIT;
  real32_T FW_T_I_GAIN_THR;
  real32_T FW_T_THR_DAMP;
  real32_T FW_T_SPDWEIGHT;
  real32_T FW_T_CLMB_MAX;
  real32_T FW_T_SINK_MIN;
  real32_T FW_T_SINK_MAX;
  real32_T FW_T_CLMB_R_SP;
  real32_T FW_T_SINK_R_SP;
  real32_T FW_P_LIM_MAX;
  real32_T FW_P_LIM_MIN;
  real32_T FW_R_LIM;
  real32_T FW_T_VERT_ACC;
  real32_T FW_T_ALT_TC;
  real32_T FW_T_HRATE_FF;
  real32_T FW_T_RLL2THR;
  real32_T FW_RR_FF;
  real32_T FW_PR_FF;
  real32_T FW_YR_FF;
  real32_T FW_R_RMAX;
  real32_T FW_P_RMAX;
  real32_T FW_Y_RMAX;
  real32_T FW_THR_MAX;
  real32_T FW_THR_MIN;
  real32_T FW_THR_TRIM;
  real32_T FW_T_SEB_R_FF;
  real32_T FW_T_PTCH_DAMP;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_RybhgqIOamJFBGFK48xLQB_
#define DEFINED_TYPEDEF_FOR_struct_RybhgqIOamJFBGFK48xLQB_

struct struct_RybhgqIOamJFBGFK48xLQB
{
  real_T UAV_ID;
  real_T ADJ_MARTIX[9];
  real_T REL_X_MATRIX[9];
  real_T REL_Y_MATRIX[9];
  real_T REL_Z_MATRIX[9];
  real_T NUM_UAV;
  real_T FORM_POINT[9];
  real32_T FORM_RADIUS;
  real32_T ASSEMBLE_KT;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_U9pfOUhK42GcE1cZiAFZlB_
#define DEFINED_TYPEDEF_FOR_struct_U9pfOUhK42GcE1cZiAFZlB_

struct struct_U9pfOUhK42GcE1cZiAFZlB
{
  real32_T FW_AIRSPD_TRIM;
  real32_T FW_HEIGHT_TRIM;
  real32_T THROTTLE_DZ;
  real32_T YAW_DZ;
  real32_T ROLL_DZ;
  real32_T PITCH_DZ;
  real32_T AIRSPD_P;
  real32_T Z_P;
  real32_T VEL_Z_LIM;
  real32_T YAW_P;
  real32_T YAW_RATE_LIM;
  real32_T ROLL_PITCH_LIM;
  real32_T L1;
  real32_T ACCEPT_R;
  real32_T LOITER_R;
  real32_T Y_P;
  real32_T ACC_Y_LIM;
};

#endif
#endif                                 // RTW_HEADER_FMS_TECS_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
