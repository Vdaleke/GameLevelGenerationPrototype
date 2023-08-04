// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalLevelGameMode.h"

AGlobalLevelGameMode::AGlobalLevelGameMode()
{
	CurrentLevel = 0;
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

	FVector NextArenaLocation = {0.0f, 0.0f, 0.0f};

	for (int ArenaNumber = 0; ArenaNumber < ArenaData.Num(); ++ArenaNumber)
	{
		bool bSuccess;
		LoadedArenas.Add(ULevelStreamingDynamic::LoadLevelInstance(
			GWorld, ArenaData[ArenaNumber].Name, NextArenaLocation, FRotator::ZeroRotator, bSuccess));

		if (bSuccess == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Arena number #%d with the name %s was not loaded"), ArenaNumber,
			       *ArenaData[ArenaNumber].Name);
		}

		NextArenaLocation = FVector{NextArenaLocation.X, 0, NextArenaLocation.Z} + FMath::RandPointInBox(
			RunLevelGenerationData->GetArenaOffset());
	}
}
