SETLOCAL EnableDelayedExpansion

rem Disable launching the JIT debugger for ctest.exe
reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\AeDebug\AutoExclusionList" /v "ctest.ext" /t REG_DWORD /d 1
if "%CONFIGURATION%"=="Debug" (
  .\x64\Debug\TESTS.exe -r Junit >> test.xml
)
if "%CONFIGURATION%"=="Release" (
  .\x64\Release\TESTS.exe -r Junit >> test.xml
)