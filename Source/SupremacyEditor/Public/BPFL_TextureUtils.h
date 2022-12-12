#pragma once

#include "BPFL_TextureUtils.generated.h"

UCLASS()
class SUPREMACYEDITOR_API UBPFL_TextureUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static UTexture2D *CreateLinearTextureFromPixels(const FString Path, const FString TextureName, const int Width, const int Height, const bool OverwriteExisting, const TArray<FLinearColor>& Pixels);

	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static TArray<FLinearColor> GetPixelsFromLinearTexture(UTexture2D* Texture);

	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static void FloatToShort(float Value, uint8& A, uint8& B);

	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static float ShortToFloat(uint8 A, uint8 B);
};
