/*
 * Kalman_boucle_mexutil.c
 *
 * Code generation for function 'Kalman_boucle_mexutil'
 *
 * C source code generated on: Tue Jan 07 09:14:10 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Kalman_boucle.h"
#include "Kalman_boucle_mexutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
const mxArray *message(const mxArray *b, const mxArray *c, emlrtMCInfo *location)
{
  const mxArray *pArrays[2];
  const mxArray *m8;
  pArrays[0] = b;
  pArrays[1] = c;
  return emlrtCallMATLAB(1, &m8, 2, pArrays, "message", TRUE, location);
}

/* End of code generation (Kalman_boucle_mexutil.c) */
