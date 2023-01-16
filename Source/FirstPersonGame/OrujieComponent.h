// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OrujieComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSONGAME_API UOrujieComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOrujieComponent();

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
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
