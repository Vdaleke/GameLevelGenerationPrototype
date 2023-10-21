// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RunLevelGenerationData.h"
#include "Engine/LevelStreamingDynamic.h"
#include "GlobalLevelController.generated.h"

/**
	Contains the current state of the system and the main logic for arenas and the transition between them.
 */
UCLASS()
class LEVELGENERATIONMODEL_API UGlobalLevelController : public UObject
{
	GENERATED_BODY()

public:
	explicit UGlobalLevelController();

	UFUNCTION(BlueprintCallable)
	void GenerateGlobalLevel();

	UFUNCTION(BlueprintCallable)
	void ActivateZeroArena();

	UFUNCTION(BlueprintCallable)
	void GoToNextArena(AActor* Player);

	UFUNCTION(BlueprintCallable)
	void SpawnArenaActorsAfterFight();

	UFUNCTION(BlueprintCallable)
	void ActivateTeleportOnCurrentArena();

	[[nodiscard]] int32 GetCurrentLevel() const;

	UFUNCTION(BlueprintCallable)
	int32 GetNumberOfArenas() const;

	void SetRunLevelGenerationData(URunLevelGenerationData* const NewRunLevelGenerationData);

protected:
	template<typename T>
	T* FindNearestActorOfClass(TSubclassOf<AActor> ActorClass, FVector Origin, float& Distance);

	UPROPERTY(Transient, BlueprintReadOnly)
	int32 CurrentArena;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ZeroArenaLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URunLevelGenerationData* RunLevelGenerationData;

	UPROPERTY(Transient)
	TArray<ULevelStreamingDynamic*> LoadedArenas;

	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<FVector> LoadedArenaPositions;
};

