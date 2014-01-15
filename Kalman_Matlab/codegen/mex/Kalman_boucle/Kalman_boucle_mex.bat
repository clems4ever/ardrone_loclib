@echo off
set MATLAB=C:\PROGRA~1\MATLAB~1
set MATLAB_ARCH=win64
set MATLAB_BIN="C:\Program Files\MatLab 2012a\bin"
set ENTRYPOINT=mexFunction
set OUTDIR=.\
set LIB_NAME=Kalman_boucle_mex
set MEX_NAME=Kalman_boucle_mex
set MEX_EXT=.mexw64
call mexopts.bat
echo # Make settings for Kalman_boucle > Kalman_boucle_mex.mki
echo COMPILER=%COMPILER%>> Kalman_boucle_mex.mki
echo COMPFLAGS=%COMPFLAGS%>> Kalman_boucle_mex.mki
echo OPTIMFLAGS=%OPTIMFLAGS%>> Kalman_boucle_mex.mki
echo DEBUGFLAGS=%DEBUGFLAGS%>> Kalman_boucle_mex.mki
echo LINKER=%LINKER%>> Kalman_boucle_mex.mki
echo LINKFLAGS=%LINKFLAGS%>> Kalman_boucle_mex.mki
echo LINKOPTIMFLAGS=%LINKOPTIMFLAGS%>> Kalman_boucle_mex.mki
echo LINKDEBUGFLAGS=%LINKDEBUGFLAGS%>> Kalman_boucle_mex.mki
echo MATLAB_ARCH=%MATLAB_ARCH%>> Kalman_boucle_mex.mki
echo BORLAND=%BORLAND%>> Kalman_boucle_mex.mki
echo OMPFLAGS= >> Kalman_boucle_mex.mki
echo OMPLINKFLAGS= >> Kalman_boucle_mex.mki
echo EMC_COMPILER=msvc90>> Kalman_boucle_mex.mki
echo EMC_CONFIG=optim>> Kalman_boucle_mex.mki
"C:\Program Files\MatLab 2012a\bin\win64\gmake" -B -f Kalman_boucle_mex.mk
