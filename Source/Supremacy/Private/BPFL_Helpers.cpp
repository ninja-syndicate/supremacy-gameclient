// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFL_Helpers.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "GenericPlatform/GenericPlatformApplicationMisc.h"
#include "Weapons/Weapon.h"
#include "Weapons/WeaponizedInterface.h"
#include "Weapons/Components/WeaponAmmunitionComponent.h"
#include "Mechs/PowerCoreBase.h"

void UBPFL_Helpers::ParseNetMessage(const TArray<uint8> Bytes, uint8& Type, FString& Message)
{
	Type = Bytes[0];
	if (Bytes.Num() > 1)
	{
		FString Broken = BytesToString(&Bytes[1],  Bytes.Num()-1);
		for (int i = 0; i < Broken.Len(); i++)
		{
			const TCHAR c = Broken[i] - 1;
			Message.AppendChar(c);
		}
	}
}

TArray<uint8> UBPFL_Helpers::ConvertIntToBytes(const int Input)
{
	TArray<uint8> Bytes = TArray<uint8>();
	Bytes.Emplace((Input >> 24) & 0xFF);
	Bytes.Emplace((Input >> 16) & 0xFF);
	Bytes.Emplace((Input >> 8) & 0xFF);
	Bytes.Emplace((Input >> 0) & 0xFF);
	return Bytes;
}

TArray<uint8> UBPFL_Helpers::ConvertUInt16ToBytes(const uint16 Input)
{
	TArray<uint8> Bytes = TArray<uint8>();
	Bytes.Emplace(Input >> 8);
	Bytes.Emplace(Input >> 0);
	return Bytes;
}

void UBPFL_Helpers::PackWarMachineUpdate(const uint8 Number, const int X, const int Y, const int Yaw, const int Health, const int Shield, const int Energy, 
										 const TArray<bool> DiffArray, TArray<uint8>& Bytes)
{
	Bytes = TArray<uint8>();
	Bytes.Emplace(Number);
	Bytes.Emplace(PackBooleansIntoByte(DiffArray));

	if (DiffArray[0])
	{
		Bytes.Append(ConvertIntToBytes(X));
		Bytes.Append(ConvertIntToBytes(Y));
		Bytes.Append(ConvertIntToBytes(Yaw));
	}
	if (DiffArray[1])
		Bytes.Append(ConvertIntToBytes(Health));
	if (DiffArray[2])
		Bytes.Append(ConvertIntToBytes(Shield));
	if (DiffArray[3])
		Bytes.Append(ConvertIntToBytes(Energy));
}

void UBPFL_Helpers::PackWarMachineWeaponUpdates(UObject* WarMachine, const int PreviousTotalAmmo, TArray<uint8>& Bytes, int& TotalAmmo) {
	// Get Weapons
	if (!WarMachine->GetClass()->ImplementsInterface(UWeaponizedInterface::StaticClass())) return;
	const IWeaponizedInterface* Weaponized = Cast<IWeaponizedInterface>(WarMachine);
	TArray<AWeapon*> Weapons;
	Weaponized->Execute_GetWeapons(WarMachine, Weapons);
	
	if (Weapons.IsEmpty()) return;

	// weapon count
	TArray<uint8> OutBytes = TArray<uint8>();
	OutBytes.Emplace(static_cast<uint8>(Weapons.Num()));

	for (int i = 0; i < Weapons.Num(); i++)
	{
		// Get Ammo
		UActorComponent* Comp = Weapons[i]->GetComponentByClass(UWeaponAmmunitionComponent::StaticClass());
		const UWeaponAmmunitionComponent* AmmoComp = Cast<UWeaponAmmunitionComponent>(Comp);

		TotalAmmo += AmmoComp->GetAmmo();

		// socket index + ammo count
		OutBytes.Emplace(static_cast<uint8>(i));
		OutBytes.Append(ConvertIntToBytes(AmmoComp->GetAmmo()));
	}

	// Total ammo changed - return packed bytes
	if (TotalAmmo != PreviousTotalAmmo)
		Bytes = OutBytes;
}

void UBPFL_Helpers::PackWarMachinePowerCoreUpdate(UObject* WarMachine, const float PreviousTotalPower, TArray<uint8>& Bytes, float& TotalPower) {
	AActor *Actor = Cast<AActor>(WarMachine);
	if (!Actor) return;

	UActorComponent *Component = Actor->GetComponentByClass(UPowerCoreBase::StaticClass());
	if (!Component) return;

	UPowerCoreBase* PowerCore = Cast<UPowerCoreBase>(Component);
	if (!PowerCore) return;

	float Total = PowerCore->TotalCurrentPower();

	if (fabs(PreviousTotalPower - Total) < DBL_EPSILON) {
		Bytes.Emplace(0);
		return;
	}
	
	Bytes.Emplace(1);
	Bytes.Append(ConvertFloatToBytes(Total));
}

void UBPFL_Helpers::ConvertStringToBytes(const FString String, TArray<uint8> &Bytes)
{
	const int32 BufferSize = String.Len();
	uint8* Buffer = new uint8[String.Len()];
	StringToBytes(String, Buffer, BufferSize);
	Bytes = TArray<uint8>();
	for (int i = 0; i < BufferSize; i++)
	{
		Bytes.Add(Buffer[i]);
	}
}

TArray<uint8> UBPFL_Helpers::ConvertFloatToBytes(const float& Value) {
	TArray<uint8> Bytes;

	union {
		float f;
		uint8 b[4];
	} data;

	data.f = Value;

	Bytes.Emplace(data.b[0]);
	Bytes.Emplace(data.b[1]);
	Bytes.Emplace(data.b[2]);
	Bytes.Emplace(data.b[3]);

	return Bytes;
}

void UBPFL_Helpers::ConvertBytesToString(const TArray<uint8> Bytes, FString& String)
{
	FString Broken = BytesToString(&Bytes[0],  Bytes.Num());
	for (int i = 0; i < Broken.Len(); i++)
	{
		const TCHAR c = Broken[i] - 1;
		String.AppendChar(c);
	}
}

uint8 UBPFL_Helpers::PackBooleansIntoByte(const TArray<bool> Booleans)
{
	uint8 Byte = 0;
	for (int i = 0; i < Booleans.Num(); ++i)
	{
		if (Booleans[i])
			Byte |= 1 << i;
	}
	return Byte;
}

TArray<bool> UBPFL_Helpers::UnpackBooleansFromByte(const uint8 Byte)
{
	TArray<bool> Booleans = TArray<bool>();
	Booleans.Init(false, 8);
	for (int i = 0; i < 8; ++i)
		Booleans[i] = (Byte & (1 << i)) != 0;
	return Booleans;
}

TArray<uint8> UBPFL_Helpers::PackBooleansIntoBytes(const TArray<bool> Booleans)
{
	TArray<uint8> Bytes = TArray<uint8>();
	int Count = -1;
	for (int i = 0; i < Booleans.Num(); ++i)
	{
		if (i % 8 == 0)
		{
			Count++;
			Bytes.Emplace(0);
		}
		if (Booleans[i])
			Bytes[Count] |= 1 << i;
	}
	return Bytes;
}

TArray<bool> UBPFL_Helpers::UnpackBooleansFromBytes(const TArray<uint8> Bytes)
{
	TArray<bool> Booleans = TArray<bool>();
	for (const uint8 Byte : Bytes)
	{
		for (int i = 0; i < 8; ++i)
			Booleans.Emplace((Byte & (1 << i)) != 0);
	}
	return Booleans;
}

FColor UBPFL_Helpers::HexToColor(const FString HexString)
{
	return FColor::FromHex(HexString);
}

FString UBPFL_Helpers::ColorToHex(const FColor Color)
{
	return Color.ToHex();
}

ECollisionResponse UBPFL_Helpers::GetComponentsCollisionResponseToChannel(AActor* Actor, ECollisionChannel Channel)
{
	// Return ignore response if the actor is not valid.
	if (!IsValid(Actor))
		return ECollisionResponse::ECR_Ignore;

	return Actor->GetComponentsCollisionResponseToChannel(Channel);
}

FString UBPFL_Helpers::CopyMapDetailsToClipboard(const FMapDetails MapDetails)
{
	FString Text =R""""(  {
    "Name",
    {
      "Name",
      "ImageURL",
      Width, Height,
      CellsX, CellsY,
      PixelLeft, PixelTop,
      {DisabledCells}
    },
  },)"""";
	Text = Text.Replace(TEXT("Name"), ToCStr(MapDetails.Name));
	Text = Text.Replace(TEXT("ImageURL"), ToCStr(MapDetails.Image_URL));
	Text = Text.Replace(TEXT("Width"), ToCStr(FString::FromInt(MapDetails.Width)));
	Text = Text.Replace(TEXT("Height"), ToCStr(FString::FromInt(MapDetails.Height)));
	Text = Text.Replace(TEXT("CellsX"), ToCStr(FString::FromInt(MapDetails.Cells_X)));
	Text = Text.Replace(TEXT("CellsY"), ToCStr(FString::FromInt(MapDetails.Cells_Y)));
	Text = Text.Replace(TEXT("PixelLeft"), ToCStr(FString::FromInt(MapDetails.Pixel_Left)));
	Text = Text.Replace(TEXT("PixelTop"), ToCStr(FString::FromInt(MapDetails.Pixel_Top)));

	FString DisabledCells = "";
	for (const int DisabledCell : MapDetails.Disabled_Cells)
	{
		if (!DisabledCells.IsEmpty()) DisabledCells += ",";
		DisabledCells += FString::FromInt(DisabledCell);
	}
	
	Text = Text.Replace(TEXT("DisabledCells"), ToCStr(DisabledCells));
	
	FGenericPlatformApplicationMisc::ClipboardCopy(*Text);
	return Text;
}

FString UBPFL_Helpers::GetTextFromClipboard()
{
	FString Text = "";
	FGenericPlatformApplicationMisc::ClipboardPaste(Text);
	return Text;
}

FString UBPFL_Helpers::ReadTextFile(const FString FilePath)
{
	FString FileData = "";
	if (IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile(); FileManager.FileExists(*FilePath))
	{
		if (!FFileHelper::LoadFileToString(FileData,*FilePath,FFileHelper::EHashOptions::None))
		{
			UE_LOG(LogTemp, Warning, TEXT("ReadTextFile: Did not load text from file"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ReadTextFile: ERROR: Can not read the file because it was not found."));
		UE_LOG(LogTemp, Warning, TEXT("ReadTextFile: Expected file location: %s"),*FilePath);
	}
	return FileData;
}

void UBPFL_Helpers::ForceDestroyComponent(UActorComponent* ActorComponent)
{
    if (IsValid(ActorComponent))
    {
		ActorComponent->DestroyComponent();
    }
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BPFL_Helpers: Failed to force destroy the actor component!"));
	}
}

void UBPFL_Helpers::SetLockPhysiscs(UStaticMeshComponent* Mesh, const bool LockTranslationX, const bool LockTranslationY, const bool LockTranslationZ, const bool LockRotationX, const bool LockRotationY, const bool LockRotationZ)
{
	Mesh->BodyInstance.bLockXTranslation = LockTranslationX;
	Mesh->BodyInstance.bLockYTranslation = LockTranslationY;
	Mesh->BodyInstance.bLockZTranslation = LockTranslationZ;
	Mesh->BodyInstance.bLockXRotation = LockRotationX;
	Mesh->BodyInstance.bLockYRotation = LockRotationY;
	Mesh->BodyInstance.bLockZRotation = LockRotationZ;
	Mesh->BodyInstance.CreateDOFLock();
}

void UBPFL_Helpers::Crash()
{
	FDebug::AssertFailed("This crash was caused by UBPFL_Helpers::Crash() and was meant to happen.", __FILE__, __LINE__);
}

void UBPFL_Helpers::StopResponding()
{
	bool B = false;
	while(true)
		B = !B;
}

FTransform UBPFL_Helpers::GetRotationByQuat(const FTransform& Transform, const FRotator& RotationDelta)
{
	FTransform NewTransform = Transform;
	NewTransform.ConcatenateRotation(RotationDelta.Quaternion());
	NewTransform.NormalizeRotation();
	return NewTransform;
}

bool UBPFL_Helpers::MultiConeTraceForObjects(
	const UObject* WorldContextObject,
	const FVector& Start,
	const FVector& End,
	float HalfAngleInDegrees,
	float ConeBackwardOffset,
	const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes,
	UClass* ActorClassFilter,
	const TArray<AActor*>& ActorsToIgnore,
	TArray<class AActor*>& OutActors)
{
	// Fail-fast on invalid degrees.
	if (HalfAngleInDegrees <= 0) return false;
	if (HalfAngleInDegrees >= 90) return false;

	const FVector ToEndDirection = (End - Start).GetSafeNormal();
	const FVector AdjustedStart = Start - ToEndDirection * ConeBackwardOffset;
	const FVector ToEnd = End - AdjustedStart;

	const float ConeHeight = ToEnd.Length();
	const float HalfAngleInRadians = FMath::DegreesToRadians(HalfAngleInDegrees);
	const float ConeBaseRadius = ConeHeight * FMath::Atan(HalfAngleInRadians);
	const float ConeSlantHeight = FMath::Sqrt(FMath::Square(ConeBaseRadius) + FMath::Square(ConeHeight));
	
	const FVector CoverSphereLoc = AdjustedStart + ToEnd / 2;
	const float CoverSphereRadius = ConeSlantHeight / 2;

	TArray<AActor*> SphereHitActors;
	UKismetSystemLibrary::SphereOverlapActors(WorldContextObject, CoverSphereLoc, CoverSphereRadius, ObjectTypes, ActorClassFilter, ActorsToIgnore, SphereHitActors);

	// Filter sphere hit actors that are within the cone angle.
	const float CosHalfAngle = FMath::Cos(HalfAngleInRadians);
	for (auto HitActor : SphereHitActors)
	{
		const FVector ToHitDirection = (HitActor->GetActorLocation() - AdjustedStart).GetSafeNormal();
		const float Dot = FVector::DotProduct(ToEndDirection, ToHitDirection);
		
		if (Dot > CosHalfAngle)
		{
			// TODO: To prevent overshooting given `End` location, use the Dot angle to make another cone to calculate the slant distance
			// and if the distance to actor is greater than this slant distance, ignore. 
			OutActors.Add(HitActor);

		}
	}
	return !OutActors.IsEmpty();
}