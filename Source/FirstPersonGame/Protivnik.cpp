// Fill out your copyright notice in the Description page of Project Settings.


#include "Protivnik.h"

#include "Components/BoxComponent.h"
#include "Geroiche.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "TimerManager.h"

// Sets default values
AProtivnik::AProtivnik()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);

	AIPerComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	SightConfig->SightRadius = 1250.f;
	SightConfig->LoseSightRadius = 1280.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->SetMaxAge(0.1f);

	AIPerComp->ConfigureSense(*SightConfig);
	AIPerComp->SetDominantSense(SightConfig->GetSenseImplementation());
	AIPerComp->OnPerceptionUpdated.AddDynamic(this, &AProtivnik::OnSensed);
	
	MovementSpeed = 375.f;
	DamageValue = 5.0f;
	RememberDamage = 5.0f;
	CurrentVelocity = FVector::ZeroVector;

	HeadHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Head Hitbox"));
	HeadHitbox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "Head");

	SpineHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spine Hitbox"));
	SpineHitbox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "Spine");

	LeftLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftLeg Hitbox"));
	LeftLegHitbox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "LeftLeg");

	RightLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightLeg Hitbox"));
	RightLegHitbox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "RightLeg");

	RightHandHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHand Hitbox"));
	RightHandHitbox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "RightHandIndex2");

	RightForeArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightForeArm Hitbox"));
	RightForeArmHitbox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "RightForeArm");

	LeftHandHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHand Hitbox"));
	LeftHandHitbox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "LeftHandIndex2");

	LeftForeArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftForeArm Hitbox"));
	LeftForeArmHitbox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "LeftForeArm");

	
	DistanceSquared = BIG_NUMBER;

}

// Called when the game starts or when spawned
void AProtivnik::BeginPlay()
{
	Super::BeginPlay();
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AProtivnik::OnHit);
	BaseLocation = this->GetActorLocation();
}

//Called Every Frame

void AProtivnik::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (MovementSpeed == 0.f) {
		DamageValue = 0;

	}
	else {
		DamageValue = RememberDamage;
	}
	if (!CurrentVelocity.IsZero())
	{
		NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
		if (BackToBaseLocation)
		{
			if ((NewLocation - BaseLocation).SizeSquared2D() < DistanceSquared)
			{
				DistanceSquared = (NewLocation - BaseLocation).SizeSquared2D();
			}
			else
			{
				CurrentVelocity = FVector::ZeroVector;
				DistanceSquared = BIG_NUMBER;
				BackToBaseLocation = false;

				SetNewRotation(GetActorForwardVector(), GetActorLocation());
			}

		}

		else
		{
			TimeSinceLastSeen += DeltaTime;
			if (TimeSinceLastSeen > Timeout)
			{
				FVector dir = BaseLocation - GetActorLocation();
				dir.Z = 0.0f;
				CurrentVelocity = dir.GetSafeNormal() * MovementSpeed;
				BackToBaseLocation = true;
				DistanceSquared = BIG_NUMBER;
				TimeSinceLastSeen = 0;
				SetNewRotation(BaseLocation, GetActorLocation());
			}
		}


		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void AProtivnik::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AProtivnik::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AGeroiche* Geroiche = Cast<AGeroiche>(OtherActor);
	
	if (Geroiche) {
		MovementSpeed = 0.f;
		Geroiche->TakeDamageGeroiche(DamageValue);
		GetWorldTimerManager().SetTimer(CheckTimerHandle, this, &AProtivnik::RestoreSpeed, 0.5f, false);

	}
	

	
}

void AProtivnik::OnSensed(const TArray<AActor*>& UpdatedActors)
{
	for (int i = 0; i < UpdatedActors.Num(); i++)
	{
		FActorPerceptionBlueprintInfo Info;

		AIPerComp->GetActorsPerception(UpdatedActors[i], Info);

		if (Info.LastSensedStimuli[0].WasSuccessfullySensed())
		{
			LastPlayerSeenLocation = UpdatedActors[i]->GetActorLocation();
			FVector dir = UpdatedActors[i]->GetActorLocation() - GetActorLocation();
			dir.Z = 0.0f;
			CurrentVelocity = dir.GetSafeNormal() * MovementSpeed;
			SetNewRotation(UpdatedActors[i]->GetActorLocation(), GetActorLocation());
			BackToBaseLocation = false;
		}
		else
		{
			FVector dir = LastPlayerSeenLocation - GetActorLocation();
			dir.Z = 0.0f;
			if (dir.SizeSquared2D() > 1.0f)
			{
				CurrentVelocity = dir.GetSafeNormal() * MovementSpeed;
				BackToBaseLocation = false;

				SetNewRotation(LastPlayerSeenLocation, GetActorLocation());
			}
			else
			{
				dir = BaseLocation - GetActorLocation();
				dir.Z = 0.0f;
				if (dir.SizeSquared2D() > 1.0f)
				{
					CurrentVelocity = dir.GetSafeNormal() * MovementSpeed;
					BackToBaseLocation = true;

					SetNewRotation(BaseLocation, GetActorLocation());
				}
				else
				{
					CurrentVelocity = FVector::ZeroVector;
					BackToBaseLocation = false;
				}
			}
		}
	}
}


void AProtivnik::SetNewRotation(FVector TargetPosition, FVector CurrentPosition)
{


	FVector NewDirection = TargetPosition - CurrentPosition;
	NewDirection.Z = 0.0f;

	EnemyRotation = NewDirection.Rotation();

	SetActorRotation(EnemyRotation);


}

void AProtivnik::TakeDamageProtivnik(float DamageAmount)
{
	Health -= DamageAmount;

	if (Health <= 0.0f) {
		Destroy();
	}
}

void AProtivnik::SetSpeed(float speed)
{
	MovementSpeed = speed;
}

float AProtivnik::GetSpeed()
{
	return MovementSpeed;
}

float AProtivnik::GetDamage()
{
	return DamageValue;
}



void AProtivnik::SetDamage(float value)
{
	DamageValue = value;
}

void AProtivnik::RestoreSpeed()
{
	MovementSpeed = 375;
}





