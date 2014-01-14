/*
 * inv.c
 *
 * Code generation for function 'inv'
 *
 * C source code generated on: Tue Jan 07 09:14:11 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Kalman_boucle.h"
#include "inv.h"
#include "Kalman_boucle_mexutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static emlrtRSInfo g_emlrtRSI = { 170, "inv",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/inv.m" };

static emlrtRSInfo h_emlrtRSI = { 171, "inv",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/inv.m" };

static emlrtRSInfo i_emlrtRSI = { 177, "inv",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/inv.m" };

static emlrtRSInfo j_emlrtRSI = { 180, "inv",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/inv.m" };

static emlrtRSInfo k_emlrtRSI = { 187, "inv",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/matfun/inv.m" };

static emlrtRSInfo l_emlrtRSI = { 8, "eml_xgetrf",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m"
};

static emlrtRSInfo m_emlrtRSI = { 8, "eml_lapack_xgetrf",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m"
};

static emlrtRSInfo n_emlrtRSI = { 36, "eml_matlab_zgetrf",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"
};

static emlrtRSInfo o_emlrtRSI = { 44, "eml_matlab_zgetrf",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"
};

static emlrtRSInfo p_emlrtRSI = { 50, "eml_matlab_zgetrf",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"
};

static emlrtRSInfo q_emlrtRSI = { 58, "eml_matlab_zgetrf",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"
};

static emlrtRSInfo r_emlrtRSI = { 20, "eml_ixamax",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m" };

static emlrtRSInfo s_emlrtRSI = { 18, "eml_blas_ixamax",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m"
};

static emlrtRSInfo t_emlrtRSI = { 23, "eml_refblas_ixamax",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m"
};

static emlrtRSInfo u_emlrtRSI = { 13, "eml_int_forloop_overflow_check",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

static emlrtRSInfo v_emlrtRSI = { 26, "eml_xswap",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m" };

static emlrtRSInfo w_emlrtRSI = { 15, "eml_blas_xswap",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m"
};

static emlrtRSInfo x_emlrtRSI = { 13, "eml_int_forloop_overflow_check",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

static emlrtRSInfo y_emlrtRSI = { 42, "eml_xgeru",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m" };

static emlrtRSInfo ab_emlrtRSI = { 37, "eml_xger",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/eml_xger.m" };

static emlrtRSInfo bb_emlrtRSI = { 18, "eml_blas_xger",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m"
};

static emlrtRSInfo cb_emlrtRSI = { 14, "eml_refblas_xger",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m"
};

static emlrtRSInfo db_emlrtRSI = { 40, "eml_refblas_xgerx",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m"
};

static emlrtRSInfo eb_emlrtRSI = { 53, "eml_refblas_xgerx",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m"
};

static emlrtRSInfo fb_emlrtRSI = { 54, "eml_xtrsm",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m" };

static emlrtRSInfo hb_emlrtRSI = { 28, "eml_blas_xtrsm",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m"
};

static emlrtRSInfo jb_emlrtRSI = { 80, "eml_blas_xtrsm",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m"
};

static emlrtMCInfo emlrtMCI = { 14, 9, "eml_int_forloop_overflow_check",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

static emlrtMCInfo b_emlrtMCI = { 13, 19, "eml_int_forloop_overflow_check",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

static emlrtMCInfo c_emlrtMCI = { 14, 9, "eml_int_forloop_overflow_check",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

static emlrtMCInfo d_emlrtMCI = { 13, 19, "eml_int_forloop_overflow_check",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

static emlrtBCInfo emlrtBCI = { 1, 64, 25, 28, "", "eml_refblas_ixamax",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m",
  0 };

static emlrtBCInfo b_emlrtBCI = { 1, 8, 25, 16, "", "eml_ipiv2perm",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_ipiv2perm.m", 0
};

static emlrtBCInfo c_emlrtBCI = { 1, 8, 26, 9, "", "eml_ipiv2perm",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/eml_ipiv2perm.m", 0
};

static emlrtBCInfo d_emlrtBCI = { 1, 64, 42, 15, "", "eml_refblas_xgerx",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m",
  0 };

static emlrtBCInfo e_emlrtBCI = { 1, 64, 55, 17, "", "eml_refblas_xgerx",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m",
  0 };

static emlrtBCInfo f_emlrtBCI = { 1, 64, 55, 26, "", "eml_refblas_xgerx",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m",
  0 };

static emlrtBCInfo g_emlrtBCI = { 1, 64, 55, 35, "", "eml_refblas_xgerx",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m",
  0 };

static emlrtBCInfo h_emlrtBCI = { 1, 64, 20, 12, "", "eml_refblas_xswap",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m",
  0 };

static emlrtBCInfo i_emlrtBCI = { 1, 64, 22, 17, "", "eml_refblas_xswap",
  "C:/Program Files/MatLab 2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m",
  0 };

/* Function Declarations */
static void b_eml_int_forloop_overflow_chec(int32_T a, int32_T b);
static void eml_int_forloop_overflow_check(int32_T b);
static void error(const mxArray *b, emlrtMCInfo *location);

/* Function Definitions */
static void b_eml_int_forloop_overflow_chec(int32_T a, int32_T b)
{
  boolean_T overflow;
  const mxArray *y;
  static const int32_T iv7[2] = { 1, 34 };

  const mxArray *m2;
  static const char_T cv3[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o',
    'l', 'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o',
    'p', '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  const mxArray *b_y;
  static const int32_T iv8[2] = { 1, 5 };

  static const char_T cv4[5] = { 'i', 'n', 't', '3', '2' };

  if (a > b) {
    overflow = FALSE;
  } else {
    overflow = (b > 2147483646);
  }

  if (!overflow) {
  } else {
    EMLRTPUSHRTSTACK(&x_emlrtRSI);
    y = NULL;
    m2 = mxCreateCharArray(2, iv7);
    emlrtInitCharArray(34, m2, cv3);
    emlrtAssign(&y, m2);
    b_y = NULL;
    m2 = mxCreateCharArray(2, iv8);
    emlrtInitCharArray(5, m2, cv4);
    emlrtAssign(&b_y, m2);
    error(message(y, b_y, &c_emlrtMCI), &d_emlrtMCI);
    EMLRTPOPRTSTACK(&x_emlrtRSI);
  }
}

static void eml_int_forloop_overflow_check(int32_T b)
{
  boolean_T overflow;
  const mxArray *y;
  static const int32_T iv5[2] = { 1, 34 };

  const mxArray *m1;
  static const char_T cv1[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o',
    'l', 'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o',
    'p', '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  const mxArray *b_y;
  static const int32_T iv6[2] = { 1, 5 };

  static const char_T cv2[5] = { 'i', 'n', 't', '3', '2' };

  if (2 > b) {
    overflow = FALSE;
  } else {
    overflow = (b > 2147483646);
  }

  if (!overflow) {
  } else {
    EMLRTPUSHRTSTACK(&u_emlrtRSI);
    y = NULL;
    m1 = mxCreateCharArray(2, iv5);
    emlrtInitCharArray(34, m1, cv1);
    emlrtAssign(&y, m1);
    b_y = NULL;
    m1 = mxCreateCharArray(2, iv6);
    emlrtInitCharArray(5, m1, cv2);
    emlrtAssign(&b_y, m1);
    error(message(y, b_y, &emlrtMCI), &b_emlrtMCI);
    EMLRTPOPRTSTACK(&u_emlrtRSI);
  }
}

static void error(const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLAB(0, NULL, 1, &pArray, "error", TRUE, location);
}

void invNxN(const real_T x[64], real_T y[64])
{
  real_T A[64];
  int8_T ipiv[8];
  int32_T i2;
  int32_T j;
  int32_T jj;
  int32_T jp1j;
  int32_T pipk;
  int32_T lda;
  int32_T ix;
  real_T smax;
  int32_T k;
  real_T s;
  int32_T jrow;
  int8_T p[8];
  char_T SIDE;
  char_T UPLO;
  char_T TRANSA;
  char_T DIAGA;
  memset(&y[0], 0, sizeof(real_T) << 6);
  EMLRTPUSHRTSTACK(&g_emlrtRSI);
  EMLRTPUSHRTSTACK(&l_emlrtRSI);
  EMLRTPUSHRTSTACK(&m_emlrtRSI);
  memcpy(&A[0], &x[0], sizeof(real_T) << 6);
  for (i2 = 0; i2 < 8; i2++) {
    ipiv[i2] = (int8_T)(1 + i2);
  }

  for (j = 0; j < 7; j++) {
    jj = j * 9;
    jp1j = jj + 2;
    EMLRTPUSHRTSTACK(&n_emlrtRSI);
    pipk = 8 - j;
    EMLRTPUSHRTSTACK(&r_emlrtRSI);
    EMLRTPUSHRTSTACK(&s_emlrtRSI);
    lda = 1;
    ix = jj;
    smax = muDoubleScalarAbs(A[jj]);
    EMLRTPUSHRTSTACK(&t_emlrtRSI);
    eml_int_forloop_overflow_check(pipk);
    EMLRTPOPRTSTACK(&t_emlrtRSI);
    for (k = 2; k <= pipk; k++) {
      ix++;
      emlrtBoundsCheck(ix + 1, &emlrtBCI);
      s = muDoubleScalarAbs(A[ix]);
      if (s > smax) {
        lda = k;
        smax = s;
      }
    }

    EMLRTPOPRTSTACK(&s_emlrtRSI);
    EMLRTPOPRTSTACK(&r_emlrtRSI);
    EMLRTPOPRTSTACK(&n_emlrtRSI);
    if (A[(jj + lda) - 1] != 0.0) {
      if (lda - 1 != 0) {
        ipiv[j] = (int8_T)(j + lda);
        jrow = 1 + j;
        EMLRTPUSHRTSTACK(&o_emlrtRSI);
        EMLRTPUSHRTSTACK(&v_emlrtRSI);
        EMLRTPUSHRTSTACK(&w_emlrtRSI);
        pipk = (jrow + lda) - 1;
        for (k = 0; k < 8; k++) {
          smax = A[emlrtBoundsCheck(jrow, &h_emlrtBCI) - 1];
          A[jrow - 1] = A[emlrtBoundsCheck(pipk, &i_emlrtBCI) - 1];
          A[pipk - 1] = smax;
          jrow += 8;
          pipk += 8;
        }

        EMLRTPOPRTSTACK(&w_emlrtRSI);
        EMLRTPOPRTSTACK(&v_emlrtRSI);
        EMLRTPOPRTSTACK(&o_emlrtRSI);
      }

      i2 = (jp1j - j) + 6;
      EMLRTPUSHRTSTACK(&p_emlrtRSI);
      b_eml_int_forloop_overflow_chec(jp1j, i2);
      EMLRTPOPRTSTACK(&p_emlrtRSI);
      for (pipk = jp1j; pipk <= i2; pipk++) {
        A[pipk - 1] /= A[jj];
      }
    }

    EMLRTPUSHRTSTACK(&q_emlrtRSI);
    EMLRTPUSHRTSTACK(&y_emlrtRSI);
    EMLRTPUSHRTSTACK(&ab_emlrtRSI);
    EMLRTPUSHRTSTACK(&bb_emlrtRSI);
    EMLRTPUSHRTSTACK(&cb_emlrtRSI);
    jrow = jj + 10;
    pipk = jj + 8;
    EMLRTPUSHRTSTACK(&db_emlrtRSI);
    b_eml_int_forloop_overflow_chec(1, 7 - j);
    EMLRTPOPRTSTACK(&db_emlrtRSI);
    for (lda = 1; lda <= 7 - j; lda++) {
      smax = A[emlrtBoundsCheck(pipk + 1, &d_emlrtBCI) - 1];
      if (A[pipk] != 0.0) {
        ix = jp1j;
        i2 = (jrow - j) + 6;
        EMLRTPUSHRTSTACK(&eb_emlrtRSI);
        b_eml_int_forloop_overflow_chec(jrow, i2);
        EMLRTPOPRTSTACK(&eb_emlrtRSI);
        for (k = jrow; k <= i2; k++) {
          A[emlrtBoundsCheck(k, &e_emlrtBCI) - 1] = A[emlrtBoundsCheck(k,
            &f_emlrtBCI) - 1] + A[emlrtBoundsCheck(ix, &g_emlrtBCI) - 1] * -smax;
          ix++;
        }
      }

      pipk += 8;
      jrow += 8;
    }

    EMLRTPOPRTSTACK(&cb_emlrtRSI);
    EMLRTPOPRTSTACK(&bb_emlrtRSI);
    EMLRTPOPRTSTACK(&ab_emlrtRSI);
    EMLRTPOPRTSTACK(&y_emlrtRSI);
    EMLRTPOPRTSTACK(&q_emlrtRSI);
  }

  EMLRTPOPRTSTACK(&m_emlrtRSI);
  EMLRTPOPRTSTACK(&l_emlrtRSI);
  EMLRTPOPRTSTACK(&g_emlrtRSI);
  EMLRTPUSHRTSTACK(&h_emlrtRSI);
  for (i2 = 0; i2 < 8; i2++) {
    p[i2] = (int8_T)(1 + i2);
  }

  for (k = 0; k < 7; k++) {
    if (ipiv[k] > 1 + k) {
      pipk = p[emlrtBoundsCheck((int32_T)ipiv[k], &b_emlrtBCI) - 1];
      p[emlrtBoundsCheck((int32_T)ipiv[k], &c_emlrtBCI) - 1] = p[k];
      p[k] = (int8_T)pipk;
    }
  }

  EMLRTPOPRTSTACK(&h_emlrtRSI);
  for (k = 0; k < 8; k++) {
    y[k + ((p[k] - 1) << 3)] = 1.0;
    EMLRTPUSHRTSTACK(&i_emlrtRSI);
    b_eml_int_forloop_overflow_chec(k + 1, 8);
    EMLRTPOPRTSTACK(&i_emlrtRSI);
    for (j = k; j + 1 < 9; j++) {
      if (y[j + ((p[k] - 1) << 3)] != 0.0) {
        EMLRTPUSHRTSTACK(&j_emlrtRSI);
        b_eml_int_forloop_overflow_chec(j + 2, 8);
        EMLRTPOPRTSTACK(&j_emlrtRSI);
        for (pipk = j + 1; pipk + 1 < 9; pipk++) {
          y[pipk + ((p[k] - 1) << 3)] -= y[j + ((p[k] - 1) << 3)] * A[pipk + (j <<
            3)];
        }
      }
    }
  }

  EMLRTPUSHRTSTACK(&k_emlrtRSI);
  EMLRTPUSHRTSTACK(&fb_emlrtRSI);
  EMLRTPUSHRTSTACK(&hb_emlrtRSI);
  pipk = 8;
  jrow = 8;
  smax = 1.0;
  lda = 8;
  k = 8;
  SIDE = 'L';
  UPLO = 'U';
  TRANSA = 'N';
  DIAGA = 'N';
  EMLRTPUSHRTSTACK(&jb_emlrtRSI);
  dtrsm32(&SIDE, &UPLO, &TRANSA, &DIAGA, &pipk, &jrow, &smax, &A[0], &lda, &y[0],
          &k);
  EMLRTPOPRTSTACK(&jb_emlrtRSI);
  EMLRTPOPRTSTACK(&hb_emlrtRSI);
  EMLRTPOPRTSTACK(&fb_emlrtRSI);
  EMLRTPOPRTSTACK(&k_emlrtRSI);
}

/* End of code generation (inv.c) */
