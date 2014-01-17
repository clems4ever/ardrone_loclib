@echo off
call "%VS90COMNTOOLS%..\..\VC\vcvarsall.bat" AMD64

cd .
nmake -f Kalman_boucle_rtw.mk  GENERATE_REPORT=0 ADD_MDL_NAME_TO_GLOBALS=0
@if errorlevel 1 goto error_exit
exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
An_error_occurred_during_the_call_to_make
