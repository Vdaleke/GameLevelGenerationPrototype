// Copyright Epic Games, Inc. All Rights Reserved.

#include "CloneDataLayerGameModeBase.h"

#include "AssetDefinitionDefault.h"
#include "Editor.h"
#include "Containers/Array.h"
#include "Engine/LevelStreamingDynamic.h"
#include "DataLayer/DataLayerEditorSubsystem.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "WorldPartition/DataLayer/DataLayerInstance.h"
#include "Subsystems/SubsystemCollection.h"
#include "WorldPartition/DataLayer/DataLayerSubsystem.h"

void ACloneDataLayerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	UDataLayerSubsystem* DataLayerSubsystem = UWorld::GetSubsystem<UDataLayerSubsystem>(GetWorld());
	
	if (HasAuthority() && DataLayerAsset1 && DataLayerAsset2 && DataLayerSubsystem)
	{
		if ( DataLayerSubsystem->GetDataLayerInstanceRuntimeState(DataLayerAsset1) == EDataLayerRuntimeState::Activated)
		{
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Activated"));	
		}
		
		bool bSuccess = false;

		LevelStreaming = ULevelStreamingDynamic::LoadLevelInstance(GWorld, "Arena", FVector::ZeroVector, FRotator::ZeroRotator, bSuccess);

		UDataLayerInstance* DataLayerInstance1 = DataLayerSubsystem->GetDataLayerInstanceFromAsset(DataLayerAsset1);

		/*
		if (TestActor->RemoveDataLayer(DataLayerAsset1) && GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Removed data layer 1 from Test Actor") );
		}
		*/

		const FVector SpawnLocation = FVector(200.0f,0.0f,0.0f);

		TestActor = GetWorld()->SpawnActor(SpawnedActorClass, &SpawnLocation, &FRotator::ZeroRotator);

		if (TestActor) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Spawned Actor") );
		} else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Cant spawn Actor") );
		}

		const UDataLayerInstance* DataLayerInstance2 = DataLayerSubsystem->GetDataLayerInstanceFromAsset(DataLayerAsset2);
		
		if (TestActor && TestActor->AddDataLayer(DataLayerInstance2) && GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Added data layer 2 to Test Actor") );
		}
		
		// LevelStreaming->OnLevelLoaded.AddDynamic(this, &ACloneDataLayerGameModeBase::GetAllActorsOfClassFromStreamLevel);

		// DataLayerSubsystem->SetDataLayerInstanceRuntimeState(DataLayerAsset1, EDataLayerRuntimeState::Unloaded);
		
		// if(GEngine && DataLayerInstance1)
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("DataLayerInstance1 laoded") );

		// DataLayerSubsystem->RemoveDataLayer(DataLayerInstance1);
		
	
		
		// if(GEngine && DataLayerInstance2)
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("DataLayerInstance2 laoded") );

		// DataLayerEditorSubsystem->AddActorsToDataLayer(Actors, DataLayerInstance2);

		// ULevelStreamingDynamic* StreamingLevel2 = ULevelStreamingDynamic::LoadLevelInstance(GWorld, "Arena", FVector(200.0,0.0,0.0), FRotator::ZeroRotator, bSuccess);
		
		// DataLayerSubsystem->SetDataLayerInstanceRuntimeState(DataLayerAsset2, EDataL
	}
}

void ACloneDataLayerGameModeBase::RemoveDataLayerFromActor(AActor* Actor)
{
	Actor->RemoveAllDataLayers();
}

void ACloneDataLayerGameModeBase::GetAllActorsOfClassFromStreamLevel()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Delegate on loaded"));

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, LevelStreaming->GetName());
	
	UDataLayerSubsystem* DataLayerSubsystem = UWorld::GetSubsystem<UDataLayerSubsystem>(GetWorld());
	
	if (!LevelStreaming)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("no streaming level"));
		return;
	}
	
}
