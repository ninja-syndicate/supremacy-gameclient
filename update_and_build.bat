@echo off 
setlocal
set project=%~dp0Supremacy.uproject
set build_dir=%~dp0Build
set ConfigFile=%build_dir%\Windows\Supremacy\Saved\Config\Windows\Engine.ini
set DefaultEngineFile=%~dp0Config\DefaultEngine.ini
for /f %%i in ('git describe --tags') do set Version=%%i
for /f %%i in ('git rev-parse --abbrev-ref HEAD') do set Branch=%%i
for /f %%i in ('git rev-parse --verify HEAD') do set Hash=%%i

if exist "%RunUAT%" (
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
          sh "install-v8-libs.sh"
          endlocal
     )

     Config\inifile %DefaultEngineFile% [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0
     Config\inifile %DefaultEngineFile% [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11

     "%RunUAT%" BuildCookRun -project="%project%" -targetplatform=Win64 -clientconfig=Development -cook -build -stage -pak -archive -archivedirectory="%build_dir%"

     Config\inifile %ConfigFile% [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0
     Config\inifile %ConfigFile% [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11

     Config\inifile %DefaultEngineFile% [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=
     Config\inifile %DefaultEngineFile% [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX12

     Config\inifile %ConfigFile% [/Game/UI/HUD.HUD_C] Version=%Version%
     Config\inifile %ConfigFile% [/Game/UI/HUD.HUD_C] BuildBranch=%Branch%
	Config\inifile %ConfigFile% [/Game/UI/HUD.HUD_C] Hash=%Hash%
     echo BuildNo %Version% Branch %Branch% Hash %Hash%
pause

) else (
     echo Failed to find RunUAT.bat
     echo.
     echo Please set the RunUAT environment variable to:
     echo UnrealEngine\UE_5.0EA\Engine\Build\BatchFiles\RunUAT.bat
     echo.
     pause
)
