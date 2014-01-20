/*
 * File: Pos_Controller.cpp
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

/* External inputs (root inport signals with auto storage) */
ExternalInputs_Pos_Controller Pos_Controller_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_Pos_Controller Pos_Controller_Y;

/* Real-time model */
RT_MODEL_Pos_Controller Pos_Controller_M_;
RT_MODEL_Pos_Controller *Pos_Controller_M = &Pos_Controller_M_;

/* Model step function */
void Pos_Controller_step(void)
{
  real_T rtb_modulo;
  real_T rtb_Saturation;
  real_T rtb_Saturation_l;

  /* Gain: '<S2>/Proportional Gain' incorporates:
   *  Inport: '<Root>/consigne'
   *  Inport: '<Root>/position'
   *  Sum: '<S1>/Sum'
   */
  rtb_modulo = (Pos_Controller_U.consigne[0] - Pos_Controller_U.position[0]) *
    Pos_Controller_P.ProportionalGain_Gain;

  /* Saturate: '<S2>/Saturation' */
  rtb_Saturation = rt_SATURATE(rtb_modulo, Pos_Controller_P.Saturation_LowerSat,
    Pos_Controller_P.Saturation_UpperSat);

  /* Gain: '<S3>/Proportional Gain' incorporates:
   *  Inport: '<Root>/consigne'
   *  Inport: '<Root>/position'
   *  Sum: '<S1>/Sum'
   */
  rtb_modulo = (Pos_Controller_U.consigne[1] - Pos_Controller_U.position[1]) *
    Pos_Controller_P.ProportionalGain_Gain_j;

  /* Saturate: '<S3>/Saturation' */
  rtb_Saturation_l = rt_SATURATE(rtb_modulo,
    Pos_Controller_P.Saturation_LowerSat_h,
    Pos_Controller_P.Saturation_UpperSat_h);

  /* Embedded MATLAB: '<S1>/reference change' */
  /* Embedded MATLAB Function 'Pos_Controller/reference change': '<S7>:1' */
  /* #codegen */
  /* '<S7>:1:4' */
  /* phi en radians, angle entre X et X1 */
  /* i.e. positif si rotation de X(nouveau rep) vers X1(ancien rep) dans le sens trigonométrique */
  /* =the output vector is a rotation of -phi of the input vector */
  /* '<S7>:1:4' */

  /* Gain: '<S5>/Proportional Gain' incorporates:
   *  Inport: '<Root>/consigne'
   *  Inport: '<Root>/position'
   *  Sum: '<S1>/Sum'
   */
  rtb_modulo = (Pos_Controller_U.consigne[2] - Pos_Controller_U.position[2]) *
    Pos_Controller_P.ProportionalGain_Gain_c;

  /* Saturate: '<S5>/Saturation' */
  rtb_modulo = rt_SATURATE(rtb_modulo, Pos_Controller_P.Saturation_LowerSat_e,
    Pos_Controller_P.Saturation_UpperSat_k);

  /* Outport: '<Root>/speed cmd' incorporates:
   *  Inport: '<Root>/yaw'
   */
  Pos_Controller_Y.speedcmd[0] = rtb_Saturation * cos(Pos_Controller_U.yaw) +
    rtb_Saturation_l * sin(Pos_Controller_U.yaw);
  Pos_Controller_Y.speedcmd[1] = (-rtb_Saturation) * sin(Pos_Controller_U.yaw) +
    rtb_Saturation_l * cos(Pos_Controller_U.yaw);
  Pos_Controller_Y.speedcmd[2] = rtb_modulo;

  /* Switch: '<S1>/if_yaw_is_relative' incorporates:
   *  Constant: '<S1>/constant'
   *  Inport: '<Root>/yaw_is_relative'
   *  Product: '<S6>/Divide'
   *  Sum: '<S6>/Sum4'
   *  Trigonometry: '<S6>/Trigonometric Function'
   */
  if (Pos_Controller_U.yaw_is_relative) {
    /* Switch: '<S6>/if_X_pos' incorporates:
     *  Constant: '<S6>/add_if_x_neg'
     *  Constant: '<S6>/add_if_x_pos'
     */
    if (rtb_Saturation >= Pos_Controller_P.if_X_pos_Threshold) {
      rtb_modulo = Pos_Controller_P.add_if_x_pos_Value;
    } else {
      rtb_modulo = Pos_Controller_P.add_if_x_neg_Value;
    }

    rtb_modulo += atan(rtb_Saturation_l / rtb_Saturation);
  } else {
    rtb_modulo = Pos_Controller_P.constant_Value;
  }

  /* Gain: '<S4>/Proportional Gain' incorporates:
   *  Constant: '<S1>/pi'
   *  Gain: '<S1>/Gain'
   *  Inport: '<Root>/yaw'
   *  Inport: '<Root>/yaw_cons'
   *  Math: '<S1>/modulo'
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S1>/Sum2'
   *  Sum: '<S1>/Sum3'
   *  Sum: '<S1>/Sum5'
   */
  rtb_modulo = (rt_mod(((Pos_Controller_U.yaw_cons - Pos_Controller_U.yaw) +
                        rtb_modulo) + Pos_Controller_P.pi_Value,
                       Pos_Controller_P.Gain_Gain * Pos_Controller_P.pi_Value) -
                Pos_Controller_P.pi_Value) *
    Pos_Controller_P.ProportionalGain_Gain_f;

  /* Outport: '<Root>/yaw cmd' incorporates:
   *  Saturate: '<S4>/Saturation'
   */
  Pos_Controller_Y.yawcmd = rt_SATURATE(rtb_modulo,
    Pos_Controller_P.Saturation_LowerSat_hv,
    Pos_Controller_P.Saturation_UpperSat_d);
}

/* Model initialize function */
void Pos_Controller_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Pos_Controller_M, (NULL));

  /* external inputs */
  (void) memset((void *)&Pos_Controller_U, 0,
                sizeof(ExternalInputs_Pos_Controller));

  /* external outputs */
  (void) memset((void *)&Pos_Controller_Y, 0,
                sizeof(ExternalOutputs_Pos_Controller));
}

/* Model terminate function */
void Pos_Controller_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
