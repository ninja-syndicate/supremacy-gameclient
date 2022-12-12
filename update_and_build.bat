@echo off 
setlocal
set project=%~dp0Supremacy.uproject
set build_dir=%~dp0Build
set ConfigFolder=%build_dir%\Windows\Supremacy\Saved\Config\Windows\
set ConfigFile=%ConfigFolder%Engine.ini
set GameFile=%ConfigFolder%Game.ini
set DefaultEngineFile=%~dp0Config\DefaultEngine.ini
for /f %%i in ('git describe --tags') do set Version=%%i
for /f %%i in ('git rev-parse --abbrev-ref HEAD') do set Branch=%%i
for /f %%i in ('git rev-parse --verify HEAD') do set Hash=%%i

if not defined SUPREMACY_EOS_ARTIFACT (
     echo [101;93m Warning: SUPREMACY_EOS_ARTIFACT env variable is unset [0m
     echo.
)

if exist "%RunUAT%" (
     REM Pull latest
     git pull --tags | find /i "Already up to date."
     echo.
     if not errorlevel 1 (
          echo Press any key to build the project anyway...
          pause >nul
     )
     
     REM Check if V8 Library is installed
     if not exist %~dp0\Plugins\UnrealJs\ThirdParty\v8\lib\Win64\Release\v8_init.lib (
          echo V8 library required for UnrealJS is missing, will download/unpack now
          setlocal
          cd "%~dp0\Plugins\UnrealJs"
          sh "install-v8-libs.sh"
          endlocal
     )

     REM Set Secrets for EOS
     Config\inifile %DefaultEngineFile% [/Script/OnlineSubsystemEOS.EOSSettings] +Artifacts=%SUPREMACY_EOS_ARTIFACT%

     REM BUILD
     "%RunUAT%" BuildCookRun -project="%project%" -targetplatform=Win64 -clientconfig=Development -cook -iterate -build -stage -pak -archive -archivedirectory="%build_dir%"

     REM Remove Secrets for EOS
     Config\inifile %DefaultEngineFile% [/Script/OnlineSubsystemEOS.EOSSettings] +Artifacts=

     REM Create Config Folder, Engine.ini, and Game.ini if they don't exist
     if not exist %ConfigFolder% mkdir %ConfigFolder%
     if not exist %ConfigFile% type nul >%ConfigFile%
     if not exist %GameFile% type nul >%GameFile%

     REM Set version number
     Config\inifile %ConfigFile% [/Game/UI/HUD.HUD_C] Version=%Version%
     Config\inifile %ConfigFile% [/Game/UI/HUD.HUD_C] BuildBranch=%Branch%
     Config\inifile %ConfigFile% [/Game/UI/HUD.HUD_C] Hash=%Hash%

     REM Set BuildNo for HUD
     Config\inifile %ConfigFile% [/Game/UI/HUD.HUD_C] BuildNo=%Version%

     REM Enable display of build number
     Config\inifile %GameFile% [/Game/Blueprints/SupremacyGameInstance.SupremacyGameInstance_C] ShowBuildNo=True

     REM Stream client - enable connection to battle server
     Config\inifile %GameFile% [/Game/Blueprints/SupremacyGameInstance.SupremacyGameInstance_C] ConnectToBattleServer=True
     Config\inifile %GameFile% [/Game/Blueprints/SupremacyGameInstance.SupremacyGameInstance_C] AutoHost=True

     echo BuildNo %Version% Branch %Branch% Hash %Hash%
pause

) else (
     echo [101;93m Failed to find RunUAT.bat [0m
     echo.
     echo Please set the RunUAT environment variable to:
     echo UnrealEngine\UE_5.1\Engine\Build\BatchFiles\RunUAT.bat
     echo.
     pause
)
