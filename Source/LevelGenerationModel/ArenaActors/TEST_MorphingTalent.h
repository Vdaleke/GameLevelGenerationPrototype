// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TEST_MorphingTalent.generated.h"

UCLASS()
class LEVELGENERATIONMODEL_API ATEST_MorphingTalent : public AActor
{
	GENERATED_BODY()

public:
	ATEST_MorphingTalent();

	[[nodiscard]] UStaticMeshComponent* GetMeshComponent() const;

protected:
	UFUNCTION()
	void UseMorphingTalent(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                       class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                       const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComponent;
};
