/*
 * File: Pos_Controller.h
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

#ifndef RTW_HEADER_Pos_Controller_h_
#define RTW_HEADER_Pos_Controller_h_
#ifndef Pos_Controller_COMMON_INCLUDES_
# define Pos_Controller_COMMON_INCLUDES_
#include <float.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rt_SATURATE.h"
#include "rt_SIGNd.h"
#include "rt_mod.h"
#endif                                 /* Pos_Controller_COMMON_INCLUDES_ */

#include "Pos_Controller_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S2>/Integrator' */
  real_T Filter_DSTATE;                /* '<S2>/Filter' */
  real_T Integrator_DSTATE_f;          /* '<S3>/Integrator' */
  real_T Filter_DSTATE_p;              /* '<S3>/Filter' */
  real_T Integrator_DSTATE_l;          /* '<S5>/Integrator' */
  real_T Filter_DSTATE_k;              /* '<S5>/Filter' */
  real_T Integrator_DSTATE_lc;         /* '<S4>/Integrator' */
  real_T Filter_DSTATE_ke;             /* '<S4>/Filter' */
} D_Work_Pos_Controller;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T consigne[3];                  /* '<Root>/consigne' */
  real_T yaw_cons;                     /* '<Root>/yaw_cons' */
  boolean_T yaw_is_relative;           /* '<Root>/yaw_is_relative' */
  real_T position[3];                  /* '<Root>/position' */
  real_T yaw;                          /* '<Root>/yaw' */
} ExternalInputs_Pos_Controller;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T speedcmd[3];                  /* '<Root>/speed cmd' */
  real_T yawcmd;                       /* '<Root>/yaw cmd' */
} ExternalOutputs_Pos_Controller;

/* Parameters (auto storage) */
struct Parameters_Pos_Controller_ {
  real_T ProportionalGain_Gain;        /* Expression: P
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T Integrator_IC;                /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T DerivativeGain_Gain;          /* Expression: D
                                        * Referenced by: '<S2>/Derivative Gain'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S2>/Filter'
                                        */
  real_T Filter_IC;                    /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
  real_T FilterCoefficient_Gain;       /* Expression: N
                                        * Referenced by: '<S2>/Filter Coefficient'
                                        */
  real_T Saturation_UpperSat;          /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S2>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S2>/Saturation'
                                        */
  real_T ProportionalGain_Gain_j;      /* Expression: P
                                        * Referenced by: '<S3>/Proportional Gain'
                                        */
  real_T Integrator_gainval_n;         /* Computed Parameter: Integrator_gainval_n
                                        * Referenced by: '<S3>/Integrator'
                                        */
  real_T Integrator_IC_f;              /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S3>/Integrator'
                                        */
  real_T DerivativeGain_Gain_h;        /* Expression: D
                                        * Referenced by: '<S3>/Derivative Gain'
                                        */
  real_T Filter_gainval_i;             /* Computed Parameter: Filter_gainval_i
                                        * Referenced by: '<S3>/Filter'
                                        */
  real_T Filter_IC_e;                  /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S3>/Filter'
                                        */
  real_T FilterCoefficient_Gain_h;     /* Expression: N
                                        * Referenced by: '<S3>/Filter Coefficient'
                                        */
  real_T Saturation_UpperSat_h;        /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S3>/Saturation'
                                        */
  real_T Saturation_LowerSat_h;        /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S3>/Saturation'
                                        */
  real_T ProportionalGain_Gain_c;      /* Expression: P
                                        * Referenced by: '<S5>/Proportional Gain'
                                        */
  real_T Integrator_gainval_h;         /* Computed Parameter: Integrator_gainval_h
                                        * Referenced by: '<S5>/Integrator'
                                        */
  real_T Integrator_IC_k;              /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S5>/Integrator'
                                        */
  real_T DerivativeGain_Gain_k;        /* Expression: D
                                        * Referenced by: '<S5>/Derivative Gain'
                                        */
  real_T Filter_gainval_iy;            /* Computed Parameter: Filter_gainval_iy
                                        * Referenced by: '<S5>/Filter'
                                        */
  real_T Filter_IC_c;                  /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S5>/Filter'
                                        */
  real_T FilterCoefficient_Gain_k;     /* Expression: N
                                        * Referenced by: '<S5>/Filter Coefficient'
                                        */
  real_T Saturation_UpperSat_k;        /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S5>/Saturation'
                                        */
  real_T Saturation_LowerSat_e;        /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S5>/Saturation'
                                        */
  real_T pi_Value;                     /* Expression: pi
                                        * Referenced by: '<S1>/pi'
                                        */
  real_T Gain_Gain;                    /* Expression: 2
                                        * Referenced by: '<S1>/Gain'
                                        */
  real_T ProportionalGain_Gain_f;      /* Expression: P
                                        * Referenced by: '<S4>/Proportional Gain'
                                        */
  real_T Integrator_gainval_m;         /* Computed Parameter: Integrator_gainval_m
                                        * Referenced by: '<S4>/Integrator'
                                        */
  real_T Integrator_IC_o;              /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S4>/Integrator'
                                        */
  real_T DerivativeGain_Gain_hy;       /* Expression: D
                                        * Referenced by: '<S4>/Derivative Gain'
                                        */
  real_T Filter_gainval_ig;            /* Computed Parameter: Filter_gainval_ig
                                        * Referenced by: '<S4>/Filter'
                                        */
  real_T Filter_IC_g;                  /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S4>/Filter'
                                        */
  real_T FilterCoefficient_Gain_j;     /* Expression: N
                                        * Referenced by: '<S4>/Filter Coefficient'
                                        */
  real_T Saturation_UpperSat_d;        /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S4>/Saturation'
                                        */
  real_T Saturation_LowerSat_hv;       /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S4>/Saturation'
                                        */
  real_T IntegralGain_Gain;            /* Expression: I
                                        * Referenced by: '<S2>/Integral Gain'
                                        */
  real_T IntegralGain_Gain_n;          /* Expression: I
                                        * Referenced by: '<S3>/Integral Gain'
                                        */
  real_T IntegralGain_Gain_m;          /* Expression: I
                                        * Referenced by: '<S4>/Integral Gain'
                                        */
  real_T IntegralGain_Gain_a;          /* Expression: I
                                        * Referenced by: '<S5>/Integral Gain'
                                        */
  real_T constant_Value;               /* Expression: 0
                                        * Referenced by: '<S1>/constant'
                                        */
  real_T add_if_x_neg_Value;           /* Expression: pi
                                        * Referenced by: '<S1>/add_if_x_neg'
                                        */
  real_T add_if_x_pos_Value;           /* Expression: 0
                                        * Referenced by: '<S1>/add_if_x_pos'
                                        */
  real_T if_X_pos_Threshold;           /* Expression: 0
                                        * Referenced by: '<S1>/if_X_pos'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_Pos_Controller {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern Parameters_Pos_Controller Pos_Controller_P;

/* Block states (auto storage) */
extern D_Work_Pos_Controller Pos_Controller_DWork;

/* External inputs (root inport signals with auto storage) */
extern ExternalInputs_Pos_Controller Pos_Controller_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs_Pos_Controller Pos_Controller_Y;

/* Model entry point functions */
extern void Pos_Controller_initialize(void);
extern void Pos_Controller_step(void);
extern void Pos_Controller_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Pos_Controller *Pos_Controller_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('BF_Drone/Pos_Controller')    - opens subsystem BF_Drone/Pos_Controller
 * hilite_system('BF_Drone/Pos_Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : BF_Drone
 * '<S1>'   : BF_Drone/Pos_Controller
 * '<S2>'   : BF_Drone/Pos_Controller/PID x
 * '<S3>'   : BF_Drone/Pos_Controller/PID y
 * '<S4>'   : BF_Drone/Pos_Controller/PID yaw
 * '<S5>'   : BF_Drone/Pos_Controller/PID z
 * '<S6>'   : BF_Drone/Pos_Controller/reference change
 * '<S7>'   : BF_Drone/Pos_Controller/PID x/Clamping circuit
 * '<S8>'   : BF_Drone/Pos_Controller/PID y/Clamping circuit
 * '<S9>'   : BF_Drone/Pos_Controller/PID yaw/Clamping circuit
 * '<S10>'  : BF_Drone/Pos_Controller/PID z/Clamping circuit
 */
#endif                                 /* RTW_HEADER_Pos_Controller_h_ */

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
