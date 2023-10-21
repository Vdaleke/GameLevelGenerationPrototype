// Fill out your copyright notice in the Description page of Project Settings.


#include "RunLevelGenerationData.h"

URunLevelGenerationData::URunLevelGenerationData()
{
	ArenaOffset = {FVector{150.0f, -100, 50.0f}, FVector{200.0f, 100.0f, 100.0f}};
}

const TArray<TSoftObjectPtr<UWorld>>& URunLevelGenerationData::GetArenas() const
{
	return Arenas;
}

FBox URunLevelGenerationData::GetArenaOffset() const
{
	return ArenaOffset;
}
