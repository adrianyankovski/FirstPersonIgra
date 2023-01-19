// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Protivnik.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	CollisionSphere->InitSphereRadius(3.0f);

	RootComponent = CollisionSphere;

	ProjectileMovement =
		CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->UpdatedComponent = CollisionSphere;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0;

	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AProtivnik* Protivnik = Cast<AProtivnik>(OtherActor);
	if (Protivnik) {
		if (OtherComp->GetName() == "Head Hitbox") {
			Protivnik->TakeDamageProtivnik(100.f);
			Destroy();
		}
		else if (OtherComp->GetName() == "Spine Hitbox") {
			Protivnik->TakeDamageProtivnik(40.f);
			Destroy();
		}
		else if (OtherComp->GetName() == "LeftLeg HitBox") {
			Protivnik->TakeDamageProtivnik(30.f);
			Protivnik->SetSpeed(Protivnik->GetSpeed() * slowDown);
			Destroy();
		}
		else if (OtherComp->GetName() == "RightLeg HitBox") {
			Protivnik->TakeDamageProtivnik(30.f);
			Protivnik->SetSpeed(Protivnik->GetSpeed() * slowDown);
			Destroy();
		}
		else if (OtherComp->GetName() == "RightForeArm HitBox") {
			Protivnik->TakeDamageProtivnik(20.f);
			Protivnik->SetDamage(Protivnik->GetSpeed() -1);
			Protivnik->RememberDamage -= 1;
			Destroy();
		}
		else if (OtherComp->GetName() == "LeftForeArm HitBox") {
			Protivnik->TakeDamageProtivnik(20.f);
			Protivnik->SetDamage(Protivnik->GetSpeed() - 1);
			Protivnik->RememberDamage -= 1;
			Destroy();
		}
		else if (OtherComp->GetName() == "RightHand HitBox") {
			Protivnik->TakeDamageProtivnik(10.f);
			Protivnik->SetDamage(Protivnik->GetSpeed() -1);
			Protivnik->RememberDamage -= 1;
			Destroy();
		}
		else if (OtherComp->GetName() == "LeftHand HitBox") {
			Protivnik->TakeDamageProtivnik(10.f);
			Protivnik->SetDamage(Protivnik->GetSpeed() -1);
			Protivnik->RememberDamage -= 1;
			Destroy();
		}

	}

}


