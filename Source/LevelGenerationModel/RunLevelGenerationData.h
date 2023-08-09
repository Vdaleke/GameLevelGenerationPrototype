// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerSpawn.h"
#include "Engine/DataAsset.h"
#include "RunLevelGenerationData.generated.h"

USTRUCT(BlueprintType)
struct FArenaData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<APlayerSpawn> PlayerSpawn;
};

/**
	Contains all the data and parameters for generating the GlobalLevel
 */
UCLASS(Blueprintable)
class LEVELGENERATIONMODEL_API URunLevelGenerationData : public UDataAsset
{
	GENERATED_BODY()

public:
	explicit URunLevelGenerationData();

	[[nodiscard]] TArray<FArenaData> GetArenaData() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FArenaData> ArenaData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBox ArenaOffset;

public:
	[[nodiscard]] FBox GetArenaOffset() const;
};
