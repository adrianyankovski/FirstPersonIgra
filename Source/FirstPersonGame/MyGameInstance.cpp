// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"



void UMyGameInstance::Reset()
{

    Health = 100.0f;
    MaxHealth = 100.0f;
    clipAmmo = 12;
    totalAmmo = 64;
    XP = 0;
    XPToLevelUp = 2;
    PlayerLevel = 1;
}
