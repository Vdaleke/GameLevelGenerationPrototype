// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectPtr.h"
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "WorldPartition/DataLayer/DataLayerAsset.h"
#include "CloneDataLayerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CLONEDATALAYER_API ACloneDataLayerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "DataLayer")
	TObjectPtr<const UDataLayerAsset> DataLayerAsset1;

	UPROPERTY(EditAnywhere, Category = "DataLayer")
	TObjectPtr<const UDataLayerAsset> DataLayerAsset2;
	
	virtual void BeginPlay() override;
};
