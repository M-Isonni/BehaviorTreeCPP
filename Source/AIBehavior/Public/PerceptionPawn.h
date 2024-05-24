// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomAIPawn.h"
#include "Perception/AIPerceptionComponent.h"
#include "GenericTeamAgentInterface.h"
#include "PerceptionPawn.generated.h"

UENUM()
enum ETeamType : uint8
{
	Enemy = 0,
	NPC = 1,
	Allies = 2,
};

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API APerceptionPawn : public ACustomAIPawn, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	APerceptionPawn();

	void MakeSomeNoise(float Loudness);

protected:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	class UAISenseConfig_Sight* SightConfig;
	class UAISenseConfig_Hearing* HearingConfig;

	UFUNCTION()
	virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAIPerceptionStimuliSourceComponent* PerceptionStimuliSource;


	FGenericTeamId PawnTeamID = FGenericTeamId::NoTeam;

	inline virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override { PawnTeamID = TeamID; };
	inline virtual FGenericTeamId GetGenericTeamId() const override { return PawnTeamID; }

	/** Retrieved owner attitude toward given Other object */
	inline virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override
	{		
		return ETeamAttitude::Neutral;
	}	
};
