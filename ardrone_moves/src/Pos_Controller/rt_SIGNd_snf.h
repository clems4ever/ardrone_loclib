/*
 * File: rt_SIGNd_snf.h
 *
 * Real-Time Workshop code generated for Simulink model Pos_Controller.
 *
 * Model version                        : 1.383
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Wed Jan  1 19:08:22 2014
 * TLC version                          : 7.4 (Jul 13 2009)
 * C/C++ source code generated on       : Wed Jan  1 19:08:22 2014
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86/Pentium
 * Code generation objective: Efficiency
 * Validation result: Passed (0), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_rt_SIGNd_snf_h_
#define RTW_HEADER_rt_SIGNd_snf_h_
#include "rt_nonfinite.h"
#define rt_SIGNd_snf(a)                ( ((a) < 0.0) ? -1.0 : ((a) > 0.0) ? 1.0 : ((a) == 0.0) ? 0.0 : (rtNaN) )
#endif                                 /* RTW_HEADER_rt_SIGNd_snf_h_ */

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
