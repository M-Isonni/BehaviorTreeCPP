// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericTeamAgentInterface.h"
#include "PerceivableActor.generated.h"

UCLASS()
class AIBEHAVIOR_API APerceivableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerceivableActor();

	void MakeSomeNoise(float Loudness);

private:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAIPerceptionStimuliSourceComponent* PerceptionStimuliSource;
};
