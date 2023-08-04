// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RunLevelGenerationData.generated.h"

USTRUCT(BlueprintType)
struct FArenaData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FArenaData> ArenaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBox ArenaOffset;

public:
	[[nodiscard]] FBox GetArenaOffset() const;
};
