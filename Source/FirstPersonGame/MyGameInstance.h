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
		float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int clipAmmo = 12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int totalAmmo = 64;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int XP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int XPToLevelUp = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int PlayerLevel = 1;
	
	

public:
	float GetHealth() const;
	float GetMaxHealth() const;
	int GetClipAmmo() const;
	int GetTotalAmmo() const;
	int GetXP() const;
	int GetXPToLevelUp() const;
	int GetPlayerLevel() const;
	void Reset();

};
