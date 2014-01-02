/*
 * File: Pos_Controller.cpp
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

/* Block states (auto storage) */
D_Work_Pos_Controller Pos_Controller_DWork;

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
  real_T rtb_IntegralGain;
  real_T rtb_IntegralGain_m;
  real_T rtb_FilterCoefficient;
  real_T rtb_Saturation;
  real_T rtb_Sum_l;
  real_T rtb_FilterCoefficient_l;
  real_T rtb_Saturation_l;
  real_T rtb_Saturation_h;
  real_T rtb_FilterCoefficient_lu;
  real_T rtb_IntegralGain_d;
  real_T rtb_Sum_d;
  real_T rtb_IntegralGain_h;
  real_T rtb_FilterCoefficient_a;
  boolean_T rtb_NotEqual;
  real_T rtb_if_X_pos;
  real_T rtb_Sum_idx;
  real_T rtb_Sum_idx_0;
  real_T rtb_Sum_idx_1;

  /* Sum: '<S1>/Sum' incorporates:
   *  Inport: '<Root>/consigne'
   *  Inport: '<Root>/position'
   */
  rtb_Sum_idx = Pos_Controller_U.consigne[0] - Pos_Controller_U.position[0];
  rtb_Sum_idx_0 = Pos_Controller_U.consigne[1] - Pos_Controller_U.position[1];
  rtb_Sum_idx_1 = Pos_Controller_U.consigne[2] - Pos_Controller_U.position[2];

  /* Gain: '<S2>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S2>/Filter'
   *  Gain: '<S2>/Derivative Gain'
   *  Sum: '<S2>/SumD'
   */
  rtb_FilterCoefficient = (Pos_Controller_P.DerivativeGain_Gain * rtb_Sum_idx -
    Pos_Controller_DWork.Filter_DSTATE) *
    Pos_Controller_P.FilterCoefficient_Gain;

  /* Sum: '<S2>/Sum' incorporates:
   *  DiscreteIntegrator: '<S2>/Integrator'
   *  Gain: '<S2>/Proportional Gain'
   */
  rtb_IntegralGain = (Pos_Controller_P.ProportionalGain_Gain * rtb_Sum_idx +
                      Pos_Controller_DWork.Integrator_DSTATE) +
    rtb_FilterCoefficient;

  /* Saturate: '<S2>/Saturation' */
  rtb_Saturation = rt_SATURATE(rtb_IntegralGain,
    Pos_Controller_P.Saturation_LowerSat, Pos_Controller_P.Saturation_UpperSat);

  /* Gain: '<S3>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S3>/Filter'
   *  Gain: '<S3>/Derivative Gain'
   *  Sum: '<S3>/SumD'
   */
  rtb_FilterCoefficient_l = (Pos_Controller_P.DerivativeGain_Gain_h *
    rtb_Sum_idx_0 - Pos_Controller_DWork.Filter_DSTATE_p) *
    Pos_Controller_P.FilterCoefficient_Gain_h;

  /* Sum: '<S3>/Sum' incorporates:
   *  DiscreteIntegrator: '<S3>/Integrator'
   *  Gain: '<S3>/Proportional Gain'
   */
  rtb_IntegralGain_m = (Pos_Controller_P.ProportionalGain_Gain_j * rtb_Sum_idx_0
                        + Pos_Controller_DWork.Integrator_DSTATE_f) +
    rtb_FilterCoefficient_l;

  /* Saturate: '<S3>/Saturation' */
  rtb_Saturation_l = rt_SATURATE(rtb_IntegralGain_m,
    Pos_Controller_P.Saturation_LowerSat_h,
    Pos_Controller_P.Saturation_UpperSat_h);

  /* Embedded MATLAB: '<S1>/reference change' */
  /* Embedded MATLAB Function 'Pos_Controller/reference change': '<S6>:1' */
  /* #codegen */
  /* '<S6>:1:4' */
  /* phi en radians, angle entre X et X1 */
  /* i.e. positif si rotation de X(nouveau rep) vers X1(ancien rep) dans le sens trigonométrique */
  /* =the output vector is a rotation of -phi of the input vector */
  /* '<S6>:1:4' */

  /* Gain: '<S5>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S5>/Filter'
   *  Gain: '<S5>/Derivative Gain'
   *  Sum: '<S5>/SumD'
   */
  rtb_FilterCoefficient_lu = (Pos_Controller_P.DerivativeGain_Gain_k *
    rtb_Sum_idx_1 - Pos_Controller_DWork.Filter_DSTATE_k) *
    Pos_Controller_P.FilterCoefficient_Gain_k;

  /* Sum: '<S5>/Sum' incorporates:
   *  DiscreteIntegrator: '<S5>/Integrator'
   *  Gain: '<S5>/Proportional Gain'
   */
  rtb_Sum_l = (Pos_Controller_P.ProportionalGain_Gain_c * rtb_Sum_idx_1 +
               Pos_Controller_DWork.Integrator_DSTATE_l) +
    rtb_FilterCoefficient_lu;

  /* Saturate: '<S5>/Saturation' */
  rtb_Saturation_h = rt_SATURATE(rtb_Sum_l,
    Pos_Controller_P.Saturation_LowerSat_e,
    Pos_Controller_P.Saturation_UpperSat_k);

  /* Outport: '<Root>/speed cmd' incorporates:
   *  Inport: '<Root>/yaw'
   */
  Pos_Controller_Y.speedcmd[0] = rtb_Saturation * cos(Pos_Controller_U.yaw) +
    rtb_Saturation_l * sin(Pos_Controller_U.yaw);
  Pos_Controller_Y.speedcmd[1] = (-rtb_Saturation) * sin(Pos_Controller_U.yaw) +
    rtb_Saturation_l * cos(Pos_Controller_U.yaw);
  Pos_Controller_Y.speedcmd[2] = rtb_Saturation_h;

  /* Switch: '<S1>/if_yaw_is_relative' incorporates:
   *  Constant: '<S1>/constant'
   *  Inport: '<Root>/yaw_is_relative'
   *  Product: '<S1>/Divide'
   *  Sum: '<S1>/Sum4'
   *  Trigonometry: '<S1>/Trigonometric Function'
   */
  if (Pos_Controller_U.yaw_is_relative) {
    /* Switch: '<S1>/if_X_pos' incorporates:
     *  Constant: '<S1>/add_if_x_neg'
     *  Constant: '<S1>/add_if_x_pos'
     */
    if (rtb_Saturation >= Pos_Controller_P.if_X_pos_Threshold) {
      rtb_if_X_pos = Pos_Controller_P.add_if_x_pos_Value;
    } else {
      rtb_if_X_pos = Pos_Controller_P.add_if_x_neg_Value;
    }

    rtb_IntegralGain_d = atan(rtb_Saturation_l / rtb_Saturation) + rtb_if_X_pos;
  } else {
    rtb_IntegralGain_d = Pos_Controller_P.constant_Value;
  }

  /* Sum: '<S1>/Sum2' incorporates:
   *  Constant: '<S1>/pi'
   *  Gain: '<S1>/Gain'
   *  Inport: '<Root>/yaw'
   *  Inport: '<Root>/yaw_cons'
   *  Math: '<S1>/modulo'
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S1>/Sum3'
   *  Sum: '<S1>/Sum5'
   */
  rtb_IntegralGain_d = rt_mod(((Pos_Controller_U.yaw_cons - Pos_Controller_U.yaw)
    + rtb_IntegralGain_d) + Pos_Controller_P.pi_Value,
    Pos_Controller_P.Gain_Gain * Pos_Controller_P.pi_Value) -
    Pos_Controller_P.pi_Value;

  /* Gain: '<S4>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S4>/Filter'
   *  Gain: '<S4>/Derivative Gain'
   *  Sum: '<S4>/SumD'
   */
  rtb_FilterCoefficient_a = (Pos_Controller_P.DerivativeGain_Gain_hy *
    rtb_IntegralGain_d - Pos_Controller_DWork.Filter_DSTATE_ke) *
    Pos_Controller_P.FilterCoefficient_Gain_j;

  /* Sum: '<S4>/Sum' incorporates:
   *  DiscreteIntegrator: '<S4>/Integrator'
   *  Gain: '<S4>/Proportional Gain'
   */
  rtb_Sum_d = (Pos_Controller_P.ProportionalGain_Gain_f * rtb_IntegralGain_d +
               Pos_Controller_DWork.Integrator_DSTATE_lc) +
    rtb_FilterCoefficient_a;

  /* Saturate: '<S4>/Saturation' */
  rtb_IntegralGain_h = rt_SATURATE(rtb_Sum_d,
    Pos_Controller_P.Saturation_LowerSat_hv,
    Pos_Controller_P.Saturation_UpperSat_d);

  /* Outport: '<Root>/yaw cmd' */
  Pos_Controller_Y.yawcmd = rtb_IntegralGain_h;

  /* RelationalOperator: '<S7>/NotEqual' */
  rtb_NotEqual = (rtb_IntegralGain != rtb_Saturation);

  /* Signum: '<S7>/SignPreSat' */
  rtb_if_X_pos = rt_SIGNd(rtb_IntegralGain);

  /* Gain: '<S2>/Integral Gain' */
  rtb_IntegralGain = Pos_Controller_P.IntegralGain_Gain * rtb_Sum_idx;

  /* Switch: '<S2>/Switch' incorporates:
   *  Logic: '<S7>/AND'
   *  RelationalOperator: '<S7>/Equal'
   *  Signum: '<S7>/SignPreIntegrator'
   */
  if (rtb_NotEqual && (rtb_if_X_pos == rt_SIGNd(rtb_IntegralGain))) {
    rtb_IntegralGain = 0.0;
  }

  /* RelationalOperator: '<S8>/NotEqual' */
  rtb_NotEqual = (rtb_IntegralGain_m != rtb_Saturation_l);

  /* Signum: '<S8>/SignPreSat' */
  rtb_if_X_pos = rt_SIGNd(rtb_IntegralGain_m);

  /* Gain: '<S3>/Integral Gain' */
  rtb_IntegralGain_m = Pos_Controller_P.IntegralGain_Gain_n * rtb_Sum_idx_0;

  /* Switch: '<S3>/Switch' incorporates:
   *  Logic: '<S8>/AND'
   *  RelationalOperator: '<S8>/Equal'
   *  Signum: '<S8>/SignPreIntegrator'
   */
  if (rtb_NotEqual && (rtb_if_X_pos == rt_SIGNd(rtb_IntegralGain_m))) {
    rtb_IntegralGain_m = 0.0;
  }

  /* Gain: '<S4>/Integral Gain' */
  rtb_IntegralGain_d *= Pos_Controller_P.IntegralGain_Gain_m;

  /* Switch: '<S4>/Switch' incorporates:
   *  Logic: '<S9>/AND'
   *  RelationalOperator: '<S9>/Equal'
   *  RelationalOperator: '<S9>/NotEqual'
   *  Signum: '<S9>/SignPreIntegrator'
   *  Signum: '<S9>/SignPreSat'
   */
  if ((rtb_Sum_d != rtb_IntegralGain_h) && (rt_SIGNd(rtb_Sum_d) == rt_SIGNd
       (rtb_IntegralGain_d))) {
    rtb_IntegralGain_d = 0.0;
  }

  /* Gain: '<S5>/Integral Gain' */
  rtb_IntegralGain_h = Pos_Controller_P.IntegralGain_Gain_a * rtb_Sum_idx_1;

  /* Switch: '<S5>/Switch' incorporates:
   *  Logic: '<S10>/AND'
   *  RelationalOperator: '<S10>/Equal'
   *  RelationalOperator: '<S10>/NotEqual'
   *  Signum: '<S10>/SignPreIntegrator'
   *  Signum: '<S10>/SignPreSat'
   */
  if ((rtb_Sum_l != rtb_Saturation_h) && (rt_SIGNd(rtb_Sum_l) == rt_SIGNd
       (rtb_IntegralGain_h))) {
    rtb_IntegralGain_h = 0.0;
  }

  /* Update for DiscreteIntegrator: '<S2>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE = Pos_Controller_P.Integrator_gainval *
    rtb_IntegralGain + Pos_Controller_DWork.Integrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S2>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE = Pos_Controller_P.Filter_gainval *
    rtb_FilterCoefficient + Pos_Controller_DWork.Filter_DSTATE;

  /* Update for DiscreteIntegrator: '<S3>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE_f =
    Pos_Controller_P.Integrator_gainval_n * rtb_IntegralGain_m +
    Pos_Controller_DWork.Integrator_DSTATE_f;

  /* Update for DiscreteIntegrator: '<S3>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE_p = Pos_Controller_P.Filter_gainval_i *
    rtb_FilterCoefficient_l + Pos_Controller_DWork.Filter_DSTATE_p;

  /* Update for DiscreteIntegrator: '<S5>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE_l =
    Pos_Controller_P.Integrator_gainval_h * rtb_IntegralGain_h +
    Pos_Controller_DWork.Integrator_DSTATE_l;

  /* Update for DiscreteIntegrator: '<S5>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE_k = Pos_Controller_P.Filter_gainval_iy *
    rtb_FilterCoefficient_lu + Pos_Controller_DWork.Filter_DSTATE_k;

  /* Update for DiscreteIntegrator: '<S4>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE_lc =
    Pos_Controller_P.Integrator_gainval_m * rtb_IntegralGain_d +
    Pos_Controller_DWork.Integrator_DSTATE_lc;

  /* Update for DiscreteIntegrator: '<S4>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE_ke = Pos_Controller_P.Filter_gainval_ig *
    rtb_FilterCoefficient_a + Pos_Controller_DWork.Filter_DSTATE_ke;
}

/* Model initialize function */
void Pos_Controller_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Pos_Controller_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&Pos_Controller_DWork, 0,
                sizeof(D_Work_Pos_Controller));

  /* external inputs */
  (void) memset((void *)&Pos_Controller_U, 0,
                sizeof(ExternalInputs_Pos_Controller));

  /* external outputs */
  (void) memset((void *)&Pos_Controller_Y, 0,
                sizeof(ExternalOutputs_Pos_Controller));

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE = Pos_Controller_P.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE = Pos_Controller_P.Filter_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S3>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE_f = Pos_Controller_P.Integrator_IC_f;

  /* InitializeConditions for DiscreteIntegrator: '<S3>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE_p = Pos_Controller_P.Filter_IC_e;

  /* InitializeConditions for DiscreteIntegrator: '<S5>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE_l = Pos_Controller_P.Integrator_IC_k;

  /* InitializeConditions for DiscreteIntegrator: '<S5>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE_k = Pos_Controller_P.Filter_IC_c;

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE_lc = Pos_Controller_P.Integrator_IC_o;

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE_ke = Pos_Controller_P.Filter_IC_g;
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
