// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Protivnik.generated.h"

UCLASS(Blueprintable)
class FIRSTPERSONGAME_API AProtivnik : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProtivnik();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* DamageCollision;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& Hit);

	UPROPERTY(VisibleDefaultsOnly, Category = Enemy)
		class UAIPerceptionComponent* AIPerComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Enemy)
		class UAISenseConfig_Sight* SightConfig;
	//Dali sa vidqni Actori or Perception componenta
	UFUNCTION()
		void OnSensed(const TArray<AActor*>& UpdatedActors);

	UPROPERTY(VisibleAnywhere, Category = Movement)
		FRotator EnemyRotation;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		FVector BaseLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)

		float TimeSinceLastSeen = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Timeout = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		FVector CurrentVelocity;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		float MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hitboxes")
		UBoxComponent* HeadHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hitboxes")
		UBoxComponent* SpineHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hitboxes")
		UBoxComponent* LeftLegHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hitboxes")
		UBoxComponent* RightLegHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hitboxes")
		UBoxComponent* RightHandHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hitboxes")
		UBoxComponent* RightForeArmHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hitboxes")
		UBoxComponent* LeftHandHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hitboxes")
		UBoxComponent* LeftForeArmHitbox;

	void SetNewRotation(FVector TargetPosition, FVector CurrentPosition);
	float RememberDamage;
	bool BackToBaseLocation;
	FTimerHandle CheckTimerHandle;
	FVector NewLocation;
	FVector LastPlayerSeenLocation;

	float DistanceSquared;

	UPROPERTY(EditAnywhere, BLueprintReadOnly)
		float Health = 100.0f;

	UPROPERTY(EditAnywhere)
		float DamageValue;

public:
	void TakeDamageProtivnik(float DamageAmount);
	void SetSpeed(float speed);
	float GetSpeed();
	float GetDamage();
	void SetDamage(float value);
	void RestoreSpeed();

};
