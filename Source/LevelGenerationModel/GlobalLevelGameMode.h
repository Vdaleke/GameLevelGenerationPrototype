// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunLevelGenerationData.h"
#include "Engine/LevelStreamingDynamic.h"
#include "GameFramework/GameModeBase.h"
#include "GlobalLevelGameMode.generated.h"

/**
	Contains the current state of the system and the main logic for arenas and the transition between them.
 */
UCLASS()
class LEVELGENERATIONMODEL_API AGlobalLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	explicit AGlobalLevelGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ActivateZeroArena();

	UFUNCTION(BlueprintCallable)
	void GoToArena(int32 ArenaNumber, AActor* Player);

	UFUNCTION(BlueprintCallable)
	void SpawnArenaActorsAfterFight();

	UFUNCTION(BlueprintCallable)
	void ActivateTeleportOnCurrentArena();

	[[nodiscard]] int32 GetCurrentLevel() const;

	UFUNCTION(BlueprintCallable)
	int32 GetNumberOfLevels() const;

protected:
	UFUNCTION(BlueprintCallable)
	AActor* FindNearestActorOfClass(TSubclassOf<AActor> ActorClass, FVector Origin, float& Distance);

	UPROPERTY(VisibleAnywhere)
	int32 CurrentArena;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ZeroArenaLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URunLevelGenerationData* RunLevelGenerationData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ULevelStreamingDynamic*> LoadedArenas;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FVector> LoadedArenaPositions;
};
