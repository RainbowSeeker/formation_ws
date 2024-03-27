//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Formation_FMS_data.cpp
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

// Constant parameters (default storage)
const Formation_FMS::ConstP_Formation_FMS_T Formation_FMS_ConstP{
  // Expression: adj_matrix
  //  Referenced by: '<S44>/Consensus Controller'

  { 0.0, 1.0, 1.0, 0.2, 0.0, 0.0, 0.2, 0.0, 0.0 },

  // Expression: rel_x
  //  Referenced by: '<S44>/Consensus Controller'

  { 0.0, -20.0, -20.0, 20.0, 0.0, 0.0, 20.0, 0.0, 0.0 },

  // Expression: rel_y
  //  Referenced by: '<S44>/Consensus Controller'

  { 0.0, -20.0, 20.0, 20.0, 0.0, 40.0, -20.0, -40.0, 0.0 }
};

//
// File trailer for generated code.
//
// [EOF]
//
