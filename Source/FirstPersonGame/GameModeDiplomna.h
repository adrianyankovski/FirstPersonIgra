// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeDiplomna.generated.h"

/**
 *
 */
	UCLASS()
	class FIRSTPERSONGAME_API AGameModeFPS : public AGameMode
{

	GENERATED_BODY()

public:
	void Level2(bool Reset);
	void Level3(bool Reset);
	void RestartGame(bool Reset);

private:

	void ResetLevel();

public:

	void BeginPlay() override;




};

