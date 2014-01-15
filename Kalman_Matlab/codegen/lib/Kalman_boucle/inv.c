/*
 * inv.c
 *
 * Code generation for function 'inv'
 *
 * C source code generated on: Fri Jan 10 15:18:56 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Kalman_boucle.h"
#include "inv.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void invNxN(const real_T x[64], real_T y[64])
{
  real_T A[64];
  int32_T i2;
  int8_T ipiv[8];
  int32_T j;
  int32_T jj;
  int32_T jp1j;
  int32_T pipk;
  int32_T ix;
  real_T smax;
  int32_T jA;
  real_T s;
  int32_T i;
  int8_T p[8];
  for (i2 = 0; i2 < 64; i2++) {
    y[i2] = 0.0;
    A[i2] = x[i2];
  }

  for (i2 = 0; i2 < 8; i2++) {
    ipiv[i2] = (int8_T)(1 + i2);
  }

  for (j = 0; j < 7; j++) {
    jj = j * 9;
    jp1j = jj + 2;
    pipk = 1;
    ix = jj;
    smax = fabs(A[jj]);
    for (jA = 2; jA <= 8 - j; jA++) {
      ix++;
      s = fabs(A[ix]);
      if (s > smax) {
        pipk = jA;
        smax = s;
      }
    }

    if (A[(jj + pipk) - 1] != 0.0) {
      if (pipk - 1 != 0) {
        ipiv[j] = (int8_T)(j + pipk);
        ix = j;
        pipk = (j + pipk) - 1;
        for (jA = 0; jA < 8; jA++) {
          smax = A[ix];
          A[ix] = A[pipk];
          A[pipk] = smax;
          ix += 8;
          pipk += 8;
        }
      }

      i2 = (jp1j - j) + 6;
      for (i = jp1j; i <= i2; i++) {
        A[i - 1] /= A[jj];
      }
    }

    jA = jj + 9;
    pipk = jj + 8;
    for (jj = 1; jj <= 7 - j; jj++) {
      smax = A[pipk];
      if (A[pipk] != 0.0) {
        ix = jp1j;
        i2 = (jA - j) + 7;
        for (i = jA; i + 1 <= i2; i++) {
          A[i] += A[ix - 1] * -smax;
          ix++;
        }
      }

      pipk += 8;
      jA += 8;
    }
  }

  for (i2 = 0; i2 < 8; i2++) {
    p[i2] = (int8_T)(1 + i2);
  }

  for (jA = 0; jA < 7; jA++) {
    if (ipiv[jA] > 1 + jA) {
      pipk = p[ipiv[jA] - 1];
      p[ipiv[jA] - 1] = p[jA];
      p[jA] = (int8_T)pipk;
    }
  }

  for (jA = 0; jA < 8; jA++) {
    y[jA + ((p[jA] - 1) << 3)] = 1.0;
    for (j = jA; j + 1 < 9; j++) {
      if (y[j + ((p[jA] - 1) << 3)] != 0.0) {
        for (i = j + 1; i + 1 < 9; i++) {
          y[i + ((p[jA] - 1) << 3)] -= y[j + ((p[jA] - 1) << 3)] * A[i + (j << 3)];
        }
      }
    }
  }

  for (j = 0; j < 8; j++) {
    pipk = j << 3;
    for (jA = 7; jA > -1; jA += -1) {
      jj = jA << 3;
      if (y[jA + pipk] != 0.0) {
        y[jA + pipk] /= A[jA + jj];
        for (i = 0; i + 1 <= jA; i++) {
          y[i + pipk] -= y[jA + pipk] * A[i + jj];
        }
      }
    }
  }
}

/* End of code generation (inv.c) */
