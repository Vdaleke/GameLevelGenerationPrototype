// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TEST_Teleport.generated.h"

UCLASS()
class LEVELGENERATIONMODEL_API ATEST_Teleport : public AActor
{
	GENERATED_BODY()

public:
	ATEST_Teleport();

	[[nodiscard]] UStaticMeshComponent* GetMeshComponent() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComponent;

	UFUNCTION()
	void UseTeleport(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                 class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                 const FHitResult& SweepResult);
};
