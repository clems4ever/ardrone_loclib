/*
 * File: Pos_Controller_data.cpp
 *
 * Real-Time Workshop code generated for Simulink model Pos_Controller.
 *
 * Model version                        : 1.408
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Thu Jan  2 12:38:17 2014
 * TLC version                          : 7.4 (Jul 13 2009)
 * C/C++ source code generated on       : Thu Jan  2 12:38:18 2014
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
  4.1997709983345699E-01,              /* Expression: P
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
  /*0.005,*/0.005,                               /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S2>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
  /*2.7541646632060800E+01,*/0.01,              /* Expression: D
                                        * Referenced by: '<S2>/Derivative Gain'
                                        */
  0.005,                               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S2>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
  5.1506722229987297E+01,              /* Expression: N
                                        * Referenced by: '<S2>/Filter Coefficient'
                                        */
  0.34,                                /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S2>/Saturation'
                                        */
  -0.34,                               /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S2>/Saturation'
                                        */
  4.1997709983345699E-01,              /* Expression: P
                                        * Referenced by: '<S3>/Proportional Gain'
                                        */
  /*0.005,*/0.005,                               /* Computed Parameter: Integrator_gainval_n
                                        * Referenced by: '<S3>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S3>/Integrator'
                                        */
  /*2.7541646632060800E+01,*/0.01,              /* Expression: D
                                        * Referenced by: '<S3>/Derivative Gain'
                                        */
  0.005,                               /* Computed Parameter: Filter_gainval_i
                                        * Referenced by: '<S3>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S3>/Filter'
                                        */
  5.1506722229987297E+01,              /* Expression: N
                                        * Referenced by: '<S3>/Filter Coefficient'
                                        */
  0.34,                                /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S3>/Saturation'
                                        */
  -0.34,                               /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S3>/Saturation'
                                        */
  2.4909082795731101E+00,              /* Expression: P
                                        * Referenced by: '<S5>/Proportional Gain'
                                        */
  0.005,                               /* Computed Parameter: Integrator_gainval_h
                                        * Referenced by: '<S5>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S5>/Integrator'
                                        */
  2.6179755316459801E+00,              /* Expression: D
                                        * Referenced by: '<S5>/Derivative Gain'
                                        */
  0.005,                               /* Computed Parameter: Filter_gainval_iy
                                        * Referenced by: '<S5>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S5>/Filter'
                                        */
  2.1853072056216000E+01,              /* Expression: N
                                        * Referenced by: '<S5>/Filter Coefficient'
                                        */
  2.0,                                 /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S5>/Saturation'
                                        */
  -2.0,                                /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S5>/Saturation'
                                        */
  3.1415926535897931E+00,              /* Expression: pi
                                        * Referenced by: '<S1>/pi'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain'
                                        */
  9.0601472541377404E+02,              /* Expression: P
                                        * Referenced by: '<S4>/Proportional Gain'
                                        */
  0.005,                               /* Computed Parameter: Integrator_gainval_m
                                        * Referenced by: '<S4>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S4>/Integrator'
                                        */
  -1.2370397758102000E+02,             /* Expression: D
                                        * Referenced by: '<S4>/Derivative Gain'
                                        */
  0.005,                               /* Computed Parameter: Filter_gainval_ig
                                        * Referenced by: '<S4>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S4>/Filter'
                                        */
  5.3134742355322997E+00,              /* Expression: N
                                        * Referenced by: '<S4>/Filter Coefficient'
                                        */
  360.0,                               /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S4>/Saturation'
                                        */
  -360.0,                              /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S4>/Saturation'
                                        */
  1.4526222165903099E-03,              /* Expression: I
                                        * Referenced by: '<S2>/Integral Gain'
                                        */
  1.4526222165903099E-03,              /* Expression: I
                                        * Referenced by: '<S3>/Integral Gain'
                                        */
  3.0310056750280800E+01,              /* Expression: I
                                        * Referenced by: '<S4>/Integral Gain'
                                        */
  2.1341653146207601E-01,              /* Expression: I
                                        * Referenced by: '<S5>/Integral Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/constant'
                                        */
  3.1415926535897931E+00,              /* Expression: pi
                                        * Referenced by: '<S1>/add_if_x_neg'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/add_if_x_pos'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S1>/if_X_pos'
                                        */
};

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
