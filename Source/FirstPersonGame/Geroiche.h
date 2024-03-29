// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/CharacterMovementComponent.h"
#include "CoreMinimal.h"
#include "OrujieComponent.h"
#include "GameFramework/Character.h"
#include "Geroiche.generated.h"

UCLASS()
class FIRSTPERSONGAME_API AGeroiche : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGeroiche();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* HandsMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* MuzzleLocation;

	UPROPERTY(VisibleAnywhere, BLueprintReadOnly, Category = Camera)
		class UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float TurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float LookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		//FRotator GunOffset2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponComponent)
		UOrujieComponent* WeaponComponent;


protected:

	const float TimeDilation = 0.1f;
	FTimerHandle SlowHandle;
	FTimerHandle FireTimerHandle;

	void OnFire();
	void SlowTime();
	void RestoreTime();

	
	bool Wait = true;
	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookAtRate(float Rate);
	void True();
	void ReloadWeapon();

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void TriggerOutOfAmmoPopUp();




public:

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* EmptyMagazineSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* ReloadSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	class UAnimInstance* AnimInstance;

	class UWorld* World;

	FRotator SpawnRotation;
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Health = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int PlayerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int XP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int XPToLevelUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxHealth = 100.f;

public:
	void TakeDamageGeroiche(float DamageAmount);
	void LevelUp();




};
