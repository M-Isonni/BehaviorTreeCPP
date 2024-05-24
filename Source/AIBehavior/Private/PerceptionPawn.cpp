// Fill out your copyright notice in the Description page of Project Settings.


#include "PerceptionPawn.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Kismet/GameplayStatics.h"

APerceptionPawn::APerceptionPawn()
{
	//Create AiPerception component
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	//create sight config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AIPerceptionSight"));

	//Configure sight
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1200.0;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	//Create hearing
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("AIPerceptionHearing"));

	//Configure hearing
	HearingConfig->HearingRange = 600.0f;
	HearingConfig->LoSHearingRange = 1200.0f;
	HearingConfig->bUseLoSHearing = true;
	HearingConfig->SetMaxAge(5.0);
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->ConfigureSense(*HearingConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &APerceptionPawn::OnPerceptionUpdated);


	//create stimuli source
	PerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("StimuliSourceComponent");

	//register senses
	PerceptionStimuliSource->RegisterForSense(TSubclassOf<UAISense_Hearing>());
	PerceptionStimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
	PerceptionStimuliSource->RegisterWithPerceptionSystem();
}

void APerceptionPawn::MakeSomeNoise(float Loudness)
{
	//This is heard by AI but doesn't produce a sound that can be heard from the player
	APawn* NoiseInstigator = Cast<APawn>(this);
	MakeNoise(Loudness, NoiseInstigator, GetActorLocation());

	//This is not heard by the AI but produces a sound that can be heard from the player
	FSoftObjectPath SoundAssetPath(TEXT("/Engine/EditorSounds/Notifications/CompileSuccess_Cue.CompileSuccess_Cue"));
	USoundBase* Sound = Cast<USoundBase>(SoundAssetPath.TryLoad());
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
	}
}

void APerceptionPawn::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
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
					UE_LOG(LogTemp, Warning, TEXT("Saw Actor: %s at location: %s"), *Actor->GetName(), *Stimulus.StimulusLocation.ToString());
				}
				else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>() && Stimulus.WasSuccessfullySensed())
				{
					UE_LOG(LogTemp, Warning, TEXT("Heard actor: %s at: %s"), *Actor->GetName(), *Stimulus.StimulusLocation.ToString());						
				}
			}
		}
	}
}
