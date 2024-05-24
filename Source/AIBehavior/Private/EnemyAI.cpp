// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

AEnemyAI::AEnemyAI()
{
	SightConfig->SightRadius = 500.0f;

	FGenericTeamId EnemyTeamID(ETeamType::Enemy);
	SetGenericTeamId(EnemyTeamID);
}

void AEnemyAI::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		FActorPerceptionBlueprintInfo Info;
		AIPerceptionComponent->GetActorsPerception(Actor, Info);

		if (Info.LastSensedStimuli.Num() > 0)
		{
			for (const FAIStimulus& Stimulus : Info.LastSensedStimuli)
			{

				if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>() && Stimulus.WasSuccessfullySensed())
				{
					if (GetTeamAttitudeTowards(*Actor) == ETeamAttitude::Hostile)
					{
						//Attack or chase or something hostile
					}
					else
					{
						//Something else
					}
				}
				else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>() && Stimulus.WasSuccessfullySensed())
				{
					UE_LOG(LogTemp, Warning, TEXT("Heard actor: %s at: %s"), *Actor->GetName(), *Stimulus.StimulusLocation.ToString());
				}
			}
		}
	}
}
