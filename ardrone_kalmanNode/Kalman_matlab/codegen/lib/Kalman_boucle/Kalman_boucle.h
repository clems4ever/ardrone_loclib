/*
 * Kalman_boucle.h
 *
 * Code generation for function 'Kalman_boucle'
 *
 * C source code generated on: Thu Jan 16 18:41:52 2014
 *
 */

#ifndef __KALMAN_BOUCLE_H__
#define __KALMAN_BOUCLE_H__
/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include "rtwtypes.h"
#include "Kalman_boucle_types.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern void Kalman_boucle(const real_T R[64], const real_T Xprec[4], const real_T Pprec[16], const real_T Zprec[8], real_T Xk[4], real_T Pk[16], real_T Prediction[4]);
#endif
/* End of code generation (Kalman_boucle.h) */
