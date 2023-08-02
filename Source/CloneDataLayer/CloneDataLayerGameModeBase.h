// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RayTracingBuiltInResources.h"
#include "UObject/ObjectPtr.h"
#include "Engine/World.h"
#include "Engine/LevelStreamingDynamic.h"
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
	
	UPROPERTY(EditAnywhere, Category = "DataLayer")
	AActor* TestActor;

	UPROPERTY(EditAnywhere, Category = "DataLayer")
	TSubclassOf<AActor> SpawnedActorClass;

	UPROPERTY(EditAnywhere)
	ULevelStreamingDynamic* LevelStreaming;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void RemoveDataLayerFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Meta = (WorldContext = WorldContextObject))
	void GetAllActorsOfClassFromStreamLevel();
};
