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
	
	UDataLayerSubsystem* DataLayerSubsystem = UWorld::GetSubsystem<UDataLayerSubsystem>(GetWorld());

	UDataLayerEditorSubsystem* DataLayerEditorSubsystem = GEditor->GetEditorSubsystem<UDataLayerEditorSubsystem>();
	
	if (HasAuthority() && DataLayerAsset1 && DataLayerAsset2 && DataLayerSubsystem && DataLayerEditorSubsystem)
	{
		if ( DataLayerSubsystem->GetDataLayerInstanceRuntimeState(DataLayerAsset1) == EDataLayerRuntimeState::Activated)
		{
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Activated"));	
		}

		// DataLayerSubsystem->SetDataLayerInstanceRuntimeState(DataLayerAsset1, EDataLayerRuntimeState::Unloaded);

		if ( DataLayerSubsystem->GetDataLayerInstanceRuntimeState(DataLayerAsset1) == EDataLayerRuntimeState::Unloaded)
		{
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Unloaded"));	
		}

		bool bSuccess = false;

		LevelStreaming = ULevelStreamingDynamic::LoadLevelInstance(GWorld, "Arena", FVector::ZeroVector, FRotator::ZeroRotator, bSuccess);

		LevelStreaming->OnLevelLoaded.AddDynamic(this, &ACloneDataLayerGameModeBase::GetAllActorsOfClassFromStreamLevel);

		// DataLayerSubsystem->SetDataLayerInstanceRuntimeState(DataLayerAsset1, EDataLayerRuntimeState::Unloaded);
		
		// UDataLayerInstance* DataLayerInstance1 = DataLayerSubsystem->GetDataLayerInstanceFromAsset(DataLayerAsset1);

		// DataLayerSubsystem->RemoveDataLayer(DataLayerInstance1);
		
		// TArray<AActor*> LevelInstanceActors = DataLayerEditorSubsystem->GetActorsFromDataLayer(DataLayerInstance1);

		// UDataLayerInstance* DataLayerInstance2 = DataLayerSubsystem->GetDataLayerInstanceFromAsset(DataLayerAsset2);

		// DataLayerEditorSubsystem->AddActorsToDataLayer(LevelInstanceActors, DataLayerInstance2);

		// ULevelStreamingDynamic* StreamingLevel2 = ULevelStreamingDynamic::LoadLevelInstance(GWorld, "Arena", FVector(200.0,0.0,0.0), FRotator::ZeroRotator, bSuccess);
		
		// DataLayerSubsystem->SetDataLayerInstanceRuntimeState(DataLayerAsset2, EDataL
	}
}

void ACloneDataLayerGameModeBase::GetAllActorsOfClassFromStreamLevel()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Delegate on loaded"));

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, LevelStreaming->GetName());
	
	UDataLayerSubsystem* DataLayerSubsystem = UWorld::GetSubsystem<UDataLayerSubsystem>(GetWorld());
	
	UDataLayerEditorSubsystem* DataLayerEditorSubsystem = GEditor->GetEditorSubsystem<UDataLayerEditorSubsystem>();
	
	if (!LevelStreaming)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("no streaming level"));
		return;
	}

	if (LevelStreaming->GetLoadedLevel() && LevelStreaming->GetLoadedLevel()->Actors[1] && DataLayerSubsystem->GetDataLayerInstanceFromAsset(DataLayerAsset1) && DataLayerEditorSubsystem)
	{
	 	for (AActor* LevelActor : LevelStreaming->GetLoadedLevel()->Actors)
	 	{
	 		if(GEngine)
	 			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,  LevelActor->GetName());
	 	}
		
		bool result = DataLayerEditorSubsystem->AddActorToDataLayer(LevelStreaming->GetLoadedLevel()->Actors[1], DataLayerSubsystem->GetDataLayerInstanceFromAsset(DataLayerAsset1));
		if (result)
		{
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Added to data layer"));
		}
		else
		 {
		 	if(GEngine)
		 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Didn't add to data layer"));
		 }
	} else
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Something bad"));
		
		if(GEngine && !LevelStreaming->GetLoadedLevel())
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("can't get loaded level"));
			
		if(GEngine && LevelStreaming->GetLoadedLevel() && LevelStreaming->GetLoadedLevel()->Actors.Num() == 0 )
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("no actors"));

		if(GEngine && !DataLayerSubsystem->GetDataLayerInstanceFromAsset(DataLayerAsset1))
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("no data layer instance"));

		if(GEngine && !DataLayerEditorSubsystem)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("no data layer editor system"));
	}
}

