//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Formation_FMS.h
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
#ifndef RTW_HEADER_Formation_FMS_h_
#define RTW_HEADER_Formation_FMS_h_
#include "rtwtypes.h"
#include "Formation_FMS_types.h"

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rt_nonfinite.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

#include "zero_crossing_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

//
//  Exported Global Parameters
//
//  Note: Exported global parameters are tunable parameters with an exported
//  global storage class designation.  Code generation will declare the memory for
//  these parameters and exports their symbols.
//

extern struct_FebwIpiU9Ih55vl7WG22GB CONTROL_PARAM;// Variable: CONTROL_PARAM
                                                      //  Referenced by:
                                                      //    '<S15>/Constant'
                                                      //    '<S16>/Saturation'
                                                      //    '<S64>/Constant'
                                                      //    '<S65>/Saturation'
                                                      //    '<S19>/Constant'
                                                      //    '<S20>/Saturation'
                                                      //    '<S42>/Constant'
                                                      //    '<S43>/Saturation'

extern struct_9QCb8LDOYrZ6XTvfIWkyaC FMS_PARAM;// Variable: FMS_PARAM
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


// Class declaration for model Formation_FMS
class Formation_FMS final
{
  // public data and function members
 public:
  // Block signals for system '<S3>/Vehicle.Formation.FormAssemble.dubinsPath'
  struct B_VehicleFormationFormAssembl_T {
    sGXMO9PmoeW2JqDMJvYKnvG_Forma_T object[3];
    real_T result[75];
    sGXMO9PmoeW2JqDMJvYKnvG_Forma_T obj;
    real_T b_data[4];
    real_T c_data[4];
    int32_T i_data[4];
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
    captured_var_Formation_FMS_T PhiMaximum;
    captured_var_Formation_FMS_T rad2deg;
  };

  // Block signals (default storage)
  struct B_Formation_FMS_T {
    Other_Mission_Data_Bus mission;    // '<S83>/MATLAB Function'
    Formation_Cross_Bus Formation_Cross_d;
    real32_T xyz_O_nx3[9];             // '<S44>/Vector Concatenate'
    real32_T vNED_O_nx3[9];            // '<S44>/Vector Concatenate1'
    Commander_In_Bus Cmd_In;           // '<Root>/FMS State Machine'
    real32_T pose[3];
    real32_T new_vel_err[2];
    real32_T Reshape2_bi[2];           // '<S48>/Reshape2'
    real32_T P_mr[2];                  // '<S49>/SearchL1RefWP'
    real32_T P_b[2];                   // '<S49>/OutRegionRegWP'
    real32_T BusConversion_InsertedFor_FMS_c[2];
    real32_T unit_point_to_next[2];
    real32_T unit_centre_to_pose[2];
    real32_T Saturation1;              // '<S47>/Saturation1'
    real32_T a;
    real32_T psi;
    real32_T Sum1_e;                   // '<S19>/Sum1'
    real32_T u;                        // '<S25>/SearchL1RefWP'
    real32_T Saturation_g;             // '<S56>/Saturation'
    real32_T l1_a_cmd_m;               // '<S56>/Divide'
    real32_T u_e;                      // '<S49>/SearchL1RefWP'
    real32_T rtb_P_mr_m;
    real32_T pos_err_idx_2;
    real32_T pos_err_idx_0;
    real32_T new_pos_err_idx_1;
    real32_T new_pos_err_idx_0;
    real32_T rtb_Switch_i_idx_0;
    real32_T a_tmp;
    real32_T y;
    real32_T scale;
    real32_T absxk;
    real32_T t;
    real32_T nearest_cross;
    real32_T project_line;
    real32_T dotProduct;
    real32_T nearest_cross_tmp;
    real32_T nearest_cross_tmp_c;
    real32_T unit_centre_to_pose_idx_0;
    real32_T unit_point_to_next_tmp;
    real32_T unit_point_to_next_tmp_k;
    real32_T scale_c;
    real32_T absxk_b;
    real32_T t_p;
    real32_T q;
    int32_T n;                         // '<S67>/SearchL1RefWP'
    int32_T i;
    int32_T b_vlen;
    int32_T i_c;
    int32_T i1;
    uint32_T Mission_Data_timestamp_prev;
    uint32_T VehicleFormationFormAssembleWay;
    PilotMode mode_prev;
    VehicleState state;                // '<Root>/FMS State Machine'
    boolean_T x[2];
    boolean_T b_x[2];
    uint16_T wp_index;                 // '<Root>/FMS State Machine'
    uint16_T wp_index_f;
    int8_T rtPrevAction;
    boolean_T FixPtRelationalOperator_m;// '<S40>/FixPt Relational Operator'
    boolean_T c_y;
    boolean_T rEQ0;
    B_VehicleFormationFormAssembl_T VehicleFormationFormAssembled_o;
                            // '<S3>/Vehicle.Formation.FormAssemble.dubinsPath'
  };

  // Block states (default storage) for system '<Root>'
  struct DW_Formation_FMS_T {
    real_T Delay_DSTATE;               // '<S65>/Delay'
    real_T Delay_DSTATE_l;             // '<S20>/Delay'
    real_T Delay_DSTATE_c;             // '<S43>/Delay'
    real32_T DiscreteTimeIntegrator5_DSTATE;// '<S86>/Discrete-Time Integrator5' 
    real32_T Delay_DSTATE_p;           // '<S16>/Delay'
    real32_T start_vel_DSTATE[2];      // '<S69>/start_vel'
    real32_T DiscreteTimeIntegrator1_DSTATE;// '<S4>/Discrete-Time Integrator1'
    uint32_T DelayInput1_DSTATE;       // '<S7>/Delay Input1'
    PilotMode Delay_DSTATE_j;          // '<S5>/Delay'
    real32_T waypoints[25];            // '<Root>/FMS State Machine'
    real32_T DiscreteTimeIntegrator5_PREV_U;// '<S86>/Discrete-Time Integrator5' 
    uint32_T Mission_Data_timestamp_start;// '<Root>/FMS State Machine'
    uint32_T VehicleFormationFormAssembleW_m;
                          // '<S3>/Vehicle.Formation.FormAssemble.Waypoint.LPF'
    PilotMode mode_start;              // '<Root>/FMS State Machine'
    uint16_T DelayInput1_DSTATE_h;     // '<S17>/Delay Input1'
    uint16_T DelayInput1_DSTATE_d;     // '<S40>/Delay Input1'
    int8_T SwitchCase_ActiveSubsystem; // '<S10>/Switch Case'
    uint8_T is_Vehicle;                // '<Root>/FMS State Machine'
    uint8_T is_Formation;              // '<Root>/FMS State Machine'
    uint8_T is_FormAssemble;           // '<Root>/FMS State Machine'
    uint8_T is_FormMission;            // '<Root>/FMS State Machine'
    uint8_T is_Mission;                // '<Root>/FMS State Machine'
    uint8_T is_active_c3_Formation_FMS;// '<Root>/FMS State Machine'
    uint8_T DiscreteTimeIntegrator5_IC_LOAD;// '<S86>/Discrete-Time Integrator5' 
    uint8_T DiscreteTimeIntegrator5_SYSTEM_;// '<S86>/Discrete-Time Integrator5' 
    boolean_T VehicleFormationFormAssembleW_o;
                          // '<S3>/Vehicle.Formation.FormAssemble.Waypoint.LPF'
    boolean_T icLoad;                  // '<S16>/Delay'
    boolean_T icLoad_c;                // '<S69>/start_vel'
    boolean_T icLoad_m;                // '<S65>/Delay'
    boolean_T icLoad_h;                // '<S20>/Delay'
    boolean_T icLoad_n;                // '<S43>/Delay'
  };

  // Zero-crossing (trigger) state
  struct PrevZCX_Formation_FMS_T {
    ZCSigState Mission_SubSystem_Reset_ZCE;// '<S12>/Mission_SubSystem'
    ZCSigState FormMission_SubSystem_Reset_ZCE;// '<S13>/FormMission_SubSystem'
  };

  // Constant parameters (default storage)
  struct ConstP_Formation_FMS_T {
    // Expression: adj_matrix
    //  Referenced by: '<S44>/Consensus Controller'

    real_T ConsensusController_adj_matrix[9];

    // Expression: rel_x
    //  Referenced by: '<S44>/Consensus Controller'

    real_T ConsensusController_rel_x[9];

    // Expression: rel_y
    //  Referenced by: '<S44>/Consensus Controller'

    real_T ConsensusController_rel_y[9];
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_Formation_FMS_T {
    Pilot_Cmd_Bus Pilot_Cmd;           // '<Root>/Pilot_Cmd'
    Mission_Data_Bus Mission_Data;     // '<Root>/Mission_Data'
    INS_Out_Bus INS_Out;               // '<Root>/INS_Out'
    Formation_Cross_Bus Formation_Cross;// '<Root>/Formation_Cross'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_Formation_FMS_T {
    FMS_Out_Bus FMS_Out;               // '<Root>/FMS_Out'
    Other_Mission_Data_Bus Other_Mission_Data;// '<Root>/Other_Mission_Data'
    real32_T Form_Single;              // '<Root>/Form_Single'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_Formation_FMS_T {
    const char_T * volatile errorStatus;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      uint32_T clockTick0;
    } Timing;
  };

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

  // Root inports set method
  void setExternalInputs(const ExtU_Formation_FMS_T *pExtU_Formation_FMS_T)
  {
    Formation_FMS_U = *pExtU_Formation_FMS_T;
  }

  // Root outports get method
  const ExtY_Formation_FMS_T &getExternalOutputs() const
  {
    return Formation_FMS_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  Formation_FMS();

  // Destructor
  ~Formation_FMS();

  // private data and function members
 private:
  // External inputs
  ExtU_Formation_FMS_T Formation_FMS_U;

  // External outputs
  ExtY_Formation_FMS_T Formation_FMS_Y;

  // Block signals
  B_Formation_FMS_T Formation_FMS_B;

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

  // private member function(s) for subsystem '<S3>/Vehicle.Formation.FormAssemble.dubinsPath'
  void VehicleFormationFormAssembledub(const Formation_Cross_Bus
    *rtu_Formation_Cross, Other_Mission_Data_Bus *rty_Other_Mission_Data,
    B_VehicleFormationFormAssembl_T *localB);
  real_T Formation_FMS_atan3(real_T x, real_T y, real_T x0, real_T b_y0);
  void Formation_FMS_Dubins(const captured_var_Formation_FMS_T *PhiMaximum,
    const captured_var_Formation_FMS_T *rad2deg, real_T xs, real_T ys, real_T
    psi_s, real_T xf, real_T yf, real_T psi_f, real_T v, real_T xts[4], real_T
    yts[4], real_T xtf[4], real_T ytf[4], real_T cs[4], real_T cf[4], real_T lt
    [4], real_T l[4], real_T pos[4], real_T pof[4], real_T *r, real_T m_data[],
    int32_T *m_size, real_T n_data[], int32_T *n_size,
    B_VehicleFormationFormAssembl_T *localB);

  // private member function(s) for subsystem '<Root>'
  real32_T Formation_FMS_norm(const real32_T x[2]);
  real32_T Formation_FMS_rt_atan2f_snf(real32_T u0, real32_T u1);
  real32_T Formation_FMS_mod(real32_T x);
  void Formati_getMinDistanceAtSegment(const real32_T waypoints[25], const
    real32_T pose[3], uint16_T segment, real32_T *dist, real32_T *ratio);
  void Formation_exit_internal_Vehicle(void);
  void Formation_FMS_Vehicle(const INS_Out_Bus *BusConversion_InsertedFor_FMS_c,
    const Formation_Cross_Bus *BusConversion_InsertedFor_FMS_p, const
    Mission_Data_Bus *BusConversion_InsertedFor_FMSSt, const uint32_T
    *Mission_Data_timestamp_prev, const PilotMode *mode_prev,
    Formation_Cross_Bus *Formation_Cross_d);

  // Real-Time Model
  RT_MODEL_Formation_FMS_T Formation_FMS_M;
};

// Constant parameters (default storage)
extern const Formation_FMS::ConstP_Formation_FMS_T Formation_FMS_ConstP;

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
//  Block '<S86>/Data Type Conversion' : Eliminate redundant data type conversion


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
//  '<S82>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.Waypoint.LPF'
//  '<S83>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.dubinsPath'
//  '<S84>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.dubinsPathRatio'
//  '<S85>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.check_form_valid'
//  '<S86>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.Waypoint.LPF/First Order LPF'
//  '<S87>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.dubinsPath/MATLAB Function'
//  '<S88>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.FormAssemble.dubinsPathRatio/Dubins Closest Point'
//  '<S89>'  : 'Formation_FMS/FMS State Machine/Vehicle.Formation.check_form_valid/MATLAB Function'

#endif                                 // RTW_HEADER_Formation_FMS_h_

//
// File trailer for generated code.
//
// [EOF]
//
