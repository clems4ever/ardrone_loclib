/*
 * File: Pos_Controller.cpp
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
  real_T rtb_Sum_d;
  real_T rtb_IntegralGain_d;
  real_T rtb_Saturation_c;
  real_T rtb_FilterCoefficient;
  real_T rtb_Sum_l;
  real_T rtb_Saturation;
  real_T rtb_Saturation_l;
  real_T rtb_IntegralGain;
  real_T rtb_FilterCoefficient_l;
  boolean_T rtb_NotEqual_p;
  real_T rtb_Sum_idx;

  /* Sum: '<S1>/Sum2' incorporates:
   *  Constant: '<S1>/pi'
   *  Gain: '<S1>/Gain'
   *  Inport: '<Root>/yaw'
   *  Inport: '<Root>/yaw_cons'
   *  Math: '<S1>/modulo'
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S1>/Sum3'
   */
  rtb_IntegralGain_d = rt_mod_snf((Pos_Controller_U.yaw_cons -
    Pos_Controller_U.yaw) + Pos_Controller_P.pi_Value,
    Pos_Controller_P.Gain_Gain * Pos_Controller_P.pi_Value) -
    Pos_Controller_P.pi_Value;

  /* Gain: '<S4>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S4>/Filter'
   *  Gain: '<S4>/Derivative Gain'
   *  Sum: '<S4>/SumD'
   */
  rtb_FilterCoefficient = (Pos_Controller_P.DerivativeGain_Gain *
    rtb_IntegralGain_d - Pos_Controller_DWork.Filter_DSTATE) *
    Pos_Controller_P.FilterCoefficient_Gain;

  /* Sum: '<S4>/Sum' incorporates:
   *  DiscreteIntegrator: '<S4>/Integrator'
   *  Gain: '<S4>/Proportional Gain'
   */
  rtb_Sum_d = (Pos_Controller_P.ProportionalGain_Gain * rtb_IntegralGain_d +
               Pos_Controller_DWork.Integrator_DSTATE) + rtb_FilterCoefficient;

  /* Saturate: '<S4>/Saturation' */
  rtb_Saturation_c = rt_SATURATE(rtb_Sum_d, Pos_Controller_P.Saturation_LowerSat,
    Pos_Controller_P.Saturation_UpperSat);

  /* Outport: '<Root>/yaw cmd' */
  Pos_Controller_Y.yawcmd = rtb_Saturation_c;

  /* Sum: '<S1>/Sum' incorporates:
   *  Inport: '<Root>/consigne'
   *  Inport: '<Root>/position'
   */
  rtb_Sum_idx = Pos_Controller_U.consigne[2] - Pos_Controller_U.position[2];

  /* Gain: '<S2>/Proportional Gain' incorporates:
   *  Inport: '<Root>/consigne'
   *  Inport: '<Root>/position'
   */
  rtb_Sum_l = (Pos_Controller_U.consigne[0] - Pos_Controller_U.position[0]) *
    Pos_Controller_P.ProportionalGain_Gain_l;

  /* Saturate: '<S2>/Saturation' */
  rtb_Saturation = rt_SATURATE(rtb_Sum_l, Pos_Controller_P.Saturation_LowerSat_f,
    Pos_Controller_P.Saturation_UpperSat_j);

  /* Gain: '<S3>/Proportional Gain' incorporates:
   *  Inport: '<Root>/consigne'
   *  Inport: '<Root>/position'
   */
  rtb_Sum_l = (Pos_Controller_U.consigne[1] - Pos_Controller_U.position[1]) *
    Pos_Controller_P.ProportionalGain_Gain_j;

  /* Saturate: '<S3>/Saturation' */
  rtb_Saturation_l = rt_SATURATE(rtb_Sum_l,
    Pos_Controller_P.Saturation_LowerSat_h,
    Pos_Controller_P.Saturation_UpperSat_h);

  /* Embedded MATLAB: '<S1>/reference change' */
  /* Embedded MATLAB Function 'Pos_Controller/reference change': '<S6>:1' */
  /* #codegen */
  /* '<S6>:1:4' */
  /* phi en radians, angle entre X et X1 */
  /* i.e. positif si rotation de X(nouveau rep) vers X1(ancien rep) dans le sens trigonométrique */
  /* '<S6>:1:4' */

  /* Gain: '<S5>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S5>/Filter'
   *  Gain: '<S5>/Derivative Gain'
   *  Sum: '<S5>/SumD'
   */
  rtb_FilterCoefficient_l = (Pos_Controller_P.DerivativeGain_Gain_k *
    rtb_Sum_idx - Pos_Controller_DWork.Filter_DSTATE_k) *
    Pos_Controller_P.FilterCoefficient_Gain_k;

  /* Sum: '<S5>/Sum' incorporates:
   *  DiscreteIntegrator: '<S5>/Integrator'
   *  Gain: '<S5>/Proportional Gain'
   */
  rtb_Sum_l = (Pos_Controller_P.ProportionalGain_Gain_c * rtb_Sum_idx +
               Pos_Controller_DWork.Integrator_DSTATE_l) +
    rtb_FilterCoefficient_l;

  /* Saturate: '<S5>/Saturation' */
  rtb_IntegralGain = rt_SATURATE(rtb_Sum_l,
    Pos_Controller_P.Saturation_LowerSat_e,
    Pos_Controller_P.Saturation_UpperSat_k);

	/* added for debug output (Jules)*/
	Pos_Controller_Y.absolute_speedcmd[0]=rtb_Saturation;
	Pos_Controller_Y.absolute_speedcmd[1]=rtb_Saturation_l;
	Pos_Controller_Y.absolute_speedcmd[2]=rtb_IntegralGain;

  /* Outport: '<Root>/speed cmd' incorporates:
   *  Inport: '<Root>/yaw'
   *  Sum: '<S1>/Sum5'
   */

  Pos_Controller_Y.speedcmd[0] = rtb_Saturation * cos(Pos_Controller_U.yaw) +
    rtb_Saturation_l * sin(Pos_Controller_U.yaw);
  Pos_Controller_Y.speedcmd[1] = -rtb_Saturation * sin(Pos_Controller_U.yaw) +
    rtb_Saturation_l * cos(Pos_Controller_U.yaw);
  Pos_Controller_Y.speedcmd[2] = rtb_IntegralGain;

  /* Gain: '<S4>/Integral Gain' */
  rtb_IntegralGain_d *= Pos_Controller_P.IntegralGain_Gain;

  /* Switch: '<S4>/Switch' incorporates:
   *  Logic: '<S7>/AND'
   *  RelationalOperator: '<S7>/Equal'
   *  RelationalOperator: '<S7>/NotEqual'
   *  Signum: '<S7>/SignPreIntegrator'
   *  Signum: '<S7>/SignPreSat'
   */
  if ((rtb_Sum_d != rtb_Saturation_c) && (rt_SIGNd_snf(rtb_Sum_d) ==
       rt_SIGNd_snf(rtb_IntegralGain_d))) {
    rtb_IntegralGain_d = 0.0;
  }

  /* RelationalOperator: '<S8>/NotEqual' */
  rtb_NotEqual_p = (rtb_Sum_l != rtb_IntegralGain);

  /* Gain: '<S5>/Integral Gain' */
  rtb_IntegralGain = Pos_Controller_P.IntegralGain_Gain_a * rtb_Sum_idx;

  /* Switch: '<S5>/Switch' incorporates:
   *  Logic: '<S8>/AND'
   *  RelationalOperator: '<S8>/Equal'
   *  Signum: '<S8>/SignPreIntegrator'
   *  Signum: '<S8>/SignPreSat'
   */
  if (rtb_NotEqual_p && (rt_SIGNd_snf(rtb_Sum_l) == rt_SIGNd_snf
                         (rtb_IntegralGain))) {
    rtb_IntegralGain = 0.0;
  }

  /* Update for DiscreteIntegrator: '<S4>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE = Pos_Controller_P.Integrator_gainval *
    rtb_IntegralGain_d + Pos_Controller_DWork.Integrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S4>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE = Pos_Controller_P.Filter_gainval *
    rtb_FilterCoefficient + Pos_Controller_DWork.Filter_DSTATE;

  /* Update for DiscreteIntegrator: '<S5>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE_l =
    Pos_Controller_P.Integrator_gainval_h * rtb_IntegralGain +
    Pos_Controller_DWork.Integrator_DSTATE_l;

  /* Update for DiscreteIntegrator: '<S5>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE_k = Pos_Controller_P.Filter_gainval_i *
    rtb_FilterCoefficient_l + Pos_Controller_DWork.Filter_DSTATE_k;
}

/* Model initialize function */
void Pos_Controller_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

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

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE = Pos_Controller_P.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE = Pos_Controller_P.Filter_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S5>/Integrator' */
  Pos_Controller_DWork.Integrator_DSTATE_l = Pos_Controller_P.Integrator_IC_k;

  /* InitializeConditions for DiscreteIntegrator: '<S5>/Filter' */
  Pos_Controller_DWork.Filter_DSTATE_k = Pos_Controller_P.Filter_IC_c;
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
