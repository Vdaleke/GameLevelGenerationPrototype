// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalLevelGameMode.h"

AGlobalLevelGameMode::AGlobalLevelGameMode()
{
	CurrentLevel = 0;
	ZeroArenaLocation = {0.0f, 0.0f, 0.0f};
	LastLoadedArena = 0;
}

int32 AGlobalLevelGameMode::GetCurrentLevel() const
{
	return CurrentLevel;
}

void AGlobalLevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	const TArray<FArenaData> ArenaData = RunLevelGenerationData->GetArenaData();
	LoadedArenas.Reserve(ArenaData.Num());

	FVector NextArenaLocation = ZeroArenaLocation;

	for (int ArenaNumber = 0; ArenaNumber < ArenaData.Num(); ++ArenaNumber)
	{
		bool bSuccess;
		LoadedArenas.Add(ULevelStreamingDynamic::LoadLevelInstance(
			GWorld, ArenaData[ArenaNumber].Name, NextArenaLocation, FRotator::ZeroRotator, bSuccess));

		LoadedArenas.Last()->OnLevelLoaded.AddDynamic(this, &AGlobalLevelGameMode::PutActorsToDataAsset);

		if (bSuccess == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Arena number #%d with the name %s was not loaded"), ArenaNumber,
			       *ArenaData[ArenaNumber].Name);
		}

		NextArenaLocation = FVector{NextArenaLocation.X, 0, NextArenaLocation.Z} + FMath::RandPointInBox(
			RunLevelGenerationData->GetArenaOffset());
	}
}

void AGlobalLevelGameMode::PutActorsToDataAsset()
{
	ULevelStreamingDynamic* LastArena = LoadedArenas[LastLoadedArena];

	if (LastArena->GetLoadedLevel())
	{
		for (auto i : LastArena->GetLoadedLevel()->Actors)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *i->GetName());
		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Level not loaded"));
	}
	
	LastLoadedArena++;
}
