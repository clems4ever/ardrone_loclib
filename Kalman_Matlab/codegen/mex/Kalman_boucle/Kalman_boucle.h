/*
 * Kalman_boucle.h
 *
 * Code generation for function 'Kalman_boucle'
 *
 * C source code generated on: Tue Jan 07 09:14:11 2014
 *
 */

#ifndef __KALMAN_BOUCLE_H__
#define __KALMAN_BOUCLE_H__
/* Include files */
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blascompat32.h"
#include "rtwtypes.h"
#include "Kalman_boucle_types.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern void Kalman_boucle(const real_T NewMeasure[8], const real_T R[64], const real_T Xpre[4], const real_T Ppre[16], const real_T Zpre[8], real_T Xk[4], real_T Pk[16], real_T Zk[8], real_T Pred[4]);
#endif
/* End of code generation (Kalman_boucle.h) */
