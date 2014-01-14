/*
 * Kalman_boucle_api.c
 *
 * Code generation for function 'Kalman_boucle_api'
 *
 * C source code generated on: Tue Jan 07 09:14:11 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Kalman_boucle.h"
#include "Kalman_boucle_api.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static const mxArray *b_emlrt_marshallOut(const real_T u[16]);
static void c_emlrt_marshallIn(const mxArray *NewMeasure, const char_T
  *identifier, real_T y[8]);
static const mxArray *c_emlrt_marshallOut(const real_T u[8]);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[8]);
static void e_emlrt_marshallIn(const mxArray *R, const char_T *identifier,
  real_T y[64]);
static const mxArray *emlrt_marshallOut(const real_T u[4]);
static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[64]);
static void g_emlrt_marshallIn(const mxArray *Xpre, const char_T *identifier,
  real_T y[4]);
static void h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[4]);
static void i_emlrt_marshallIn(const mxArray *Ppre, const char_T *identifier,
  real_T y[16]);
static void j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[16]);
static void l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[8]);
static void m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[64]);
static void n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[4]);
static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[16]);

/* Function Definitions */
static const mxArray *b_emlrt_marshallOut(const real_T u[16])
{
  const mxArray *y;
  static const int32_T iv13[2] = { 4, 4 };

  const mxArray *m6;
  real_T (*pData)[];
  int32_T i;
  y = NULL;
  m6 = mxCreateNumericArray(2, (int32_T *)&iv13, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T (*)[])mxGetPr(m6);
  for (i = 0; i < 16; i++) {
    (*pData)[i] = u[i];
  }

  emlrtAssign(&y, m6);
  return y;
}

static void c_emlrt_marshallIn(const mxArray *NewMeasure, const char_T
  *identifier, real_T y[8])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  d_emlrt_marshallIn(emlrtAlias(NewMeasure), &thisId, y);
  emlrtDestroyArray(&NewMeasure);
}

static const mxArray *c_emlrt_marshallOut(const real_T u[8])
{
  const mxArray *y;
  static const int32_T iv14[1] = { 8 };

  const mxArray *m7;
  real_T (*pData)[];
  int32_T i;
  y = NULL;
  m7 = mxCreateNumericArray(1, (int32_T *)&iv14, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T (*)[])mxGetPr(m7);
  for (i = 0; i < 8; i++) {
    (*pData)[i] = u[i];
  }

  emlrtAssign(&y, m7);
  return y;
}

static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[8])
{
  l_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void e_emlrt_marshallIn(const mxArray *R, const char_T *identifier,
  real_T y[64])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  f_emlrt_marshallIn(emlrtAlias(R), &thisId, y);
  emlrtDestroyArray(&R);
}

static const mxArray *emlrt_marshallOut(const real_T u[4])
{
  const mxArray *y;
  static const int32_T iv12[1] = { 4 };

  const mxArray *m5;
  real_T (*pData)[];
  int32_T i;
  y = NULL;
  m5 = mxCreateNumericArray(1, (int32_T *)&iv12, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T (*)[])mxGetPr(m5);
  for (i = 0; i < 4; i++) {
    (*pData)[i] = u[i];
  }

  emlrtAssign(&y, m5);
  return y;
}

static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[64])
{
  m_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void g_emlrt_marshallIn(const mxArray *Xpre, const char_T *identifier,
  real_T y[4])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  h_emlrt_marshallIn(emlrtAlias(Xpre), &thisId, y);
  emlrtDestroyArray(&Xpre);
}

static void h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[4])
{
  n_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void i_emlrt_marshallIn(const mxArray *Ppre, const char_T *identifier,
  real_T y[16])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  j_emlrt_marshallIn(emlrtAlias(Ppre), &thisId, y);
  emlrtDestroyArray(&Ppre);
}

static void j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[16])
{
  o_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[8])
{
  int32_T iv16[1];
  int32_T i4;
  iv16[0] = 8;
  emlrtCheckBuiltInCtxR2011b(&emlrtContextGlobal, msgId, src, "double", FALSE,
    1U, iv16);
  for (i4 = 0; i4 < 8; i4++) {
    ret[i4] = (*(real_T (*)[8])mxGetData(src))[i4];
  }

  emlrtDestroyArray(&src);
}

static void m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[64])
{
  int32_T iv17[2];
  int32_T i;
  int32_T i5;
  for (i = 0; i < 2; i++) {
    iv17[i] = 8;
  }

  emlrtCheckBuiltInCtxR2011b(&emlrtContextGlobal, msgId, src, "double", FALSE,
    2U, iv17);
  for (i = 0; i < 8; i++) {
    for (i5 = 0; i5 < 8; i5++) {
      ret[i5 + (i << 3)] = (*(real_T (*)[64])mxGetData(src))[i5 + (i << 3)];
    }
  }

  emlrtDestroyArray(&src);
}

static void n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[4])
{
  int32_T iv18[1];
  int32_T i6;
  iv18[0] = 4;
  emlrtCheckBuiltInCtxR2011b(&emlrtContextGlobal, msgId, src, "double", FALSE,
    1U, iv18);
  for (i6 = 0; i6 < 4; i6++) {
    ret[i6] = (*(real_T (*)[4])mxGetData(src))[i6];
  }

  emlrtDestroyArray(&src);
}

static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[16])
{
  int32_T iv19[2];
  int32_T i;
  int32_T i7;
  for (i = 0; i < 2; i++) {
    iv19[i] = 4;
  }

  emlrtCheckBuiltInCtxR2011b(&emlrtContextGlobal, msgId, src, "double", FALSE,
    2U, iv19);
  for (i = 0; i < 4; i++) {
    for (i7 = 0; i7 < 4; i7++) {
      ret[i7 + (i << 2)] = (*(real_T (*)[16])mxGetData(src))[i7 + (i << 2)];
    }
  }

  emlrtDestroyArray(&src);
}

void Kalman_boucle_api(const mxArray * const prhs[5], const mxArray *plhs[4])
{
  real_T NewMeasure[8];
  real_T R[64];
  real_T Xpre[4];
  real_T Ppre[16];
  real_T Zpre[8];
  real_T b_NewMeasure[8];
  real_T b_Xpre[4];
  int32_T i;
  real_T b_Ppre[16];
  real_T Pred[4];

  /* Marshall function inputs */
  c_emlrt_marshallIn(emlrtAliasP(prhs[0]), "NewMeasure", NewMeasure);
  e_emlrt_marshallIn(emlrtAliasP(prhs[1]), "R", R);
  g_emlrt_marshallIn(emlrtAliasP(prhs[2]), "Xpre", Xpre);
  i_emlrt_marshallIn(emlrtAliasP(prhs[3]), "Ppre", Ppre);
  c_emlrt_marshallIn(emlrtAliasP(prhs[4]), "Zpre", Zpre);

  /* Invoke the target function */
  memcpy(&b_NewMeasure[0], &NewMeasure[0], sizeof(real_T) << 3);
  for (i = 0; i < 4; i++) {
    b_Xpre[i] = Xpre[i];
  }

  memcpy(&b_Ppre[0], &Ppre[0], sizeof(real_T) << 4);
  Kalman_boucle(b_NewMeasure, R, b_Xpre, b_Ppre, Zpre, Xpre, Ppre, NewMeasure,
                Pred);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(Xpre);
  plhs[1] = b_emlrt_marshallOut(Ppre);
  plhs[2] = c_emlrt_marshallOut(NewMeasure);
  plhs[3] = emlrt_marshallOut(Pred);
}

/* End of code generation (Kalman_boucle_api.c) */
