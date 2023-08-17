// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TEST_WinNotice.generated.h"

UCLASS()
class LEVELGENERATIONMODEL_API ATEST_WinNotice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATEST_WinNotice();

	[[nodiscard]] UStaticMeshComponent* GetMeshComponent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComponent;
};
