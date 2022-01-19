@echo off 

set RunUAT=G:\Development\UnrealEngine\UE_5.0EA\Engine\Build\BatchFiless\RunUAT.bat
if exist %RunUAT% (
     git pull | find /i "Already up to date."
     echo.
     if not errorlevel 1 (
          echo Press any key to build the project anyway...
          pause >nul
     )

     set project=%~dp0Supremacy.uproject
     set build_dir=%~dp0Build

     %RunUAT% BuildCookRun -project=%project% -targetplatform=Win64 -clientconfig=Development -cook -build -stage -pak -archive -archivedirectory=%build_dir%
pause

) else (
     cls
     echo Failed to find RunUAT.bat
     echo.
     pause
)