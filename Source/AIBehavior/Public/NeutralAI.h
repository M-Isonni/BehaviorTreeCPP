// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PerceptionPawn.h"
#include "NeutralAI.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API ANeutralAI : public APerceptionPawn
{
	GENERATED_BODY()
public:
	ANeutralAI();

protected:

	UFUNCTION()
	virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;

	inline virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override
	{
		const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
		if (OtherTeamAgent)
		{
			if (GetGenericTeamId() == OtherTeamAgent->GetGenericTeamId())
			{
				return ETeamAttitude::Friendly;
			}
			else
			{
				return ETeamAttitude::Hostile;
			}
		}
		return ETeamAttitude::Neutral;
	}
	
};
