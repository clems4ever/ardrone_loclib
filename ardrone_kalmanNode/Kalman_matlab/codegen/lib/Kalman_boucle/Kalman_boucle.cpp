/*
 * Kalman_boucle.c
 *
 * Code generation for function 'Kalman_boucle'
 *
 * C source code generated on: Tue Jan 21 20:56:11 2014
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
void Kalman_boucle(const real_T Cmesure[16], const real_T R[64], const real_T
                   Xprec1[2], const real_T Pprec1[4], const real_T Zprec1[8],
                   real_T Xk[2], real_T Pk[4], real_T Prediction[2])
{
  int32_T i;
  int32_T i0;
  static const int8_T A[4] = { 1, 0, 0, 1 };

  real_T d0;
  int32_T i1;
  real_T b_Cmesure[16];
  real_T x[64];
  real_T y[64];
  real_T Kk[16];
  real_T b_Zprec1[8];
  int8_T I[4];
  real_T b_I[4];
  real_T c_I[4];

  /* KALMAN_boucle Summary of this function goes here */
  /*    Detailed explanation goes here */
  /*  Boucle de filtre de Kalman */
  /* Initialisations */
  /* Temps d'échantillonnage */
  /* Process noise */
  /* 6 si on prend en compte l'accélération */
  for (i = 0; i < 2; i++) {
    Prediction[i] = 0.0;

    /* 6 si on prend en compte l'accélération */
    /* 6 si on prend en compte l'accélération */
    /* 10 si on prend en compte l'accélération */
    /* 10 */
    /*  Matrice d'état */
    /* position, vitesse sur X */
    /* position, vitesse sur Y  */
    /*  Matrice des mesures */
    /*      C=[ 1 0      %position X     GPS */
    /*          0 1      %position Y     GPS */
    /*          1 0      %position X     ODOM */
    /*          0 1      %position Y     ODOM */
    /*          1 0      %position X     TAG */
    /*          0 1      %position Y     TAG */
    /*          1 0      %position X     XTUM */
    /*          0 1];    %position Y     YTUM */
    /* Prediction */
    Xk[i] = 0.0;
    for (i0 = 0; i0 < 2; i0++) {
      Xk[i] += (real_T)A[i + (i0 << 1)] * Xprec1[i0];
    }
  }

  for (i0 = 0; i0 < 2; i0++) {
    for (i = 0; i < 2; i++) {
      d0 = 0.0;
      for (i1 = 0; i1 < 2; i1++) {
        d0 += (real_T)A[i0 + (i1 << 1)] * Pprec1[i1 + (i << 1)];
      }

      Pk[i0 + (i << 1)] = d0 + (real_T)A[i0 + (i << 1)];
    }
  }

  /* Innovation */
  for (i0 = 0; i0 < 8; i0++) {
    for (i = 0; i < 2; i++) {
      b_Cmesure[i0 + (i << 3)] = 0.0;
      for (i1 = 0; i1 < 2; i1++) {
        b_Cmesure[i0 + (i << 3)] += Cmesure[i0 + (i1 << 3)] * Pk[i1 + (i << 1)];
      }
    }
  }

  for (i0 = 0; i0 < 8; i0++) {
    for (i = 0; i < 8; i++) {
      d0 = 0.0;
      for (i1 = 0; i1 < 2; i1++) {
        d0 += b_Cmesure[i0 + (i1 << 3)] * Cmesure[i + (i1 << 3)];
      }

      x[i0 + (i << 3)] = d0 + R[i0 + (i << 3)];
    }
  }

  invNxN(x, y);
  for (i0 = 0; i0 < 2; i0++) {
    for (i = 0; i < 8; i++) {
      b_Cmesure[i0 + (i << 1)] = 0.0;
      for (i1 = 0; i1 < 2; i1++) {
        b_Cmesure[i0 + (i << 1)] += Pk[i0 + (i1 << 1)] * Cmesure[i + (i1 << 3)];
      }
    }

    for (i = 0; i < 8; i++) {
      Kk[i0 + (i << 1)] = 0.0;
      for (i1 = 0; i1 < 8; i1++) {
        Kk[i0 + (i << 1)] += b_Cmesure[i0 + (i1 << 1)] * y[i1 + (i << 3)];
      }
    }
  }

  /* Mise a jour */
  for (i0 = 0; i0 < 8; i0++) {
    d0 = 0.0;
    for (i = 0; i < 2; i++) {
      d0 += Cmesure[i0 + (i << 3)] * Xk[i];
    }

    b_Zprec1[i0] = Zprec1[i0] - d0;
  }

  for (i0 = 0; i0 < 2; i0++) {
    d0 = 0.0;
    for (i = 0; i < 8; i++) {
      d0 += Kk[i0 + (i << 1)] * b_Zprec1[i];
    }

    Xk[i0] += d0;
  }

  for (i0 = 0; i0 < 4; i0++) {
    I[i0] = 0;
  }

  for (i = 0; i < 2; i++) {
    I[i + (i << 1)] = 1;
  }

  for (i0 = 0; i0 < 2; i0++) {
    for (i = 0; i < 2; i++) {
      d0 = 0.0;
      for (i1 = 0; i1 < 8; i1++) {
        d0 += Kk[i0 + (i1 << 1)] * Cmesure[i1 + (i << 3)];
      }

      b_I[i0 + (i << 1)] = (real_T)I[i0 + (i << 1)] - d0;
    }
  }

  for (i0 = 0; i0 < 2; i0++) {
    for (i = 0; i < 2; i++) {
      c_I[i0 + (i << 1)] = 0.0;
      for (i1 = 0; i1 < 2; i1++) {
        c_I[i0 + (i << 1)] += b_I[i0 + (i1 << 1)] * Pk[i1 + (i << 1)];
      }
    }
  }

  for (i0 = 0; i0 < 2; i0++) {
    for (i = 0; i < 2; i++) {
      Pk[i + (i0 << 1)] = c_I[i + (i0 << 1)];
    }
  }

  /* Incrementation */
  Prediction[0] = Xk[0];

  /* X */
  Prediction[1] = Xk[1];

  /* Y */
}

/* End of code generation (Kalman_boucle.c) */
