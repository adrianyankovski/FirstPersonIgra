// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelCompleted.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Geroiche.h"
#include "GameModeDiplomna.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelCompleted::ALevelCompleted()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = DoorMesh;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	CollisionComponent -> SetupAttachment(DoorMesh);
	


}

// Called when the game starts or when spawned
void ALevelCompleted::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ALevelCompleted::OnHit);
	
}

// Called every frame
void ALevelCompleted::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelCompleted::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OTherCOmp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

	ACharacter* Char = Cast<ACharacter>(OtherActor);

	if (Char)
	{
		AGameModeFPS* MyGameMode =
			Cast<AGameModeFPS>(UGameplayStatics::GetGameMode(GetWorld()));
		if (MyGameMode) {
			MyGameMode->RestartGame(true);
		}
	}

}

