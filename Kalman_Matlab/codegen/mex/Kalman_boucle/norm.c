/*
 * norm.c
 *
 * Code generation for function 'norm'
 *
 * C source code generated on: Tue Jan 07 09:14:11 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Kalman_boucle.h"
#include "norm.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static emlrtRSInfo ob_emlrtRSI = { 44, "norm",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/norm.m" };

/* Function Declarations */

/* Function Definitions */
real_T norm(const real_T x[64])
{
  real_T y;
  int32_T j;
  boolean_T exitg1;
  real_T s;
  int32_T i;
  EMLRTPUSHRTSTACK(&ob_emlrtRSI);
  y = 0.0;
  j = 0;
  exitg1 = FALSE;
  while ((exitg1 == 0U) && (j < 8)) {
    s = 0.0;
    for (i = 0; i < 8; i++) {
      s += muDoubleScalarAbs(x[i + (j << 3)]);
    }

    if (muDoubleScalarIsNaN(s)) {
      y = rtNaN;
      exitg1 = TRUE;
    } else {
      if (s > y) {
        y = s;
      }

      j++;
    }
  }

  EMLRTPOPRTSTACK(&ob_emlrtRSI);
  return y;
}

/* End of code generation (norm.c) */
