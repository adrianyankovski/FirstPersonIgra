// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeDiplomna.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void AGameModeFPS::BeginPlay()
{
	Super::BeginPlay();
}

void AGameModeFPS::RestartGame(bool Reset)
{
	if (Reset)
	{
		ResetLevel();
	}
}


void AGameModeFPS::ResetLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "FirstPersonMap");
}




