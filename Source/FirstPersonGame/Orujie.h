// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Orujie.generated.h"

UCLASS()
class FIRSTPERSONGAME_API AOrujie : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrujie();
	
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Weapon)
		int maxTotalAmmo;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Weapon)
		int maxClipAmmo;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Weapon)
		int totalAmmo;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Weapon)
		int clipAmmo;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Weapon)
		float reloadTime;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
