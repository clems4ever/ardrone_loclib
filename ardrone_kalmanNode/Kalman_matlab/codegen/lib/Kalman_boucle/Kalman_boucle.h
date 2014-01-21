/*
 * Kalman_boucle.h
 *
 * Code generation for function 'Kalman_boucle'
 *
 * C source code generated on: Tue Jan 21 20:56:11 2014
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
extern void Kalman_boucle(const real_T Cmesure[16], const real_T R[64], const real_T Xprec1[2], const real_T Pprec1[4], const real_T Zprec1[8], real_T Xk[2], real_T Pk[4], real_T Prediction[2]);
#endif
/* End of code generation (Kalman_boucle.h) */
