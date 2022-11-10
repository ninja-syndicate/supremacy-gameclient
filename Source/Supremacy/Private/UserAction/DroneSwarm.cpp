// Fill out your copyright notice in the Description page of Project Settings.


#include "UserAction/DroneSwarm.h"
#include "Boid.h"
#include "BoidManager.h"

void ADroneSwarm::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);
	if (MainMesh && OwningBoidManager)
	{
		DroneFlock(OwningBoidManager->Boids);
		Update();
	}
}

void ADroneSwarm::DroneFlock(TArray<ABoid*> Boids)
{
	if (SeparationWeight > 0)
	{
		FVector sep = Seperate(Boids);   // Separation
		sep *= (SeparationWeight);
		ApplyForce(sep);
	}
	if (AlignmentWeight > 0)
	{
		FVector ali = Align(Boids);      // Alignment
		ali *= (AlignmentWeight);
		ApplyForce(ali);
	}
	if (CohesionWeight > 0)
	{
		FVector coh = Cohesion(Boids);   // Cohesion
		coh *= (CohesionWeight);
		ApplyForce(coh);
	}
	if (Goal != nullptr && GoalSeekWeight > 0)
		ApplyForce(DroneSeek((Goal->GetActorLocation())) * GoalSeekWeight);
}

// A method that calculates and applies a steering force towards a target
// STEER = DESIRED MINUS VELOCITY
FVector ADroneSwarm::DroneSeek(FVector target)
{
	FVector current = GetActorLocation();
	FVector delta = target - current;     
	FVector reverseDelta = current - target;
	reverseDelta.Normalize();
	reverseDelta *= DesiredDistance;
	FVector desired = reverseDelta + delta;

	FRotator LookAtRotation = bEnableLookAt ? desired.Rotation() + CustomRotationOffset : FRotator::ZeroRotator;
	//MainSM->GetComponentRotation();
	float AngularSpeed = 1.0f;// MainMesh->GetPhysicsAngularVelocity().Size() * GetWorld()->DeltaTimeSeconds;
	//FRotator SmoothedLookAtRotation = FMath::RInterpTo(MainMesh->GetComponentRotation(), LookAtRotation, GetWorld()->DeltaTimeSeconds, AngularSpeed);
	if (false)
	{
		//In all actuality, the look direction here should be driven by an animation probably? Maybe also for Static Mesh? 
		//So locking XYZ rotation and using an animation would probably look ok. Desired would need to be exposed to editor. 
		//MainSKM = (USkeletalMeshComponent*)MainMesh;
		//MainMesh->SetWorldRotation(SmoothedLookAtRotation, false, 0, ETeleportType::TeleportPhysics);
	}
	else
	{
		if (bEnableLookAt)
		{
			MainMesh->SetWorldRotation(LookAtRotation);
		}
	}

	float totalLength = desired.Length();
	float speed = FMath::Min(totalLength / 25.0f, MaxSpeed);

	desired = (desired / totalLength) * speed;

	// Steering = Desired minus Velocity
	FVector steer = desired - MainMesh->GetPhysicsLinearVelocity();
	steer = steer.GetClampedToMaxSize(MaxForce);  // Limit to maximum steering force
	return steer;
}