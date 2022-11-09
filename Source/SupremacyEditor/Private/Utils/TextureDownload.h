#pragma once

#include "HttpManager.h"
#include "HttpModule.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "SupremacyEditorModule.h"
#include "Interfaces/IHttpResponse.h"
#include "UObject/SavePackage.h"

typedef TSharedPtr<IImageWrapper> IImageWrapperPtr;

namespace StaticDataImporter
{
	static FString GetPackageNameForURL(const FString URL, const FString PackageDirectory, FString& AssetFileName)
	{
		FString PackageName = TEXT("/Game/" + PackageDirectory);
		int32 LastSlashIndex, LastPeriodIndex = 0;
		URL.FindLastChar('/', LastSlashIndex);
		URL.FindLastChar('.', LastPeriodIndex);
		FString AvatarFileName = URL.Mid(LastSlashIndex + 1);
		AvatarFileName.RemoveFromEnd(".png");
		PackageName += AvatarFileName;

		AssetFileName = AvatarFileName;
		return PackageName;
	}

	static FString GetPackageNameForURL(const FString URL, const FString PackageDirectory)
	{
		FString AvatarFileName;
		return GetPackageNameForURL(URL, PackageDirectory, AvatarFileName);
	}

	/**
	 * Downloads Image from URl and saves it as an asset
	 *
	 * @param URL URL to use.
	 * @param PackageDirectory The Directory to save the asset to.
	 */
	static UTexture2D* GetTexture2DFromURL(const FString URL, const FString PackageDirectory)
	{
		// Download image
		const auto HTTPRequest = FHttpModule::Get().CreateRequest();
		HTTPRequest->SetURL(FString(URL));
		// HTTPRequest->OnProcessRequestComplete().BindLambda([PackageDirectory](const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool Success) {
		// 	
		// });
		if (!HTTPRequest->ProcessRequest())
		{
			UE_LOG(LogSupremacyEditor, Error, TEXT("Failed to start http request for: %s"), *URL);
			return nullptr;
		}

		// Wait for response
		double LastTime = FPlatformTime::Seconds();
		while (HTTPRequest->GetStatus() == EHttpRequestStatus::Processing)
		{
			const double AppTime = FPlatformTime::Seconds();
			FHttpModule::Get().GetHttpManager().Tick(AppTime - LastTime);
			LastTime = AppTime;
			FPlatformProcess::Sleep(0.1f);
		}

		const auto Response = HTTPRequest->GetResponse();
		if (Response->GetResponseCode() != 200)
		{
			UE_LOG(LogSupremacyEditor, Error, TEXT("Failed to download: %s (%d)"), *URL, Response->GetResponseCode());
			return nullptr;
		}

		// get name
		FString AvatarFileName;
		const FString PackageName = GetPackageNameForURL(URL, PackageDirectory, AvatarFileName);

		// create package
		UPackage* Package = CreatePackage(*PackageName);
		Package->FullyLoad();

		// create texture
		const FName AvatarTextureName = MakeUniqueObjectName(Package, UTexture2D::StaticClass(), FName(*AvatarFileName));
		UTexture2D* AvatarTexture = NewObject<UTexture2D>(Package, AvatarTextureName,RF_Public | RF_Standalone | RF_MarkAsRootSet);
		AvatarTexture->AddToRoot(); // prevent garbage collection

		// get image data
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		const IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

		const TArray<uint8> ImageDataArray = Response->GetContent();
		if (!ImageWrapper.IsValid())
		{
			UE_LOG(LogSupremacyEditor, Error, TEXT("Failed to get valid image wrapper for: %s"), *URL);
			return nullptr;
		}
		if (!ImageWrapper->SetCompressed(ImageDataArray.GetData(), ImageDataArray.Num()))
		{
			UE_LOG(LogSupremacyEditor, Error, TEXT("Failed to set image wrapper for: %s"), *URL);
			return nullptr;
		}

		TArray<unsigned char> UncompressedBGRA = TArray<uint8>();
		if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			UE_LOG(LogSupremacyEditor, Error, TEXT("Failed to get image data for: %s"), *URL);
			return nullptr;
		}

		// texture settings
		const int32 TextureWidth = ImageWrapper->GetWidth();
		const int32 TextureHeight = ImageWrapper->GetHeight();

		FTexturePlatformData* AvatarTexturePlatformData = new FTexturePlatformData();
		AvatarTexturePlatformData->SizeX = TextureWidth;
		AvatarTexturePlatformData->SizeY = TextureHeight;
		AvatarTexturePlatformData->PixelFormat = PF_B8G8R8A8;
		AvatarTexture->SetPlatformData(AvatarTexturePlatformData);

		// allocate first mipmap
		FTexture2DMipMap* Mip = new FTexture2DMipMap();
		AvatarTexturePlatformData->Mips.Add(Mip);
		Mip->SizeX = AvatarTexturePlatformData->SizeX;
		Mip->SizeY = AvatarTexturePlatformData->SizeY;

		// lock the texture so it can be modified
		Mip->BulkData.Lock(LOCK_READ_WRITE);
		uint8* TextureData = static_cast<uint8*>(Mip->BulkData.Realloc(TextureWidth * TextureHeight * 4));
		FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
		Mip->BulkData.Unlock();

		// save texture
		AvatarTexture->AddToRoot();
		AvatarTexture->UpdateResource();
		bool bMarkedDirty = Package->MarkPackageDirty();
		FAssetRegistryModule::AssetCreated(AvatarTexture);

		// const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
		// FSavePackageArgs SaveArgs = FSavePackageArgs();
		// SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
		// SaveArgs.bForceByteSwapping = true;
		// SaveArgs.bWarnOfLongFilename = true;
		// SaveArgs.SaveFlags = SAVE_NoError;
		// const bool bSaved = UPackage::SavePackage(Package, AvatarTexture, *PackageFileName, SaveArgs);
		// if (bSaved)
		// 	UE_LOG(LogSupremacyEditor, Log, TEXT("Saved: %s"), *URL);

		return AvatarTexture;
	}
}
