// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ShooterWeaponBase.h"

// Sets default values
AShooterWeaponBase::AShooterWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

