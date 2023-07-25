// Copyright Epic Games, Inc. All Rights Reserved.

#include "CloneDataLayerGameModeBase.h"

#include "AssetDefinitionDefault.h"
#include "Editor.h"
#include "Containers/Array.h"
#include "Engine/LevelStreamingDynamic.h"
#include "DataLayer/DataLayerEditorSubsystem.h"
#include "Engine/World.h"
#include "WorldPartition/DataLayer/DataLayerInstance.h"
#include "Subsystems/SubsystemCollection.h"
#include "WorldPartition/DataLayer/DataLayerSubsystem.h"

void ACloneDataLayerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	/*
	UDataLayerSubsystem* DataLayerSubsystem = UWorld::GetSubsystem<UDataLayerSubsystem>(GetWorld());

	UDataLayerEditorSubsystem* DataLayerEditorSubsystem = GEditor->GetEditorSubsystem<UDataLayerEditorSubsystem>();
	
	if (HasAuthority() && DataLayerAsset1 && DataLayerAsset2 && DataLayerSubsystem && DataLayerEditorSubsystem) {
			if ( DataLayerSubsystem->GetDataLayerInstanceRuntimeState(DataLayerAsset1) == EDataLayerRuntimeState::Activated)
			{
				if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Activated"));	
			}

			DataLayerSubsystem->SetDataLayerInstanceRuntimeState(DataLayerAsset1, EDataLayerRuntimeState::Unloaded);

			if ( DataLayerSubsystem->GetDataLayerInstanceRuntimeState(DataLayerAsset1) == EDataLayerRuntimeState::Unloaded)
			{
				if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Unloaded"));	
			}

			
			// bool bSuccess;
			// ULevelStreamingDynamic* StreamingLevel1 = ULevelStreamingDynamic::LoadLevelInstance(GWorld, "Arena", FVector::ZeroVector, FRotator::ZeroRotator, bSuccess);

			// DataLayerSubsystem->SetDataLayerInstanceRuntimeState(DataLayerAsset1, EDataLayerRuntimeState::Unloaded);
		
			// UDataLayerInstance* DataLayerInstance1 = DataLayerSubsystem->GetDataLayerInstanceFromAsset(DataLayerAsset1);

			// DataLayerSubsystem->RemoveDataLayer(DataLayerInstance1);
		
			// TArray<AActor*> LevelInstanceActors = DataLayerEditorSubsystem->GetActorsFromDataLayer(DataLayerInstance1);

			// UDataLayerInstance* DataLayerInstance2 = DataLayerSubsystem->GetDataLayerInstanceFromAsset(DataLayerAsset2);

			// DataLayerEditorSubsystem->AddActorsToDataLayer(LevelInstanceActors, DataLayerInstance2);

			// ULevelStreamingDynamic* StreamingLevel2 = ULevelStreamingDynamic::LoadLevelInstance(GWorld, "Arena", FVector(200.0,0.0,0.0), FRotator::ZeroRotator, bSuccess);
		
			// DataLayerSubsystem->SetDataLayerInstanceRuntimeState(DataLayerAsset2, EDataLayerRuntimeState::Unloaded);
	}
	*/
}
