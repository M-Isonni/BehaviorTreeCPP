// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomAIPawn.h"
#include "PerceptionPawn.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API APerceptionPawn : public ACustomAIPawn
{
	GENERATED_BODY()

public:
	APerceptionPawn();

private:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAIPerceptionComponent* AIPerceptionComponent;

	class UAISenseConfig_Sight* SightConfig;
	class UAISenseConfig_Hearing* HearingConfig;

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	
};
