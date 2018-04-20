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

	if (HasAuthority()) {
		this->SetReplicates(true);
		this->SetReplicateMovement(true);//s'applique � l'actor (lui-m�me)
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ActiveTriggers == 1) {

		if (HasAuthority())//Si modele client/serveur l'autorit� d'execu du code suivant est donn� au serveur, Sinon donn� � la premi�re instance -game
		{
			FVector Location = GetActorLocation();
			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if (JourneyTravelled >= JourneyLength) {

				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;

			}

			FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal();
			Location += speed * DeltaTime * Direction;
			SetActorLocation(Location);


			//UE_LOG(LogTemp, Warning,TEXT("Begin called"));
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
		ActiveTriggers--;
}


