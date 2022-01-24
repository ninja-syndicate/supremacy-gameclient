# Supremacy
Developed with Unreal Engine 5

## Getting Started
To get started, you will need to meet the prerequisites first:

### Prerequisites
+ [Git](https://git-scm.com/download) or [GitHub Desktop](https://desktop.github.com/)
+ [Unreal Engine 5](https://www.unrealengine.com/en-US/unreal-engine-5)
+ [Visual Studio 2019/2022](https://visualstudio.microsoft.com/downloads/)

> **_NOTE:_**  It is recommended that you have at least 100GiB of free space to install Unreal Engine 5 and clone the repository.

While you are installing VS2019/2022 or you have already met all those prerequisites, in the Visual Studio Installer that comes along with VS2019/2022, modify the installation to check the following:

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

## Coding Standard
+ [Coding Standard By Unreal](https://docs.unrealengine.com/4.27/en-US/ProductionPipelines/DevelopmentSetup/CodingStandard/)
+ [Recommended Asset Naming Convention](https://docs.unrealengine.com/4.27/en-US/ProductionPipelines/AssetNaming/)