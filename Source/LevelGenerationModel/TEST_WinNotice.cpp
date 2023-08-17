// Fill out your copyright notice in the Description page of Project Settings.


#include "TEST_WinNotice.h"

// Sets default values
ATEST_WinNotice::ATEST_WinNotice()
{
	SetHidden(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	MeshComponent->SetupAttachment(RootComponent);
}

UStaticMeshComponent* ATEST_WinNotice::GetMeshComponent() const
{
	return MeshComponent;
}

// Called when the game starts or when spawned
void ATEST_WinNotice::BeginPlay()
{
	Super::BeginPlay();
}
