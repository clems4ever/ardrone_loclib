/*
 * File: Pos_Controller_data.cpp
 *
 * Real-Time Workshop code generated for Simulink model Pos_Controller.
 *
 * Model version                        : 1.338
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Sun Dec 15 14:39:42 2013
 * TLC version                          : 7.4 (Jul 13 2009)
 * C/C++ source code generated on       : Sun Dec 15 14:39:42 2013
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Passed (0), Warning (1), Error (0)
 */

#include "Pos_Controller.h"
#include "Pos_Controller_private.h"

/* Block parameters (auto storage) */
Parameters_Pos_Controller Pos_Controller_P = {
  3.1415926535897931E+00,              /* Expression: pi
                                        * Referenced by: '<S1>/pi'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain'
                                        */
  9.0601472541377404E+02,              /* Expression: P
                                        * Referenced by: '<S4>/Proportional Gain'
                                        */
  0.005,                               /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S4>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S4>/Integrator'
                                        */
  -1.2370397758102000E+02,             /* Expression: D
                                        * Referenced by: '<S4>/Derivative Gain'
                                        */
  0.005,                               /* Computed Parameter: Filter_gainval
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
  1.5191928876765000E-01,             /* Expression: P //-4.1136422919626900E-03
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
  0.34,                                /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S2>/Saturation'
                                        */
  -0.34,                               /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S2>/Saturation'
                                        */
  1.5191928876765000E-01,             /* Expression: P //-1.1191928876765000E-01
                                        * Referenced by: '<S3>/Proportional Gain'
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
  0.005,                               /* Computed Parameter: Filter_gainval_i
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
  -2.5,                                /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S5>/Saturation'
                                        */
  3.0310056750280800E+01,              /* Expression: I
                                        * Referenced by: '<S4>/Integral Gain'
                                        */
  2.1341653146207601E-01               /* Expression: I
                                        * Referenced by: '<S5>/Integral Gain'
                                        */
};

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
