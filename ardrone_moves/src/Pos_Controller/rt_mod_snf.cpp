/*
 * File: rt_mod_snf.cpp
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

#include "rt_mod_snf.h"
#include "rt_nonfinite.h"
#include <float.h>
#include <math.h>

extern "C" {
  /*
   * Calls double-precision version of MOD, with guard against domain error
   * and guards against non-finites
   */
  real_T rt_mod_snf(const real_T xr, const real_T yr)
  {
    real_T zr, yrf, tr, trf, wr;
    if (yr == 0.0) {
      zr = xr;
    } else if (rtIsInf(xr) || rtIsInf(yr) || rtIsNaN(xr) || rtIsNaN(yr)) {
      zr = (rtNaN);
    } else {
      yrf = floor(yr);
      tr = xr/yr;
      if (yr == yrf) {
        /* Integer denominator.  Use conventional formula.*/
        trf = floor(tr);
        zr = xr - trf*yr;
      } else {
        /* Noninteger denominator. Check for nearly integer quotient.*/
        {
          if (fabs(tr) < 4.5035996273704960E+15) {
            wr = ((tr < 0.0) ? -floor((fabs(tr) + 0.5)) : floor((fabs(tr) + 0.5)));
          } else {
            wr = tr;
          }
        }

        if (fabs(tr - wr) <= ((DBL_EPSILON)*fabs(tr))) {
          zr = 0.0;
        } else {
          trf = floor(tr);
          zr = (tr - trf)*yr;
        }
      }
    }

    return zr;
  }                                    /* end rt_mod_snf */
}
/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
