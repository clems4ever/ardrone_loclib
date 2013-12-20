/*
 * File: rtGetInf.cpp
 *
 * Real-Time Workshop code generated for Simulink model Pos_Controller.
 *
 * Model version                        : 1.338
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Sun Dec 15 14:39:42 2013
 * TLC version                          : 7.4 (Jul 13 2009)
 * C/C++ source code generated on       : Sun Dec 15 14:39:42 2013
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Passed (0), Warning (1), Error (0)
 */

/*
 * Abstract:
 *      Real-Time Workshop function to intialize non-finite, Inf
 */
#include "rtGetInf.h"
#define NumBitsPerChar                 8

extern "C" {
  /*
   * Initialize rtInf needed by the generated code.
   * Inf is initialized as non-signaling. Assumes IEEE.
   */
  real_T rtGetInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T inf = 0.0;
    if (bitsPerReal == 32) {
      inf = rtGetInfF();
    } else {
      uint16_T one = 1;
      enum {
        LittleEndian,
        BigEndian
      } machByteOrder = (*((uint8_T *) &one) == 1) ? LittleEndian : BigEndian;
      switch (machByteOrder) {
       case LittleEndian:
        {
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

          tmpVal.bitVal.words.wordH = 0x7FF00000;
          tmpVal.bitVal.words.wordL = 0x00000000;
          inf = tmpVal.fltVal;
          break;
        }

       case BigEndian:
        {
          typedef struct {
            struct {
              uint32_T wordH;
              uint32_T wordL;
            } words;
          } BigEndianIEEEDouble;

          union {
            BigEndianIEEEDouble bitVal;
            real_T fltVal;
          } tmpVal;

          tmpVal.bitVal.words.wordH = 0x7FF00000;
          tmpVal.bitVal.words.wordL = 0x00000000;
          inf = tmpVal.fltVal;
          break;
        }
      }
    }

    return inf;
  }

  /*
   * Initialize rtInfF needed by the generated code.
   * Inf is initialized as non-signaling. Assumes IEEE.
   */
  real32_T rtGetInfF(void)
  {
    typedef struct {
      union {
        real32_T wordLreal;
        uint32_T wordLuint;
      } wordL;
    } IEEESingle;

    IEEESingle infF;
    infF.wordL.wordLuint = 0x7F800000;
    return infF.wordL.wordLreal;
  }

  /*
   * Initialize rtMinusInf needed by the generated code.
   * Inf is initialized as non-signaling. Assumes IEEE.
   */
  real_T rtGetMinusInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T minf = 0.0;
    if (bitsPerReal == 32) {
      minf = rtGetMinusInfF();
    } else {
      uint16_T one = 1;
      enum {
        LittleEndian,
        BigEndian
      } machByteOrder = (*((uint8_T *) &one) == 1) ? LittleEndian : BigEndian;
      switch (machByteOrder) {
       case LittleEndian:
        {
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

          tmpVal.bitVal.words.wordH = 0xFFF00000;
          tmpVal.bitVal.words.wordL = 0x00000000;
          minf = tmpVal.fltVal;
          break;
        }

       case BigEndian:
        {
          typedef struct {
            struct {
              uint32_T wordH;
              uint32_T wordL;
            } words;
          } BigEndianIEEEDouble;

          union {
            BigEndianIEEEDouble bitVal;
            real_T fltVal;
          } tmpVal;

          tmpVal.bitVal.words.wordH = 0xFFF00000;
          tmpVal.bitVal.words.wordL = 0x00000000;
          minf = tmpVal.fltVal;
          break;
        }
      }
    }

    return minf;
  }

  /*
   * Initialize rtMinusInfF needed by the generated code.
   * Inf is initialized as non-signaling. Assumes IEEE.
   */
  real32_T rtGetMinusInfF(void)
  {
    typedef struct {
      union {
        real32_T wordLreal;
        uint32_T wordLuint;
      } wordL;
    } IEEESingle;

    IEEESingle minfF;
    minfF.wordL.wordLuint = 0xFF800000;
    return minfF.wordL.wordLreal;
  }
}
/* end rtGetInf.c */
/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
