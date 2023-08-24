// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalLevelGameMode.h"

#include "ArenaActors/TeleportPoint.h"
#include "ArenaActors/TEST_MorphingTalent.h"
#include "ArenaActors/TEST_Teleport.h"
#include "ArenaActors/TEST_WinNotice.h"
#include "Kismet/GameplayStatics.h"

AGlobalLevelGameMode::AGlobalLevelGameMode()
{
	LevelController = CreateDefaultSubobject<UGlobalLevelController>("Level Controller");
}

UGlobalLevelController* AGlobalLevelGameMode::GetLevelController() const
{
	return LevelController;
}

void AGlobalLevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (LevelController)
	{
		LevelController->SetRunLevelGenerationData(RunLevelGenerationData);
		LevelController->GenerateGlobalLevel();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Level controller not found"));
		return;
	}
}
