//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: FMS_TECS.cpp
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
#include "FMS_TECS.h"
#include "rtwtypes.h"
#include <cmath>
#include <cstring>
#include "FMS_TECS_types.h"
#include "Formation_FMS.h"

// Exported block parameters
struct_RybhgqIOamJFBGFK48xLQB FORMATION_PARAM{
  1.0,

  { 0.0, 1.0, 1.0, 0.2, 0.0, 0.0, 0.2, 0.0, 0.0 },

  { 0.0, -20.0, -20.0, 20.0, 0.0, 0.0, 20.0, 0.0, 0.0 },

  { 0.0, -20.0, 20.0, 20.0, 0.0, 40.0, -20.0, -40.0, 0.0 },

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
  3.0,

  { 0.0, 50.0, -50.0, 1000.0, 1000.0, 1000.0, 0.0, 0.0, 0.0 },
  100.0F,
  5.0F
} ;                                    // Variable: FORMATION_PARAM
                                          //  Referenced by: '<Root>/Model'


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


struct_U9pfOUhK42GcE1cZiAFZlB FMS_PARAM{
  25.0F,
  1000.0F,
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
                                          //  Referenced by: '<Root>/Model'


static void rate_scheduler(FMS_TECS::RT_MODEL_FMS_TECS_T *const FMS_TECS_M);

//
//         This function updates active task flag for each subrate.
//         The function is called at model base rate, hence the
//         generated code self-manages all its subrates.
//
static void rate_scheduler(FMS_TECS::RT_MODEL_FMS_TECS_T *const FMS_TECS_M)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (FMS_TECS_M->Timing.TaskCounters.TID[1])++;
  if ((FMS_TECS_M->Timing.TaskCounters.TID[1]) > 3) {// Sample time: [0.2s, 0.0s] 
    FMS_TECS_M->Timing.TaskCounters.TID[1] = 0;
  }
}

//
// Output and update for atomic system:
//    '<S17>/Integrator_Clamping'
//    '<S23>/Integrator_Clamping'
//
void FMS_TECS::FMS_TECS_Integrator_Clamping(real32_T rtu_err, real32_T
  rtu_measure, real32_T *rty_out, real32_T rtp_downlimit, real32_T rtp_uplimit)
{
  if (rtu_measure >= rtp_uplimit) {
    *rty_out = std::fmin(rtu_err, 0.0F);
  } else if (rtu_measure <= rtp_downlimit) {
    *rty_out = std::fmax(rtu_err, 0.0F);
  } else {
    *rty_out = rtu_err;
  }
}

// Model step function
void FMS_TECS::step()
{
  // local block i/o variables
  uint32_T rtb_timestamp;
  uint32_T rtb_timestamp_o;
  uint32_T rtb_type[3];
  real32_T rtb_ax_cmd;
  real32_T rtb_ay_cmd;
  real32_T rtb_vh_cmd;
  real32_T rtb_x[24];
  real32_T rtb_y[24];
  real32_T rtb_z[24];
  real32_T rtb_heading[24];
  real32_T rtb_ext1[24];
  real32_T rtb_ext2[24];
  uint8_T rtb_valid_items[3];
  real32_T rtb_new_state_idx_0;
  real32_T rtb_out_a;
  if ((&FMS_TECS_M)->Timing.TaskCounters.TID[1] == 0) {
    real32_T innovation_idx_0;
    real32_T rtb_Add_mp;
    real32_T rtb_DiscreteTimeIntegrator_g;
    real32_T rtb_Product;
    real32_T rtb_Product2;
    real32_T rtb_Product3;
    real32_T rtb_Product_h4;
    real32_T rtb_out;
    real32_T rtb_ske_rate;

    // ModelReference generated from: '<Root>/Model' incorporates:
    //   Inport: '<Root>/Formation_Cross'
    //   Inport: '<Root>/INS_Out'
    //   Inport: '<Root>/Mission_Data'
    //   Inport: '<Root>/Pilot_Cmd'

    ModelMDLOBJ1.step(&FMS_TECS_U.Pilot_Cmd.timestamp,
                      &FMS_TECS_U.Pilot_Cmd.mode,
                      &FMS_TECS_U.Mission_Data.timestamp,
                      &FMS_TECS_U.Mission_Data.type,
                      &FMS_TECS_U.Mission_Data.valid_items,
                      &FMS_TECS_U.Mission_Data.x[0], &FMS_TECS_U.Mission_Data.y
                      [0], &FMS_TECS_U.Mission_Data.z[0],
                      &FMS_TECS_U.Mission_Data.heading[0],
                      &FMS_TECS_U.Mission_Data.ext1[0],
                      &FMS_TECS_U.Mission_Data.ext2[0],
                      &FMS_TECS_U.INS_Out.timestamp, &FMS_TECS_U.INS_Out.phi,
                      &FMS_TECS_U.INS_Out.theta, &FMS_TECS_U.INS_Out.psi,
                      &FMS_TECS_U.INS_Out.p, &FMS_TECS_U.INS_Out.q,
                      &FMS_TECS_U.INS_Out.r, &FMS_TECS_U.INS_Out.quat[0],
                      &FMS_TECS_U.INS_Out.x_R, &FMS_TECS_U.INS_Out.y_R,
                      &FMS_TECS_U.INS_Out.h_R, &FMS_TECS_U.INS_Out.airspeed,
                      &FMS_TECS_U.INS_Out.ax, &FMS_TECS_U.INS_Out.ay,
                      &FMS_TECS_U.INS_Out.az, &FMS_TECS_U.INS_Out.vn,
                      &FMS_TECS_U.INS_Out.ve, &FMS_TECS_U.INS_Out.vd,
                      &FMS_TECS_U.Formation_Cross.timestamp[0],
                      &FMS_TECS_U.Formation_Cross.x_R[0],
                      &FMS_TECS_U.Formation_Cross.y_R[0],
                      &FMS_TECS_U.Formation_Cross.h_R[0],
                      &FMS_TECS_U.Formation_Cross.vn[0],
                      &FMS_TECS_U.Formation_Cross.ve[0],
                      &FMS_TECS_U.Formation_Cross.vd[0],
                      &FMS_TECS_U.Formation_Cross.psi[0],
                      &FMS_TECS_U.Formation_Cross.left_time[0], &rtb_timestamp,
                      &rtb_ax_cmd, &rtb_ay_cmd, &rtb_vh_cmd, &rtb_timestamp_o,
                      &rtb_type[0], &rtb_valid_items[0], &rtb_x[0], &rtb_y[0],
                      &rtb_z[0], &rtb_heading[0], &rtb_ext1[0], &rtb_ext2[0],
                      &FMS_TECS_B.left_time);

    // MATLAB Function: '<S6>/MATLAB Function' incorporates:
    //   Constant: '<S2>/Constant1'
    //   Inport: '<Root>/INS_Out'
    //   SampleTimeMath: '<S6>/Weighted Sample Time'
    //
    //  About '<S6>/Weighted Sample Time':
    //   y = K where K = ( w * Ts )

    rtb_out_a = 0.2F * FMS_TECS_DW.airspeed_state[1] +
      FMS_TECS_DW.airspeed_state[0];
    rtb_ske_rate = 0.0F * FMS_TECS_DW.airspeed_state[0] +
      FMS_TECS_DW.airspeed_state[1];
    FMS_TECS_DW.kalman_gain[0] = 0.866025388F;
    FMS_TECS_DW.kalman_gain[2] = 0.5F;
    FMS_TECS_DW.kalman_gain[1] = 0.5F;
    FMS_TECS_DW.kalman_gain[3] = 0.866025388F;
    innovation_idx_0 = FMS_TECS_U.INS_Out.airspeed - rtb_out_a;
    rtb_Add_mp = (0.0F - rtb_ske_rate) * FMS_TECS_DW.kalman_gain[2];
    rtb_new_state_idx_0 = (FMS_TECS_DW.kalman_gain[0] * innovation_idx_0 +
      rtb_Add_mp) * 0.2F + rtb_out_a;
    rtb_Product_h4 = (0.0F - rtb_ske_rate) * FMS_TECS_DW.kalman_gain[3];
    innovation_idx_0 = (FMS_TECS_DW.kalman_gain[1] * innovation_idx_0 +
                        rtb_Product_h4) * 0.2F + rtb_ske_rate;
    if (rtb_new_state_idx_0 < 2.22044605E-16F) {
      rtb_new_state_idx_0 = 0.0F;
      innovation_idx_0 = ((-rtb_out_a / 0.2F - rtb_Add_mp) /
                          FMS_TECS_DW.kalman_gain[0] * FMS_TECS_DW.kalman_gain[1]
                          + rtb_Product_h4) * 0.2F + rtb_ske_rate;
    }

    FMS_TECS_DW.airspeed_state[0] = rtb_new_state_idx_0;
    FMS_TECS_DW.airspeed_state[1] = innovation_idx_0;

    // End of MATLAB Function: '<S6>/MATLAB Function'

    // Product: '<S11>/Product3'
    rtb_ske_rate = rtb_new_state_idx_0 * innovation_idx_0;

    // Saturate: '<S14>/Saturation' incorporates:
    //   Constant: '<S14>/Constant'

    if (CONTROL_PARAM.FW_T_SPDWEIGHT > 2.0F) {
      innovation_idx_0 = 2.0F;
    } else if (CONTROL_PARAM.FW_T_SPDWEIGHT < 0.0F) {
      innovation_idx_0 = 0.0F;
    } else {
      innovation_idx_0 = CONTROL_PARAM.FW_T_SPDWEIGHT;
    }

    // End of Saturate: '<S14>/Saturation'

    // Saturate: '<S14>/Saturation1'
    if (innovation_idx_0 > 1.0F) {
      rtb_out_a = 1.0F;
    } else {
      rtb_out_a = innovation_idx_0;
    }

    // End of Saturate: '<S14>/Saturation1'

    // Product: '<S14>/Product3'
    rtb_Product3 = rtb_ske_rate * rtb_out_a;

    // Saturate: '<S14>/Saturation2' incorporates:
    //   Constant: '<S14>/Constant1'
    //   Sum: '<S14>/Add'

    if (2.0F - innovation_idx_0 > 1.0F) {
      innovation_idx_0 = 1.0F;
    } else {
      innovation_idx_0 = 2.0F - innovation_idx_0;
    }

    // End of Saturate: '<S14>/Saturation2'

    // Product: '<S11>/Product2' incorporates:
    //   Constant: '<S11>/Constant'
    //   Gain: '<S3>/Gain1'
    //   Inport: '<Root>/INS_Out'

    rtb_Add_mp = 9.80665F * -FMS_TECS_U.INS_Out.vd;

    // Product: '<S14>/Product2'
    rtb_Product2 = rtb_Add_mp * innovation_idx_0;

    // Saturate: '<S3>/Saturation'
    if (rtb_vh_cmd > CONTROL_PARAM.FW_T_CLMB_MAX) {
      rtb_Product_h4 = CONTROL_PARAM.FW_T_CLMB_MAX;
    } else if (rtb_vh_cmd < -CONTROL_PARAM.FW_T_SINK_MAX) {
      rtb_Product_h4 = -CONTROL_PARAM.FW_T_SINK_MAX;
    } else {
      rtb_Product_h4 = rtb_vh_cmd;
    }

    // Product: '<S11>/Product4' incorporates:
    //   Constant: '<S11>/Constant'
    //   Saturate: '<S3>/Saturation'

    rtb_DiscreteTimeIntegrator_g = rtb_Product_h4 * 9.80665F;

    // Product: '<S14>/Product'
    rtb_Product = rtb_DiscreteTimeIntegrator_g * innovation_idx_0;

    // Product: '<S7>/Product' incorporates:
    //   Constant: '<S21>/throttle_above_trim'
    //   Constant: '<S7>/Constant'
    //   Inport: '<Root>/INS_Out'
    //   Saturate: '<S21>/Saturation'
    //   Switch: '<S21>/Switch'

    rtb_Product_h4 = 9.80665F * CONTROL_PARAM.FW_T_CLMB_MAX;
    innovation_idx_0 = rtb_Product_h4 * 0.5F / FMS_TECS_U.INS_Out.airspeed;

    // MATLAB Function: '<S7>/Integrator_Clamping' incorporates:
    //   Inport: '<Root>/INS_Out'

    if (FMS_TECS_U.INS_Out.airspeed >= CONTROL_PARAM.FW_AIRSPD_MAX) {
      rtb_out = std::fmin(rtb_ax_cmd, 0.0F);
    } else if (FMS_TECS_U.INS_Out.airspeed <= CONTROL_PARAM.FW_AIRSPD_MIN) {
      rtb_out = std::fmax(rtb_ax_cmd, 0.0F);
    } else {
      rtb_out = rtb_ax_cmd;
    }

    // End of MATLAB Function: '<S7>/Integrator_Clamping'

    // Switch: '<S10>/Switch2' incorporates:
    //   RelationalOperator: '<S10>/LowerRelop1'

    if (!(rtb_out > innovation_idx_0)) {
      // Product: '<S7>/Product1' incorporates:
      //   Constant: '<S7>/Constant1'
      //   Inport: '<Root>/INS_Out'

      innovation_idx_0 = -9.80665F * CONTROL_PARAM.FW_T_SINK_MIN * 0.5F * (1.0F /
        FMS_TECS_U.INS_Out.airspeed);

      // Switch: '<S10>/Switch' incorporates:
      //   RelationalOperator: '<S10>/UpperRelop'

      if (!(rtb_out < innovation_idx_0)) {
        innovation_idx_0 = rtb_out;
      }

      // End of Switch: '<S10>/Switch'
    }

    // End of Switch: '<S10>/Switch2'

    // Product: '<S11>/Product1'
    innovation_idx_0 *= rtb_new_state_idx_0;

    // Sum: '<S14>/Add1' incorporates:
    //   Product: '<S14>/Product1'

    rtb_out_a = rtb_Product - innovation_idx_0 * rtb_out_a;

    // Sum: '<S14>/Add3' incorporates:
    //   Sum: '<S14>/Add2'

    rtb_Product3 = rtb_out_a - (rtb_Product2 - rtb_Product3);

    // Gain: '<S16>/seb_rate_ff'
    rtb_Product2 = CONTROL_PARAM.FW_T_SEB_R_FF * rtb_out_a;

    // Product: '<S15>/Product' incorporates:
    //   Constant: '<S15>/Constant1'

    rtb_out_a = 9.80665F * rtb_new_state_idx_0;

    // DiscreteIntegrator: '<S17>/Discrete-Time Integrator'
    if (FMS_TECS_DW.DiscreteTimeIntegrator_PrevRese != 0) {
      FMS_TECS_DW.DiscreteTimeIntegrator_DSTATE = 0.0F;
    }

    // Sum: '<S12>/Add' incorporates:
    //   DiscreteIntegrator: '<S17>/Discrete-Time Integrator'
    //   Gain: '<S16>/pitch_damping_gain'
    //   Product: '<S16>/Divide'
    //   Sum: '<S16>/Add'

    rtb_Product = (CONTROL_PARAM.FW_T_PTCH_DAMP * rtb_Product3 + rtb_Product2) /
      rtb_out_a + FMS_TECS_DW.DiscreteTimeIntegrator_DSTATE;

    // Saturate: '<S18>/Saturation'
    if (rtb_Product > CONTROL_PARAM.FW_P_LIM_MAX) {
      rtb_Product = CONTROL_PARAM.FW_P_LIM_MAX;
    } else if (rtb_Product < CONTROL_PARAM.FW_P_LIM_MIN) {
      rtb_Product = CONTROL_PARAM.FW_P_LIM_MIN;
    }

    // End of Saturate: '<S18>/Saturation'

    // Delay: '<S12>/Delay'
    rtb_Product2 = FMS_TECS_DW.Delay_DSTATE;

    // MATLAB Function: '<S18>/Pitch_Saturation' incorporates:
    //   Delay: '<S12>/Delay'
    //   SampleTimeMath: '<S18>/Weighted Sample Time'
    //
    //  About '<S18>/Weighted Sample Time':
    //   y = K where K = ( w * Ts )

    rtb_out = 0.2F * CONTROL_PARAM.FW_T_VERT_ACC / std::fmax(rtb_new_state_idx_0,
      1.1920929E-7F);
    rtb_new_state_idx_0 = rtb_Product2 - rtb_out;
    FMS_TECS_DW.Delay_DSTATE = rtb_Product2 + rtb_out;
    if (rtb_Product < rtb_new_state_idx_0) {
      FMS_TECS_DW.Delay_DSTATE = rtb_new_state_idx_0;
    } else if (!(rtb_Product > FMS_TECS_DW.Delay_DSTATE)) {
      FMS_TECS_DW.Delay_DSTATE = rtb_Product;
    }

    // End of MATLAB Function: '<S18>/Pitch_Saturation'

    // Trigonometry: '<S4>/Atan' incorporates:
    //   Constant: '<S4>/Constant'
    //   Product: '<S4>/Product'

    rtb_new_state_idx_0 = std::atan(0.101971619F * rtb_ay_cmd);

    // Saturate: '<S4>/Saturation'
    if (rtb_new_state_idx_0 > CONTROL_PARAM.FW_R_LIM) {
      // Outport: '<Root>/att_cmd'
      FMS_TECS_Y.att_cmd[0] = CONTROL_PARAM.FW_R_LIM;
    } else if (rtb_new_state_idx_0 < -CONTROL_PARAM.FW_R_LIM) {
      // Outport: '<Root>/att_cmd'
      FMS_TECS_Y.att_cmd[0] = -CONTROL_PARAM.FW_R_LIM;
    } else {
      // Outport: '<Root>/att_cmd'
      FMS_TECS_Y.att_cmd[0] = rtb_new_state_idx_0;
    }

    // End of Saturate: '<S4>/Saturation'

    // Outport: '<Root>/att_cmd' incorporates:
    //   Delay: '<S12>/Delay'

    FMS_TECS_Y.att_cmd[1] = FMS_TECS_DW.Delay_DSTATE;

    // MATLAB Function: '<S17>/Integrator_Clamping' incorporates:
    //   Product: '<S17>/Divide'

    FMS_TECS_Integrator_Clamping(rtb_Product3 / rtb_out_a, rtb_Product2,
      &rtb_out_a, CONTROL_PARAM.FW_P_LIM_MIN, CONTROL_PARAM.FW_P_LIM_MAX);

    // Sum: '<S21>/Add5' incorporates:
    //   Bias: '<S25>/Bias'
    //   Constant: '<S25>/Constant1'
    //   Gain: '<S25>/load_factor_correction'
    //   Inport: '<Root>/INS_Out'
    //   Product: '<S25>/Divide3'
    //   Sum: '<S21>/Add1'
    //   Trigonometry: '<S25>/Cos'

    rtb_new_state_idx_0 = (1.0F / std::cos(FMS_TECS_U.INS_Out.phi) - 1.0F) *
      CONTROL_PARAM.FW_T_RLL2THR + (rtb_DiscreteTimeIntegrator_g +
      innovation_idx_0);

    // Saturate: '<S21>/Saturation'
    innovation_idx_0 = -CONTROL_PARAM.FW_T_SINK_MIN * 9.80665F;
    if (rtb_new_state_idx_0 > rtb_Product_h4) {
      rtb_new_state_idx_0 = rtb_Product_h4;
    } else if (rtb_new_state_idx_0 < innovation_idx_0) {
      rtb_new_state_idx_0 = innovation_idx_0;
    }

    // Switch: '<S21>/Switch' incorporates:
    //   Constant: '<S21>/throttle_above_trim'
    //   Constant: '<S21>/throttle_below_trim'

    if (rtb_new_state_idx_0 >= 1.1920929E-7F) {
      rtb_Product_h4 = (CONTROL_PARAM.FW_THR_MAX - CONTROL_PARAM.FW_THR_TRIM) /
        rtb_Product_h4;
    } else {
      rtb_Product_h4 = (CONTROL_PARAM.FW_THR_TRIM - CONTROL_PARAM.FW_THR_MIN) /
        (CONTROL_PARAM.FW_T_SINK_MIN * 9.80665F);
    }

    // Product: '<S21>/Product' incorporates:
    //   Switch: '<S21>/Switch'

    rtb_Product_h4 *= rtb_new_state_idx_0;

    // Sum: '<S21>/Add'
    rtb_ske_rate += rtb_Add_mp;

    // DiscreteIntegrator: '<S24>/Discrete-Time Integrator5'
    if (FMS_TECS_DW.DiscreteTimeIntegrator5_IC_LOAD != 0) {
      FMS_TECS_DW.DiscreteTimeIntegrator5_DSTATE = rtb_ske_rate;
    }

    // Sum: '<S21>/Add3' incorporates:
    //   DiscreteIntegrator: '<S24>/Discrete-Time Integrator5'

    rtb_new_state_idx_0 -= FMS_TECS_DW.DiscreteTimeIntegrator5_DSTATE;

    // DiscreteIntegrator: '<S23>/Discrete-Time Integrator'
    if (FMS_TECS_DW.DiscreteTimeIntegrator_PrevRe_m != 0) {
      FMS_TECS_DW.DiscreteTimeIntegrator_DSTATE_l = 0.0F;
    }

    // Saturate: '<S13>/Saturation' incorporates:
    //   Constant: '<S21>/throttle_trim_adjusted'
    //   Constant: '<S22>/STE_rate_to_throttle'
    //   DiscreteIntegrator: '<S23>/Discrete-Time Integrator'
    //   Gain: '<S22>/throttle_damping_gain'
    //   Product: '<S22>/Product'
    //   Sum: '<S13>/Add'
    //   Sum: '<S21>/Add4'
    //   Sum: '<S22>/Add'

    FMS_TECS_Y.throttle_cmd = (1.0F / ((CONTROL_PARAM.FW_T_CLMB_MAX +
      CONTROL_PARAM.FW_T_SINK_MAX) * 9.80665F) * (CONTROL_PARAM.FW_T_THR_DAMP *
      rtb_new_state_idx_0) + (CONTROL_PARAM.FW_THR_TRIM + rtb_Product_h4)) +
      FMS_TECS_DW.DiscreteTimeIntegrator_DSTATE_l;

    // Saturate: '<S13>/Saturation'
    if (FMS_TECS_Y.throttle_cmd > CONTROL_PARAM.FW_THR_MAX) {
      // Saturate: '<S13>/Saturation'
      FMS_TECS_Y.throttle_cmd = CONTROL_PARAM.FW_THR_MAX;
    } else if (FMS_TECS_Y.throttle_cmd < CONTROL_PARAM.FW_THR_MIN) {
      // Saturate: '<S13>/Saturation'
      FMS_TECS_Y.throttle_cmd = CONTROL_PARAM.FW_THR_MIN;
    }

    // End of Saturate: '<S13>/Saturation'

    // MATLAB Function: '<S23>/Integrator_Clamping' incorporates:
    //   Constant: '<S23>/STE_rate_to_throttle'
    //   Delay: '<S13>/Delay'
    //   Product: '<S23>/Product'

    FMS_TECS_Integrator_Clamping(rtb_new_state_idx_0 * (1.0F / (9.80665F *
      (CONTROL_PARAM.FW_T_CLMB_MAX + CONTROL_PARAM.FW_T_SINK_MAX))),
      FMS_TECS_DW.Delay_DSTATE_n, &rtb_new_state_idx_0, CONTROL_PARAM.FW_THR_MIN,
      CONTROL_PARAM.FW_THR_MAX);

    // Outport: '<Root>/Other_Mission_Data' incorporates:
    //   BusCreator generated from: '<Root>/Other_Mission_Data'
    //   ModelReference generated from: '<Root>/Model'

    FMS_TECS_Y.Other_Mission_Data.timestamp = rtb_timestamp_o;
    FMS_TECS_Y.Other_Mission_Data.type[0] = rtb_type[0];
    FMS_TECS_Y.Other_Mission_Data.valid_items[0] = rtb_valid_items[0];
    FMS_TECS_Y.Other_Mission_Data.type[1] = rtb_type[1];
    FMS_TECS_Y.Other_Mission_Data.valid_items[1] = rtb_valid_items[1];
    FMS_TECS_Y.Other_Mission_Data.type[2] = rtb_type[2];
    FMS_TECS_Y.Other_Mission_Data.valid_items[2] = rtb_valid_items[2];
    std::memcpy(&FMS_TECS_Y.Other_Mission_Data.x[0], &rtb_x[0], 24U * sizeof
                (real32_T));
    std::memcpy(&FMS_TECS_Y.Other_Mission_Data.y[0], &rtb_y[0], 24U * sizeof
                (real32_T));
    std::memcpy(&FMS_TECS_Y.Other_Mission_Data.z[0], &rtb_z[0], 24U * sizeof
                (real32_T));
    std::memcpy(&FMS_TECS_Y.Other_Mission_Data.heading[0], &rtb_heading[0], 24U *
                sizeof(real32_T));
    std::memcpy(&FMS_TECS_Y.Other_Mission_Data.ext1[0], &rtb_ext1[0], 24U *
                sizeof(real32_T));
    std::memcpy(&FMS_TECS_Y.Other_Mission_Data.ext2[0], &rtb_ext2[0], 24U *
                sizeof(real32_T));

    // Outport: '<Root>/Form_Single'
    FMS_TECS_Y.Form_Single = FMS_TECS_B.left_time;

    // Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' incorporates:
    //   Gain: '<S17>/I_Gain'

    FMS_TECS_DW.DiscreteTimeIntegrator_DSTATE += CONTROL_PARAM.FW_T_I_GAIN_PIT *
      rtb_out_a * 0.2F;
    FMS_TECS_DW.DiscreteTimeIntegrator_PrevRese = 0;

    // Update for DiscreteIntegrator: '<S24>/Discrete-Time Integrator5' incorporates:
    //   Gain: '<S24>/Gain'
    //   Sum: '<S24>/Sum5'

    FMS_TECS_DW.DiscreteTimeIntegrator5_IC_LOAD = 0U;
    FMS_TECS_DW.DiscreteTimeIntegrator5_DSTATE += (rtb_ske_rate -
      FMS_TECS_DW.DiscreteTimeIntegrator5_DSTATE) * 2.5F * 0.2F;

    // Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
    //   Gain: '<S23>/I_Gain'

    FMS_TECS_DW.DiscreteTimeIntegrator_DSTATE_l += CONTROL_PARAM.FW_T_I_GAIN_THR
      * rtb_new_state_idx_0 * 0.2F;
    FMS_TECS_DW.DiscreteTimeIntegrator_PrevRe_m = 0;

    // Update for Delay: '<S13>/Delay'
    FMS_TECS_DW.Delay_DSTATE_n = FMS_TECS_Y.throttle_cmd;
  }

  rate_scheduler((&FMS_TECS_M));
}

// Model initialize function
void FMS_TECS::initialize()
{
  // Model Initialize function for ModelReference Block: '<Root>/Model'

  // Set error status pointer for ModelReference Block: '<Root>/Model'
  ModelMDLOBJ1.setErrorStatusPointer(rtmGetErrorStatusPointer((&FMS_TECS_M)));
  ModelMDLOBJ1.initialize();

  {
    // local block i/o variables
    uint32_T rtb_timestamp;
    uint32_T rtb_timestamp_o;
    uint32_T rtb_type[3];
    real32_T rtb_ax_cmd;
    real32_T rtb_ay_cmd;
    real32_T rtb_vh_cmd;
    real32_T rtb_x[24];
    real32_T rtb_y[24];
    real32_T rtb_z[24];
    real32_T rtb_heading[24];
    real32_T rtb_ext1[24];
    real32_T rtb_ext2[24];
    uint8_T rtb_valid_items[3];

    // InitializeConditions for DiscreteIntegrator: '<S24>/Discrete-Time Integrator5' 
    FMS_TECS_DW.DiscreteTimeIntegrator5_IC_LOAD = 1U;

    // SystemInitialize for ModelReference generated from: '<Root>/Model'
    ModelMDLOBJ1.init(&rtb_timestamp, &rtb_ax_cmd, &rtb_ay_cmd, &rtb_vh_cmd,
                      &rtb_timestamp_o, &rtb_type[0], &rtb_valid_items[0],
                      &rtb_x[0], &rtb_y[0], &rtb_z[0], &rtb_heading[0],
                      &rtb_ext1[0], &rtb_ext2[0]);
  }
}

// Model terminate function
void FMS_TECS::terminate()
{
  // (no terminate code required)
}

// Constructor
FMS_TECS::FMS_TECS() :
  FMS_TECS_U(),
  FMS_TECS_Y(),
  FMS_TECS_B(),
  FMS_TECS_DW(),
  FMS_TECS_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
FMS_TECS::~FMS_TECS()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
FMS_TECS::RT_MODEL_FMS_TECS_T * FMS_TECS::getRTM()
{
  return (&FMS_TECS_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
