/*
 * Kalman_boucle_mex.c
 *
 * Code generation for function 'Kalman_boucle'
 *
 * C source code generated on: Tue Jan 07 09:14:11 2014
 *
 */

/* Include files */
#include "mex.h"
#include "Kalman_boucle_api.h"
#include "Kalman_boucle_initialize.h"
#include "Kalman_boucle_terminate.h"

/* Type Definitions */

/* Function Declarations */
static void Kalman_boucle_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);
MEXFUNCTION_LINKAGE mxArray *emlrtMexFcnProperties(void);

/* Variable Definitions */
emlrtContext emlrtContextGlobal = { true, false, EMLRT_VERSION_INFO, NULL, "Kalman_boucle", NULL, false, {2045744189U,2170104910U,2743257031U,4284093946U}, 0, false, 1, false };

/* Function Definitions */
static void Kalman_boucle_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Temporary copy for mex outputs. */
  mxArray *outputs[4];
  int n = 0;
  int nOutputs = (nlhs < 1 ? 1 : nlhs);
  /* Check for proper number of arguments. */
  if(nrhs != 5) {
    mexErrMsgIdAndTxt("emlcoder:emlmex:WrongNumberOfInputs","5 inputs required for entry-point 'Kalman_boucle'.");
  } else if(nlhs > 4) {
    mexErrMsgIdAndTxt("emlcoder:emlmex:TooManyOutputArguments","Too many output arguments for entry-point 'Kalman_boucle'.");
  }
  /* Module initialization. */
  Kalman_boucle_initialize(&emlrtContextGlobal);
  /* Call the function. */
  Kalman_boucle_api(prhs,(const mxArray**)outputs);
  /* Copy over outputs to the caller. */
  for (n = 0; n < nOutputs; ++n) {
    plhs[n] = emlrtReturnArrayR2009a(outputs[n]);
  }
  /* Module finalization. */
  Kalman_boucle_terminate();
}

void Kalman_boucle_atexit_wrapper(void)
{
  Kalman_boucle_atexit();
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Initialize the memory manager. */
  mexAtExit(Kalman_boucle_atexit_wrapper);
  emlrtClearAllocCount(&emlrtContextGlobal, 0, 0, NULL);
  /* Dispatch the entry-point. */
  Kalman_boucle_mexFunction(nlhs, plhs, nrhs, prhs);
}

mxArray *emlrtMexFcnProperties(void)
{
    const char *mexProperties[] = {
        "Version",
        "EntryPoints"};
    const char *epProperties[] = {
        "Name",
        "NumberOfInputs",
        "NumberOfOutputs",
        "ConstantInputs"};
    mxArray *xResult = mxCreateStructMatrix(1,1,2,mexProperties);
    mxArray *xEntryPoints = mxCreateStructMatrix(1,1,4,epProperties);
    mxArray *xInputs = NULL;
    xInputs = mxCreateLogicalMatrix(1, 5);
    mxSetFieldByNumber(xEntryPoints, 0, 0, mxCreateString("Kalman_boucle"));
    mxSetFieldByNumber(xEntryPoints, 0, 1, mxCreateDoubleScalar(5));
    mxSetFieldByNumber(xEntryPoints, 0, 2, mxCreateDoubleScalar(4));
    mxSetFieldByNumber(xEntryPoints, 0, 3, xInputs);
    mxSetFieldByNumber(xResult, 0, 0, mxCreateString("7.14.0.739 (R2012a)"));
    mxSetFieldByNumber(xResult, 0, 1, xEntryPoints);

    return xResult;
}
/* End of code generation (Kalman_boucle_mex.c) */
