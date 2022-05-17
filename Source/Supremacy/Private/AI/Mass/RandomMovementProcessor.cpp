// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Mass/RandomMovementProcessor.h"

#include "MassCommonTypes.h"
#include "MassCommonFragments.h"
#include "MassMovementFragments.h"
#include "MassNavigationFragments.h"
#include "AI/Mass/MovementFragment.h"

URandomMovementProcessor::URandomMovementProcessor()
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (int32)EProcessorExecutionFlags::All;
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Avoidance);
}

void URandomMovementProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FMassMoveTargetFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddConstSharedRequirement<FMassMovementParameters>(EMassFragmentPresence::All);
}

void URandomMovementProcessor::Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(EntitySubsystem, Context, ([this](FMassExecutionContext& Context)
		{
			const TConstArrayView<FTransformFragment> TransformsList = Context.GetFragmentView<FTransformFragment>();
			const TArrayView<FMassMoveTargetFragment> NavTargetsList = Context.GetMutableFragmentView<FMassMoveTargetFragment>();
			const FMassMovementParameters& MovementParams = Context.GetConstSharedFragment<FMassMovementParameters>();
			const float WorldDeltaTime = Context.GetDeltaTimeSeconds();

			for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
			{
				const FTransform& Transform = TransformsList[EntityIndex].GetTransform();
				FMassMoveTargetFragment& MoveTarget = NavTargetsList[EntityIndex];

				FVector CurrentLocation = Transform.GetLocation();
				FVector TargetVector = MoveTarget.Center - Transform.GetLocation();
				TargetVector.Z = 0;

				MoveTarget.DistanceToGoal = (TargetVector).Size();
				MoveTarget.Forward = (TargetVector).GetSafeNormal();

				if (MoveTarget.DistanceToGoal <= 20.0f || MoveTarget.Center == FVector::ZeroVector)
				{
					MoveTarget.Center = FVector(FMath::RandRange(-1.f, 1.f) * 10000.0f, FMath::RandRange(-1.f, 1.f) * 10000.f, CurrentLocation.Z);
					MoveTarget.DistanceToGoal = (MoveTarget.Center - Transform.GetLocation()).Size();
					MoveTarget.Forward = (MoveTarget.Center - Transform.GetLocation()).GetSafeNormal();
					MoveTarget.DesiredSpeed = FMassInt16Real(MovementParams.DefaultDesiredSpeed);
				}
			}
		}));
}