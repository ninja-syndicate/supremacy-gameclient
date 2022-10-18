# Supremacy
Developed with Unreal Engine 5

## Getting Started
To get started, you will need to meet the prerequisites first:

### Prerequisites
+ [Git](https://git-scm.com/download) or [GitHub Desktop](https://desktop.github.com/)
+ [Unreal Engine 5](https://www.unrealengine.com/en-US/unreal-engine-5)
+ [Visual Studio 2019](https://visualstudio.microsoft.com/downloads/)

> **_NOTE:_**  It is recommended that you have at least 300GiB of free space to install Unreal Engine 5 and clone the repository.

While you are installing VS2019 or you have already met all those prerequisites, in the Visual Studio Installer that comes along with VS2019, modify the 
installation to check the following:

- ASP.NET and web development ✅
  - .NET Core 3.1 Runtime (LTS) ✅
- Desktop development with C++ ✅
- Game Development with C++ ✅
  - Unreal Engine Installer (even if you have UE5 installed) ✅

And then, click install.

### Git

Note that if you are using Git on Cmd or Bash, you will also need to download [Git LFS](https://git-lfs.github.com/). Install it and execute the following 
command on Git Cmd/Bash:

```
git lfs install
```

Once Git LFS has been installed and configured by the above step, clone the repository by executing the following command:

> **_NOTE:_** Cloning the repository can take very long time. If you already have a local copy of supremacy-gameclient, you can skip this clone step. If your
> local copy of supremacy-gameclient contains auto-generated files that were built on other PC, you will need to regenerate them. See 
> [Troubleshooting](#Troubleshooting) section on how to clean up the auto-generated files.

```
git clone https://github.com/ninja-syndicate/supremacy-gameclient.git
```

After the repository has been cloned, you may want to set your Git username and email by executing the following commands on the repository you have cloned to 
unless you have already done so.

```
git config user.name "Your Full Name"
git config user.email "Your Email Address"
```

### Plugins

The following Unreal Engine Plugins need to be installed. Find them in the Library tab of the Epic Launcher, under Vault.

*( Note: You'll need to be signed in with the company's Epic Account to have access to paid assets/plugins. )*

- Quixel Bridge
- [LE Extended Standard Library](https://www.unrealengine.com/marketplace/en-US/product/low-entry-extended-standard-library)
- [BlueprintWebSocket](https://www.unrealengine.com/marketplace/en-US/product/blueprintwebsocket)
- [JSONParser](https://www.unrealengine.com/marketplace/en-US/product/jsonparser)
- [EasyBallistics Plugin](https://www.unrealengine.com/marketplace/en-US/product/easyballistics-plugin)
- [Actor Pool Manager Plugin](https://www.unrealengine.com/marketplace/en-US/product/actor-pool-manager-plugin)
- [Flying Navigation System](https://www.unrealengine.com/marketplace/en-US/product/flying-navigation-system)

[UnrealJS](https://github.com/getnamo/UnrealJs) is also used but is included in the repo. It does however require the V8 library to be installed which can be 
done via `setup.bat`. If `setup.bat` doesn't work due to `sh` command not being recognised, navigate to `Plugins/UnrealJs` directory and run 
`install-v8-libs.bat` instead.

Once you have finished installing all the necessary plugins, right click `Supremacy.uproject`, click "Show More Options" if you are using Windows 11, and click
"Generate Visual Studio Project files". Then, open the `Supremacy.sln`, click "Build" in the menu bar and click "Build Solution". Once the project is built, you
can simply open up `Supremacy.uproject` in the repository, and you are ready for the development!

### Recommended Workflow
#### Turn-off Editor Auto Save Option
Since Unreal's blueprints are binary, it is recommended to turn off auto-save option in the Editor Preferences setting. Sometimes, when this auto-save option is
enabled, Unreal will save blueprints that are open even if there are no changes. This can make it hard to track which files have actually changed and more 
time-consuming to resolve merge conflicts.

#### Make a GitHub Issue and Assign Yourself
Before making changes to the existing files or work on a new feature, make a GitHub issue if it doesn't already exist and assign yourself. This will help others
know which conflicts are expected and possibly work on something else meanwhile. 

## Keybinds

- **SHIFT+ENTER :** Show Main Menu / Start test match if on specific map  *(for testing without a server)*
- **CTRL+SHIFT+ENTER :** Start test match and skip the intro animations
- **CTRL+SHIFT+R:** Load battle from clipboard (text w/ battle commands on each line)
- **ENTER :** Toggle free camera
- **SHIFT+K :** Kill random mech
- **DELETE :** Force restart
- **X :** Toggle cursor / mouse capture
- **T :** Set random time of day
- **-/+ :** Decrease/Increase global time dilation
- **CTRL+Q:** Possess Red Mountain Mech
- **CTRL+W:** Possess Boston Mech
- **CTRL+E:** Possess Zaibatsu Mech
- **SHIFT+H:** Toggle Health Bars
- **SHIFT+z:** Force Next Battle Zone
- **CTRL+ALT+SHIFT+BACKSPACE:** Force Crash
- **CTRL+ALT+SHIFT+\\:** Force Not Responding

### Abilities (Numbers or Numpad)
- **1 :** Airstrike *(on random mech)*
- **2 :** Nuke *(on random mech)*
- **3 :** Heal *(on random mech)*
- **SHIFT+3 :** Shield Buff *(on random mech)*
- **ALT+3 :** Ammo *(on random mech)*
- **4 :** Robot Dogs
- **5 :** Red Mountain Reinforcements
- **SHIFT+5 :** Mini Mech
- **ALT+5 :** Turret
- **6 :** Satellite Overload *(on random mech)*
- **7 :** Landmines *(on random mech)*
- **8 :** EMP *(on random mech)*
- **9 :** Hacker Drone *(on random mech)*
- **SHIFT+9 :** Camera Drone *(on random mech)*
- **0 :** Incognito *(on random mech)*
- **SHIFT+0 :** Blackout *(on random mech)*
- **F :** Fireworks *(on random mech)*
- **G :** Move Command *(on random mech, to random map spawn point)*
- **SHIFT+G :** Cancel Move Command *(on random mech)*
- **H :** Lower Tile *(on random mech, NOTE: The Hive map only)*

## Troubleshooting
**Missing C++ files after pulling, warnings/errors or certain things don't work**

Unreal sometimes fail to recognise new C++ files if you open up the project after pulling. It sometimes works and sometimes doesn't. So if there were changes to
C++ files, often you will have to rebuild the project.

> **_NOTE:_**  Rebuilding the project can take quite some time and storage space, so it is recommended that you have sufficient disk space for it.

**Cleaning up auto-generated files**

If the problem persists even after rebuilding the project, it could be the case that existing auto-generated folders are causing conflicts. So, close Unreal and
try deleting automatically generated folders in the project. These are:

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
If you'd like to run the built game-client for development purposes, you can edit `GameUserSettings.ini` file (found in 
`Supremacy/Saved/Config/Windows/GameUserSettings.ini`) to reduce CPU and GPU usage:

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

## Battle Replaying
You can emulate incoming messages from the server to "replay" a previous battle. With a list of battles commands in your clipboard you can use **CTRL+SHIFT+R** 
to start a match that uses them.

Each line is a battle command; starting with `BATTLE:INIT`, each line after that starts with the delay in seconds followed by a `|`.

<details>
  <summary>Example Battle Replay</summary>

```ini
{"battleCommand":"BATTLE:INIT","payload":{"battleID":"989e374e-631a-4a34-92a4-1ad562d10f4c","mapName":"DesertCity","warMachines":[{"id":"c306678a-0beb-428e-a781-afa69acf945d","hash":"kG0YeoPE2w","participantID":0,"factionID":"7c6dde21-b067-46cf-9e56-155c88a520e2","maxHealth":1000,"health":1000,"maxShield":1300,"shield":1300,"energy":0,"stat":null,"imageAvatar":"https://afiles.ninja-cdn.com/passport/genesis/avatar/boston-cybernetics_law-enforcer-x-1000_dune_avatar.png","position":null,"rotation":0,"ownedByID":"a104bdc5-9fc0-4f27-a5a0-b66807509f08","name":"Ur Gf's BF","description":null,"externalUrl":"","image":"https://afiles.ninja-cdn.com/passport/genesis/img/boston-cybernetics_law-enforcer-x-1000_dune.png","model":"XFVS","skin":"Dune","shieldRechargeRate":80,"speed":2750,"durability":1000,"powerGrid":1,"cpu":1,"weaponHardpoint":2,"turretHardpoint":0,"utilitySlots":1,"faction":{"id":"7c6dde21-b067-46cf-9e56-155c88a520e2","label":"Boston Cybernetics","theme":{"primary":"#428EC1","secondary":"#FFFFFF","background":"#080C12"}},"weaponNames":["Boston Cybernetics Plasma Rifle","Boston Cybernetics Sword"],"abilities":null,"tier":"MEGA"},{"id":"991fff09-ed41-4268-b08a-1ec1b3fa43a2","hash":"wmY1jwa5vy","participantID":0,"factionID":"7c6dde21-b067-46cf-9e56-155c88a520e2","maxHealth":1000,"health":1000,"maxShield":1300,"shield":1300,"energy":0,"stat":null,"imageAvatar":"https://afiles.ninja-cdn.com/passport/genesis/avatar/boston-cybernetics_law-enforcer-x-1000_dune_avatar.png","position":null,"rotation":0,"ownedByID":"bf5ccac4-9242-4203-85bb-5cf68611065a","name":"JNKDOG","description":null,"externalUrl":"","image":"https://afiles.ninja-cdn.com/passport/genesis/img/boston-cybernetics_law-enforcer-x-1000_dune.png","model":"XFVS","skin":"Dune","shieldRechargeRate":80,"speed":2750,"durability":1000,"powerGrid":1,"cpu":1,"weaponHardpoint":2,"turretHardpoint":0,"utilitySlots":1,"faction":{"id":"7c6dde21-b067-46cf-9e56-155c88a520e2","label":"Boston Cybernetics","theme":{"primary":"#428EC1","secondary":"#FFFFFF","background":"#080C12"}},"weaponNames":["Boston Cybernetics Plasma Rifle","Boston Cybernetics Sword"],"abilities":null,"tier":"MEGA"},{"id":"29ba5047-25c4-4763-b7cd-7c9612fba07f","hash":"o6Zr02m5w3","participantID":0,"factionID":"7c6dde21-b067-46cf-9e56-155c88a520e2","maxHealth":1000,"health":1000,"maxShield":1300,"shield":1300,"energy":0,"stat":null,"imageAvatar":"https://afiles.ninja-cdn.com/passport/genesis/avatar/boston-cybernetics_law-enforcer-x-1000_dune_avatar.png","position":null,"rotation":0,"ownedByID":"fff4c8f7-e935-4855-b41f-a42289886ab6","name":"ENSI","description":null,"externalUrl":"","image":"https://afiles.ninja-cdn.com/passport/genesis/img/boston-cybernetics_law-enforcer-x-1000_dune.png","model":"XFVS","skin":"Dune","shieldRechargeRate":80,"speed":2750,"durability":1000,"powerGrid":1,"cpu":1,"weaponHardpoint":2,"turretHardpoint":0,"utilitySlots":1,"faction":{"id":"7c6dde21-b067-46cf-9e56-155c88a520e2","label":"Boston Cybernetics","theme":{"primary":"#428EC1","secondary":"#FFFFFF","background":"#080C12"}},"weaponNames":["Boston Cybernetics Plasma Rifle","Boston Cybernetics Sword"],"abilities":null,"tier":"MEGA"},{"id":"693549b7-a875-40a9-9a99-7be0eaf226c4","hash":"mr9oGQEng","participantID":0,"factionID":"880db344-e405-428d-84e5-6ebebab1fe6d","maxHealth":1750,"health":1750,"maxShield":1050,"shield":1050,"energy":0,"stat":null,"imageAvatar":"https://afiles.ninja-cdn.com/passport/genesis/avatar/red-mountain_olympus-mons-ly07_evo_avatar.png","position":null,"rotation":0,"ownedByID":"15aa2ad7-2745-4e97-ae80-feb44d9dc171","name":"Need2Win2FeedKids","description":null,"externalUrl":"","image":"https://afiles.ninja-cdn.com/passport/genesis/img/red-mountain_olympus-mons-ly07_evo.png","model":"BXSD","skin":"EVA-02","shieldRechargeRate":100,"speed":1900,"durability":1750,"powerGrid":1,"cpu":1,"weaponHardpoint":2,"turretHardpoint":2,"utilitySlots":1,"faction":{"id":"880db344-e405-428d-84e5-6ebebab1fe6d","label":"Zaibatsu Heavy Industries","theme":{"primary":"#FFFFFF","secondary":"#000000","background":"#0D0D0D"}},"weaponNames":["Auto Cannon","Auto Cannon"],"abilities":null,"tier":"EXOTIC"},{"id":"34bdbd5e-c568-45bc-9feb-8200d5730087","hash":"QPIYRaynR","participantID":0,"factionID":"880db344-e405-428d-84e5-6ebebab1fe6d","maxHealth":1690,"health":1690,"maxShield":1050,"shield":1050,"energy":0,"stat":null,"imageAvatar":"https://afiles.ninja-cdn.com/passport/genesis/avatar/red-mountain_olympus-mons-ly07_gold_avatar.png","position":null,"rotation":0,"ownedByID":"15aa2ad7-2745-4e97-ae80-feb44d9dc171","name":"Smex.ELEM","description":null,"externalUrl":"","image":"https://afiles.ninja-cdn.com/passport/genesis/img/red-mountain_olympus-mons-ly07_gold.png","model":"BXSD","skin":"Gold","shieldRechargeRate":100,"speed":1900,"durability":1690,"powerGrid":1,"cpu":1,"weaponHardpoint":2,"turretHardpoint":2,"utilitySlots":1,"faction":{"id":"880db344-e405-428d-84e5-6ebebab1fe6d","label":"Zaibatsu Heavy Industries","theme":{"primary":"#FFFFFF","secondary":"#000000","background":"#0D0D0D"}},"weaponNames":["Auto Cannon","Auto Cannon"],"abilities":null,"tier":"LEGENDARY"},{"id":"334bb730-d1f0-4ad7-bb5b-1c369ce354a3","hash":"82lEa2BZbV","participantID":0,"factionID":"880db344-e405-428d-84e5-6ebebab1fe6d","maxHealth":1100,"health":1100,"maxShield":1100,"shield":1100,"energy":0,"stat":null,"imageAvatar":"https://afiles.ninja-cdn.com/passport/genesis/avatar/zaibatsu_tenshi-mk1_black-digi_avatar.png","position":null,"rotation":0,"ownedByID":"15aa2ad7-2745-4e97-ae80-feb44d9dc171","name":"Elemental Esports","description":null,"externalUrl":"","image":"https://afiles.ninja-cdn.com/passport/genesis/img/zaibatsu_tenshi-mk1_black-digi.png","model":"WREX","skin":"BlackDigi","shieldRechargeRate":100,"speed":2500,"durability":1100,"powerGrid":1,"cpu":1,"weaponHardpoint":2,"turretHardpoint":2,"utilitySlots":1,"faction":{"id":"880db344-e405-428d-84e5-6ebebab1fe6d","label":"Zaibatsu Heavy Industries","theme":{"primary":"#FFFFFF","secondary":"#000000","background":"#0D0D0D"}},"weaponNames":["Zaibatsu Heavy Industries Sniper Rifle","Zaibatsu Heavy Industries Laser Sword"],"abilities":null,"tier":"MEGA"},{"id":"af596157-bbf7-43e4-b446-a1edd96ff4fe","hash":"l1EjB77EAX","participantID":0,"factionID":"98bf7bb3-1a7c-4f21-8843-458d62884060","maxHealth":1750,"health":1750,"maxShield":1050,"shield":1050,"energy":0,"stat":null,"imageAvatar":"https://afiles.ninja-cdn.com/passport/genesis/avatar/red-mountain_olympus-mons-ly07_nautical_avatar.png","position":null,"rotation":0,"ownedByID":"bc4251e5-4a0f-49e5-bd41-a79c4fed1a42","name":"Blue boy","description":null,"externalUrl":"","image":"https://afiles.ninja-cdn.com/passport/genesis/img/red-mountain_olympus-mons-ly07_nautical.png","model":"BXSD","skin":"Nautical","shieldRechargeRate":100,"speed":1900,"durability":1750,"powerGrid":1,"cpu":1,"weaponHardpoint":2,"turretHardpoint":2,"utilitySlots":1,"faction":{"id":"98bf7bb3-1a7c-4f21-8843-458d62884060","label":"Red Mountain Offworld Mining Corporation","theme":{"primary":"#C24242","secondary":"#FFFFFF","background":"#120E0E"}},"weaponNames":["Red Mountain Offworld Mining Corporation Auto Cannon","Red Mountain Offworld Mining Corporation Auto Cannon"],"abilities":null,"tier":"ULTRA_RARE"},{"id":"81aa97ed-a074-4240-a2e0-eda43842918e","hash":"vTO5V8EnR","participantID":0,"factionID":"98bf7bb3-1a7c-4f21-8843-458d62884060","maxHealth":1750,"health":1750,"maxShield":1050,"shield":1050,"energy":0,"stat":null,"imageAvatar":"https://afiles.ninja-cdn.com/passport/genesis/avatar/red-mountain_olympus-mons-ly07_nautical_avatar.png","position":null,"rotation":0,"ownedByID":"f80fc806-0091-4b6a-be67-6cefd4f33dfe","name":"HAN SOLO","description":null,"externalUrl":"","image":"https://afiles.ninja-cdn.com/passport/genesis/img/red-mountain_olympus-mons-ly07_nautical.png","model":"BXSD","skin":"Nautical","shieldRechargeRate":100,"speed":1900,"durability":1750,"powerGrid":1,"cpu":1,"weaponHardpoint":2,"turretHardpoint":2,"utilitySlots":1,"faction":{"id":"98bf7bb3-1a7c-4f21-8843-458d62884060","label":"Red Mountain Offworld Mining Corporation","theme":{"primary":"#C24242","secondary":"#FFFFFF","background":"#120E0E"}},"weaponNames":["Auto Cannon","Auto Cannon"],"abilities":null,"tier":"ULTRA_RARE"},{"id":"45426e36-ed73-48ed-b448-ca629f3e94e0","hash":"4auMNIlng","participantID":0,"factionID":"98bf7bb3-1a7c-4f21-8843-458d62884060","maxHealth":1590,"health":1590,"maxShield":1000,"shield":1000,"energy":0,"stat":null,"imageAvatar":"https://afiles.ninja-cdn.com/passport/genesis/avatar/red-mountain_olympus-mons-ly07_gold_avatar.png","position":null,"rotation":0,"ownedByID":"543dc8a3-1c20-4a60-b2b5-c92c78376564","name":"Tom Crown Spicy Mech","description":null,"externalUrl":"","image":"https://afiles.ninja-cdn.com/passport/genesis/img/red-mountain_olympus-mons-ly07_gold.png","model":"BXSD","skin":"Gold","shieldRechargeRate":80,"speed":1750,"durability":1590,"powerGrid":1,"cpu":1,"weaponHardpoint":2,"turretHardpoint":2,"utilitySlots":1,"faction":{"id":"98bf7bb3-1a7c-4f21-8843-458d62884060","label":"Red Mountain Offworld Mining Corporation","theme":{"primary":"#C24242","secondary":"#FFFFFF","background":"#120E0E"}},"weaponNames":["Auto Cannon","Auto Cannon"],"abilities":null,"tier":"LEGENDARY"}],"SpawnedAI":null,"id":"989e374e-631a-4a34-92a4-1ad562d10f4c","game_map_id":"4ea7c20f-08b4-406f-9838-c27beb8a9151","started_at":"2022-05-05T08:23:26.677848002+08:00","ended_at":null,"battle_number":0,"started_battle_seconds":null,"ended_battle_seconds":null}}
57|{"battleCommand":"BATTLE:ABILITY","payload":{"eventID":"195712e4-0e4c-458b-bae2-d6ffd4de2efa","gameClientAbilityID":7,"participantID":3,"warMachineHash":"o6Zr02m5w3","isTriggered":true,"triggeredByUsername":null,"gameLocation":{"x":0,"y":0}}}
15|{"battleCommand":"BATTLE:ABILITY","payload":{"eventID":"bfa0c495-bb00-4324-8ba1-d67ba27668df","gameClientAbilityID":1,"factionID":"7c6dde21-b067-46cf-9e56-155c88a520e2","isTriggered":true,"TriggeredByUserID":"a104bdc5-9fc0-4f27-a5a0-b66807509f08","triggeredByUsername":"beepbooppeep","triggeredOnCellX":15,"triggeredOnCellY":13,"gameLocation":{"x":-9000,"y":-13000}}}
13|{"battleCommand":"BATTLE:ABILITY","payload":{"eventID":"fab01394-d4c6-45cb-b162-cec52b938dea","gameClientAbilityID":7,"participantID":9,"warMachineHash":"4auMNIlng","isTriggered":true,"triggeredByUsername":null,"gameLocation":{"x":0,"y":0}}}
83|{"battleCommand":"BATTLE:ABILITY","payload":{"eventID":"8e800e27-d54c-44c2-aa10-6cff17169db2","gameClientAbilityID":7,"participantID":4,"warMachineHash":"mr9oGQEng","isTriggered":true,"triggeredByUsername":null,"gameLocation":{"x":0,"y":0}}}
22|{"battleCommand":"BATTLE:ABILITY","payload":{"eventID":"8cc44de9-837f-415e-8fb4-e044706aede8","gameClientAbilityID":7,"participantID":8,"warMachineHash":"vTO5V8EnR","isTriggered":true,"triggeredByUsername":null,"gameLocation":{"x":0,"y":0}}}
140|{"battleCommand":"BATTLE:ABILITY","payload":{"eventID":"6e4d504d-abb1-439a-a9b7-d0718a80d276","gameClientAbilityID":7,"participantID":7,"warMachineHash":"l1EjB77EAX","isTriggered":true,"triggeredByUsername":null,"gameLocation":{"x":0,"y":0}}}
```
</details>
