#include "BPFL_TextureUtils.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "AssetRegistry/AssetRegistryModule.h"

UTexture2D* UBPFL_TextureUtils::CreateLinearTextureFromPixels(const FString Path, const FString TextureName, const int Width, const int Height, const bool OverwriteExisting, const TArray<FLinearColor>& Pixels) {
	IAssetTools& AssetTools = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	FString PackageName;
	FString AssetName;
	if (OverwriteExisting) {
		PackageName = Path + TextureName;
		AssetName = TextureName;
	}
	else {
		AssetTools.CreateUniqueAssetName(Path, TextureName, PackageName, AssetName);
	}

	UPackage* Package = CreatePackage(*PackageName);
	Package->FullyLoad();

	UTexture2D *Texture = NewObject<UTexture2D>(Package, *AssetName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
	Texture->AddToRoot();

	Texture->Filter = TF_Nearest;
	Texture->MipGenSettings = TMGS_NoMipmaps;
	Texture->CompressionSettings = TC_Masks;
	Texture->SRGB = 0;
	Texture->AddressX = TA_Clamp;
	Texture->AddressY = TA_Clamp;

	FTexturePlatformData *PlatformData = new FTexturePlatformData();
	PlatformData->SizeX = Width;
	PlatformData->SizeY = Height;
	PlatformData->SetNumSlices(1);
	PlatformData->PixelFormat = PF_A16B16G16R16;

	FTexture2DMipMap* Mip = new FTexture2DMipMap;
	Mip->SizeX = Width;
	Mip->SizeY = Height;
	PlatformData->Mips.Add(Mip);

	Texture->SetPlatformData(PlatformData);

	FFloat16Color* PixelData = new FFloat16Color[Width * Height];
	for (int y = 0; y < Height; y++) {
		for (int x = 0; x < Width; x++) {
			int32 Index = x + y * Width;
			PixelData[Index].B = Pixels[Index].B;
			PixelData[Index].G = Pixels[Index].G;
			PixelData[Index].R = Pixels[Index].R;
			PixelData[Index].A = Pixels[Index].A;
		}
	}

	Mip->BulkData.Lock(LOCK_READ_WRITE);
	uint8* TextureData = (uint8*)Mip->BulkData.Realloc(Width * Height * sizeof(FFloat16Color));
	FMemory::Memcpy(TextureData, (void *)PixelData, Width * Height * sizeof(FFloat16Color));
	Mip->BulkData.Unlock();

	Texture->Source.Init(Width, Height, 1, 1, ETextureSourceFormat::TSF_RGBA16F, (const uint8 *)PixelData);

	Texture->UpdateResource();
	Package->MarkPackageDirty();
	FAssetRegistryModule::AssetCreated(Texture);

	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	UPackage::SavePackage(Package, Texture, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr, true, true, SAVE_NoError);

	UE_LOG(LogTemp, Error, TEXT("Created linear texture: %s"), *PackageName);

	return Texture;
}

TArray<FLinearColor> UBPFL_TextureUtils::GetPixelsFromLinearTexture(UTexture2D* Texture) {
	TArray<FLinearColor> Colors;

	if (!Texture) return Colors;

	FTexturePlatformData* PlatformData = Texture->GetPlatformData();
	const FFloat16Color*Data = (const FFloat16Color*) PlatformData->Mips[0].BulkData.LockReadOnly();

	int Width = PlatformData->Mips[0].SizeX;
	int Height = PlatformData->Mips[0].SizeY;

	for (int y = 0; y < Height; y++) {
		for (int x = 0; x < Width; x++) {
			FLinearColor Color;
			Color.B = Data[x + y * Width].B;
			Color.G = Data[x + y * Width].G;
			Color.R = Data[x + y * Width].R;
			Color.A = Data[x + y * Width].A;
			Colors.Emplace(Color);
		}
	}

	PlatformData->Mips[0].BulkData.Unlock();

	return Colors;
}

void UBPFL_TextureUtils::FloatToShort(float Value, uint8& A, uint8& B) {
	uint16 Encoded;
	FGenericPlatformMath::StoreHalf(&Encoded, Value);

	union {
		struct {
			uint8 A;
			uint8 B;
		};
		uint16 E;
	} Data;

	Data.E = Encoded;

	A = Data.A;
	B = Data.B;
}

float UBPFL_TextureUtils::ShortToFloat(uint8 A, uint8 B) {
	union {
		struct {
			uint8 A;
			uint8 B;
		};
		uint16 E;
	} Data;

	if (FGenericPlatformProperties::IsLittleEndian()) {
		Data.A = A;
		Data.B = B;
	}
	else {
		Data.A = B;
		Data.B = A;
	}

	return FGenericPlatformMath::LoadHalf(&Data.E);
}