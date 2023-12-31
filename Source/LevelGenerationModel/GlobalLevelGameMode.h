// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalLevelController.h"
#include "RunLevelGenerationData.h"
#include "Engine/LevelStreamingDynamic.h"
#include "GameFramework/GameModeBase.h"
#include "GlobalLevelGameMode.generated.h"

UCLASS()
class LEVELGENERATIONMODEL_API AGlobalLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	explicit AGlobalLevelGameMode();

	virtual void BeginPlay() override;

	[[nodiscard]] UGlobalLevelController* GetLevelController() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	UGlobalLevelController* LevelController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URunLevelGenerationData* RunLevelGenerationData;
};
