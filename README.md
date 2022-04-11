# Supremacy
Developed with Unreal Engine 5

## Getting Started
To get started, you will need to meet the prerequisites first:

### Prerequisites
+ [Git](https://git-scm.com/download) or [GitHub Desktop](https://desktop.github.com/)
+ [Unreal Engine 5](https://www.unrealengine.com/en-US/unreal-engine-5)
+ [Visual Studio 2019](https://visualstudio.microsoft.com/downloads/)

> **_NOTE:_**  It is recommended that you have at least 100GiB of free space to install Unreal Engine 5 and clone the repository.

While you are installing VS2019 or you have already met all those prerequisites, in the Visual Studio Installer that comes along with VS2019, modify the installation to check the following:

- ASP.NET and web development ✅
  - .NET Core 3.1 Runtime (LTS) ✅
- Desktop development with C++ ✅
- Game Development with C++ ✅
  - Unreal Engine Installer (even if you have UE5 installed) ✅

And then, click install. Note that if you are using Git on Cmd or Bash, you will also need to download [Git LFS](https://git-lfs.github.com/). Install it and execute the following command on Git Cmd/Bash:

```
git lfs install
```

Once Git LFS has been installed and configured by the above step, clone the repository by executing the following command:

```
git clone https://github.com/ninja-syndicate/supremacy-gameclient.git
```

After the repository has been cloned, you may want to set your Git username and email by executing the following commands on the repository you have cloned to unless you have already done so.

```
git config user.name "Your Full Name"
git config user.email "Your Email Address"
```

Now, simply open up Supremacy.uproject in the repository, and you are ready for the development!

## Keybinds

- **SHIFT+ENTER :** Start test match *(for testing without a server)*
- **CTRL+SHIFT+ENTER :** Start test match and skip the intro animations
- **ENTER :** Toggle free camera
- **SHIFT+K :** Kill random mech
- **DELETE :** Force restart
- **X :** Toggle cursor / mouse capture
- **T :** Set random time of day
- **-/+ :** Decrease/Increase global time dialation

### Abilities (Numbers or Numpad)
- **1 :** Airstrike *(on random mech)*
- **2 :** Nuke *(on random mech)*
- **3 :** Heal *(on random mech)*
- **4 :** Robot Dogs
- **5 :** Red Mountain Reinforcements
- **6 :** Satellite Overload *(on random mech)*
- **7 :** Lower Tile *(on random mech, NOTE: The Hive map only)*
- **8 :** Fireworks *(on random mech)*
- **9 :** Move Command *(on random mech, to random map spawn point)*
- **0 :** Cancel Move Command *(on random mech)*

## Troubleshooting
**Missing C++ files after pulling, warnings/errors or certain things don't work**

Unreal sometimes fail to recognise new C++ files if you open up the project after pulling. It sometimes works and sometimes doesn't. So if there were changes to C++ files, often you will have to rebuild the project.

> **_NOTE:_**  Rebuilding the project can take quite some time and storage space, so it is recommended that you have sufficient disk space for it.

If the problem persists even after rebuilding the project, it could be the case that existing auto-generated folders are causing conflicts. So, close Unreal and try deleting automatically generated folders in the project. These are:

- Binaries
- DerivedDataCache
- Intermediate
- Saved
- Script

And then open up the project again. This will cause those folders to be re-generated.

## Coding Standard
+ [Coding Standard By Unreal](https://docs.unrealengine.com/4.27/en-US/ProductionPipelines/DevelopmentSetup/CodingStandard/)
+ [Recommended Asset Naming Convention](https://docs.unrealengine.com/4.27/en-US/ProductionPipelines/AssetNaming/)

## Configs
If you'd like to run the built game-client for development purposes, you can edit `GameUserSettings.ini` file (found in `Supremacy/Saved/Config/Windows/GameUserSettings.ini`) to reduce CPU and GPU usage:

<details>
  <summary>Recommended settings for <code>GameUserSettings.ini</code> <strong>(Click to expand)</strong></summary>
  
```ini
[ScalabilityGroups]
sg.ResolutionQuality=10
sg.ViewDistanceQuality=3
sg.AntiAliasingQuality=0
sg.ShadowQuality=0
sg.PostProcessQuality=0
sg.TextureQuality=0
sg.EffectsQuality=0
sg.FoliageQuality=0
sg.ShadingQuality=0
sg.GlobalIlluminationQuality=0
sg.ReflectionQuality=0

[/Script/Engine.GameUserSettings]
bUseVSync=False
bUseDynamicResolution=False
ResolutionSizeX=640
ResolutionSizeY=480
LastUserConfirmedResolutionSizeX=640
LastUserConfirmedResolutionSizeY=480
WindowPosX=-1
WindowPosY=-1
FullscreenMode=2
LastConfirmedFullscreenMode=2
PreferredFullscreenMode=1
Version=5
AudioQualityLevel=0
LastConfirmedAudioQualityLevel=0
FrameRateLimit=30.000000
DesiredScreenWidth=1280
bUseDesiredScreenHeight=False
DesiredScreenHeight=720
LastUserConfirmedDesiredScreenWidth=1280
LastUserConfirmedDesiredScreenHeight=720
LastRecommendedScreenWidth=-1.000000
LastRecommendedScreenHeight=-1.000000
LastCPUBenchmarkResult=-1.000000
LastGPUBenchmarkResult=-1.000000
LastGPUBenchmarkMultiplier=1.000000
bUseHDRDisplayOutput=False
HDRDisplayOutputNits=1000
```
</details>
