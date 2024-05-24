// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomAIPawn.h"
#include "SensingPawn.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API ASensingPawn : public ACustomAIPawn
{
	GENERATED_BODY()

public:
	ASensingPawn();

private:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComponent;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnPawnHeard(APawn* HeardPawn, const FVector& Location, float Volume);
	
};
