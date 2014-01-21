/*
 * File: Pos_Controller_data.cpp
 *
 * Real-Time Workshop code generated for Simulink model Pos_Controller.
 *
 * Model version                        : 1.416
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Sat Jan 18 17:18:04 2014
 * TLC version                          : 7.4 (Jul 13 2009)
 * C/C++ source code generated on       : Sat Jan 18 17:18:05 2014
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86/Pentium
 * Code generation objective: Efficiency
 * Validation result: Passed (9), Warning (1), Error (0)
 */

#include "Pos_Controller.h"
#include "Pos_Controller_private.h"

/* Block parameters (auto storage) */
Parameters_Pos_Controller Pos_Controller_P = {
  0.1,                                 /* Expression: P
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
  1.0,                                 /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S2>/Saturation'
                                        */
  -1.0,                                /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S2>/Saturation'
                                        */
  0.1,										              /* Expression: P
                                        * Referenced by: '<S3>/Proportional Gain'
                                        */
  1.0,                                 /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S3>/Saturation'
                                        */
  -1.0,                                /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S3>/Saturation'
                                        */
  /*2.4909082795731101E+00*/7.0E-1,              /* Expression: P
                                        * Referenced by: '<S5>/Proportional Gain'
                                        */
  1.0,                                 /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S5>/Saturation'
                                        */
  -1.0,                                /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S5>/Saturation'
                                        */
  3.1415926535897931E+00,              /* Expression: pi
                                        * Referenced by: '<S1>/pi'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain'
                                        */
  4E+00,								               /* Expression: P
                                        * Referenced by: '<S4>/Proportional Gain'
                                        */
  1.0,                                 /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S4>/Saturation'
                                        */
  -1.0,                                /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S4>/Saturation'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/constant'
                                        */
  3.1415926535897931E+00,              /* Expression: pi
                                        * Referenced by: '<S6>/add_if_x_neg'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/add_if_x_pos'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S6>/if_X_pos'
                                        */
};

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
