//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Lateral_Longitudinal_Control.cpp
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
#include "Lateral_Longitudinal_Control.h"
#include "rtwtypes.h"
#include <cmath>
#include "Lateral_Longitudinal_Control_types.h"

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


//
// Output and update for atomic system:
//    '<S16>/Error_Saturation'
//    '<S21>/Error_Saturation'
//
void Lateral_Longitudinal_Control::Lateral_Longit_Error_Saturation(real32_T
  rtu_err, real32_T rtu_cmd_last, real32_T *rty_y, real32_T rtp_downlimit,
  real32_T rtp_uplimit)
{
  if (rtu_cmd_last >= rtp_uplimit) {
    *rty_y = std::fmin(rtu_err, 0.0F);
  } else if (rtu_cmd_last <= rtp_downlimit) {
    *rty_y = std::fmax(rtu_err, 0.0F);
  } else {
    *rty_y = rtu_err;
  }
}

// Model step function
void Lateral_Longitudinal_Control::step()
{
  real32_T rtb_Add_mp;
  real32_T rtb_DiscreteTimeIntegrator;
  real32_T rtb_DiscreteTimeIntegrator_g;
  real32_T rtb_Product;
  real32_T rtb_Product1_f;
  real32_T rtb_Product2;
  real32_T rtb_Product3;
  real32_T rtb_Product_j;
  real32_T rtb_Sum;
  real32_T rtb_gain1;
  real32_T rtb_out;
  real32_T rtb_ske_rate;
  real32_T rtb_y;

  // DiscreteIntegrator: '<S7>/Integrator'
  if (Lateral_Longitudinal_Control_DW.Integrator_PrevResetState != 0) {
    Lateral_Longitudinal_Control_DW.Integrator_DSTATE = 0.0F;
  }

  // DiscreteIntegrator: '<S7>/Integrator1' incorporates:
  //   Inport: '<Root>/INS_Out'

  if (Lateral_Longitudinal_Control_DW.Integrator1_IC_LOADING != 0) {
    Lateral_Longitudinal_Control_DW.Integrator1_DSTATE =
      Lateral_Longitudinal_Control_U.INS_Out.airspeed;
  }

  if (Lateral_Longitudinal_Control_DW.Integrator1_PrevResetState != 0) {
    Lateral_Longitudinal_Control_DW.Integrator1_DSTATE =
      Lateral_Longitudinal_Control_U.INS_Out.airspeed;
  }

  // Sum: '<S7>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S7>/Integrator1'
  //   Inport: '<Root>/INS_Out'

  rtb_y = Lateral_Longitudinal_Control_U.INS_Out.airspeed -
    Lateral_Longitudinal_Control_DW.Integrator1_DSTATE;

  // Sum: '<S7>/Sum' incorporates:
  //   DiscreteIntegrator: '<S7>/Integrator'
  //   Gain: '<S7>/gain'

  rtb_Sum = 20.0F * rtb_y + Lateral_Longitudinal_Control_DW.Integrator_DSTATE;

  // Gain: '<S7>/gain1'
  rtb_gain1 = 100.0F * rtb_y;

  // Saturate: '<S2>/Saturation2' incorporates:
  //   Inport: '<Root>/INS_Out'

  if (Lateral_Longitudinal_Control_U.INS_Out.airspeed <= 0.0F) {
    rtb_y = 0.0F;
  } else {
    rtb_y = Lateral_Longitudinal_Control_U.INS_Out.airspeed;
  }

  // End of Saturate: '<S2>/Saturation2'

  // Product: '<S10>/Product3' incorporates:
  //   DiscreteIntegrator: '<S7>/Integrator'

  rtb_ske_rate = Lateral_Longitudinal_Control_DW.Integrator_DSTATE * rtb_y;

  // Saturate: '<S13>/Saturation' incorporates:
  //   Constant: '<S13>/Constant'

  if (CONTROL_PARAM.FW_T_SPDWEIGHT > 2.0F) {
    rtb_Product1_f = 2.0F;
  } else if (CONTROL_PARAM.FW_T_SPDWEIGHT < 0.0F) {
    rtb_Product1_f = 0.0F;
  } else {
    rtb_Product1_f = CONTROL_PARAM.FW_T_SPDWEIGHT;
  }

  // End of Saturate: '<S13>/Saturation'

  // Saturate: '<S13>/Saturation1'
  if (rtb_Product1_f > 1.0F) {
    rtb_DiscreteTimeIntegrator = 1.0F;
  } else {
    rtb_DiscreteTimeIntegrator = rtb_Product1_f;
  }

  // End of Saturate: '<S13>/Saturation1'

  // Product: '<S13>/Product3'
  rtb_Product3 = rtb_ske_rate * rtb_DiscreteTimeIntegrator;

  // Saturate: '<S13>/Saturation2' incorporates:
  //   Constant: '<S13>/Constant1'
  //   Sum: '<S13>/Add'

  if (2.0F - rtb_Product1_f > 1.0F) {
    rtb_Product1_f = 1.0F;
  } else {
    rtb_Product1_f = 2.0F - rtb_Product1_f;
  }

  // End of Saturate: '<S13>/Saturation2'

  // Product: '<S10>/Product2' incorporates:
  //   Constant: '<S10>/Constant'
  //   Gain: '<S3>/Gain1'
  //   Inport: '<Root>/INS_Out'

  rtb_Add_mp = 9.80665F * -Lateral_Longitudinal_Control_U.INS_Out.vd;

  // Product: '<S13>/Product2'
  rtb_Product2 = rtb_Add_mp * rtb_Product1_f;

  // Saturate: '<S3>/Saturation' incorporates:
  //   Inport: '<Root>/FMS_Out'

  if (Lateral_Longitudinal_Control_U.FMS_Out.vh_cmd >
      CONTROL_PARAM.FW_T_CLMB_MAX) {
    rtb_Product_j = CONTROL_PARAM.FW_T_CLMB_MAX;
  } else if (Lateral_Longitudinal_Control_U.FMS_Out.vh_cmd <
             -CONTROL_PARAM.FW_T_SINK_MAX) {
    rtb_Product_j = -CONTROL_PARAM.FW_T_SINK_MAX;
  } else {
    rtb_Product_j = Lateral_Longitudinal_Control_U.FMS_Out.vh_cmd;
  }

  // Product: '<S10>/Product4' incorporates:
  //   Constant: '<S10>/Constant'
  //   Saturate: '<S3>/Saturation'

  rtb_DiscreteTimeIntegrator_g = rtb_Product_j * 9.80665F;

  // Product: '<S13>/Product'
  rtb_Product = rtb_DiscreteTimeIntegrator_g * rtb_Product1_f;

  // Product: '<S6>/Product' incorporates:
  //   Constant: '<S19>/throttle_above_trim'
  //   Constant: '<S6>/Constant'
  //   Inport: '<Root>/INS_Out'
  //   Saturate: '<S19>/Saturation'
  //   Switch: '<S19>/Switch'

  rtb_Product_j = 9.80665F * CONTROL_PARAM.FW_T_CLMB_MAX;
  rtb_Product1_f = rtb_Product_j * 0.5F /
    Lateral_Longitudinal_Control_U.INS_Out.airspeed;

  // MATLAB Function: '<S6>/Integrator_Clamping' incorporates:
  //   Inport: '<Root>/FMS_Out'
  //   Inport: '<Root>/INS_Out'

  if (Lateral_Longitudinal_Control_U.INS_Out.airspeed >=
      CONTROL_PARAM.FW_AIRSPD_MAX) {
    rtb_out = std::fmin(Lateral_Longitudinal_Control_U.FMS_Out.ax_cmd, 0.0F);
  } else if (Lateral_Longitudinal_Control_U.INS_Out.airspeed <=
             CONTROL_PARAM.FW_AIRSPD_MIN) {
    rtb_out = std::fmax(Lateral_Longitudinal_Control_U.FMS_Out.ax_cmd, 0.0F);
  } else {
    rtb_out = Lateral_Longitudinal_Control_U.FMS_Out.ax_cmd;
  }

  // End of MATLAB Function: '<S6>/Integrator_Clamping'

  // Switch: '<S9>/Switch2' incorporates:
  //   RelationalOperator: '<S9>/LowerRelop1'

  if (!(rtb_out > rtb_Product1_f)) {
    // Product: '<S6>/Product1' incorporates:
    //   Constant: '<S6>/Constant1'
    //   Inport: '<Root>/INS_Out'

    rtb_Product1_f = -9.80665F * CONTROL_PARAM.FW_T_SINK_MIN * 0.5F * (1.0F /
      Lateral_Longitudinal_Control_U.INS_Out.airspeed);

    // Switch: '<S9>/Switch' incorporates:
    //   RelationalOperator: '<S9>/UpperRelop'

    if (!(rtb_out < rtb_Product1_f)) {
      rtb_Product1_f = rtb_out;
    }

    // End of Switch: '<S9>/Switch'
  }

  // End of Switch: '<S9>/Switch2'

  // Product: '<S10>/Product1'
  rtb_Product1_f *= rtb_y;

  // Sum: '<S13>/Add1' incorporates:
  //   Product: '<S13>/Product1'

  rtb_DiscreteTimeIntegrator = rtb_Product - rtb_Product1_f *
    rtb_DiscreteTimeIntegrator;

  // Sum: '<S13>/Add3' incorporates:
  //   Sum: '<S13>/Add2'

  rtb_Product3 = rtb_DiscreteTimeIntegrator - (rtb_Product2 - rtb_Product3);

  // Product: '<S14>/Product' incorporates:
  //   Constant: '<S14>/Constant1'

  rtb_y *= 9.80665F;

  // DiscreteIntegrator: '<S16>/Discrete-Time Integrator'
  if (Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator_PrevRese != 0) {
    Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator_DSTATE = 0.0F;
  }

  // Sum: '<S11>/Add' incorporates:
  //   DiscreteIntegrator: '<S16>/Discrete-Time Integrator'
  //   Gain: '<S15>/pitch_damping_gain'
  //   Gain: '<S15>/seb_rate_ff'
  //   Product: '<S15>/Divide'
  //   Sum: '<S15>/Add'

  rtb_DiscreteTimeIntegrator = (CONTROL_PARAM.FW_T_PTCH_DAMP * rtb_Product3 +
    CONTROL_PARAM.FW_T_SEB_R_FF * rtb_DiscreteTimeIntegrator) / rtb_y +
    Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator_DSTATE;

  // Saturate: '<S17>/Saturation'
  if (rtb_DiscreteTimeIntegrator > CONTROL_PARAM.FW_P_LIM_MAX) {
    rtb_DiscreteTimeIntegrator = CONTROL_PARAM.FW_P_LIM_MAX;
  } else if (rtb_DiscreteTimeIntegrator < CONTROL_PARAM.FW_P_LIM_MIN) {
    rtb_DiscreteTimeIntegrator = CONTROL_PARAM.FW_P_LIM_MIN;
  }

  // End of Saturate: '<S17>/Saturation'

  // Trigonometry: '<S4>/Atan' incorporates:
  //   Constant: '<S4>/Constant'
  //   Inport: '<Root>/FMS_Out'
  //   Product: '<S4>/Product'

  rtb_Product2 = std::atan(0.101971619F *
    Lateral_Longitudinal_Control_U.FMS_Out.ay_cmd);

  // Saturate: '<S4>/Saturation'
  if (rtb_Product2 > CONTROL_PARAM.FW_R_LIM) {
    // Outport: '<Root>/att_cmd'
    Lateral_Longitudinal_Control_Y.att_cmd[0] = CONTROL_PARAM.FW_R_LIM;
  } else if (rtb_Product2 < -CONTROL_PARAM.FW_R_LIM) {
    // Outport: '<Root>/att_cmd'
    Lateral_Longitudinal_Control_Y.att_cmd[0] = -CONTROL_PARAM.FW_R_LIM;
  } else {
    // Outport: '<Root>/att_cmd'
    Lateral_Longitudinal_Control_Y.att_cmd[0] = rtb_Product2;
  }

  // End of Saturate: '<S4>/Saturation'

  // Outport: '<Root>/att_cmd'
  Lateral_Longitudinal_Control_Y.att_cmd[1] = rtb_DiscreteTimeIntegrator;

  // MATLAB Function: '<S16>/Error_Saturation' incorporates:
  //   Delay: '<S11>/Delay'
  //   Product: '<S16>/Divide'

  Lateral_Longit_Error_Saturation(rtb_Product3 / rtb_y,
    Lateral_Longitudinal_Control_DW.Delay_DSTATE, &rtb_y,
    CONTROL_PARAM.FW_P_LIM_MIN, CONTROL_PARAM.FW_P_LIM_MAX);

  // Sum: '<S19>/Add5' incorporates:
  //   Bias: '<S23>/Bias'
  //   Constant: '<S23>/Constant1'
  //   Gain: '<S23>/load_factor_correction'
  //   Inport: '<Root>/INS_Out'
  //   Product: '<S23>/Divide3'
  //   Sum: '<S19>/Add1'
  //   Trigonometry: '<S23>/Cos'

  rtb_Product1_f = (1.0F / std::cos(Lateral_Longitudinal_Control_U.INS_Out.phi)
                    - 1.0F) * CONTROL_PARAM.FW_T_RLL2THR +
    (rtb_DiscreteTimeIntegrator_g + rtb_Product1_f);

  // Saturate: '<S19>/Saturation'
  rtb_DiscreteTimeIntegrator_g = -CONTROL_PARAM.FW_T_SINK_MIN * 9.80665F;
  if (rtb_Product1_f > rtb_Product_j) {
    rtb_Product1_f = rtb_Product_j;
  } else if (rtb_Product1_f < rtb_DiscreteTimeIntegrator_g) {
    rtb_Product1_f = rtb_DiscreteTimeIntegrator_g;
  }

  // Switch: '<S19>/Switch' incorporates:
  //   Constant: '<S19>/throttle_above_trim'
  //   Constant: '<S19>/throttle_below_trim'

  if (rtb_Product1_f >= 1.1920929E-7F) {
    rtb_Product_j = (CONTROL_PARAM.FW_THR_MAX - CONTROL_PARAM.FW_THR_TRIM) /
      rtb_Product_j;
  } else {
    rtb_Product_j = (CONTROL_PARAM.FW_THR_TRIM - CONTROL_PARAM.FW_THR_MIN) /
      (CONTROL_PARAM.FW_T_SINK_MIN * 9.80665F);
  }

  // Product: '<S19>/Product' incorporates:
  //   Switch: '<S19>/Switch'

  rtb_Product_j *= rtb_Product1_f;

  // Sum: '<S19>/Add'
  rtb_ske_rate += rtb_Add_mp;

  // DiscreteIntegrator: '<S22>/Discrete-Time Integrator5'
  if (Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator5_IC_LOAD != 0) {
    Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator5_DSTATE =
      rtb_ske_rate;
  }

  // Sum: '<S19>/Add3' incorporates:
  //   DiscreteIntegrator: '<S22>/Discrete-Time Integrator5'

  rtb_Product1_f -=
    Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator5_DSTATE;

  // DiscreteIntegrator: '<S21>/Discrete-Time Integrator'
  if (Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator_PrevRe_m != 0) {
    Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator_DSTATE_l = 0.0F;
  }

  // Saturate: '<S12>/Saturation' incorporates:
  //   Constant: '<S19>/throttle_trim_adjusted'
  //   Constant: '<S20>/STE_rate_to_throttle'
  //   DiscreteIntegrator: '<S21>/Discrete-Time Integrator'
  //   Gain: '<S20>/throttle_damping_gain'
  //   Product: '<S20>/Product'
  //   Sum: '<S12>/Add'
  //   Sum: '<S19>/Add4'
  //   Sum: '<S20>/Add'

  Lateral_Longitudinal_Control_Y.throttle_cmd = (1.0F /
    ((CONTROL_PARAM.FW_T_CLMB_MAX + CONTROL_PARAM.FW_T_SINK_MAX) * 9.80665F) *
    (CONTROL_PARAM.FW_T_THR_DAMP * rtb_Product1_f) + (CONTROL_PARAM.FW_THR_TRIM
    + rtb_Product_j)) +
    Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator_DSTATE_l;

  // Saturate: '<S12>/Saturation'
  if (Lateral_Longitudinal_Control_Y.throttle_cmd > CONTROL_PARAM.FW_THR_MAX) {
    // Saturate: '<S12>/Saturation'
    Lateral_Longitudinal_Control_Y.throttle_cmd = CONTROL_PARAM.FW_THR_MAX;
  } else if (Lateral_Longitudinal_Control_Y.throttle_cmd <
             CONTROL_PARAM.FW_THR_MIN) {
    // Saturate: '<S12>/Saturation'
    Lateral_Longitudinal_Control_Y.throttle_cmd = CONTROL_PARAM.FW_THR_MIN;
  }

  // End of Saturate: '<S12>/Saturation'

  // MATLAB Function: '<S21>/Error_Saturation' incorporates:
  //   Constant: '<S21>/STE_rate_to_throttle'
  //   Delay: '<S12>/Delay'
  //   Product: '<S21>/Product'

  Lateral_Longit_Error_Saturation(rtb_Product1_f * (1.0F / (9.80665F *
    (CONTROL_PARAM.FW_T_CLMB_MAX + CONTROL_PARAM.FW_T_SINK_MAX))),
    Lateral_Longitudinal_Control_DW.Delay_DSTATE_n, &rtb_Product1_f,
    CONTROL_PARAM.FW_THR_MIN, CONTROL_PARAM.FW_THR_MAX);

  // Update for DiscreteIntegrator: '<S7>/Integrator'
  Lateral_Longitudinal_Control_DW.Integrator_DSTATE += 0.005F * rtb_gain1;
  Lateral_Longitudinal_Control_DW.Integrator_PrevResetState = 0;

  // Update for DiscreteIntegrator: '<S7>/Integrator1'
  Lateral_Longitudinal_Control_DW.Integrator1_IC_LOADING = 0U;
  Lateral_Longitudinal_Control_DW.Integrator1_DSTATE += 0.005F * rtb_Sum;
  Lateral_Longitudinal_Control_DW.Integrator1_PrevResetState = 0;

  // Update for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S16>/I_Gain'

  Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator_DSTATE +=
    CONTROL_PARAM.FW_T_I_GAIN_PIT * rtb_y * 0.005F;
  Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator_PrevRese = 0;

  // Update for Delay: '<S11>/Delay'
  Lateral_Longitudinal_Control_DW.Delay_DSTATE = rtb_DiscreteTimeIntegrator;

  // Update for DiscreteIntegrator: '<S22>/Discrete-Time Integrator5' incorporates:
  //   Gain: '<S22>/Gain'
  //   Sum: '<S22>/Sum5'

  Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator5_IC_LOAD = 0U;
  Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator5_DSTATE +=
    (rtb_ske_rate -
     Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator5_DSTATE) * 2.5F *
    0.005F;

  // Update for DiscreteIntegrator: '<S21>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S21>/I_Gain'

  Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator_DSTATE_l +=
    CONTROL_PARAM.FW_T_I_GAIN_THR * rtb_Product1_f * 0.005F;
  Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator_PrevRe_m = 0;

  // Update for Delay: '<S12>/Delay'
  Lateral_Longitudinal_Control_DW.Delay_DSTATE_n =
    Lateral_Longitudinal_Control_Y.throttle_cmd;
}

// Model initialize function
void Lateral_Longitudinal_Control::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S7>/Integrator1'
  Lateral_Longitudinal_Control_DW.Integrator1_IC_LOADING = 1U;

  // InitializeConditions for DiscreteIntegrator: '<S22>/Discrete-Time Integrator5' 
  Lateral_Longitudinal_Control_DW.DiscreteTimeIntegrator5_IC_LOAD = 1U;
}

// Model terminate function
void Lateral_Longitudinal_Control::terminate()
{
  // (no terminate code required)
}

// Constructor
Lateral_Longitudinal_Control::Lateral_Longitudinal_Control() :
  Lateral_Longitudinal_Control_U(),
  Lateral_Longitudinal_Control_Y(),
  Lateral_Longitudinal_Control_DW(),
  Lateral_Longitudinal_Control_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
Lateral_Longitudinal_Control::~Lateral_Longitudinal_Control()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
Lateral_Longitudinal_Control::RT_MODEL_Lateral_Longitudinal_T
  * Lateral_Longitudinal_Control::getRTM()
{
  return (&Lateral_Longitudinal_Control_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
