
// Fill out your copyright notice in the Description page of Project Settings.


#include "Geroiche.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Projectile.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameModeDiplomna.h"
#include "TimerManager.h"
#include "OrujieComponent.h"


// Sets default values
AGeroiche::AGeroiche()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 95.0f);

	TurnRate = 45.0f;
	LookUpRate = 45.0f;
	XP = 0;
	PlayerLevel = 1;
	XPToLevelUp = 2;
	WeaponComponent = CreateDefaultSubobject<UOrujieComponent>(TEXT("Weapon Data"));
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->AddRelativeLocation(FVector(-39.65f, 1.75f, 64.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));

	HandsMesh->SetOnlyOwnerSee(true);
	HandsMesh->SetupAttachment(FirstPersonCamera);
	HandsMesh->bCastDynamicShadow = false;
	HandsMesh->CastShadow = false;
	HandsMesh->AddRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	HandsMesh->AddRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	GunMesh->SetOnlyOwnerSee(true);
	GunMesh->bCastDynamicShadow = false;
	GunMesh->CastShadow = false;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocation->SetupAttachment(GunMesh);
	//MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.0f, -17.0f, 15.0f);
	//GunOffset2 = FRotator(0.f,0.f, 10.f);


}

// Called when the game starts or when spawned
void AGeroiche::BeginPlay()
{
	Super::BeginPlay();

	GunMesh->AttachToComponent(HandsMesh,
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		TEXT("GripPoint"));

	World = GetWorld();
	AnimInstance = HandsMesh->GetAnimInstance();


}

// Called every frame
void AGeroiche::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGeroiche::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Slow", IE_Pressed, this, &AGeroiche::SlowTime);
	PlayerInputComponent->BindAction("ReloadWeapon", IE_Pressed, this, &AGeroiche::ReloadWeapon);

	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AGeroiche::OnFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGeroiche::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGeroiche::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AGeroiche::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AGeroiche::LookAtRate);
}
void AGeroiche::OnFire()
{

	if (World != NULL) {
		if (Wait) {
			if (WeaponComponent) {
				if (WeaponComponent->clipAmmo > 0) {
					SpawnRotation = GetControlRotation();

					SpawnLocation = ((MuzzleLocation != nullptr) ?
						MuzzleLocation->GetComponentLocation() :
						GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride =
						ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

					World->SpawnActor<AProjectile>(Projectile,
						SpawnLocation, SpawnRotation, ActorSpawnParams);

					if (FireSound != NULL) {
						UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

					}

					if (FireAnimation != NULL && AnimInstance != NULL)
					{
						AnimInstance->Montage_Play(FireAnimation, 0.3f);
					}

					WeaponComponent->clipAmmo -= 1;
				}
				else {
					if (EmptyMagazineSound != NULL) {
						UGameplayStatics::PlaySoundAtLocation(this, EmptyMagazineSound, GetActorLocation());
					}
					TriggerOutOfAmmoPopUp();
				}
			}
		}
	}
}

void AGeroiche::SlowTime()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeDilation);
	GetWorldTimerManager().SetTimer(SlowHandle, this, &AGeroiche::RestoreTime, 0.3f, false);
}

void AGeroiche::RestoreTime()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	GetWorldTimerManager().ClearTimer(SlowHandle);
}

void AGeroiche::MoveForward(float Value)
{
	if (Value != 0.0f) {
		AddMovementInput(GetActorForwardVector(), Value);

	}
}

void AGeroiche::MoveRight(float Value)
{
	if (Value != 0.0f) {
		AddMovementInput(GetActorRightVector(), Value);

	}
}

void AGeroiche::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AGeroiche::LookAtRate(float Rate)
{
	AddControllerPitchInput(Rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGeroiche::ReloadWeapon()
{
	if (WeaponComponent) {
		if (WeaponComponent->totalAmmo > 0) {

			if (WeaponComponent->clipAmmo != WeaponComponent->maxClipAmmo) {

				if (WeaponComponent->totalAmmo - (WeaponComponent->maxClipAmmo - WeaponComponent->clipAmmo) >= 0) {
					Wait = false;
					GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AGeroiche::True, WeaponComponent->reloadTime, false);
					WeaponComponent->totalAmmo -= (WeaponComponent->maxClipAmmo - WeaponComponent->clipAmmo);
					WeaponComponent->clipAmmo = WeaponComponent->maxClipAmmo;
					if (ReloadSound != NULL) {
						UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
					}
				}
				else {
					Wait = false;
					GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AGeroiche::True, WeaponComponent->reloadTime, false);
					WeaponComponent->clipAmmo += WeaponComponent->totalAmmo;
					WeaponComponent->totalAmmo = 0;
					if (ReloadSound != NULL) {
						UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
					}
				}
			}
		}
	}
}

void AGeroiche::LevelUp()
{
	if (XP == XPToLevelUp) {
		XP = 0;
		XPToLevelUp *= 2;
		PlayerLevel += 1;
	}
	if (PlayerLevel > 1) {
				
	}
}

void AGeroiche::True() {
	Wait = true;
}

void AGeroiche::TakeDamageGeroiche(float DamageAmount)
{
	Health -= DamageAmount;

	if (Health <= 0.0f) {
		Destroy();
		AGameModeFPS* MyGameMode =
			Cast<AGameModeFPS>(UGameplayStatics::GetGameMode(GetWorld()));
		if (MyGameMode) {
			MyGameMode->RestartGame(true);
		}
	}
}




