// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	GlobalStartLocation = GetActorLocation();
	//gets the local offset of target location and converts it to a global location
	GlobalTargetLocation= GetTransform().TransformPosition(TargetLocation);
}
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			//gets the actors world location
			FVector Location = GetActorLocation();

			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if (JourneyTravelled >= JourneyLength)
			{
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}
			//gets the direction by using the formula A-B gets the direction then normalize to get proper scaling of direction
			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

			//updates location to add a vector direction based on speed and delta time 
			Location += Speed * DeltaTime * Direction;

			//sets the new location to this actor 
			SetActorLocation(Location);
		}
	}	
}
void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}
