@echo off 
setlocal

if not exist %~dp0\Plugins\UnrealJs\ThirdParty\v8\lib\Win64\Release\v8_init.lib (
     echo V8 library required for UnrealJS is missing, will download/unpack now
     setlocal
     cd "%~dp0\Plugins\UnrealJs"
     install-v8-libs.bat
     endlocal
)

echo Setup Complete
pause