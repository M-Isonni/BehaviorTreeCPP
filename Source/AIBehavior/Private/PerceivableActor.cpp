// Fill out your copyright notice in the Description page of Project Settings.


#include "PerceivableActor.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APerceivableActor::APerceivableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create stimuli source
	PerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("StimuliSourceComponent");

	//register senses
	PerceptionStimuliSource->RegisterForSense(TSubclassOf<UAISense_Hearing>());
	PerceptionStimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
	PerceptionStimuliSource->RegisterWithPerceptionSystem();

	//PerceptionStimuliSource->Team
}

void APerceivableActor::MakeSomeNoise(float Loudness)
{
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

