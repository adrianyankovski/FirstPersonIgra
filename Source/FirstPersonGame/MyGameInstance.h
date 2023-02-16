// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONGAME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()



public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		float Health ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		float MaxHealth ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int clipAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int totalAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int XP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int XPToLevelUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int PlayerLevel;
	
	

public:
	void Reset();

};
