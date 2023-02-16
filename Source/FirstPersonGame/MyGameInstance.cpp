// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

float UMyGameInstance::GetHealth() const
{
    return Health;
}

float UMyGameInstance::GetMaxHealth() const
{
    return MaxHealth;
}

int UMyGameInstance::GetClipAmmo() const
{
    return clipAmmo;
}

int UMyGameInstance::GetTotalAmmo() const
{
    return totalAmmo;
}

int UMyGameInstance::GetXP() const
{
    return XP;
}

int UMyGameInstance::GetXPToLevelUp() const
{
    return XPToLevelUp;
}

int UMyGameInstance::GetPlayerLevel() const
{
    return PlayerLevel;
}

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
