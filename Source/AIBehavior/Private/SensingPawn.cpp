// Fill out your copyright notice in the Description page of Project Settings.


#include "SensingPawn.h"
#include "Perception/PawnSensingComponent.h"

ASensingPawn::ASensingPawn()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SightRadius = 1000.0f;
	PawnSensingComponent->SetPeripheralVisionAngle(90.0f);
	PawnSensingComponent->HearingThreshold = 600;
	PawnSensingComponent->LOSHearingThreshold = 1200.0f;

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASensingPawn::OnPawnSeen);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &ASensingPawn::OnPawnHeard);
}

void ASensingPawn::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Saw pawn: %s"), *SeenPawn->GetName());
	}
}

void ASensingPawn::OnPawnHeard(APawn* HeardPawn, const FVector& Location, float Volume)
{
	FString NoiseInstigator;
	if (HeardPawn)
	{
		NoiseInstigator = HeardPawn->GetName();
	}
	else
	{
		NoiseInstigator = "Unknown";
	}

	UE_LOG(LogTemp, Warning, TEXT("Heard noise from %s at Location: %s with volume: %f"), *NoiseInstigator, *Location.ToString(), Volume);
}



