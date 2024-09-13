// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMonster.h"

// Sets default values
ATestMonster::ATestMonster()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    m_corruptionSpread = 2.0;

    MonsterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Monster Mesh"));
    RootComponent = MonsterMesh;
    MonsterMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    MonsterMesh->SetRelativeLocation(FVector(-200, -1000, 0));

    m_movingForward = true;
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
    MoveMonster(DeltaTime);

    if (MonsterMesh->GetRelativeLocation().Y > 1000)
    {
        m_movingForward = false;
    }
    else if (MonsterMesh->GetRelativeLocation().Y < -1000)
    {
        m_movingForward = true;
    }
}

void ATestMonster::MoveMonster(float DeltaTime)
{
    if (m_movingForward)
    {
        FVector newPossition = MonsterMesh->GetRelativeLocation() + FVector(0, 1000, 0) * DeltaTime;
        MonsterMesh->SetRelativeLocation(newPossition);
    }
    else
    {
        FVector newPossition = MonsterMesh->GetRelativeLocation() + FVector(0, -1000, 0) * DeltaTime;
        MonsterMesh->SetRelativeLocation(newPossition);
    }
}

