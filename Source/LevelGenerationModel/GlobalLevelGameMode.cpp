// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalLevelGameMode.h"

#include "FunctionalUIScreenshotTest.h"
#include "TEST_MorhingTalent.h"
#include "TEST_Teleport.h"
#include "Kismet/GameplayStatics.h"

AGlobalLevelGameMode::AGlobalLevelGameMode()
{
	CurrentArena = 0;
	ZeroArenaLocation = {0.0f, 0.0f, 0.0f};
}

int32 AGlobalLevelGameMode::GetCurrentLevel() const
{
	return CurrentArena;
}

void AGlobalLevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	const TArray<FArenaData> ArenaData = RunLevelGenerationData->GetArenaData();
	LoadedArenas.SetNum(ArenaData.Num());
	LoadedArenaPositions.SetNum(ArenaData.Num());

	FVector NextArenaLocation = ZeroArenaLocation;

	for (int ArenaNumber = 0; ArenaNumber < ArenaData.Num(); ++ArenaNumber)
	{
		bool bSuccess;
		LoadedArenas[ArenaNumber] = ULevelStreamingDynamic::LoadLevelInstance(
			GWorld, ArenaData[ArenaNumber].Name, NextArenaLocation, FRotator::ZeroRotator, bSuccess);

		LoadedArenaPositions[ArenaNumber] = NextArenaLocation;

		if (bSuccess == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Arena number #%d with the name %s was not loaded"), ArenaNumber,
			       *ArenaData[ArenaNumber].Name);
		}

		NextArenaLocation = FVector{NextArenaLocation.X, 0, NextArenaLocation.Z} + FMath::RandPointInBox(
			RunLevelGenerationData->GetArenaOffset());
	}

	LoadedArenas[0]->OnLevelLoaded.AddDynamic(this, &AGlobalLevelGameMode::ActivateZeroArena);
	
	for (FVector Position : LoadedArenaPositions)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			                                 FString::Printf(
				                                 TEXT("x %f, y %f, z %f"), Position.X, Position.Y, Position.Z));
	}
}

void AGlobalLevelGameMode::GoToArena(int32 ArenaNumber, AActor* Player)
{
	if (ArenaNumber < 0 || LoadedArenas.Num() <= ArenaNumber)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			                                 FString::Printf(TEXT("Arena with number %d doesn't exist"), ArenaNumber));
		return;
	}

	float DistanceToNearestSpawn;

	APlayerSpawn const* PlayerSpawn = Cast<APlayerSpawn>(
		FindNearestActorOfClass(APlayerSpawn::StaticClass(), LoadedArenaPositions[ArenaNumber],
		                        DistanceToNearestSpawn));

	float DistanceToNearestMorphingTalent;
	ATEST_MorhingTalent* MorphingTalent = Cast<ATEST_MorhingTalent>(
		FindNearestActorOfClass(ATEST_MorhingTalent::StaticClass(), LoadedArenaPositions[ArenaNumber],
		                        DistanceToNearestMorphingTalent));

	if (PlayerSpawn && MorphingTalent)
	{
		Player->TeleportTo(PlayerSpawn->GetActorLocation(), FRotator::ZeroRotator);
		MorphingTalent->SetActorHiddenInGame(false);
		MorphingTalent->GetMeshComponent()->SetGenerateOverlapEvents(true);
	}

	CurrentArena = ArenaNumber;
}

void AGlobalLevelGameMode::ActivateTeleportOnCurrentArena()
{
	float DistanceToNearestTeleport;

	if (ATEST_Teleport* Teleport = Cast<ATEST_Teleport>(
		FindNearestActorOfClass(ATEST_Teleport::StaticClass(), LoadedArenaPositions[CurrentArena],
		                        DistanceToNearestTeleport)))
	{
		Teleport->SetActorHiddenInGame(false);
		Teleport->GetMeshComponent()->SetGenerateOverlapEvents(true);
	}
}

void AGlobalLevelGameMode::ActivateZeroArena()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
										 FString::Printf(TEXT("Zero arena activated")));
	
	float DistanceToNearestMorphingTalent;
	ATEST_MorhingTalent* MorphingTalent = Cast<ATEST_MorhingTalent>(
		FindNearestActorOfClass(ATEST_MorhingTalent::StaticClass(), LoadedArenaPositions[0],
								DistanceToNearestMorphingTalent));

	if (MorphingTalent)
	{
		MorphingTalent->SetActorHiddenInGame(false);
		MorphingTalent->GetMeshComponent()->SetGenerateOverlapEvents(true);
	}
}

AActor* AGlobalLevelGameMode::FindNearestActorOfClass(TSubclassOf<AActor> ActorClass, FVector Origin,
                                                      float& Distance)
{
	TArray<AActor*> FoundSpawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClass, FoundSpawns);

	return UGameplayStatics::FindNearestActor(Origin, FoundSpawns, Distance);
}
