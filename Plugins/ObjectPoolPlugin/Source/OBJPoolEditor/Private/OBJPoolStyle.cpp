//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///			Copyright 2019 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OBJPoolStyle.h"
#include "Styling/SlateStyle.h"
#include "OBJPoolEditor_Shared.h"
#include "Interfaces/IPluginManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define PLUGIN_BRUSH(RelativePath,...) FSlateImageBrush(FOBJPoolStyle::InContent(RelativePath,TEXT(".png")),__VA_ARGS__)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TSharedPtr<FSlateStyleSet> FOBJPoolStyle::StyleSet = nullptr;
TSharedPtr<ISlateStyle> FOBJPoolStyle::Get() {return StyleSet;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FString FOBJPoolStyle::InContent(const FString &RelativePath, const TCHAR* Extension) {
	static FString Content = IPluginManager::Get().FindPlugin(TEXT("ObjectPool"))->GetContentDir();
	return (Content/RelativePath)+Extension;
}

FName FOBJPoolStyle::GetStyleSetName() {
	static FName StyleName(TEXT("OBJPoolStyle"));
	return StyleName;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FOBJPoolStyle::Initialize() {
	if (StyleSet.IsValid()) {return;}
	//
	const FVector2D Icon16x16(16.f,16.f);
	const FVector2D Icon128x128(128.f,128.f);
	//
	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("ObjectPool"))->GetContentDir());
	//
	StyleSet->Set("ClassIcon.PawnPool", new PLUGIN_BRUSH(TEXT("Icons/Pawn_16x"),Icon16x16));
	StyleSet->Set("ClassIcon.ObjectPool", new PLUGIN_BRUSH(TEXT("Icons/Pool_16x"),Icon16x16));
	StyleSet->Set("ClassIcon.CharacterPool", new PLUGIN_BRUSH(TEXT("Icons/Character_16x"),Icon16x16));
	StyleSet->Set("ClassIcon.SharedObjectPool", new PLUGIN_BRUSH(TEXT("Icons/Shared_16x"),Icon16x16));
	StyleSet->Set("ClassIcon.PooledProjectile", new PLUGIN_BRUSH(TEXT("Icons/Projectile_16x"),Icon16x16));
	StyleSet->Set("ClassIcon.PooledSplineProjectile", new PLUGIN_BRUSH(TEXT("Icons/SplineProjectile_16x"),Icon16x16));
	//
	StyleSet->Set("ClassThumbnail.PawnPool", new PLUGIN_BRUSH(TEXT("Icons/Pawn_128x"),Icon128x128));
	StyleSet->Set("ClassThumbnail.ObjectPool", new PLUGIN_BRUSH(TEXT("Icons/Pool_128x"),Icon128x128));
	StyleSet->Set("ClassThumbnail.CharacterPool", new PLUGIN_BRUSH(TEXT("Icons/Character_128x"),Icon128x128));
	StyleSet->Set("ClassThumbnail.SharedObjectPool", new PLUGIN_BRUSH(TEXT("Icons/Shared_128x"),Icon128x128));
	StyleSet->Set("ClassThumbnail.PooledProjectile", new PLUGIN_BRUSH(TEXT("Icons/Projectile_128x"),Icon128x128));
	StyleSet->Set("ClassThumbnail.PooledSplineProjectile", new PLUGIN_BRUSH(TEXT("Icons/SplineProjectile_128x"),Icon128x128));
	//
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
};

void FOBJPoolStyle::Shutdown() {
	if (StyleSet.IsValid()) {
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}///
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef PLUGIN_BRUSH

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
