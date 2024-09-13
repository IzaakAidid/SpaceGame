// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMonster.h"

// Sets default values
ATestMonster::ATestMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_corruptionSpread = 2.0;
}

// Called when the game starts or when spawned
void ATestMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

