/*
 * Kalman_boucle.c
 *
 * Code generation for function 'Kalman_boucle'
 *
 * C source code generated on: Thu Jan 16 18:41:52 2014
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
  int32_T i0;
  static const int8_T A[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1 };

  real_T d0;
  int32_T i1;
  static const int8_T iv0[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
  };

  real_T b_A[32];
  static const int8_T c_A[32] = { 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

  real_T x[64];
  static const int8_T B[32] = { 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

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
    /* vitesse Y      VIMU */
    /*  /!\ ne fonctionne pas lorsque l'on génére le code matlab en C */
    /*      %Maj de C en fonction de la présence où non des mesures /!\ */
    /*       %GPS */
    /*       if ( Zprec(1) > 2000000 || Zprec(2) > 2000000 ) */
    /*          C(1,:) = [0 0 0 0]; */
    /*          C(2,:) = [0 0 0 0];      */
    /*       else */
    /*           C(1,:) = [1 0 0 0]; */
    /*           C(2,:) = [0 1 0 0]; */
    /*       end */
    /*        */
    /*       %ODOM */
    /*       if ( Zprec(3) > 2000000 || Zprec(4) > 2000000 ) */
    /*          C(3,:) = [0 0 0 0]; */
    /*          C(4,:) = [0 0 0 0];      */
    /*       else */
    /*           C(3,:) = [1 0 0 0]; */
    /*           C(4,:) = [0 1 0 0]; */
    /*       end */
    /*        */
    /*       %TAG */
    /*       if ( Zprec(5) > 2000000 || Zprec(6) > 2000000 ) */
    /*          C(5,:) = [0 0 0 0]; */
    /*          C(6,:) = [0 0 0 0];       */
    /*       else */
    /*           C(5,:) = [1 0 0 0]; */
    /*           C(6,:) = [0 1 0 0]; */
    /*       end    */
    /*        */
    /*       %IMU */
    /*       if ( Zprec(7) > 2000000 || Zprec(8) > 2000000 ) */
    /*          C(7,:) = [0 0 0 0]; */
    /*          C(8,:) = [0 0 0 0];       */
    /*       else */
    /*           C(7,:) = [0 0 1 0]; */
    /*           C(8,:) = [0 0 0 1]; */
    /*       end    */
    /* Prediction */
    Xk[i] = 0.0;
    for (i0 = 0; i0 < 4; i0++) {
      Xk[i] += (real_T)A[i + (i0 << 2)] * Xprec[i0];
    }
  }

  for (i0 = 0; i0 < 4; i0++) {
    for (i = 0; i < 4; i++) {
      d0 = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        d0 += (real_T)A[i0 + (i1 << 2)] * Pprec[i1 + (i << 2)];
      }

      Pk[i0 + (i << 2)] = d0 + (real_T)iv0[i0 + (i << 2)];
    }
  }

  /* Innovation */
  for (i0 = 0; i0 < 8; i0++) {
    for (i = 0; i < 4; i++) {
      b_A[i0 + (i << 3)] = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        b_A[i0 + (i << 3)] += (real_T)c_A[i0 + (i1 << 3)] * Pk[i1 + (i << 2)];
      }
    }
  }

  for (i0 = 0; i0 < 8; i0++) {
    for (i = 0; i < 8; i++) {
      d0 = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        d0 += b_A[i0 + (i1 << 3)] * (real_T)B[i1 + (i << 2)];
      }

      x[i0 + (i << 3)] = d0 + R[i0 + (i << 3)];
    }
  }

  invNxN(x, y);
  for (i0 = 0; i0 < 4; i0++) {
    for (i = 0; i < 8; i++) {
      b_A[i0 + (i << 2)] = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        b_A[i0 + (i << 2)] += Pk[i0 + (i1 << 2)] * (real_T)B[i1 + (i << 2)];
      }
    }

    for (i = 0; i < 8; i++) {
      Kk[i0 + (i << 2)] = 0.0;
      for (i1 = 0; i1 < 8; i1++) {
        Kk[i0 + (i << 2)] += b_A[i0 + (i1 << 2)] * y[i1 + (i << 3)];
      }
    }
  }

  /* Mise a jour */
  for (i0 = 0; i0 < 8; i0++) {
    d0 = 0.0;
    for (i = 0; i < 4; i++) {
      d0 += (real_T)c_A[i0 + (i << 3)] * Xk[i];
    }

    b_Zprec[i0] = Zprec[i0] - d0;
  }

  for (i0 = 0; i0 < 4; i0++) {
    d0 = 0.0;
    for (i = 0; i < 8; i++) {
      d0 += Kk[i0 + (i << 2)] * b_Zprec[i];
    }

    Xk[i0] += d0;
  }

  for (i0 = 0; i0 < 16; i0++) {
    I[i0] = 0;
  }

  for (i = 0; i < 4; i++) {
    I[i + (i << 2)] = 1;
  }

  for (i0 = 0; i0 < 4; i0++) {
    for (i = 0; i < 4; i++) {
      d0 = 0.0;
      for (i1 = 0; i1 < 8; i1++) {
        d0 += Kk[i0 + (i1 << 2)] * (real_T)c_A[i1 + (i << 3)];
      }

      b_I[i0 + (i << 2)] = (real_T)I[i0 + (i << 2)] - d0;
    }
  }

  for (i0 = 0; i0 < 4; i0++) {
    for (i = 0; i < 4; i++) {
      c_I[i0 + (i << 2)] = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        c_I[i0 + (i << 2)] += b_I[i0 + (i1 << 2)] * Pk[i1 + (i << 2)];
      }
    }
  }

  for (i0 = 0; i0 < 4; i0++) {
    for (i = 0; i < 4; i++) {
      Pk[i + (i0 << 2)] = c_I[i + (i0 << 2)];
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
