/*
 * File: rtGetNaN.cpp
 *
 * Real-Time Workshop code generated for Simulink model Pos_Controller.
 *
 * Model version                        : 1.383
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Wed Jan  1 19:08:22 2014
 * TLC version                          : 7.4 (Jul 13 2009)
 * C/C++ source code generated on       : Wed Jan  1 19:08:22 2014
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86/Pentium
 * Code generation objective: Efficiency
 * Validation result: Passed (0), Warning (1), Error (0)
 */

/*
 * Abstract:
 *      Real-Time Workshop function to intialize non-finite, NaN
 */
#include "rtGetNaN.h"
#define NumBitsPerChar                 8

extern "C" {
  /*
   * Initialize rtNaN needed by the generated code.
   * NaN is initialized as non-signaling. Assumes IEEE.
   */
  real_T rtGetNaN(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T nan = 0.0;
    if (bitsPerReal == 32) {
      nan = rtGetNaNF();
    } else {
      typedef struct {
        struct {
          uint32_T wordL;
          uint32_T wordH;
        } words;
      } LittleEndianIEEEDouble;

      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF80000;
      tmpVal.bitVal.words.wordL = 0x00000000;
      nan = tmpVal.fltVal;
    }

    return nan;
  }

  /*
   * Initialize rtNaNF needed by the generated code.
   * NaN is initialized as non-signaling. Assumes IEEE.
   */
  real32_T rtGetNaNF(void)
  {
    typedef struct {
      union {
        real32_T wordLreal;
        uint32_T wordLuint;
      } wordL;
    } IEEESingle;

    IEEESingle nanF;
    nanF.wordL.wordLuint = 0xFFC00000;
    return nanF.wordL.wordLreal;
  }
}
/* end rt_getNaN.c */
/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
