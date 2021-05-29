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
}
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		//gets the actors world location
		FVector Location = GetActorLocation();
		//gets the local offset of target location and converts it to a global location
		FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
		//gets the direction by using the formula A-B gets the direction then normalize to get proper scaling of direction
		FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal();
		//updates location to add a vector direction based on speed and delta time 
		Location += Speed * DeltaTime*Direction; 
		//sets the new location to this actor 
		SetActorLocation(Location);
	}
}
