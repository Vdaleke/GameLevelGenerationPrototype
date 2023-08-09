// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunLevelGenerationData.h"
#include "Engine/LevelStreamingDynamic.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
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

	[[nodiscard]] int32 GetCurrentLevel() const;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Meta = (WorldContext = WorldContextObject))
	void PutActorsToDataAsset();

protected:
	UPROPERTY(VisibleAnywhere)
	int32 CurrentLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ULevelStreamingDynamic*> LoadedArenas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URunLevelGenerationData* RunLevelGenerationData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<APlayerStart> PlayerStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ZeroArenaLocation;

private:
	int32 LastLoadedArena;
};
