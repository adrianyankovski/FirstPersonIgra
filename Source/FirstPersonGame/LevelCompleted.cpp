// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelCompleted.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Geroiche.h"
#include "GameModeDiplomna.h"
#include "Kismet/GameplayStatics.h"
#include "Geroiche.h"
#include "Protivnik.h"
#include "OrujieComponent.h"
#include "MyGameInstance.h"

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

void ALevelCompleted::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
		UWorld* World = GetWorld();
		if (World)
		{
			TArray<AActor*> AllActors;
			UGameplayStatics::GetAllActorsOfClass(World, AProtivnik::StaticClass(), AllActors);
			AGeroiche* Char = Cast<AGeroiche>(OtherActor);
			if (Char)
			{
				if (AllActors.Num() <= 0 || (Char->WeaponComponent->totalAmmo == 0 && Char->WeaponComponent->clipAmmo == 0))
				{
				
					AGameModeFPS* MyGameMode = Cast<AGameModeFPS>(UGameplayStatics::GetGameMode(GetWorld()));
					if (MyGameMode)
					{

						UMyGameInstance* GameInstance1 = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
						if (GameInstance1) {
							GameInstance1->Health = Char->Health;
							GameInstance1->MaxHealth = Char->MaxHealth;
							GameInstance1->clipAmmo = Char->WeaponComponent->clipAmmo;
							GameInstance1->totalAmmo = Char->WeaponComponent->totalAmmo;
							GameInstance1->XP = Char->XP;
							GameInstance1->XPToLevelUp = Char->XPToLevelUp;
							GameInstance1->PlayerLevel = Char->PlayerLevel;
							GameInstance1->MaxWalkSpeed = Char->GetCharacterMovement()->MaxWalkSpeed;
						}


							FString CurrentMapName = GetWorld()->GetMapName();
							CurrentMapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, CurrentMapName);
							if (CurrentMapName.Equals("FirstPersonMap")) {
								MyGameMode->Level2(true);
							}
							if (CurrentMapName.Equals("NewMap1")) {
								MyGameMode->Level3(true);
							}
							if(CurrentMapName.Equals("NewMap2")){
								MyGameMode->RestartGame(true);
							}
						
					}
				}
			
			}
		}	
}



