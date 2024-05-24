// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PerceptionPawn.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API AEnemyAI : public APerceptionPawn
{
	GENERATED_BODY()

public:
	AEnemyAI();

protected:

	UFUNCTION()
	virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;

	inline virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override
	{
		const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
		if (GetGenericTeamId() == OtherTeamAgent->GetGenericTeamId())
		{
			return ETeamAttitude::Friendly;
		}
		else
		{
			return ETeamAttitude::Hostile;
		}
	}
	
};
