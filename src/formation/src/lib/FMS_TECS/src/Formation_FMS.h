//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Formation_FMS.h
//
// Code generated for Simulink model 'Formation_FMS'.
//
// Model version                  : 1.159
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Tue Apr  2 21:16:26 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#ifndef RTW_HEADER_Formation_FMS_h_
#define RTW_HEADER_Formation_FMS_h_
#include "rtwtypes.h"

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rt_nonfinite.h"

}

#include <cstring>
#include "zero_crossing_types.h"
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
  real32_T left_time[3];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_PilotMode_
#define DEFINED_TYPEDEF_FOR_PilotMode_

// enumeration of pilot mode
enum class PilotMode
  : int32_T {
  None = 0,                            // Default value
  Hold,
  FormAssemble,
  FormDisband,
  FormMission
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_VehicleState_
#define DEFINED_TYPEDEF_FOR_VehicleState_

// enumeration to track active leaf state of FMS/FMS State Machine/Vehicle
enum class VehicleState
  : int32_T {
  None = 0,                            // Default value
  Hold,
  FormAssemble,
  FormDisband,
  FormMission
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_FMS_Out_Bus_
#define DEFINED_TYPEDEF_FOR_FMS_Out_Bus_

struct FMS_Out_Bus
{
  uint32_T timestamp;
  VehicleState state;
  real32_T ax_cmd;
  real32_T ay_cmd;
  real32_T vh_cmd;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Commander_In_Bus_
#define DEFINED_TYPEDEF_FOR_Commander_In_Bus_

struct Commander_In_Bus
{
  uint32_T form_valid;
  boolean_T l1_enable;
  real32_T sp_waypoint[3];
  real32_T cur_waypoint[3];
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

// Custom Type definition for MATLAB Function: '<S82>/MATLAB Function'
#ifndef struct_captured_var_Formation_FMS_T
#define struct_captured_var_Formation_FMS_T

struct captured_var_Formation_FMS_T
{
  real_T contents;
};

#endif                                 // struct_captured_var_Formation_FMS_T

#ifndef struct_sGXMO9PmoeW2JqDMJvYKnvG_Forma_T
#define struct_sGXMO9PmoeW2JqDMJvYKnvG_Forma_T

struct sGXMO9PmoeW2JqDMJvYKnvG_Forma_T
{
  real_T xs;
  real_T ys;
  real_T psi_s;
  real_T xf;
  real_T yf;
  real_T psi_f;
  real_T v;
  real_T r;
  real_T pos[4];
  real_T pof[4];
  real_T xts[4];
  real_T yts[4];
  real_T xtf[4];
  real_T ytf[4];
  real_T cs[4];
  real_T cf[4];
  real_T lt[4];
  real_T l[4];
  real_T index_dubins[2];
  real_T l_ad;
  real_T precision_flag;
  real_T xm;
  real_T ym;
};

#endif                                // struct_sGXMO9PmoeW2JqDMJvYKnvG_Forma_T

//
//  Exported Global Parameters
//
//  Note: Exported global parameters are tunable parameters with an exported
//  global storage class designation.  Code generation will declare the memory for
//  these parameters and exports their symbols.
//

extern struct_RybhgqIOamJFBGFK48xLQB FORMATION_PARAM;// Variable: FORMATION_PARAM
                                                        //  Referenced by:
                                                        //    '<Root>/FMS State Machine'
                                                        //    '<S82>/MATLAB Function'
                                                        //    '<S84>/MATLAB Function'
                                                        //    '<S19>/Time Consensus Controller'
                                                        //    '<S19>/Gain1'
                                                        //    '<S44>/Consensus Controller'

extern struct_FebwIpiU9Ih55vl7WG22GB CONTROL_PARAM;// Variable: CONTROL_PARAM
                                                      //  Referenced by:
                                                      //    '<S16>/Saturation'
                                                      //    '<S65>/Saturation'
                                                      //    '<S20>/Saturation'
                                                      //    '<S43>/Saturation'

extern struct_U9pfOUhK42GcE1cZiAFZlB FMS_PARAM;// Variable: FMS_PARAM
                                                  //  Referenced by:
                                                  //    '<Root>/ACCEPT_R'
                                                  //    '<S15>/Constant'
                                                  //    '<S16>/Gain2'
                                                  //    '<S64>/Constant'
                                                  //    '<S65>/Constant'
                                                  //    '<S65>/Gain2'
                                                  //    '<S66>/L1'
                                                  //    '<S66>/R'
                                                  //    '<S19>/Constant'
                                                  //    '<S20>/Constant'
                                                  //    '<S20>/Gain2'
                                                  //    '<S42>/Constant'
                                                  //    '<S42>/Gain'
                                                  //    '<S43>/Constant'
                                                  //    '<S43>/Gain2'
                                                  //    '<S23>/L1'
                                                  //    '<S23>/Saturation1'
                                                  //    '<S47>/L1'
                                                  //    '<S47>/Saturation1'


// Class declaration for model Formation_FMS
class Formation_FMS final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for model 'Formation_FMS'
  struct DW_Formation_FMS_T {
    sGXMO9PmoeW2JqDMJvYKnvG_Forma_T object[3];
    Other_Mission_Data_Bus Other_Mission_Data;// '<Root>/FMS State Machine'
    sGXMO9PmoeW2JqDMJvYKnvG_Forma_T obj;
    Formation_Cross_Bus BusConversion_InsertedFor_FMS_p;
    INS_Out_Bus BusConversion_InsertedFor_FMS_c;
    Commander_In_Bus Cmd_In;           // '<Root>/FMS State Machine'
    FMS_Out_Bus Merge;                 // '<S10>/Merge'
    captured_var_Formation_FMS_T PhiMaximum;
    captured_var_Formation_FMS_T rad2deg;
    real_T result[75];
    real_T b_data[4];
    real_T c_data[4];
    real_T SFunction_o13;              // '<Root>/FMS State Machine'
    real_T l_ref;
    real_T search_floor;
    real_T search;
    real_T goal;
    real_T l_best;
    real_T pos_tmp;
    real_T xts_tmp;
    real_T yts_tmp;
    real_T cs_tmp;
    real_T cs_tmp_m;
    real_T cf_tmp;
    real_T lt_tmp;
    real_T deltax;
    real_T deltay;
    real32_T start_vel_DSTATE[2];      // '<S69>/start_vel'
    real32_T waypoints[25];            // '<Root>/FMS State Machine'
    real32_T xyz_O_nx3[9];             // '<S44>/Vector Concatenate'
    real32_T vNED_O_nx3[9];            // '<S44>/Vector Concatenate1'
    real32_T BusConversion_InsertedFor_FMSSt[8];
    real32_T BusConversion_InsertedFor_FMS_k[8];
    real32_T BusConversion_InsertedFor_FM_cx[8];
    real32_T BusConversion_InsertedFor_FMS_b[8];
    real32_T BusConversion_InsertedFor_FM_pb[8];
    real32_T BusConversion_InsertedFor_FM_cv[8];
    real32_T pose[3];
    real32_T Reshape2_bi[2];           // '<S48>/Reshape2'
    real32_T P_c[2];                   // '<S49>/NearbyRefWP'
    real32_T P_mr[2];                  // '<S49>/SearchL1RefWP'
    real32_T P_b[2];                   // '<S49>/OutRegionRegWP'
    real32_T unit_point_to_next[2];
    real32_T unit_centre_to_pose[2];
    real32_T Delay_DSTATE;             // '<S16>/Delay'
    real32_T Delay_DSTATE_m;           // '<S65>/Delay'
    real32_T Delay_DSTATE_l;           // '<S20>/Delay'
    real32_T Delay_DSTATE_o;           // '<S43>/Delay'
    real32_T DiscreteTimeIntegrator1_DSTATE;// '<S4>/Discrete-Time Integrator1'
    real32_T scale;
    real32_T absxk;
    real32_T t;
    real32_T Sum1_i;                   // '<S41>/Sum1'
    real32_T path_ratio;
    real32_T rtb_TmpSignalConversionAtSqua_f;
    real32_T rtb_TmpSignalConversionAtSqua_g;
    real32_T rtb_vd_idx_2;
    real32_T rtb_vd_idx_0;
    real32_T rtb_x_R_idx_0;
    real32_T rtb_y_R_idx_0;
    real32_T rtb_h_R_idx_0;
    real32_T rtb_vn_idx_0;
    real32_T rtb_x_R_idx_1;
    real32_T rtb_y_R_idx_1;
    real32_T rtb_h_R_idx_1;
    real32_T rtb_vn_idx_1;
    real32_T rtb_ve_idx_1;
    real32_T rtb_x_R_idx_2;
    real32_T rtb_y_R_idx_2;
    real32_T rtb_h_R_idx_2;
    real32_T rtb_vn_idx_2;
    real32_T rtb_ve_idx_2;
    real32_T rtb_P_c_g;
    real32_T nearest_cross;
    real32_T dotProduct;
    real32_T nearest_cross_tmp;
    real32_T unit_norm_vector_idx_0;
    real32_T unit_norm_vector_idx_1;
    real32_T unit_centre_to_pose_idx_0;
    real32_T unit_centre_to_pose_idx_1;
    real32_T unit_line_idx_0;
    real32_T unit_point_to_next_m;
    int32_T i_data[4];
    int32_T mask;
    int32_T i;
    int32_T target;
    int32_T stop_flag;
    int32_T j;
    int32_T i_n;
    int32_T b_size;
    int32_T c_size;
    uint32_T DelayInput1_DSTATE;       // '<S7>/Delay Input1'
    uint32_T Mission_Data_timestamp_prev;// '<Root>/FMS State Machine'
    uint32_T Mission_Data_timestamp_start;// '<Root>/FMS State Machine'
    uint32_T BusConversion_InsertedFor_FM_pp;
    uint32_T BusConversion_InsertedFor_FMS_l;
    PilotMode Delay_DSTATE_j;          // '<S5>/Delay'
    PilotMode mode_prev;               // '<Root>/FMS State Machine'
    PilotMode mode_start;              // '<Root>/FMS State Machine'
    PilotMode Switch;
    VehicleState state;                // '<Root>/FMS State Machine'
    uint16_T wp_index;                 // '<Root>/FMS State Machine'
    uint16_T DelayInput1_DSTATE_h;     // '<S17>/Delay Input1'
    uint16_T DelayInput1_DSTATE_d;     // '<S40>/Delay Input1'
    int8_T j_data[4];
    int8_T SwitchCase_ActiveSubsystem; // '<S10>/Switch Case'
    uint8_T is_Vehicle;                // '<Root>/FMS State Machine'
    uint8_T is_Formation;              // '<Root>/FMS State Machine'
    uint8_T is_FormAssemble;           // '<Root>/FMS State Machine'
    uint8_T is_FormMission;            // '<Root>/FMS State Machine'
    uint8_T is_active_c3_Formation_FMS;// '<Root>/FMS State Machine'
    boolean_T icLoad;                  // '<S16>/Delay'
    boolean_T icLoad_c;                // '<S69>/start_vel'
    boolean_T icLoad_j;                // '<S65>/Delay'
    boolean_T icLoad_h;                // '<S20>/Delay'
    boolean_T icLoad_k;                // '<S43>/Delay'
  };

  // Zero-crossing (trigger) state for model 'Formation_FMS'
  struct ZCV_Formation_FMS_g_T {
    real_T Mission_SubSystem_Reset_ZC; // '<S12>/Mission_SubSystem'
    real_T FormMission_SubSystem_Reset_ZC;// '<S13>/FormMission_SubSystem'
  };

  // Zero-crossing (trigger) state for model 'Formation_FMS'
  struct PrevZCX_Formation_FMS_T {
    ZCSigState Mission_SubSystem_Reset_ZCE;// '<S12>/Mission_SubSystem'
    ZCSigState FormMission_SubSystem_Reset_ZCE;// '<S13>/FormMission_SubSystem'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_Formation_FMS_T {
    const char_T **errorStatus;
  };

  // model initialize function
  void initialize();

  // Initial conditions function
  void init(uint32_T *rty_FMS_Out_timestamp, VehicleState *rty_FMS_Out_state,
            real32_T *rty_FMS_Out_ax_cmd, real32_T *rty_FMS_Out_ay_cmd, real32_T
            *rty_FMS_Out_vh_cmd, uint32_T *rty_Other_Mission_Data_timestam,
            uint32_T rty_Other_Mission_Data_type[3], uint8_T
            rty_Other_Mission_Data_valid_it[3], real32_T
            rty_Other_Mission_Data_x[24], real32_T rty_Other_Mission_Data_y[24],
            real32_T rty_Other_Mission_Data_z[24], real32_T
            rty_Other_Mission_Data_heading[24], real32_T
            rty_Other_Mission_Data_ext1[24], real32_T
            rty_Other_Mission_Data_ext2[24]);

  // Copy Constructor
  Formation_FMS(Formation_FMS const&) = delete;

  // Assignment Operator
  Formation_FMS& operator= (Formation_FMS const&) & = delete;

  // Move Constructor
  Formation_FMS(Formation_FMS &&) = delete;

  // Move Assignment Operator
  Formation_FMS& operator= (Formation_FMS &&) = delete;

  // Real-Time Model get method
  Formation_FMS::RT_MODEL_Formation_FMS_T * getRTM();

  //member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  // model step function
  void step(const uint32_T *rtu_Pilot_Cmd_timestamp, const uint32_T
            *rtu_Pilot_Cmd_mode, const uint32_T *rtu_Mission_Data_timestamp,
            const uint32_T *rtu_Mission_Data_type, const uint8_T
            *rtu_Mission_Data_valid_items, const real32_T rtu_Mission_Data_x[8],
            const real32_T rtu_Mission_Data_y[8], const real32_T
            rtu_Mission_Data_z[8], const real32_T rtu_Mission_Data_heading[8],
            const real32_T rtu_Mission_Data_ext1[8], const real32_T
            rtu_Mission_Data_ext2[8], const uint32_T *rtu_INS_Out_timestamp,
            const real32_T *rtu_INS_Out_phi, const real32_T *rtu_INS_Out_theta,
            const real32_T *rtu_INS_Out_psi, const real32_T *rtu_INS_Out_p,
            const real32_T *rtu_INS_Out_q, const real32_T *rtu_INS_Out_r, const
            real32_T rtu_INS_Out_quat[4], const real32_T *rtu_INS_Out_x_R, const
            real32_T *rtu_INS_Out_y_R, const real32_T *rtu_INS_Out_h_R, const
            real32_T *rtu_INS_Out_airspeed, const real32_T *rtu_INS_Out_ax,
            const real32_T *rtu_INS_Out_ay, const real32_T *rtu_INS_Out_az,
            const real32_T *rtu_INS_Out_vn, const real32_T *rtu_INS_Out_ve,
            const real32_T *rtu_INS_Out_vd, const uint32_T
            rtu_Formation_Cross_timestamp[3], const real32_T
            rtu_Formation_Cross_x_R[3], const real32_T rtu_Formation_Cross_y_R[3],
            const real32_T rtu_Formation_Cross_h_R[3], const real32_T
            rtu_Formation_Cross_vn[3], const real32_T rtu_Formation_Cross_ve[3],
            const real32_T rtu_Formation_Cross_vd[3], const real32_T
            rtu_Formation_Cross_left_time[3], uint32_T *rty_FMS_Out_timestamp,
            VehicleState *rty_FMS_Out_state, real32_T *rty_FMS_Out_ax_cmd,
            real32_T *rty_FMS_Out_ay_cmd, real32_T *rty_FMS_Out_vh_cmd, uint32_T
            *rty_Other_Mission_Data_timestam, uint32_T
            rty_Other_Mission_Data_type[3], uint8_T
            rty_Other_Mission_Data_valid_it[3], real32_T
            rty_Other_Mission_Data_x[24], real32_T rty_Other_Mission_Data_y[24],
            real32_T rty_Other_Mission_Data_z[24], real32_T
            rty_Other_Mission_Data_heading[24], real32_T
            rty_Other_Mission_Data_ext1[24], real32_T
            rty_Other_Mission_Data_ext2[24], real32_T *rty_Form_Single);
  void Formation_FMS_PrevZCStateInit();

  // model disable function
  void disable();

  // Constructor
  Formation_FMS();

  // Destructor
  ~Formation_FMS();

  // private data and function members
 private:
  // Block states
  DW_Formation_FMS_T Formation_FMS_DW;

  // Triggered events
  PrevZCX_Formation_FMS_T Formation_FMS_PrevZCX;

  // private member function(s) for subsystem '<S49>/NearbyRefWP'
  static void Formation_FMS_NearbyRefWP(const real32_T rtu_P2[2], const real32_T
    rtu_P3[2], real32_T rtu_L1, real32_T rty_P[2], real32_T *rty_d);

  // private member function(s) for subsystem '<S49>/OutRegionRegWP'
  static void Formation_FMS_OutRegionRegWP(const real32_T rtu_P1[2], const
    real32_T rtu_P2[2], const real32_T rtu_P3[2], real32_T rty_P[2]);

  // private member function(s) for subsystem '<S49>/SearchL1RefWP'
  static void Formation_FMS_SearchL1RefWP(const real32_T rtu_P1[2], const
    real32_T rtu_P2[2], const real32_T rtu_P3[2], real32_T rtu_L1, real32_T
    rty_P[2], real32_T *rty_u);

  // private member function(s) for subsystem '<Root>/TmpModelReferenceSubsystem'
  void Formation_exit_internal_Vehicle(void);
  real_T Formation_FMS_atan3_9FIHpp9F(real_T x, real_T y, real_T x0, real_T b_y0);
  void Formation_FMS_Dubins(const captured_var_Formation_FMS_T *PhiMaximum,
    const captured_var_Formation_FMS_T *rad2deg, real_T xs, real_T ys, real_T
    psi_s, real_T xf, real_T yf, real_T psi_f, real_T v, real_T xts[4], real_T
    yts[4], real_T xtf[4], real_T ytf[4], real_T cs[4], real_T cf[4], real_T lt
    [4], real_T l[4], real_T pos[4], real_T pof[4], real_T *r, real_T m_data[],
    int32_T *m_size, real_T n_data[], int32_T *n_size);
  void Format_enter_internal_Formation(const INS_Out_Bus
    *BusConversion_InsertedFor_FMS_c, const Formation_Cross_Bus
    *BusConversion_InsertedFor_FMS_p, const PilotMode *Switch);
  void Formati_getMinDistanceAtSegment(const real32_T waypoints[25], const
    real32_T pose[3], uint16_T segment, real32_T *dist, real32_T *ratio);

  // Real-Time Model
  RT_MODEL_Formation_FMS_T Formation_FMS_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S38>/Data Type Duplicate' : Unused code path elimination
//  Block '<S39>/Data Type Duplicate' : Unused code path elimination
//  Block '<S35>/Data Type Duplicate' : Unused code path elimination
//  Block '<S36>/Data Type Duplicate' : Unused code path elimination
//  Block '<S62>/Data Type Duplicate' : Unused code path elimination
//  Block '<S63>/Data Type Duplicate' : Unused code path elimination
//  Block '<S59>/Data Type Duplicate' : Unused code path elimination
//  Block '<S60>/Data Type Duplicate' : Unused code path elimination
//  Block '<S79>/Data Type Duplicate' : Unused code path elimination
//  Block '<S80>/Data Type Duplicate' : Unused code path elimination
//  Block '<S76>/Data Type Duplicate' : Unused code path elimination
//  Block '<S77>/Data Type Duplicate' : Unused code path elimination
//  Block '<S81>/Data Type Duplicate' : Unused code path elimination
//  Block '<S9>/Signal Copy3' : Eliminate redundant signal conversion block
//  Block '<S9>/Signal Copy5' : Eliminate redundant signal conversion block
//  Block '<S9>/Signal Copy6' : Eliminate redundant signal conversion block
//  Block '<S15>/Gain' : Eliminated nontunable gain of 1
//  Block '<S19>/Gain' : Eliminated nontunable gain of 1
//  Block '<S25>/Reshape' : Reshape block reduction
//  Block '<S24>/Reshape' : Reshape block reduction
//  Block '<S24>/Reshape1' : Reshape block reduction
//  Block '<S44>/Saturation' : Eliminated Saturate block
//  Block '<S44>/Saturation1' : Eliminated Saturate block
//  Block '<S44>/Saturation2' : Eliminated Saturate block
//  Block '<S49>/Reshape' : Reshape block reduction
//  Block '<S48>/Reshape' : Reshape block reduction
//  Block '<S48>/Reshape1' : Reshape block reduction
//  Block '<S64>/Gain' : Eliminated nontunable gain of 1
//  Block '<S67>/Reshape' : Reshape block reduction
//  Block '<S67>/Reshape1' : Reshape block reduction
//  Block '<S67>/Reshape3' : Reshape block reduction


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'Formation_FMS'
//  '<S1>'   : 'Formation_FMS/CommandProcess'
//  '<S2>'   : 'Formation_FMS/FMS Commander'
//  '<S3>'   : 'Formation_FMS/FMS State Machine'
//  '<S4>'   : 'Formation_FMS/CommandProcess/Check Valid'
//  '<S5>'   : 'Formation_FMS/CommandProcess/Mode PreProcess'
//  '<S6>'   : 'Formation_FMS/CommandProcess/Check Valid/Compare To Constant1'
//  '<S7>'   : 'Formation_FMS/CommandProcess/Check Valid/Detect Change1'
//  '<S8>'   : 'Formation_FMS/CommandProcess/Mode PreProcess/Compare To Zero1'
//  '<S9>'   : 'Formation_FMS/FMS Commander/Bus Creator'
//  '<S10>'  : 'Formation_FMS/FMS Commander/Commander'
//  '<S11>'  : 'Formation_FMS/FMS Commander/Commander/Default'
//  '<S12>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble'
//  '<S13>'  : 'Formation_FMS/FMS Commander/Commander/FormMission'
//  '<S14>'  : 'Formation_FMS/FMS Commander/Commander/Hold'
//  '<S15>'  : 'Formation_FMS/FMS Commander/Commander/Default/Airspeed Hold'
//  '<S16>'  : 'Formation_FMS/FMS Commander/Commander/Default/Altitude_Hold'
//  '<S17>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Detect Change'
//  '<S18>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem'
//  '<S19>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Airspeed Hold'
//  '<S20>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Altitude_Hold'
//  '<S21>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command'
//  '<S22>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Airspeed Hold/Time Consensus Controller'
//  '<S23>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control'
//  '<S24>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/WayPoints'
//  '<S25>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP'
//  '<S26>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core'
//  '<S27>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP/Compare To Constant'
//  '<S28>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP/Compare To Constant1'
//  '<S29>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP/NearbyRefWP'
//  '<S30>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP/OutRegionRegWP'
//  '<S31>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP/SearchL1RefWP'
//  '<S32>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration'
//  '<S33>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle'
//  '<S34>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Modulus'
//  '<S35>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize'
//  '<S36>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize1'
//  '<S37>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/2D Cross Product'
//  '<S38>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize'
//  '<S39>'  : 'Formation_FMS/FMS Commander/Commander/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize1'
//  '<S40>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/Detect Change'
//  '<S41>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem'
//  '<S42>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Airspeed Hold'
//  '<S43>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Altitude_Hold'
//  '<S44>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Formation_Controller'
//  '<S45>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command'
//  '<S46>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller'
//  '<S47>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control'
//  '<S48>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/WayPoints'
//  '<S49>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1 Reference WP'
//  '<S50>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1_Core'
//  '<S51>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1 Reference WP/Compare To Constant'
//  '<S52>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1 Reference WP/Compare To Constant1'
//  '<S53>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1 Reference WP/NearbyRefWP'
//  '<S54>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1 Reference WP/OutRegionRegWP'
//  '<S55>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1 Reference WP/SearchL1RefWP'
//  '<S56>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration'
//  '<S57>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle'
//  '<S58>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Modulus'
//  '<S59>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize'
//  '<S60>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize1'
//  '<S61>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/2D Cross Product'
//  '<S62>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize'
//  '<S63>'  : 'Formation_FMS/FMS Commander/Commander/FormMission/FormMission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize1'
//  '<S64>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Airspeed Hold'
//  '<S65>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Altitude_Hold'
//  '<S66>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control'
//  '<S67>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1 Reference WP'
//  '<S68>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core'
//  '<S69>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/Reference_Point'
//  '<S70>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1 Reference WP/Compare To Constant'
//  '<S71>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1 Reference WP/OutRegionRegWP'
//  '<S72>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1 Reference WP/SearchL1RefWP'
//  '<S73>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration'
//  '<S74>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle'
//  '<S75>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Modulus'
//  '<S76>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize'
//  '<S77>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize1'
//  '<S78>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/2D Cross Product'
//  '<S79>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize'
//  '<S80>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize1'
//  '<S81>'  : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/Reference_Point/Vector Normalize'
//  '<S82>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.dubinsPath'
//  '<S83>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.dubinsPathRatio'
//  '<S84>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.check_form_valid'
//  '<S85>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.dubinsPath/MATLAB Function'
//  '<S86>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.dubinsPathRatio/Dubins Closest Point'
//  '<S87>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.check_form_valid/MATLAB Function'

#endif                                 // RTW_HEADER_Formation_FMS_h_

//
// File trailer for generated code.
//
// [EOF]
//
