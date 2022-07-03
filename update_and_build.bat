@echo off 
setlocal

if not exist "%UNREAL_ROOT_5_0%" (
     echo Unreal 5 Root environment variable (UNREAL_ROOT_5_0^) not set.
     echo Please set it to something like \"C:\Program files\Epic Games\UE_5.0\" or wherever your UE5.0 install is
     echo note: This directory will contain "Engine", "FeaturePacks", "Samples" and "Templates" (at least^)
     pause
     exit /b 1
)

set runuat_location=%UNREAL_ROOT_5_0%\Engine\Build\BatchFiles\RunUAT.bat

if not exist "%runuat_location%" (
     echo Could not find RunUAT bach file at "%runuat_location%". 
     echo Please check that your UNREAL_ROOT_5_0 environment variable is set properly and that your engine is installed correctly
     pause
     exit /b 2
)

set project=%~dp0Supremacy.uproject
set build_dir=%~dp0Build
set ConfigFile=%build_dir%\Windows\Supremacy\Saved\Config\Windows\Engine.ini
set DefaultEngineFile=%~dp0Config\DefaultEngine.ini
for /f %%i in ('git describe --tags') do set Version=%%i
for /f %%i in ('git rev-parse --abbrev-ref HEAD') do set Branch=%%i
for /f %%i in ('git rev-parse --verify HEAD') do set Hash=%%i


git pull --tags
git pull | find /i "Already up to date."
echo.
if not errorlevel 1 (
     echo Press any key to build the project anyway...
     pause >nul
)

if not exist %~dp0\Plugins\UnrealJs\ThirdParty\v8\lib\Win64\Release\v8_init.lib (
     echo V8 library required for UnrealJS is missing, will download/unpack now
     setlocal
     cd "%~dp0\Plugins\UnrealJs"
     rem TODO this needs to handle errors on the v8 install properly.
     sh "install-v8-libs.sh"
     endlocal
)

Config\inifile %DefaultEngineFile% [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0
Config\inifile %DefaultEngineFile% [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11

"%runuat_location%" BuildCookRun -project="%project%" -targetplatform=Win64 -clientconfig=Development -cook -build -stage -pak -archive -archivedirectory="%build_dir%"

Config\inifile %ConfigFile% [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0
Config\inifile %ConfigFile% [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11

Config\inifile %DefaultEngineFile% [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=
Config\inifile %DefaultEngineFile% [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX12

Config\inifile %ConfigFile% [/Game/UI/HUD.HUD_C] Version=%Version%
Config\inifile %ConfigFile% [/Game/UI/HUD.HUD_C] BuildBranch=%Branch%
Config\inifile %ConfigFile% [/Game/UI/HUD.HUD_C] Hash=%Hash%
echo BuildNo %Version% Branch %Branch% Hash %Hash%