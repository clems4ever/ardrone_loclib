/*
 * Kalman_boucle_terminate.c
 *
 * Code generation for function 'Kalman_boucle_terminate'
 *
 * C source code generated on: Tue Jan 07 09:14:10 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Kalman_boucle.h"
#include "Kalman_boucle_terminate.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void Kalman_boucle_atexit(void)
{
  emlrtEnterRtStack(&emlrtContextGlobal);
  emlrtLeaveRtStack(&emlrtContextGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void Kalman_boucle_terminate(void)
{
  emlrtLeaveRtStack(&emlrtContextGlobal);
}

/* End of code generation (Kalman_boucle_terminate.c) */
