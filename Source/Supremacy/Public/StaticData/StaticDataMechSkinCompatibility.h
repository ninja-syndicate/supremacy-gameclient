// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "UObject/Object.h"
#include "StaticDataWarMachineModel.h"
#include "StaticDataSkin.h"
#include "StaticDataMechSkinCompatibility.generated.h"

namespace StaticDataImporter
{
	class MechSkinCompatibility;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataMechSkinCompatibility : public UStaticDataBaseRecord
{
	friend class StaticDataImporter::MechSkinCompatibility;
	
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataWarMachineModel *WarMachineModel;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataSkin *Skin;
};
