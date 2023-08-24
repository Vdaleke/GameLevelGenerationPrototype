// Fill out your copyright notice in the Description page of Project Settings.


#include "TEST_MorphingTalent.h"

#include "LevelGenerationModel/GlobalLevelGameMode.h"

ATEST_MorphingTalent::ATEST_MorphingTalent()
{
	SetHidden(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetGenerateOverlapEvents(false);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ATEST_MorphingTalent::UseMorphingTalent);
}

UStaticMeshComponent* ATEST_MorphingTalent::GetMeshComponent() const
{
	return MeshComponent;
}

void ATEST_MorphingTalent::UseMorphingTalent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                             const FHitResult& SweepResult)
{
	if (AGlobalLevelGameMode* GameMode = Cast<AGlobalLevelGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->GetLevelController()->ActivateTeleportOnCurrentArena();
		Destroy();
	}
}

void ATEST_MorphingTalent::ShowMorphingTalent()
{
	SetActorHiddenInGame(false);
	MeshComponent->SetGenerateOverlapEvents(true);
}
