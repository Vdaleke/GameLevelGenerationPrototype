// Fill out your copyright notice in the Description page of Project Settings.


#include "TEST_Teleport.h"

#include "LevelGenerationModel/GlobalLevelGameMode.h"

// Sets default values
ATEST_Teleport::ATEST_Teleport()
{
	SetHidden(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetGenerateOverlapEvents(false);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ATEST_Teleport::UseTeleport);
}

UStaticMeshComponent* ATEST_Teleport::GetMeshComponent() const
{
	return MeshComponent;
}

void ATEST_Teleport::UseTeleport(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	if (AGlobalLevelGameMode* GameMode = Cast<AGlobalLevelGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->GoToArena(GameMode->GetCurrentLevel() + 1, OtherActor);

		SetActorHiddenInGame(true);
		MeshComponent->SetGenerateOverlapEvents(false);
	}
}
