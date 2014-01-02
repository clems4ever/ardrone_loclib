/*
 * File: rt_mod.cpp
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

#include "rt_mod.h"
#include <float.h>
#include <math.h>

extern "C" {
  /*
   * Calls double-precision version of MOD directly, with no guards against
   * domain error or non-finites
   */
  real_T rt_mod(const real_T xr, const real_T yr)
  {
    real_T zr, yrf, tr, trf, wr;
    if (yr == 0.0) {
      zr = xr;
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
  }                                    /* end rt_mod */
}
/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
