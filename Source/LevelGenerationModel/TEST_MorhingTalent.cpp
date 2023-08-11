// Fill out your copyright notice in the Description page of Project Settings.


#include "TEST_MorhingTalent.h"

#include "GlobalLevelGameMode.h"

// Sets default values
ATEST_MorhingTalent::ATEST_MorhingTalent()
{
	SetHidden(true);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetGenerateOverlapEvents(false);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ATEST_MorhingTalent::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ATEST_MorhingTalent::BeginPlay()
{
	Super::BeginPlay();
}

UStaticMeshComponent* ATEST_MorhingTalent::GetMeshComponent() const
{
	return MeshComponent;
}


void ATEST_MorhingTalent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult)
{
	AGlobalLevelGameMode* GameMode = Cast<AGlobalLevelGameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		GameMode->ActivateTeleportOnCurrentArena();
		SetActorHiddenInGame(true);
		MeshComponent->SetGenerateOverlapEvents(false);
	}
}
