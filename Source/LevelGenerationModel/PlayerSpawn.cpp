// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpawn.h"

// Sets default values
APlayerSpawn::APlayerSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}
