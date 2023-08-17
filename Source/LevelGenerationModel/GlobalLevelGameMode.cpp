// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalLevelGameMode.h"

#include "FunctionalUIScreenshotTest.h"
#include "TEST_MorhingTalent.h"
#include "TEST_Teleport.h"
#include "TEST_WinNotice.h"
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

	const TArray<FString>& ArenaNames = RunLevelGenerationData->GetArenaNames();
	LoadedArenas.SetNum(ArenaNames.Num());
	LoadedArenaPositions.SetNum(ArenaNames.Num());

	FVector NextArenaLocation = ZeroArenaLocation;

	for (int ArenaNumber = 0; ArenaNumber < ArenaNames.Num(); ++ArenaNumber)
	{
		bool bSuccess;
		LoadedArenas[ArenaNumber] = ULevelStreamingDynamic::LoadLevelInstance(
			GWorld, ArenaNames[ArenaNumber], NextArenaLocation, FRotator::ZeroRotator, bSuccess);

		LoadedArenaPositions[ArenaNumber] = NextArenaLocation;

		if (bSuccess == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Arena number #%d with the name %s was not loaded"), ArenaNumber,
			       *ArenaNames[ArenaNumber]);
		}

		NextArenaLocation = FVector{NextArenaLocation.X, 0, NextArenaLocation.Z} + FMath::RandPointInBox(
			RunLevelGenerationData->GetArenaOffset());
	}

	LoadedArenas[0]->OnLevelShown.AddDynamic(this, &AGlobalLevelGameMode::ActivateZeroArena);
}

void AGlobalLevelGameMode::GoToArena(int32 ArenaNumber, AActor* Player)
{
	if (ArenaNumber < 0 || LoadedArenas.Num() <= ArenaNumber || LoadedArenas[ArenaNumber] == nullptr)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			                                 FString::Printf(TEXT("Arena with number %d doesn't exist"), ArenaNumber));
		return;
	}

	float DistanceToNearestSpawn;

	if (APlayerSpawn const* PlayerSpawn = Cast<APlayerSpawn>(
		FindNearestActorOfClass(APlayerSpawn::StaticClass(), LoadedArenaPositions[ArenaNumber],
								DistanceToNearestSpawn)))
	{
		Player->TeleportTo(PlayerSpawn->GetActorLocation(), FRotator::ZeroRotator);
		CurrentArena = ArenaNumber;
	}
}

void AGlobalLevelGameMode::OnFightEnd()
{
	if (GetCurrentLevel() + 1 != GetNumberOfLevels())
	{
		float DistanceToNearestMorphingTalent;
		ATEST_MorhingTalent* MorphingTalent = Cast<ATEST_MorhingTalent>(
			FindNearestActorOfClass(ATEST_MorhingTalent::StaticClass(), LoadedArenaPositions[GetCurrentLevel()],
			                        DistanceToNearestMorphingTalent));

		if (MorphingTalent)
		{
			MorphingTalent->SetActorHiddenInGame(false);
			MorphingTalent->GetMeshComponent()->SetGenerateOverlapEvents(true);
		}
	}
	else
	{
		float DistanceToNearestWinNotice;
		ATEST_WinNotice* WinNotice = Cast<ATEST_WinNotice>(FindNearestActorOfClass(
			ATEST_WinNotice::StaticClass(), LoadedArenaPositions[GetCurrentLevel()], DistanceToNearestWinNotice));

		if (WinNotice)
		{
			WinNotice->SetActorHiddenInGame(false);
		}
	}
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

	FTimerHandle SpawnActorTimerHandle;

	GetWorldTimerManager().SetTimer(SpawnActorTimerHandle, this, &AGlobalLevelGameMode::OnFightEnd, 1.0f, false);

	/*
	float DistanceToNearestMorphingTalent;
	ATEST_MorhingTalent* MorphingTalent = Cast<ATEST_MorhingTalent>(
		FindNearestActorOfClass(ATEST_MorhingTalent::StaticClass(), LoadedArenaPositions[0],
								DistanceToNearestMorphingTalent));

	if (MorphingTalent)
	{
		MorphingTalent->SetActorHiddenInGame(false);
		MorphingTalent->GetMeshComponent()->SetGenerateOverlapEvents(true);
	 */
}

int32 AGlobalLevelGameMode::GetNumberOfLevels() const
{
	return LoadedArenas.Num();
}

AActor* AGlobalLevelGameMode::FindNearestActorOfClass(TSubclassOf<AActor> ActorClass, FVector Origin,
                                                      float& Distance)
{
	TArray<AActor*> FoundSpawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClass, FoundSpawns);

	return UGameplayStatics::FindNearestActor(Origin, FoundSpawns, Distance);
}
