// Fill out your copyright notice in the Description page of Project Settings.


#include "Orujie.h"

// Sets default values
AOrujie::AOrujie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	maxTotalAmmo = 100;
	maxClipAmmo = 12;
	totalAmmo = 64;
	clipAmmo = 12;
	reloadTime = 1.0f;

}

// Called when the game starts or when spawned
void AOrujie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrujie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

