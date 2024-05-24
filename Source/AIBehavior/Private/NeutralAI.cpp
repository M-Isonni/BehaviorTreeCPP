// Fill out your copyright notice in the Description page of Project Settings.


#include "NeutralAI.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

ANeutralAI::ANeutralAI()
{
	FGenericTeamId NPCTeamID(ETeamType::Enemy);
	SetGenericTeamId(NPCTeamID);
}

void ANeutralAI::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
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
					ETeamAttitude::Type Attitude = GetTeamAttitudeTowards(*Actor);
					if (Attitude == ETeamAttitude::Hostile)
					{
						//run
					}
					else if(Attitude == ETeamAttitude::Friendly)
					{
						//get close and chat
					}
					else
					{
						//don't change behaviour
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
