//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: FMS_TECS.h
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
#ifndef RTW_HEADER_FMS_TECS_h_
#define RTW_HEADER_FMS_TECS_h_
#include "rtwtypes.h"
#include "FMS_TECS_types.h"
#include "Formation_FMS.h"
#include "zero_crossing_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  ((const char_T **)(&((rtm)->errorStatus)))
#endif

//
//  Exported Global Parameters
//
//  Note: Exported global parameters are tunable parameters with an exported
//  global storage class designation.  Code generation will declare the memory for
//  these parameters and exports their symbols.
//

extern struct_RybhgqIOamJFBGFK48xLQB FORMATION_PARAM;// Variable: FORMATION_PARAM
                                                        //  Referenced by: '<Root>/Model'

extern struct_FebwIpiU9Ih55vl7WG22GB CONTROL_PARAM;// Variable: CONTROL_PARAM
                                                      //  Referenced by:
                                                      //    '<Root>/Model'
                                                      //    '<S3>/Saturation'
                                                      //    '<S4>/Saturation'
                                                      //    '<S7>/Integrator_Clamping'
                                                      //    '<S7>/Constant'
                                                      //    '<S7>/Constant1'
                                                      //    '<S13>/Saturation'
                                                      //    '<S14>/Constant'
                                                      //    '<S16>/pitch_damping_gain'
                                                      //    '<S16>/seb_rate_ff'
                                                      //    '<S17>/Integrator_Clamping'
                                                      //    '<S17>/I_Gain'
                                                      //    '<S18>/Pitch_Saturation'
                                                      //    '<S18>/Saturation'
                                                      //    '<S21>/throttle_above_trim'
                                                      //    '<S21>/throttle_below_trim'
                                                      //    '<S21>/throttle_trim_adjusted'
                                                      //    '<S21>/Saturation'
                                                      //    '<S22>/STE_rate_to_throttle'
                                                      //    '<S22>/throttle_damping_gain'
                                                      //    '<S23>/Integrator_Clamping'
                                                      //    '<S23>/STE_rate_to_throttle'
                                                      //    '<S23>/I_Gain'
                                                      //    '<S25>/load_factor_correction'

extern struct_U9pfOUhK42GcE1cZiAFZlB FMS_PARAM;// Variable: FMS_PARAM
                                                  //  Referenced by: '<Root>/Model'


// Class declaration for model FMS_TECS
class FMS_TECS final
{
  // public data and function members
 public:
  // Block signals (default storage)
  struct B_FMS_TECS_T {
    real32_T left_time;                // '<Root>/Model'
  };

  // Block states (default storage) for system '<Root>'
  struct DW_FMS_TECS_T {
    real32_T DiscreteTimeIntegrator_DSTATE;// '<S17>/Discrete-Time Integrator'
    real32_T Delay_DSTATE;             // '<S12>/Delay'
    real32_T DiscreteTimeIntegrator5_DSTATE;// '<S24>/Discrete-Time Integrator5' 
    real32_T DiscreteTimeIntegrator_DSTATE_l;// '<S23>/Discrete-Time Integrator' 
    real32_T Delay_DSTATE_n;           // '<S13>/Delay'
    real32_T kalman_gain[4];           // '<S6>/MATLAB Function'
    real32_T airspeed_state[2];        // '<S6>/MATLAB Function'
    int8_T DiscreteTimeIntegrator_PrevRese;// '<S17>/Discrete-Time Integrator'
    int8_T DiscreteTimeIntegrator_PrevRe_m;// '<S23>/Discrete-Time Integrator'
    uint8_T DiscreteTimeIntegrator5_IC_LOAD;// '<S24>/Discrete-Time Integrator5' 
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_FMS_TECS_T {
    Pilot_Cmd_Bus Pilot_Cmd;           // '<Root>/Pilot_Cmd'
    Mission_Data_Bus Mission_Data;     // '<Root>/Mission_Data'
    INS_Out_Bus INS_Out;               // '<Root>/INS_Out'
    Formation_Cross_Bus Formation_Cross;// '<Root>/Formation_Cross'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_FMS_TECS_T {
    real32_T att_cmd[2];               // '<Root>/att_cmd'
    real32_T throttle_cmd;             // '<Root>/throttle_cmd'
    Other_Mission_Data_Bus Other_Mission_Data;// '<Root>/Other_Mission_Data'
    real32_T Form_Single;              // '<Root>/Form_Single'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_FMS_TECS_T {
    const char_T *errorStatus;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      struct {
        uint32_T TID[2];
      } TaskCounters;
    } Timing;
  };

  // Copy Constructor
  FMS_TECS(FMS_TECS const&) = delete;

  // Assignment Operator
  FMS_TECS& operator= (FMS_TECS const&) & = delete;

  // Move Constructor
  FMS_TECS(FMS_TECS &&) = delete;

  // Move Assignment Operator
  FMS_TECS& operator= (FMS_TECS &&) = delete;

  // Real-Time Model get method
  FMS_TECS::RT_MODEL_FMS_TECS_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_FMS_TECS_T *pExtU_FMS_TECS_T)
  {
    FMS_TECS_U = *pExtU_FMS_TECS_T;
  }

  // Root outports get method
  const ExtY_FMS_TECS_T &getExternalOutputs() const
  {
    return FMS_TECS_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  FMS_TECS();

  // Destructor
  ~FMS_TECS();

  // private data and function members
 private:
  // External inputs
  ExtU_FMS_TECS_T FMS_TECS_U;

  // External outputs
  ExtY_FMS_TECS_T FMS_TECS_Y;

  // Block signals
  B_FMS_TECS_T FMS_TECS_B;

  // Block states
  DW_FMS_TECS_T FMS_TECS_DW;

  // private member function(s) for subsystem '<S17>/Integrator_Clamping'
  static void FMS_TECS_Integrator_Clamping(real32_T rtu_err, real32_T
    rtu_measure, real32_T *rty_out, real32_T rtp_downlimit, real32_T rtp_uplimit);

  // model instance variable for '<Root>/Model'
  Formation_FMS ModelMDLOBJ1;

  // Real-Time Model
  RT_MODEL_FMS_TECS_T FMS_TECS_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S10>/Data Type Duplicate' : Unused code path elimination
//  Block '<S10>/Data Type Propagation' : Unused code path elimination
//  Block '<S3>/Constant' : Unused code path elimination
//  Block '<S24>/Data Type Conversion' : Eliminate redundant data type conversion


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
//  '<Root>' : 'FMS_TECS'
//  '<S1>'   : 'FMS_TECS/Lateral_Longitudinal_Control'
//  '<S2>'   : 'FMS_TECS/Lateral_Longitudinal_Control/Airspeed_Filter'
//  '<S3>'   : 'FMS_TECS/Lateral_Longitudinal_Control/Altitude_Control'
//  '<S4>'   : 'FMS_TECS/Lateral_Longitudinal_Control/Lateral_Control'
//  '<S5>'   : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control'
//  '<S6>'   : 'FMS_TECS/Lateral_Longitudinal_Control/Airspeed_Filter/Airspeed_Filter'
//  '<S7>'   : 'FMS_TECS/Lateral_Longitudinal_Control/Airspeed_Filter/Calc_TAS_Rate_Setpoint'
//  '<S8>'   : 'FMS_TECS/Lateral_Longitudinal_Control/Airspeed_Filter/Airspeed_Filter/MATLAB Function'
//  '<S9>'   : 'FMS_TECS/Lateral_Longitudinal_Control/Airspeed_Filter/Calc_TAS_Rate_Setpoint/Integrator_Clamping'
//  '<S10>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Airspeed_Filter/Calc_TAS_Rate_Setpoint/Saturation Dynamic'
//  '<S11>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Calc_Specific_Energy_Rates'
//  '<S12>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control'
//  '<S13>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control'
//  '<S14>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/Calc_Seb_Rate'
//  '<S15>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/Calc_climb_angle_to_SEB_rate'
//  '<S16>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/FF & Damp'
//  '<S17>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/I'
//  '<S18>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/Pitch_Saturation'
//  '<S19>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/I/Integrator_Clamping'
//  '<S20>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/Pitch_Saturation/Pitch_Saturation'
//  '<S21>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/Calc_STE_Rate'
//  '<S22>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/Damp'
//  '<S23>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/I'
//  '<S24>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/Calc_STE_Rate/First Order LPF'
//  '<S25>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/Calc_STE_Rate/induced_drag_scales'
//  '<S26>'  : 'FMS_TECS/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/I/Integrator_Clamping'

#endif                                 // RTW_HEADER_FMS_TECS_h_

//
// File trailer for generated code.
//
// [EOF]
//
