/*
 * Kalman_boucle.c
 *
 * Code generation for function 'Kalman_boucle'
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
void Kalman_boucle(const real_T R[64], const real_T Xprec[4], const real_T
                   Pprec[16], const real_T Zprec[8], real_T Xk[4], real_T Pk[16],
                   real_T Prediction[4])
{
  int32_T i;
  int8_T C[32];
  static const int8_T iv0[32] = { 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

  static const int8_T iv1[4] = { 1, 0, 0, 0 };

  static const int8_T iv2[4] = { 0, 1, 0, 0 };

  int32_T i0;
  static const int8_T A[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1 };

  real_T d0;
  int32_T i1;
  static const int8_T iv3[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
  };

  real_T b_C[32];
  real_T x[64];
  real_T y[64];
  real_T Kk[32];
  real_T b_Zprec[8];
  int8_T I[16];
  real_T b_I[16];
  real_T c_I[16];

  /* KALMAN_boucle Summary of this function goes here */
  /*    Detailed explanation goes here */
  /*  Boucle de filtre de Kalman */
  /* Initialisations */
  /* Temps d'échantillonnage */
  /* Process noise */
  /* 6 si on prend en compte l'accélération */
  for (i = 0; i < 4; i++) {
    Prediction[i] = 0.0;
  }

  /* 6 si on prend en compte l'accélération */
  /* 6 si on prend en compte l'accélération */
  /* 10 si on prend en compte l'accélération */
  /* 10 */
  /*  Matrice d'état */
  /* position, vitesse sur X */
  /* position, vitesse sur X  */
  /* vitesse sur X */
  /* vitesse sur Y */
  /*  Matrice des mesures */
  /* position X     GPS */
  /* position Y     GPS */
  /* position X     ODOM */
  /* position Y     ODOM */
  /* position X     TAG */
  /* position Y     TAG */
  /* vitesse X      VIMU */
  for (i = 0; i < 32; i++) {
    C[i] = iv0[i];
  }

  /* vitesse Y      VIMU */
  /* Maj de C en fonction de la présence où non des mesures /!\ */
  /* GPS */
  if ((Zprec[0] == 2.0E+6) || (Zprec[1] == 2.0E+6)) {
    for (i = 0; i < 4; i++) {
      C[i << 3] = 0;
      C[1 + (i << 3)] = 0;
    }
  } else {
    for (i = 0; i < 4; i++) {
      C[i << 3] = iv1[i];
      C[1 + (i << 3)] = iv2[i];
    }
  }

  /* ODOM */
  if ((Zprec[2] == 2.0E+6) || (Zprec[3] == 2.0E+6)) {
    for (i = 0; i < 4; i++) {
      C[2 + (i << 3)] = 0;
      C[3 + (i << 3)] = 0;
    }
  } else {
    for (i = 0; i < 4; i++) {
      C[2 + (i << 3)] = iv1[i];
      C[3 + (i << 3)] = iv2[i];
    }
  }

  /* TAG */
  if ((Zprec[4] == 2.0E+6) || (Zprec[5] == 2.0E+6)) {
    for (i = 0; i < 4; i++) {
      C[4 + (i << 3)] = 0;
      C[5 + (i << 3)] = 0;
    }
  } else {
    for (i = 0; i < 4; i++) {
      C[4 + (i << 3)] = iv1[i];
      C[5 + (i << 3)] = iv2[i];
    }
  }

  /* Prediction */
  for (i = 0; i < 4; i++) {
    Xk[i] = 0.0;
    for (i0 = 0; i0 < 4; i0++) {
      Xk[i] += (real_T)A[i + (i0 << 2)] * Xprec[i0];
    }
  }

  for (i = 0; i < 4; i++) {
    for (i0 = 0; i0 < 4; i0++) {
      d0 = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        d0 += (real_T)A[i + (i1 << 2)] * Pprec[i1 + (i0 << 2)];
      }

      Pk[i + (i0 << 2)] = d0 + (real_T)iv3[i + (i0 << 2)];
    }
  }

  /* Innovation */
  for (i = 0; i < 8; i++) {
    for (i0 = 0; i0 < 4; i0++) {
      b_C[i + (i0 << 3)] = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        b_C[i + (i0 << 3)] += (real_T)C[i + (i1 << 3)] * Pk[i1 + (i0 << 2)];
      }
    }
  }

  for (i = 0; i < 8; i++) {
    for (i0 = 0; i0 < 8; i0++) {
      d0 = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        d0 += b_C[i + (i1 << 3)] * (real_T)C[i0 + (i1 << 3)];
      }

      x[i + (i0 << 3)] = d0 + R[i + (i0 << 3)];
    }
  }

  invNxN(x, y);
  for (i = 0; i < 4; i++) {
    for (i0 = 0; i0 < 8; i0++) {
      b_C[i + (i0 << 2)] = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        b_C[i + (i0 << 2)] += Pk[i + (i1 << 2)] * (real_T)C[i0 + (i1 << 3)];
      }
    }

    for (i0 = 0; i0 < 8; i0++) {
      Kk[i + (i0 << 2)] = 0.0;
      for (i1 = 0; i1 < 8; i1++) {
        Kk[i + (i0 << 2)] += b_C[i + (i1 << 2)] * y[i1 + (i0 << 3)];
      }
    }
  }

  /* Mise a jour */
  for (i = 0; i < 8; i++) {
    d0 = 0.0;
    for (i0 = 0; i0 < 4; i0++) {
      d0 += (real_T)C[i + (i0 << 3)] * Xk[i0];
    }

    b_Zprec[i] = Zprec[i] - d0;
  }

  for (i = 0; i < 4; i++) {
    d0 = 0.0;
    for (i0 = 0; i0 < 8; i0++) {
      d0 += Kk[i + (i0 << 2)] * b_Zprec[i0];
    }

    Xk[i] += d0;
  }

  for (i = 0; i < 16; i++) {
    I[i] = 0;
  }

  for (i = 0; i < 4; i++) {
    I[i + (i << 2)] = 1;
  }

  for (i = 0; i < 4; i++) {
    for (i0 = 0; i0 < 4; i0++) {
      d0 = 0.0;
      for (i1 = 0; i1 < 8; i1++) {
        d0 += Kk[i + (i1 << 2)] * (real_T)C[i1 + (i0 << 3)];
      }

      b_I[i + (i0 << 2)] = (real_T)I[i + (i0 << 2)] - d0;
    }
  }

  for (i = 0; i < 4; i++) {
    for (i0 = 0; i0 < 4; i0++) {
      c_I[i + (i0 << 2)] = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        c_I[i + (i0 << 2)] += b_I[i + (i1 << 2)] * Pk[i1 + (i0 << 2)];
      }
    }
  }

  for (i = 0; i < 4; i++) {
    for (i0 = 0; i0 < 4; i0++) {
      Pk[i0 + (i << 2)] = c_I[i0 + (i << 2)];
    }
  }

  /* Incrementation */
  Prediction[0] = Xk[0];

  /* X */
  Prediction[1] = Xk[1];

  /* Y */
  Prediction[2] = Xk[2];

  /* VX */
  Prediction[3] = Xk[3];

  /* VY */
}

/* End of code generation (Kalman_boucle.c) */
