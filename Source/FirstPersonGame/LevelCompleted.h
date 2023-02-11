// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelCompleted.generated.h"

UCLASS()
class FIRSTPERSONGAME_API ALevelCompleted : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelCompleted();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComponent;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OTherCOmp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& Hit); 

};
