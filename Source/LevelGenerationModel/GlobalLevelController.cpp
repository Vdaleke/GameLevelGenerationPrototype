// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalLevelController.h"


#include "ArenaActors/TeleportPoint.h"
#include "ArenaActors/TEST_MorphingTalent.h"
#include "ArenaActors/TEST_Teleport.h"
#include "ArenaActors/TEST_WinNotice.h"
#include "Kismet/GameplayStatics.h"

UGlobalLevelController::UGlobalLevelController()
{
	CurrentArena = 0;
	ZeroArenaLocation = {0.0f, 0.0f, 0.0f};
}

void UGlobalLevelController::GenerateGlobalLevel()
{
	ensure(RunLevelGenerationData != nullptr);
	const TArray<TSoftObjectPtr<UWorld>>& Arenas = RunLevelGenerationData->GetArenas();
	LoadedArenas.SetNum(Arenas.Num());
	LoadedArenaPositions.SetNum(Arenas.Num());

	FVector ArenaLocation = ZeroArenaLocation;

	for (int ArenaNumber = 0; ArenaNumber < Arenas.Num(); ++ArenaNumber)
	{
		bool bSuccess;
		LoadedArenas[ArenaNumber] = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(
			GWorld, Arenas[ArenaNumber], ArenaLocation, FRotator::ZeroRotator, bSuccess);

		LoadedArenaPositions[ArenaNumber] = ArenaLocation;

		if (bSuccess == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Arena number #%d was not loaded"), ArenaNumber);
		}

		ArenaLocation = FVector{ArenaLocation.X, 0, ArenaLocation.Z} + FMath::RandPointInBox(
			RunLevelGenerationData->GetArenaOffset());
	}

	ensure(GetNumberOfArenas() > 0 && LoadedArenas[0] != nullptr);
	LoadedArenas[0]->OnLevelShown.AddDynamic(this, &UGlobalLevelController::ActivateZeroArena);
}

void UGlobalLevelController::ActivateZeroArena()
{
	FTimerHandle SpawnActorTimerHandle;

	/*
	*	SpawnArenaActorsAfterFight method does not work when called by the OnLevelShown delegate,
	*	because for some reason it cannot find the newly loaded MorphingTalent actor on the map.
	*	We call this method after a certain period of time, then the actor will be found.
	*	But this can cause a bug in the future, if on some client the actor does not load even after 1 second of real time.
	*	#TODO: find a solution to this problem
	*/
	GetWorld()->GetTimerManager().SetTimer(SpawnActorTimerHandle, this,
	                                       &UGlobalLevelController::SpawnArenaActorsAfterFight,
	                                       1.0f, false);
}

void UGlobalLevelController::GoToNextArena(AActor* Player)
{
	const int32 NextArena = CurrentArena + 1;

	if (GetNumberOfArenas() == NextArena)
	{
		UE_LOG(LogTemp, Warning, TEXT("This is the last arena"));
		return;
	}

	float DistanceToNearestSpawn;

	if (ATeleportPoint const* PlayerSpawn = Cast<ATeleportPoint>(
		FindNearestActorOfClass<ATeleportPoint>(ATeleportPoint::StaticClass(), LoadedArenaPositions[NextArena],
		                                        DistanceToNearestSpawn)))
	{
		Player->TeleportTo(PlayerSpawn->GetActorLocation(), FRotator::ZeroRotator);
		CurrentArena = NextArena;
	}
}

void UGlobalLevelController::SpawnArenaActorsAfterFight()
{
	if (GetCurrentLevel() + 1 != GetNumberOfArenas())
	{
		float DistanceToNearestMorphingTalent;

		if (ATEST_MorphingTalent* MorphingTalent = FindNearestActorOfClass<ATEST_MorphingTalent>(
			ATEST_MorphingTalent::StaticClass(), LoadedArenaPositions[GetCurrentLevel()],
			DistanceToNearestMorphingTalent))
		{
			MorphingTalent->ShowMorphingTalent();
		}
		else if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			                                 TEXT("Morphing talent not found!"));
			return;
		}
	}
	else
	{
		float DistanceToNearestWinNotice;

		if (ATEST_WinNotice* WinNotice = FindNearestActorOfClass<ATEST_WinNotice>(
			ATEST_WinNotice::StaticClass(), LoadedArenaPositions[GetCurrentLevel()], DistanceToNearestWinNotice))
		{
			WinNotice->ShowWinNotice();
		}
		else if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			                                 TEXT("Win Notice not found!"));
			return;
		}
	}
}

void UGlobalLevelController::ActivateTeleportOnCurrentArena()
{
	float DistanceToNearestTeleport;

	if (ATEST_Teleport* Teleport =
		FindNearestActorOfClass<ATEST_Teleport>(ATEST_Teleport::StaticClass(), LoadedArenaPositions[CurrentArena],
		                                        DistanceToNearestTeleport))
	{
		Teleport->ShowTeleport();
	}
	else if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		                                 TEXT("Teleport not found!"));
		return;
	}
}

int32 UGlobalLevelController::GetCurrentLevel() const
{
	return CurrentArena;
}

int32 UGlobalLevelController::GetNumberOfArenas() const
{
	return LoadedArenas.Num();
}

void UGlobalLevelController::SetRunLevelGenerationData(URunLevelGenerationData* const NewRunLevelGenerationData)
{
	RunLevelGenerationData = NewRunLevelGenerationData;
}

template <typename T>
T* UGlobalLevelController::FindNearestActorOfClass(TSubclassOf<AActor> ActorClass, FVector Origin, float& Distance)
{
	TArray<AActor*> FoundSpawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClass, FoundSpawns);

	return Cast<T>(UGameplayStatics::FindNearestActor(Origin, FoundSpawns, Distance));
}
