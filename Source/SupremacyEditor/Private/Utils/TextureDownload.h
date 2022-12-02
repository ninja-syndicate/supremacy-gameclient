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
	static bool IsPowerOfTwo(const int X)
	{
		return (X != 0) && ((X & (X - 1)) == 0);
	}
	
	static FString GetPackageNameForURL(const FString URL, const FString PackageDirectory, FString& AssetFileName, EImageFormat& ImageFormat)
	{
		FString PackageName = TEXT("/Game/" + PackageDirectory);
		int32 LastSlashIndex, LastPeriodIndex = 0;
		URL.FindLastChar('/', LastSlashIndex);
		URL.FindLastChar('.', LastPeriodIndex);
		FString TextureFileName = URL.Mid(LastSlashIndex + 1);

		const FString Extension = FPaths::GetExtension(TextureFileName, true);
		if (Extension == "jpg")
			ImageFormat = EImageFormat::JPEG;
		else
			ImageFormat = EImageFormat::PNG;
		
		TextureFileName.RemoveFromEnd(Extension);
		PackageName += TextureFileName;

		AssetFileName = TextureFileName;
		return PackageName;
	}

	static FString GetPackageNameForURL(const FString URL, const FString PackageDirectory, EImageFormat& ImageFormat)
	{
		FString TextureFileName;
		return GetPackageNameForURL(URL, PackageDirectory, TextureFileName, ImageFormat);
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
		FString TextureFileName;
		EImageFormat ImageFormat;
		const FString PackageName = GetPackageNameForURL(URL, PackageDirectory, TextureFileName, ImageFormat);

		// create package
		UPackage* Package = CreatePackage(*PackageName);
		Package->FullyLoad();

		// create texture
		const FName TextureTextureName = MakeUniqueObjectName(Package, UTexture2D::StaticClass(), FName(*TextureFileName));
		UTexture2D* TextureTexture = NewObject<UTexture2D>(Package, TextureTextureName,RF_Public | RF_Standalone | RF_MarkAsRootSet);
		TextureTexture->AddToRoot(); // prevent garbage collection

		// get image data
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		const IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);

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

		TArray<uint8> UncompressedBGRA = TArray<uint8>();
		if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			UE_LOG(LogSupremacyEditor, Error, TEXT("Failed to get image data for: %s"), *URL);
			return nullptr;
		}

		// texture settings
		const int32 TextureWidth = ImageWrapper->GetWidth();
		const int32 TextureHeight = ImageWrapper->GetHeight();
		if (TextureWidth != TextureHeight || !(IsPowerOfTwo(TextureWidth)))
		{
			TextureTexture->MipGenSettings = TMGS_LeaveExistingMips;
			TextureTexture->CompressionSettings = TC_EditorIcon;
			//UE_LOG(LogSupremacyEditor, Error, TEXT("Failed to create texture due to non-power of 2 texture size: %s (%dx%d)"), *URL, TextureWidth, TextureHeight);
		}

		FTexturePlatformData* TextureTexturePlatformData = new FTexturePlatformData();
		TextureTexturePlatformData->SizeX = TextureWidth;
		TextureTexturePlatformData->SizeY = TextureHeight;
		TextureTexturePlatformData->SetNumSlices(1);
		TextureTexturePlatformData->PixelFormat = PF_B8G8R8A8;
		TextureTexture->SetPlatformData(TextureTexturePlatformData);

		// allocate first mipmap
		FTexture2DMipMap* Mip = new FTexture2DMipMap();
		TextureTexturePlatformData->Mips.Add(Mip);
		Mip->SizeX = TextureWidth;
		Mip->SizeY = TextureHeight;

		// lock the texture so it can be modified
		Mip->BulkData.Lock(LOCK_READ_WRITE);
		const auto Pixels = UncompressedBGRA.GetData();
		uint8* TextureData = static_cast<uint8*>(Mip->BulkData.Realloc(TextureWidth * TextureHeight * 4));
		FMemory::Memcpy(TextureData, Pixels, UncompressedBGRA.Num());
		Mip->BulkData.Unlock();

		// save texture
		TextureTexture->Source.Init(TextureWidth, TextureHeight, 1, 1, TSF_BGRA8, Pixels);
		
		TextureTexture->UpdateResource();
		bool bMarkedDirty = Package->MarkPackageDirty();
		FAssetRegistryModule::AssetCreated(TextureTexture);

		const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
		FSavePackageArgs SaveArgs = FSavePackageArgs();
		SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
		SaveArgs.bForceByteSwapping = true;
		SaveArgs.bWarnOfLongFilename = true;
		SaveArgs.SaveFlags = SAVE_NoError;
		if (UPackage::SavePackage(Package, TextureTexture, *PackageFileName, SaveArgs))
			UE_LOG(LogSupremacyEditor, Log, TEXT("Saved: %s"), *URL);

		return TextureTexture;
	}
}
