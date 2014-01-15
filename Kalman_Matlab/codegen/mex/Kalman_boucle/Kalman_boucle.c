/*
 * Kalman_boucle.c
 *
 * Code generation for function 'Kalman_boucle'
 *
 * C source code generated on: Tue Jan 07 09:14:11 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Kalman_boucle.h"
#include "norm.h"
#include "inv.h"
#include "Kalman_boucle_mexutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = { 16, "Kalman_boucle",
  "U:/5 SEC/Projet_Roxanne/Kalman/Kalman_boucle.m" };

static emlrtRSInfo b_emlrtRSI = { 74, "Kalman_boucle",
  "U:/5 SEC/Projet_Roxanne/Kalman/Kalman_boucle.m" };

static emlrtRSInfo c_emlrtRSI = { 78, "Kalman_boucle",
  "U:/5 SEC/Projet_Roxanne/Kalman/Kalman_boucle.m" };

static emlrtRSInfo d_emlrtRSI = { 17, "eye",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/elmat/eye.m" };

static emlrtRSInfo e_emlrtRSI = { 17, "inv",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/inv.m" };

static emlrtRSInfo f_emlrtRSI = { 18, "inv",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/inv.m" };

static emlrtRSInfo kb_emlrtRSI = { 35, "inv",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/inv.m" };

static emlrtRSInfo lb_emlrtRSI = { 36, "inv",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/inv.m" };

static emlrtRSInfo mb_emlrtRSI = { 40, "inv",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/inv.m" };

static emlrtRSInfo nb_emlrtRSI = { 44, "inv",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/inv.m" };

static emlrtRSInfo pb_emlrtRSI = { 16, "eml_warning",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_warning.m" };

static emlrtRSInfo qb_emlrtRSI = { 29, "eml_flt2str",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_flt2str.m" };

static emlrtRSInfo rb_emlrtRSI = { 16, "eml_warning",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_warning.m" };

static emlrtMCInfo e_emlrtMCI = { 16, 21, "eml_warning",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_warning.m" };

static emlrtMCInfo f_emlrtMCI = { 16, 5, "eml_warning",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_warning.m" };

static emlrtMCInfo g_emlrtMCI = { 29, 23, "eml_flt2str",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_flt2str.m" };

static emlrtMCInfo h_emlrtMCI = { 29, 15, "eml_flt2str",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_flt2str.m" };

static emlrtMCInfo i_emlrtMCI = { 16, 21, "eml_warning",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_warning.m" };

static emlrtMCInfo j_emlrtMCI = { 16, 5, "eml_warning",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_warning.m" };

/* Function Declarations */
static void b_eml_warning(const char_T varargin_2[14]);
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, char_T y[14]);
static const mxArray *b_message(const mxArray *b, emlrtMCInfo *location);
static const mxArray *b_sprintf(const mxArray *b, const mxArray *c, const
  mxArray *d, emlrtMCInfo *location);
static const mxArray *c_sprintf(const mxArray *b, const mxArray *c, emlrtMCInfo *
  location);
static void eml_warning(void);
static void emlrt_marshallIn(const mxArray *d_sprintf, const char_T *identifier,
  char_T y[14]);
static void k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, char_T ret[14]);
static void warning(const mxArray *b, emlrtMCInfo *location);

/* Function Definitions */
static void b_eml_warning(const char_T varargin_2[14])
{
  const mxArray *y;
  static const int32_T iv10[2] = { 1, 33 };

  const mxArray *m4;
  static const char_T cv6[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i', 'o',
    'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  const mxArray *b_y;
  static const int32_T iv11[2] = { 1, 14 };

  EMLRTPUSHRTSTACK(&rb_emlrtRSI);
  y = NULL;
  m4 = mxCreateCharArray(2, iv10);
  emlrtInitCharArray(33, m4, cv6);
  emlrtAssign(&y, m4);
  b_y = NULL;
  m4 = mxCreateCharArray(2, iv11);
  emlrtInitCharArray(14, m4, varargin_2);
  emlrtAssign(&b_y, m4);
  warning(message(y, b_y, &i_emlrtMCI), &j_emlrtMCI);
  EMLRTPOPRTSTACK(&rb_emlrtRSI);
}

static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, char_T y[14])
{
  k_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *b_message(const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  const mxArray *m9;
  pArray = b;
  return emlrtCallMATLAB(1, &m9, 1, &pArray, "message", TRUE, location);
}

static const mxArray *b_sprintf(const mxArray *b, const mxArray *c, const
  mxArray *d, emlrtMCInfo *location)
{
  const mxArray *pArrays[3];
  const mxArray *m10;
  pArrays[0] = b;
  pArrays[1] = c;
  pArrays[2] = d;
  return emlrtCallMATLAB(1, &m10, 3, pArrays, "sprintf", TRUE, location);
}

static const mxArray *c_sprintf(const mxArray *b, const mxArray *c, emlrtMCInfo *
  location)
{
  const mxArray *pArrays[2];
  const mxArray *m11;
  pArrays[0] = b;
  pArrays[1] = c;
  return emlrtCallMATLAB(1, &m11, 2, pArrays, "sprintf", TRUE, location);
}

static void eml_warning(void)
{
  const mxArray *y;
  static const int32_T iv9[2] = { 1, 27 };

  const mxArray *m3;
  static const char_T cv5[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a', 't',
    'r', 'i', 'x' };

  EMLRTPUSHRTSTACK(&pb_emlrtRSI);
  y = NULL;
  m3 = mxCreateCharArray(2, iv9);
  emlrtInitCharArray(27, m3, cv5);
  emlrtAssign(&y, m3);
  warning(b_message(y, &e_emlrtMCI), &f_emlrtMCI);
  EMLRTPOPRTSTACK(&pb_emlrtRSI);
}

static void emlrt_marshallIn(const mxArray *d_sprintf, const char_T *identifier,
  char_T y[14])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  b_emlrt_marshallIn(emlrtAlias(d_sprintf), &thisId, y);
  emlrtDestroyArray(&d_sprintf);
}

static void k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, char_T ret[14])
{
  int32_T iv15[2];
  int32_T i3;
  for (i3 = 0; i3 < 2; i3++) {
    iv15[i3] = 1 + 13 * i3;
  }

  emlrtCheckBuiltInCtxR2011b(&emlrtContextGlobal, msgId, src, "char", FALSE, 2U,
    iv15);
  emlrtImportCharArray(src, ret, 14);
  emlrtDestroyArray(&src);
}

static void warning(const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLAB(0, NULL, 1, &pArray, "warning", TRUE, location);
}

void Kalman_boucle(const real_T NewMeasure[8], const real_T R[64], const real_T
                   Xpre[4], const real_T Ppre[16], const real_T Zpre[8], real_T
                   Xk[4], real_T Pk[16], real_T Zk[8], real_T Pred[4])
{
  int32_T i;
  int8_T C[32];
  static const int8_T iv0[32] = { 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

  static const int8_T iv1[4] = { 1, 0, 0, 0 };

  static const int8_T iv2[4] = { 0, 1, 0, 0 };

  int32_T i0;
  static const int8_T A[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1 };

  real_T n1x;
  int32_T i1;
  static const int8_T iv3[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
  };

  real_T b_C[32];
  real_T x[64];
  real_T y[64];
  real_T n1xinv;
  real_T rc;
  const mxArray *b_y;
  static const int32_T iv4[2] = { 1, 8 };

  const mxArray *m0;
  static const char_T cv0[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  char_T str[14];
  real_T Kk[32];
  real_T b_Zpre[8];
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
    Pred[i] = 0.0;
  }

  /* 6 si on prend en compte l'accélération */
  EMLRTPUSHRTSTACK(&emlrtRSI);
  EMLRTPUSHRTSTACK(&d_emlrtRSI);
  EMLRTPOPRTSTACK(&d_emlrtRSI);
  EMLRTPOPRTSTACK(&emlrtRSI);

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
  if ((Zpre[0] == 0.0) || (Zpre[1] == 0.0)) {
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
  if ((Zpre[2] == 0.0) || (Zpre[3] == 0.0)) {
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
  if ((Zpre[4] == 0.0) || (Zpre[5] == 0.0)) {
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
      Xk[i] += (real_T)A[i + (i0 << 2)] * Xpre[i0];
    }
  }

  for (i = 0; i < 4; i++) {
    for (i0 = 0; i0 < 4; i0++) {
      n1x = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        n1x += (real_T)A[i + (i1 << 2)] * Ppre[i1 + (i0 << 2)];
      }

      Pk[i + (i0 << 2)] = n1x + (real_T)iv3[i + (i0 << 2)];
    }
  }

  /* Innovation */
  EMLRTPUSHRTSTACK(&b_emlrtRSI);
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
      n1x = 0.0;
      for (i1 = 0; i1 < 4; i1++) {
        n1x += b_C[i + (i1 << 3)] * (real_T)C[i0 + (i1 << 3)];
      }

      x[i + (i0 << 3)] = n1x + R[i + (i0 << 3)];
    }
  }

  EMLRTPUSHRTSTACK(&e_emlrtRSI);
  invNxN(x, y);
  EMLRTPOPRTSTACK(&e_emlrtRSI);
  EMLRTPUSHRTSTACK(&f_emlrtRSI);
  EMLRTPUSHRTSTACK(&kb_emlrtRSI);
  n1x = norm(x);
  EMLRTPOPRTSTACK(&kb_emlrtRSI);
  EMLRTPUSHRTSTACK(&lb_emlrtRSI);
  n1xinv = norm(y);
  EMLRTPOPRTSTACK(&lb_emlrtRSI);
  rc = 1.0 / (n1x * n1xinv);
  if ((n1x == 0.0) || (n1xinv == 0.0) || (rc == 0.0)) {
    EMLRTPUSHRTSTACK(&mb_emlrtRSI);
    eml_warning();
    EMLRTPOPRTSTACK(&mb_emlrtRSI);
  } else {
    if (muDoubleScalarIsNaN(rc) || (rc < 2.2204460492503131E-16)) {
      EMLRTPUSHRTSTACK(&nb_emlrtRSI);
      EMLRTPUSHRTSTACK(&qb_emlrtRSI);
      b_y = NULL;
      m0 = mxCreateCharArray(2, iv4);
      emlrtInitCharArray(8, m0, cv0);
      emlrtAssign(&b_y, m0);
      c_y = NULL;
      m0 = mxCreateDoubleScalar(14.0);
      emlrtAssign(&c_y, m0);
      d_y = NULL;
      m0 = mxCreateDoubleScalar(6.0);
      emlrtAssign(&d_y, m0);
      e_y = NULL;
      m0 = mxCreateDoubleScalar(rc);
      emlrtAssign(&e_y, m0);
      emlrt_marshallIn(c_sprintf(b_sprintf(b_y, c_y, d_y, &g_emlrtMCI), e_y,
        &h_emlrtMCI), "sprintf", str);
      EMLRTPOPRTSTACK(&qb_emlrtRSI);
      b_eml_warning(str);
      EMLRTPOPRTSTACK(&nb_emlrtRSI);
    }
  }

  EMLRTPOPRTSTACK(&f_emlrtRSI);
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

  EMLRTPOPRTSTACK(&b_emlrtRSI);

  /* Mise a jour */
  for (i = 0; i < 8; i++) {
    n1x = 0.0;
    for (i0 = 0; i0 < 4; i0++) {
      n1x += (real_T)C[i + (i0 << 3)] * Xk[i0];
    }

    b_Zpre[i] = Zpre[i] - n1x;
  }

  for (i = 0; i < 4; i++) {
    n1x = 0.0;
    for (i0 = 0; i0 < 8; i0++) {
      n1x += Kk[i + (i0 << 2)] * b_Zpre[i0];
    }

    Xk[i] += n1x;
  }

  EMLRTPUSHRTSTACK(&c_emlrtRSI);
  EMLRTPUSHRTSTACK(&d_emlrtRSI);
  for (i = 0; i < 16; i++) {
    I[i] = 0;
  }

  for (i = 0; i < 4; i++) {
    I[i + (i << 2)] = 1;
  }

  EMLRTPOPRTSTACK(&d_emlrtRSI);
  for (i = 0; i < 4; i++) {
    for (i0 = 0; i0 < 4; i0++) {
      n1x = 0.0;
      for (i1 = 0; i1 < 8; i1++) {
        n1x += Kk[i + (i1 << 2)] * (real_T)C[i1 + (i0 << 3)];
      }

      b_I[i + (i0 << 2)] = (real_T)I[i + (i0 << 2)] - n1x;
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

  EMLRTPOPRTSTACK(&c_emlrtRSI);

  /* Incrementation */
  Pred[0] = Xk[0];

  /* X */
  Pred[1] = Xk[1];

  /* Y */
  Pred[2] = Xk[2];

  /* VX */
  Pred[3] = Xk[3];

  /* VY */
  memcpy(&Zk[0], &NewMeasure[0], sizeof(real_T) << 3);
}

/* End of code generation (Kalman_boucle.c) */
