// Fill out your copyright notice in the Description page of Project Settings.


#include "TEST_Teleport.h"

#include "GlobalLevelGameMode.h"

// Sets default values
ATEST_Teleport::ATEST_Teleport()
{
	SetHidden(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetGenerateOverlapEvents(false);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ATEST_Teleport::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ATEST_Teleport::BeginPlay()
{
	Super::BeginPlay();
}

UStaticMeshComponent* ATEST_Teleport::GetMeshComponent() const
{
	return MeshComponent;
}

void ATEST_Teleport::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	AGlobalLevelGameMode* GameMode = Cast<AGlobalLevelGameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		if (GameMode->GetCurrentLevel() != GameMode->GetNumberOfLevels())
		{
			GameMode->GoToArena(GameMode->GetCurrentLevel() + 1, OtherActor);
		}

		SetActorHiddenInGame(true);
		MeshComponent->SetGenerateOverlapEvents(false);
	}
}
