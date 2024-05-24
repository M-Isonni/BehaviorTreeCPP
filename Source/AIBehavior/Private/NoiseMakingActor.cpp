// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseMakingActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANoiseMakingActor::ANoiseMakingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANoiseMakingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANoiseMakingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANoiseMakingActor::MakeSomeNoise(float Loudness)
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

