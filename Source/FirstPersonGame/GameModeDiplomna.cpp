// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeDiplomna.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MyGameInstance.h"

void AGameModeFPS::BeginPlay()
{
	Super::BeginPlay();
}

void AGameModeFPS::Level2(bool Reset)
{
	UGameplayStatics::OpenLevel(GetWorld(), "NewMap1");
}

void AGameModeFPS::Level3(bool Reset)
{
	UGameplayStatics::OpenLevel(GetWorld(), "NewMap2");
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
	UGameplayStatics::OpenLevel(GetWorld(), "NewMap");
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance) {
		MyGameInstance->Reset();
	}
}




