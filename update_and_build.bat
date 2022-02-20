@echo off 
set project=%~dp0Supremacy.uproject
set build_dir=%~dp0Build
set ConfigFile=%build_dir%\Windows\Supremacy\Saved\Config\Windows\Engine.ini
for /f %%i in ('git rev-list --count develop') do set Version=%%i

if exist "%RunUAT%" (
     git pull | find /i "Already up to date."
     echo.
     if not errorlevel 1 (
          echo Press any key to build the project anyway...
          pause >nul
     )

     "%RunUAT%" BuildCookRun -project=%project% -targetplatform=Win64 -clientconfig=Development -cook -build -stage -pak -archive -archivedirectory=%build_dir%

     Config\inifile %ConfigFile% [/Game/UI/HUD.HUD_C] BuildNo=%Version%
     echo BuildNo %Version%
pause

) else (
     echo Failed to find RunUAT.bat
     echo.
     echo Please set the RunUAT environment variable to:
     echo UnrealEngine\UE_5.0EA\Engine\Build\BatchFiles\RunUAT.bat
     echo.
     pause
)