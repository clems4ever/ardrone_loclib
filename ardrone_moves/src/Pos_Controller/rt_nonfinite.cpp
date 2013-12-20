/*
 * File: rt_nonfinite.cpp
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

/*
 * Abstract:
 *      Real-Time Workshop function to intialize non-finites,
 *      (Inf, NaN and -Inf).
 */
#include "rt_nonfinite.h"
#include "rtGetNaN.h"
#include "rtGetInf.h"

extern "C" {
  real_T rtInf;
  real_T rtMinusInf;
  real_T rtNaN;
  real32_T rtInfF;
  real32_T rtMinusInfF;
  real32_T rtNaNF;

  /*
   * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
   * generated code. NaN is initialized as non-signaling. Assumes IEEE.
   */
  void rt_InitInfAndNaN(size_t realSize)
  {
    (void) (realSize);
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
  }

  /* Test if value is infinite */
  boolean_T rtIsInf(real_T value)
  {
    return ((value==rtInf || value==rtMinusInf) ? 1U : 0U);
  }

  /* Test if single-precision value is infinite */
  boolean_T rtIsInfF(real32_T value)
  {
    return(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
  }

  /* Test if value is not a number */
  boolean_T rtIsNaN(real_T value)
  {
    return((value!=value) ? 1U : 0U);
  }

  /* Test if single-precision value is not a number */
  boolean_T rtIsNaNF(real32_T value)
  {
    return((value!=value) ? 1U : 0U);
  }
}
/* end rt_nonfinite.c */
/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
