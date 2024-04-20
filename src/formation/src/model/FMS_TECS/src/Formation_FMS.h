//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Formation_FMS.h
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
#ifndef RTW_HEADER_Formation_FMS_h_
#define RTW_HEADER_Formation_FMS_h_
#include "rtwtypes.h"
#include "rtGetInf.h"

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
  FormHold,
  FormMission,
  FormDisband
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
  FormHold,
  FormMission,
  FormDisband
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

#ifndef DEFINED_TYPEDEF_FOR_struct_J7Uq7gTeDMxAAnCtpLwjSH_
#define DEFINED_TYPEDEF_FOR_struct_J7Uq7gTeDMxAAnCtpLwjSH_

struct struct_J7Uq7gTeDMxAAnCtpLwjSH
{
  uint32_T UAV_ID;
  real_T ADJ_MARTIX[9];
  real_T REL_X_MATRIX[9];
  real_T REL_Y_MATRIX[9];
  real_T REL_Z_MATRIX[9];
  real_T NUM_UAV;
  real_T FORM_POINT[9];
  real_T DISBAND_POINT[9];
  real32_T FORM_RADIUS;
  real32_T ASSEMBLE_KT;
  real32_T LATERAL_DAMP;
  real32_T LATERAL_PERIOD;
  real32_T FORM_POS_KP;
  real32_T FORM_POS_KD;
  real32_T FORM_VEL_KP;
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

#ifndef DEFINED_TYPEDEF_FOR_struct_krKDLIJ9OZPHOAucYn9ayF_
#define DEFINED_TYPEDEF_FOR_struct_krKDLIJ9OZPHOAucYn9ayF_

struct struct_krKDLIJ9OZPHOAucYn9ayF
{
  real32_T FW_AIRSPD_TRIM;
  real32_T FW_HEIGHT_TRIM;
  real32_T FW_RADIUS_RATIO;
  real32_T AIRSPD_P;
  real32_T Z_P;
  real32_T L1;
  real32_T ACCEPT_R;
  real32_T LOITER_R;
  real32_T ACC_Y_LIM;
};

#endif

// Custom Type definition for MATLAB Function: '<S199>/MATLAB Function'
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

extern struct_J7Uq7gTeDMxAAnCtpLwjSH FORMATION_PARAM;// Variable: FORMATION_PARAM
                                                        //  Referenced by:
                                                        //    '<Root>/FMS State Machine'
                                                        //    '<S199>/MATLAB Function'
                                                        //    '<S200>/MATLAB Function'
                                                        //    '<S82>/Constant2'
                                                        //    '<S86>/Calc_Position_Velocity_Setpoint'
                                                        //    '<S160>/min_radius'
                                                        //    '<S90>/Vel_Kp'
                                                        //    '<S93>/Pos_D'
                                                        //    '<S93>/Pos_P'
                                                        //    '<S100>/Ts//2'
                                                        //    '<S101>/Gain'

extern struct_FebwIpiU9Ih55vl7WG22GB CONTROL_PARAM;// Variable: CONTROL_PARAM
                                                      //  Referenced by:
                                                      //    '<S15>/Saturation'
                                                      //    '<S182>/Saturation'
                                                      //    '<S22>/Saturation'
                                                      //    '<S46>/Saturation'
                                                      //    '<S64>/Saturation'
                                                      //    '<S26>/Saturation'
                                                      //    '<S159>/Saturation'
                                                      //    '<S160>/min_radius'
                                                      //    '<S160>/v^2'
                                                      //    '<S93>/Saturation'

extern struct_krKDLIJ9OZPHOAucYn9ayF FMS_PARAM;// Variable: FMS_PARAM
                                                  //  Referenced by:
                                                  //    '<Root>/ACCEPT_R'
                                                  //    '<S14>/Constant'
                                                  //    '<S15>/Gain2'
                                                  //    '<S181>/Constant'
                                                  //    '<S182>/Constant'
                                                  //    '<S182>/Gain2'
                                                  //    '<S183>/L1'
                                                  //    '<S183>/R'
                                                  //    '<S21>/Constant'
                                                  //    '<S22>/Gain2'
                                                  //    '<S45>/Constant'
                                                  //    '<S46>/Constant'
                                                  //    '<S46>/Gain2'
                                                  //    '<S47>/L1'
                                                  //    '<S47>/R'
                                                  //    '<S63>/Constant'
                                                  //    '<S64>/Constant'
                                                  //    '<S64>/Gain2'
                                                  //    '<S65>/L1'
                                                  //    '<S65>/R'
                                                  //    '<S25>/Constant'
                                                  //    '<S26>/Constant'
                                                  //    '<S26>/Gain2'
                                                  //    '<S28>/L1'
                                                  //    '<S28>/Saturation1'
                                                  //    '<S158>/Constant'
                                                  //    '<S158>/Gain'
                                                  //    '<S159>/Constant'
                                                  //    '<S159>/Gain2'
                                                  //    '<S160>/Satefy'
                                                  //    '<S164>/L1'
                                                  //    '<S164>/Saturation1'


// Class declaration for model Formation_FMS
class Formation_FMS final
{
  // public data and function members
 public:
  // Block states (default storage) for system '<S12>/Default'
  struct DW_Default_Formation_FMS_T {
    real32_T Delay_DSTATE;             // '<S22>/Delay'
    boolean_T icLoad;                  // '<S22>/Delay'
  };

  // Block signals for model 'Formation_FMS'
  struct B_Formation_FMS_T {
    sGXMO9PmoeW2JqDMJvYKnvG_Forma_T object[3];
    real_T result[75];
    Other_Mission_Data_Bus Other_Mission_Data;// '<Root>/FMS State Machine'
    sGXMO9PmoeW2JqDMJvYKnvG_Forma_T obj;
    INS_Out_Bus BusConversion_InsertedFor_FMS_c;
    Formation_Cross_Bus BusConversion_InsertedFor_FMS_p;
    real32_T xyz_O_nx3[9];             // '<S84>/Vector Concatenate'
    real32_T vNED_O_nx3[9];            // '<S84>/Vector Concatenate1'
    real32_T rtb_pos_err_tmp[9];
    real32_T BusConversion_InsertedFor_FMSSt[8];
    real32_T BusConversion_InsertedFor_FM_cl[8];
    real32_T BusConversion_InsertedFor_FMS_k[8];
    Commander_In_Bus Cmd_In;           // '<Root>/FMS State Machine'
    real_T b_data[4];
    real_T c_data[4];
    FMS_Out_Bus Merge;                 // '<S10>/Merge'
    int32_T i_data[4];
    real32_T vd[3];                    // '<S9>/Signal Copy2'
    real32_T ve[3];                    // '<S9>/Signal Copy2'
    real_T SFunction_o9;               // '<Root>/FMS State Machine'
    real_T SFunction_o10;              // '<Root>/FMS State Machine'
    real_T SFunction_o11;              // '<Root>/FMS State Machine'
    real_T SFunction_o12;              // '<Root>/FMS State Machine'
    real_T ex;
    real_T n_j;                        // '<S66>/SearchL1RefWP'
    real_T l_ref;
    real_T search_floor;
    real_T search;
    real_T goal;
    real_T l_best;
    real_T pos_tmp;
    real_T xts_tmp;
    real_T yts_tmp;
    real_T cs_tmp;
    real_T cs_tmp_c;
    real_T cf_tmp;
    real_T lt_tmp;
    real_T deltax;
    real_T deltay;
    real32_T TmpSignalConversionAtSqua_c[2];
    real32_T Reshape2_bq[2];           // '<S29>/Reshape2'
    real32_T P_d[2];                   // '<S30>/SearchL1RefWP'
    real32_T P_i[2];                   // '<S30>/OutRegionRegWP'
    real32_T P[2];                     // '<S166>/SearchL1RefWP'
    real32_T P_b[2];                   // '<S166>/OutRegionRegWP'
    captured_var_Formation_FMS_T PhiMaximum;
    captured_var_Formation_FMS_T rad2deg;
    real32_T scale;
    real32_T absxk;
    real32_T t;
    real32_T Multiply1_f;              // '<S105>/Multiply1'
    real32_T Subtract_b;               // '<S98>/Subtract'
    real32_T Sin;                      // '<S99>/Sin'
    real32_T rtb_vn_idx_2;
    real32_T rtb_vn_idx_0;
    real32_T rtb_vn_idx_1;
    real32_T rtb_x_R_idx_0;
    real32_T rtb_x_R_idx_1;
    real32_T rtb_y_R_idx_1;
    real32_T rtb_x_R_idx_2;
    real32_T rtb_y_R_idx_2;
    int32_T idx;
    int32_T i;
    int32_T rtb_vd_tmp;
    int32_T target;
    int32_T stop_flag;
    int32_T d_i;
    uint32_T BusConversion_InsertedFor_FMS_b;
    uint32_T BusConversion_InsertedFor_FM_pb;
    VehicleState state;                // '<Root>/FMS State Machine'
    uint16_T wp_index;                 // '<Root>/FMS State Machine'
  };

  // Block states (default storage) for model 'Formation_FMS'
  struct DW_Formation_FMS_T {
    real32_T start_vel_DSTATE[2];      // '<S186>/start_vel'
    real32_T Delay_DSTATE;             // '<S182>/Delay'
    real32_T start_vel_DSTATE_m[2];    // '<S50>/start_vel'
    real32_T Delay_DSTATE_i;           // '<S46>/Delay'
    real32_T Delay_DSTATE_o;           // '<S159>/Delay'
    real32_T DiscreteTimeIntegrator1_DSTATE;// '<S97>/Discrete-Time Integrator1' 
    real32_T Integrator_DSTATE;        // '<S141>/Integrator'
    real32_T start_vel_DSTATE_n[2];    // '<S68>/start_vel'
    real32_T Delay_DSTATE_a;           // '<S64>/Delay'
    real32_T Delay_DSTATE_l;           // '<S26>/Delay'
    real32_T DiscreteTimeIntegrator1_DSTAT_l;// '<S4>/Discrete-Time Integrator1' 
    uint32_T DelayInput1_DSTATE;       // '<S7>/Delay Input1'
    PilotMode Delay_DSTATE_j;          // '<S5>/Delay'
    uint32_T Mission_Data_timestamp_prev;// '<Root>/FMS State Machine'
    uint32_T Mission_Data_timestamp_start;// '<Root>/FMS State Machine'
    PilotMode mode_prev;               // '<Root>/FMS State Machine'
    PilotMode mode_start;              // '<Root>/FMS State Machine'
    uint16_T DelayInput1_DSTATE_d;     // '<S81>/Delay Input1'
    uint16_T DelayInput1_DSTATE_h;     // '<S23>/Delay Input1'
    uint16_T temporalCounter_i1;       // '<Root>/FMS State Machine'
    int8_T SwitchCase_ActiveSubsystem; // '<S10>/Switch Case'
    int8_T SwitchCase_ActiveSubsystem_c;// '<S12>/Switch Case'
    int8_T DiscreteTimeIntegrator1_PrevRes;// '<S97>/Discrete-Time Integrator1'
    uint8_T is_Vehicle;                // '<Root>/FMS State Machine'
    uint8_T is_Formation;              // '<Root>/FMS State Machine'
    uint8_T is_FormAssemble;           // '<Root>/FMS State Machine'
    uint8_T is_FormMission;            // '<Root>/FMS State Machine'
    uint8_T is_active_c3_Formation_FMS;// '<Root>/FMS State Machine'
    uint8_T DiscreteTimeIntegrator1_IC_LOAD;// '<S97>/Discrete-Time Integrator1' 
    boolean_T icLoad;                  // '<S186>/start_vel'
    boolean_T icLoad_j;                // '<S182>/Delay'
    boolean_T icLoad_a;                // '<S50>/start_vel'
    boolean_T icLoad_l;                // '<S46>/Delay'
    boolean_T icLoad_k;                // '<S159>/Delay'
    boolean_T icLoad_l3;               // '<S68>/start_vel'
    boolean_T icLoad_p;                // '<S64>/Delay'
    boolean_T icLoad_h;                // '<S26>/Delay'
    DW_Default_Formation_FMS_T Default;// '<S10>/Default'
    DW_Default_Formation_FMS_T Default_d;// '<S12>/Default'
  };

  // Zero-crossing (trigger) state for model 'Formation_FMS'
  struct ZCV_Formation_FMS_g_T {
    real_T FormMission_SubSystem_Reset_ZC;// '<S20>/FormMission_SubSystem'
    real_T Mission_SubSystem_Reset_ZC; // '<S17>/Mission_SubSystem'
  };

  // Zero-crossing (trigger) state for model 'Formation_FMS'
  struct PrevZCX_Formation_FMS_T {
    ZCSigState FormMission_SubSystem_Reset_ZCE;// '<S20>/FormMission_SubSystem'
    ZCSigState Mission_SubSystem_Reset_ZCE;// '<S17>/Mission_SubSystem'
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
            rtu_Mission_Data_z[8], const uint32_T *rtu_INS_Out_timestamp, const
            real32_T *rtu_INS_Out_phi, const real32_T *rtu_INS_Out_theta, const
            real32_T *rtu_INS_Out_psi, const real32_T *rtu_INS_Out_p, const
            real32_T *rtu_INS_Out_q, const real32_T *rtu_INS_Out_r, const
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
            const real32_T rtu_Formation_Cross_vd[3], uint32_T
            *rty_FMS_Out_timestamp, VehicleState *rty_FMS_Out_state, real32_T
            *rty_FMS_Out_ax_cmd, real32_T *rty_FMS_Out_ay_cmd, real32_T
            *rty_FMS_Out_vh_cmd, uint32_T *rty_Other_Mission_Data_timestam,
            uint32_T rty_Other_Mission_Data_type[3], uint8_T
            rty_Other_Mission_Data_valid_it[3], real32_T
            rty_Other_Mission_Data_x[24], real32_T rty_Other_Mission_Data_y[24],
            real32_T rty_Other_Mission_Data_z[24], real32_T
            rty_Other_Mission_Data_heading[24], real32_T
            rty_Other_Mission_Data_ext1[24], real32_T
            rty_Other_Mission_Data_ext2[24]);
  void Formation_FMS_PrevZCStateInit();

  // model disable function
  void disable();

  // Constructor
  Formation_FMS();

  // Destructor
  ~Formation_FMS();

  // private data and function members
 private:
  // Block signals
  B_Formation_FMS_T Formation_FMS_B;

  // Block states
  DW_Formation_FMS_T Formation_FMS_DW;

  // Triggered events
  PrevZCX_Formation_FMS_T Formation_FMS_PrevZCX;

  // private member function(s) for subsystem '<S30>/NearbyRefWP'
  static void Formation_FMS_NearbyRefWP(const real32_T rtu_P2[2], const real32_T
    rtu_P3[2], real32_T rtu_L1, real32_T rty_P[2], real32_T *rty_d);

  // private member function(s) for subsystem '<S30>/OutRegionRegWP'
  static void Formation_FMS_OutRegionRegWP(const real32_T rtu_P1[2], const
    real32_T rtu_P2[2], const real32_T rtu_P3[2], real32_T rty_P[2]);

  // private member function(s) for subsystem '<S30>/SearchL1RefWP'
  static void Formation_FMS_SearchL1RefWP(const real32_T rtu_P1[2], const
    real32_T rtu_P2[2], const real32_T rtu_P3[2], real32_T rtu_L1, real32_T
    rty_P[2], real32_T *rty_u);

  // private member function(s) for subsystem '<S66>/OutRegionRegWP'
  static void Formation_FMS_OutRegionRegWP_o(const real32_T rtu_P0[2], const
    real32_T rtu_P_Vehicle[2], real32_T rtu_R, real32_T rtu_L1, const real32_T
    rtu_n[2], real32_T rty_P[2]);

  // private member function(s) for subsystem '<S66>/SearchL1RefWP'
  static void Formation_FMS_SearchL1RefWP_i(const real32_T rtu_P_0[2], const
    real32_T rtu_P_Vehicle[2], real32_T rtu_R, real32_T rtu_L1, real32_T rty_P[2],
    real_T *rty_n);

  // private member function(s) for subsystem '<S99>/signNoZero'
  static void Formation_FMS_signNoZero(real32_T rtu_u, real32_T *rty_y);

  // private member function(s) for subsystem '<S12>/Default'
  static void Formation_FMS_Default_Init(DW_Default_Formation_FMS_T *localDW);
  static void Formation_FMS_Default_Reset(DW_Default_Formation_FMS_T *localDW);
  static void Formation_FMS_Default(const real32_T *rtu_FMS_In, const real32_T
    *rtu_FMS_In_h, FMS_Out_Bus *rty_FMS_Out, DW_Default_Formation_FMS_T *localDW);

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
    *BusConversion_InsertedFor_FMS_p);

  // Real-Time Model
  RT_MODEL_Formation_FMS_T Formation_FMS_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S43>/Data Type Duplicate' : Unused code path elimination
//  Block '<S44>/Data Type Duplicate' : Unused code path elimination
//  Block '<S40>/Data Type Duplicate' : Unused code path elimination
//  Block '<S41>/Data Type Duplicate' : Unused code path elimination
//  Block '<S60>/Data Type Duplicate' : Unused code path elimination
//  Block '<S61>/Data Type Duplicate' : Unused code path elimination
//  Block '<S57>/Data Type Duplicate' : Unused code path elimination
//  Block '<S58>/Data Type Duplicate' : Unused code path elimination
//  Block '<S62>/Data Type Duplicate' : Unused code path elimination
//  Block '<S78>/Data Type Duplicate' : Unused code path elimination
//  Block '<S79>/Data Type Duplicate' : Unused code path elimination
//  Block '<S75>/Data Type Duplicate' : Unused code path elimination
//  Block '<S76>/Data Type Duplicate' : Unused code path elimination
//  Block '<S80>/Data Type Duplicate' : Unused code path elimination
//  Block '<S96>/Data Type Duplicate' : Unused code path elimination
//  Block '<S104>/Sin' : Unused code path elimination
//  Block '<S104>/Square2' : Unused code path elimination
//  Block '<S102>/Data Type Duplicate' : Unused code path elimination
//  Block '<S162>/Data Type Duplicate' : Unused code path elimination
//  Block '<S162>/Data Type Propagation' : Unused code path elimination
//  Block '<S179>/Data Type Duplicate' : Unused code path elimination
//  Block '<S180>/Data Type Duplicate' : Unused code path elimination
//  Block '<S176>/Data Type Duplicate' : Unused code path elimination
//  Block '<S177>/Data Type Duplicate' : Unused code path elimination
//  Block '<S196>/Data Type Duplicate' : Unused code path elimination
//  Block '<S197>/Data Type Duplicate' : Unused code path elimination
//  Block '<S193>/Data Type Duplicate' : Unused code path elimination
//  Block '<S194>/Data Type Duplicate' : Unused code path elimination
//  Block '<S198>/Data Type Duplicate' : Unused code path elimination
//  Block '<S9>/Signal Copy3' : Eliminate redundant signal conversion block
//  Block '<S9>/Signal Copy5' : Eliminate redundant signal conversion block
//  Block '<S9>/Signal Copy6' : Eliminate redundant signal conversion block
//  Block '<S14>/Gain' : Eliminated nontunable gain of 1
//  Block '<S21>/Gain' : Eliminated nontunable gain of 1
//  Block '<S25>/Gain' : Eliminated nontunable gain of 1
//  Block '<S30>/Reshape' : Reshape block reduction
//  Block '<S29>/Reshape' : Reshape block reduction
//  Block '<S29>/Reshape1' : Reshape block reduction
//  Block '<S45>/Gain' : Eliminated nontunable gain of 1
//  Block '<S48>/Reshape' : Reshape block reduction
//  Block '<S48>/Reshape1' : Reshape block reduction
//  Block '<S48>/Reshape3' : Reshape block reduction
//  Block '<S63>/Gain' : Eliminated nontunable gain of 1
//  Block '<S66>/Reshape' : Reshape block reduction
//  Block '<S66>/Reshape1' : Reshape block reduction
//  Block '<S66>/Reshape3' : Reshape block reduction
//  Block '<S84>/Saturation' : Eliminated Saturate block
//  Block '<S84>/Saturation1' : Eliminated Saturate block
//  Block '<S84>/Saturation2' : Eliminated Saturate block
//  Block '<S166>/Reshape' : Reshape block reduction
//  Block '<S165>/Reshape' : Reshape block reduction
//  Block '<S165>/Reshape1' : Reshape block reduction
//  Block '<S181>/Gain' : Eliminated nontunable gain of 1
//  Block '<S184>/Reshape' : Reshape block reduction
//  Block '<S184>/Reshape1' : Reshape block reduction
//  Block '<S184>/Reshape3' : Reshape block reduction
//  Block '<S97>/Gain1' : Unused code path elimination


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
//  '<S12>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem'
//  '<S13>'  : 'Formation_FMS/FMS Commander/Commander/Hold'
//  '<S14>'  : 'Formation_FMS/FMS Commander/Commander/Default/Airspeed Hold'
//  '<S15>'  : 'Formation_FMS/FMS Commander/Commander/Default/Altitude_Hold'
//  '<S16>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/Default'
//  '<S17>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble'
//  '<S18>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband'
//  '<S19>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold'
//  '<S20>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission'
//  '<S21>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/Default/Airspeed Hold'
//  '<S22>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/Default/Altitude_Hold'
//  '<S23>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Detect Change'
//  '<S24>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem'
//  '<S25>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Airspeed Hold'
//  '<S26>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Altitude_Hold'
//  '<S27>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command'
//  '<S28>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control'
//  '<S29>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/WayPoints'
//  '<S30>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP'
//  '<S31>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core'
//  '<S32>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP/Compare To Constant'
//  '<S33>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP/Compare To Constant1'
//  '<S34>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP/NearbyRefWP'
//  '<S35>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP/OutRegionRegWP'
//  '<S36>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1 Reference WP/SearchL1RefWP'
//  '<S37>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration'
//  '<S38>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle'
//  '<S39>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Modulus'
//  '<S40>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize'
//  '<S41>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize1'
//  '<S42>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/2D Cross Product'
//  '<S43>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize'
//  '<S44>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormAssemble/Mission_SubSystem/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize1'
//  '<S45>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Airspeed Hold'
//  '<S46>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Altitude_Hold'
//  '<S47>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control'
//  '<S48>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1 Reference WP'
//  '<S49>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1_Core'
//  '<S50>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/Reference_Point'
//  '<S51>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1 Reference WP/Compare To Constant'
//  '<S52>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1 Reference WP/OutRegionRegWP'
//  '<S53>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1 Reference WP/SearchL1RefWP'
//  '<S54>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1_Core/L1_Lateral_Acceleration'
//  '<S55>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle'
//  '<S56>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Modulus'
//  '<S57>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize'
//  '<S58>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize1'
//  '<S59>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/2D Cross Product'
//  '<S60>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize'
//  '<S61>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize1'
//  '<S62>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormDisband/Loiter_Control/Reference_Point/Vector Normalize'
//  '<S63>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Airspeed Hold'
//  '<S64>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Altitude_Hold'
//  '<S65>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control'
//  '<S66>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1 Reference WP'
//  '<S67>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1_Core'
//  '<S68>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/Reference_Point'
//  '<S69>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1 Reference WP/Compare To Constant'
//  '<S70>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1 Reference WP/OutRegionRegWP'
//  '<S71>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1 Reference WP/SearchL1RefWP'
//  '<S72>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1_Core/L1_Lateral_Acceleration'
//  '<S73>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle'
//  '<S74>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Modulus'
//  '<S75>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize'
//  '<S76>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize1'
//  '<S77>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/2D Cross Product'
//  '<S78>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize'
//  '<S79>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize1'
//  '<S80>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormHold/Loiter_Control/Reference_Point/Vector Normalize'
//  '<S81>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/Detect Change'
//  '<S82>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem'
//  '<S83>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Compare To Constant'
//  '<S84>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller'
//  '<S85>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller'
//  '<S86>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller'
//  '<S87>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Calc_Position_Velocity_Setpoint'
//  '<S88>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control'
//  '<S89>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller'
//  '<S90>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Forward_Control'
//  '<S91>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control'
//  '<S92>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Forward_Control/2D Cross Product'
//  '<S93>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Forward_Control/PD_Control'
//  '<S94>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Forward_Control/Vector Modulus'
//  '<S95>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Forward_Control/Vector Modulus1'
//  '<S96>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Forward_Control/Vector Normalize'
//  '<S97>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Forward_Control/PD_Control/DT Filter'
//  '<S98>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control/2D Cross Product'
//  '<S99>'  : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control/BearingVector'
//  '<S100>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control/Calc_LookAheadAngle_TrackProximity'
//  '<S101>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control/Lateral_Accel'
//  '<S102>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control/Vector Normalize'
//  '<S103>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control/BearingVector/signNoZero'
//  '<S104>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control/Calc_LookAheadAngle_TrackProximity/CalcTrackProximity'
//  '<S105>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control/Lateral_Accel/2D Cross Product'
//  '<S106>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control/Lateral_Accel/Vector Modulus'
//  '<S107>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control/Lateral_Accel/Vector Modulus1'
//  '<S108>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Forward_Lateral_control/Lateral_Control/Lateral_Accel/signNoZero'
//  '<S109>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller'
//  '<S110>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Anti-windup'
//  '<S111>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/D Gain'
//  '<S112>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Filter'
//  '<S113>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Filter ICs'
//  '<S114>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/I Gain'
//  '<S115>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Ideal P Gain'
//  '<S116>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Ideal P Gain Fdbk'
//  '<S117>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Integrator'
//  '<S118>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Integrator ICs'
//  '<S119>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/N Copy'
//  '<S120>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/N Gain'
//  '<S121>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/P Copy'
//  '<S122>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Parallel P Gain'
//  '<S123>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Reset Signal'
//  '<S124>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Saturation'
//  '<S125>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Saturation Fdbk'
//  '<S126>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Sum'
//  '<S127>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Sum Fdbk'
//  '<S128>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Tracking Mode'
//  '<S129>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Tracking Mode Sum'
//  '<S130>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Tsamp - Integral'
//  '<S131>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Tsamp - Ngain'
//  '<S132>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/postSat Signal'
//  '<S133>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/preSat Signal'
//  '<S134>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Anti-windup/Passthrough'
//  '<S135>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/D Gain/Disabled'
//  '<S136>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Filter/Disabled'
//  '<S137>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Filter ICs/Disabled'
//  '<S138>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/I Gain/Internal Parameters'
//  '<S139>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Ideal P Gain/Passthrough'
//  '<S140>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S141>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Integrator/Discrete'
//  '<S142>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Integrator ICs/Internal IC'
//  '<S143>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/N Copy/Disabled wSignal Specification'
//  '<S144>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/N Gain/Disabled'
//  '<S145>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/P Copy/Disabled'
//  '<S146>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Parallel P Gain/Internal Parameters'
//  '<S147>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Reset Signal/Disabled'
//  '<S148>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Saturation/Passthrough'
//  '<S149>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Saturation Fdbk/Disabled'
//  '<S150>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Sum/Sum_PI'
//  '<S151>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Sum Fdbk/Disabled'
//  '<S152>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Tracking Mode/Disabled'
//  '<S153>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Tracking Mode Sum/Passthrough'
//  '<S154>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Tsamp - Integral/Passthrough'
//  '<S155>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/Tsamp - Ngain/Passthrough'
//  '<S156>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/postSat Signal/Forward_Path'
//  '<S157>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Formation_Controller/Consensus Controller/Height_Controller/Discrete PID Controller/preSat Signal/Forward_Path'
//  '<S158>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Airspeed Hold'
//  '<S159>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Altitude_Hold'
//  '<S160>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/FormRadiusLimit'
//  '<S161>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command'
//  '<S162>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/FormRadiusLimit/Saturation Dynamic'
//  '<S163>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/FormRadiusLimit/min_radius'
//  '<S164>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control'
//  '<S165>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/WayPoints'
//  '<S166>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1 Reference WP'
//  '<S167>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1_Core'
//  '<S168>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1 Reference WP/Compare To Constant'
//  '<S169>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1 Reference WP/Compare To Constant1'
//  '<S170>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1 Reference WP/NearbyRefWP'
//  '<S171>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1 Reference WP/OutRegionRegWP'
//  '<S172>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1 Reference WP/SearchL1RefWP'
//  '<S173>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration'
//  '<S174>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle'
//  '<S175>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Modulus'
//  '<S176>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize'
//  '<S177>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize1'
//  '<S178>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/2D Cross Product'
//  '<S179>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize'
//  '<S180>' : 'Formation_FMS/FMS Commander/Commander/Form_Subsystem/FormMission/FormMission_SubSystem/Leader_Controller/Position Command/L1 Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize1'
//  '<S181>' : 'Formation_FMS/FMS Commander/Commander/Hold/Airspeed Hold'
//  '<S182>' : 'Formation_FMS/FMS Commander/Commander/Hold/Altitude_Hold'
//  '<S183>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control'
//  '<S184>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1 Reference WP'
//  '<S185>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core'
//  '<S186>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/Reference_Point'
//  '<S187>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1 Reference WP/Compare To Constant'
//  '<S188>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1 Reference WP/OutRegionRegWP'
//  '<S189>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1 Reference WP/SearchL1RefWP'
//  '<S190>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration'
//  '<S191>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle'
//  '<S192>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Modulus'
//  '<S193>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize'
//  '<S194>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Vector Normalize1'
//  '<S195>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/2D Cross Product'
//  '<S196>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize'
//  '<S197>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/L1_Core/L1_Lateral_Acceleration/Included Angle/Vector Normalize1'
//  '<S198>' : 'Formation_FMS/FMS Commander/Commander/Hold/Loiter_Control/Reference_Point/Vector Normalize'
//  '<S199>' : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.dubinsPath'
//  '<S200>' : 'Formation_FMS/FMS State Machine/Vehicle.Formation.check_form_valid'
//  '<S201>' : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.dubinsPath/MATLAB Function'
//  '<S202>' : 'Formation_FMS/FMS State Machine/Vehicle.Formation.check_form_valid/MATLAB Function'

#endif                                 // RTW_HEADER_Formation_FMS_h_

//
// File trailer for generated code.
//
// [EOF]
//
