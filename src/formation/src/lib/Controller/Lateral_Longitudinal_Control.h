//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Lateral_Longitudinal_Control.h
//
// Code generated for Simulink model 'Lateral_Longitudinal_Control'.
//
// Model version                  : 1.1
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Fri Mar 29 19:23:15 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_Lateral_Longitudinal_Control_h_
#define RTW_HEADER_Lateral_Longitudinal_Control_h_
#include "rtwtypes.h"
#include "Lateral_Longitudinal_Control_types.h"

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
                                                      //    '<S3>/Saturation'
                                                      //    '<S4>/Saturation'
                                                      //    '<S6>/Integrator_Clamping'
                                                      //    '<S6>/Constant'
                                                      //    '<S6>/Constant1'
                                                      //    '<S12>/Saturation'
                                                      //    '<S13>/Constant'
                                                      //    '<S15>/pitch_damping_gain'
                                                      //    '<S15>/seb_rate_ff'
                                                      //    '<S16>/Error_Saturation'
                                                      //    '<S16>/I_Gain'
                                                      //    '<S17>/Saturation'
                                                      //    '<S19>/throttle_above_trim'
                                                      //    '<S19>/throttle_below_trim'
                                                      //    '<S19>/throttle_trim_adjusted'
                                                      //    '<S19>/Saturation'
                                                      //    '<S20>/STE_rate_to_throttle'
                                                      //    '<S20>/throttle_damping_gain'
                                                      //    '<S21>/Error_Saturation'
                                                      //    '<S21>/STE_rate_to_throttle'
                                                      //    '<S21>/I_Gain'
                                                      //    '<S23>/load_factor_correction'


// Class declaration for model Lateral_Longitudinal_Control
class Lateral_Longitudinal_Control final
{
  // public data and function members
 public:
  // Block states (default storage) for system '<Root>'
  struct DW_Lateral_Longitudinal_Contr_T {
    real32_T Integrator_DSTATE;        // '<S7>/Integrator'
    real32_T Integrator1_DSTATE;       // '<S7>/Integrator1'
    real32_T DiscreteTimeIntegrator_DSTATE;// '<S16>/Discrete-Time Integrator'
    real32_T Delay_DSTATE;             // '<S11>/Delay'
    real32_T DiscreteTimeIntegrator5_DSTATE;// '<S22>/Discrete-Time Integrator5' 
    real32_T DiscreteTimeIntegrator_DSTATE_l;// '<S21>/Discrete-Time Integrator' 
    real32_T Delay_DSTATE_n;           // '<S12>/Delay'
    int8_T Integrator_PrevResetState;  // '<S7>/Integrator'
    int8_T Integrator1_PrevResetState; // '<S7>/Integrator1'
    int8_T DiscreteTimeIntegrator_PrevRese;// '<S16>/Discrete-Time Integrator'
    int8_T DiscreteTimeIntegrator_PrevRe_m;// '<S21>/Discrete-Time Integrator'
    uint8_T Integrator1_IC_LOADING;    // '<S7>/Integrator1'
    uint8_T DiscreteTimeIntegrator5_IC_LOAD;// '<S22>/Discrete-Time Integrator5' 
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_Lateral_Longitudinal_Con_T {
    INS_Out_Bus INS_Out;               // '<Root>/INS_Out'
    FMS_Out_Bus FMS_Out;               // '<Root>/FMS_Out'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_Lateral_Longitudinal_Con_T {
    real32_T att_cmd[2];               // '<Root>/att_cmd'
    real32_T throttle_cmd;             // '<Root>/throttle_cmd'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_Lateral_Longitudinal_T {
    const char_T * volatile errorStatus;
  };

  // Copy Constructor
  Lateral_Longitudinal_Control(Lateral_Longitudinal_Control const&) = delete;

  // Assignment Operator
  Lateral_Longitudinal_Control& operator= (Lateral_Longitudinal_Control const&)
    & = delete;

  // Move Constructor
  Lateral_Longitudinal_Control(Lateral_Longitudinal_Control &&) = delete;

  // Move Assignment Operator
  Lateral_Longitudinal_Control& operator= (Lateral_Longitudinal_Control &&) =
    delete;

  // Real-Time Model get method
  Lateral_Longitudinal_Control::RT_MODEL_Lateral_Longitudinal_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_Lateral_Longitudinal_Con_T
    *pExtU_Lateral_Longitudinal_Con_T)
  {
    Lateral_Longitudinal_Control_U = *pExtU_Lateral_Longitudinal_Con_T;
  }

  // Root outports get method
  const ExtY_Lateral_Longitudinal_Con_T &getExternalOutputs() const
  {
    return Lateral_Longitudinal_Control_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  Lateral_Longitudinal_Control();

  // Destructor
  ~Lateral_Longitudinal_Control();

  // private data and function members
 private:
  // External inputs
  ExtU_Lateral_Longitudinal_Con_T Lateral_Longitudinal_Control_U;

  // External outputs
  ExtY_Lateral_Longitudinal_Con_T Lateral_Longitudinal_Control_Y;

  // Block states
  DW_Lateral_Longitudinal_Contr_T Lateral_Longitudinal_Control_DW;

  // private member function(s) for subsystem '<S16>/Error_Saturation'
  static void Lateral_Longit_Error_Saturation(real32_T rtu_err, real32_T
    rtu_cmd_last, real32_T *rty_y, real32_T rtp_downlimit, real32_T rtp_uplimit);

  // Real-Time Model
  RT_MODEL_Lateral_Longitudinal_T Lateral_Longitudinal_Control_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S9>/Data Type Duplicate' : Unused code path elimination
//  Block '<S9>/Data Type Propagation' : Unused code path elimination
//  Block '<S3>/Constant' : Unused code path elimination
//  Block '<S22>/Data Type Conversion' : Eliminate redundant data type conversion


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
//  '<Root>' : 'Lateral_Longitudinal_Control'
//  '<S1>'   : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control'
//  '<S2>'   : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Airspeed_Filter'
//  '<S3>'   : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Altitude_Control'
//  '<S4>'   : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Lateral_Control'
//  '<S5>'   : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control'
//  '<S6>'   : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Airspeed_Filter/Calc_TAS_Rate_Setpoint'
//  '<S7>'   : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Airspeed_Filter/Second Order DT Filter'
//  '<S8>'   : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Airspeed_Filter/Calc_TAS_Rate_Setpoint/Integrator_Clamping'
//  '<S9>'   : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Airspeed_Filter/Calc_TAS_Rate_Setpoint/Saturation Dynamic'
//  '<S10>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Calc_Specific_Energy_Rates'
//  '<S11>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control'
//  '<S12>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control'
//  '<S13>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/Calc_Seb_Rate'
//  '<S14>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/Calc_climb_angle_to_SEB_rate'
//  '<S15>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/FF & Damp'
//  '<S16>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/I'
//  '<S17>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/Pitch_Saturation'
//  '<S18>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Pitch_Control/I/Error_Saturation'
//  '<S19>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/Calc_STE_Rate'
//  '<S20>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/Damp'
//  '<S21>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/I'
//  '<S22>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/Calc_STE_Rate/First Order LPF'
//  '<S23>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/Calc_STE_Rate/induced_drag_scales'
//  '<S24>'  : 'Lateral_Longitudinal_Control/Lateral_Longitudinal_Control/Longitudinal_Control/Throttle_Control/I/Error_Saturation'

#endif                            // RTW_HEADER_Lateral_Longitudinal_Control_h_

//
// File trailer for generated code.
//
// [EOF]
//
