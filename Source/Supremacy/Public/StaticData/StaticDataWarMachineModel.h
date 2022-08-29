// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "StaticDataBrand.h"
#include "Mechs/Mech.h"
#include "Types/WarMachineType.h"
#include "UObject/Object.h"
#include "StaticDataWarMachineModel.generated.h"

namespace StaticDataImporter
{
	class WarMachineModel;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataWarMachineModel : public UStaticDataBaseRecord
{
	friend class StaticDataImporter::WarMachineModel;
	
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	EWarMachineModelType Type;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataBrand *Brand;
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="References", meta=(AllowPrivateAccess=true))
	TSoftClassPtr<AMech> UnrealWarMachine;
};
