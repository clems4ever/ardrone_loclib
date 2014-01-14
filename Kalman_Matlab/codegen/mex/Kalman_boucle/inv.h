/*
 * inv.h
 *
 * Code generation for function 'inv'
 *
 * C source code generated on: Tue Jan 07 09:14:11 2014
 *
 */

#ifndef __INV_H__
#define __INV_H__
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
extern void invNxN(const real_T x[64], real_T y[64]);
#endif
/* End of code generation (inv.h) */
