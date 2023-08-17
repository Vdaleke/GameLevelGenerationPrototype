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
	// Sets default values for this actor's properties
	ATEST_Teleport();

	[[nodiscard]] UStaticMeshComponent* GetMeshComponent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComponent;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
};
