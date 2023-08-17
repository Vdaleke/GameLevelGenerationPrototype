// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerSpawn.h"
#include "Engine/DataAsset.h"
#include "RunLevelGenerationData.generated.h"

/**
	Contains all the data and parameters for generating the GlobalLevel
 */
UCLASS(Blueprintable)
class LEVELGENERATIONMODEL_API URunLevelGenerationData : public UDataAsset
{
	GENERATED_BODY()

public:
	explicit URunLevelGenerationData();

	[[nodiscard]] TArray<FString>& GetArenaNames();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ArenaNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBox ArenaOffset;

public:
	[[nodiscard]] FBox GetArenaOffset() const;
};
