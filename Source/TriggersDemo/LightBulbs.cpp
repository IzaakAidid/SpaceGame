// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBulbs.h"
#include "TestMonster.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"

// Sets default values
ALightBulbs::ALightBulbs()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;


    LightBulbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightBulbMesh"));
    RootComponent = LightBulbMesh;
    LightBulbMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

    CorruptionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("CorruptionRadius"));
    CorruptionRadius->InitSphereRadius(200);
    CorruptionRadius->SetupAttachment(RootComponent);
    CorruptionRadius->SetCollisionProfileName("OverlapAll");
    CorruptionRadius->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CorruptionRadius->SetRelativeLocation(FVector(0, 0, 50));

    m_isCorrrupted = false;

}

// Called when the game starts or when spawned
void ALightBulbs::BeginPlay()
{
    Super::BeginPlay();

    CorruptionRadius->OnComponentBeginOverlap.AddDynamic(this, &ALightBulbs::HitboxOverlapBegin);


    GetWorldTimerManager().SetTimer(m_corruptCooldown, this, &ALightBulbs::CheckForCorruption, 1.0f);
}

// Called every frame
void ALightBulbs::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (m_isCorrrupted)
    {
        CorruptionRadius->SetSphereRadius(200.0f);
    }
    else
    {
        CorruptionRadius->SetSphereRadius(10.0f);
    }

}

float ALightBulbs::SpreadCorruption(AActor* actorHit)
{
    //find the distance between the bulbs
    float distanceFrom = GetDistanceTo(actorHit);

    // Using the max fall of range(the size of the hitbox), then turning it into a percentage, we can find
    float spreadAmount = 1.0 - (distanceFrom / CorruptionRadius->GetScaledSphereRadius()) / 100.0;

    return spreadAmount;
}

void ALightBulbs::CheckForCorruption()
{
    if (nullptr)//Check if its overlapping an actor
    {

    }
    else
    {
        m_isCorrrupted = false;
    }
}

void ALightBulbs::ApplyCorruption(AActor* actorHit)
{
    //Check for the actor hit and see what it is

    ATestMonster* monsterHit = Cast<ATestMonster>(actorHit);

    if (monsterHit)//In Monster Radius
    {
        m_isCorrrupted = true;
        m_corruptionAmount = monsterHit->GetCorruptionSpread();
    }
    else//In Radius of Corrupt Lights
    {
        ALightBulbs* corruptLightBulb = Cast<ALightBulbs>(actorHit);

        if (corruptLightBulb)
        {
            m_isCorrrupted = corruptLightBulb->m_isCorrrupted;
            m_corruptionAmount = SpreadCorruption(corruptLightBulb);
        }
    }
}

void ALightBulbs::HitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    if (OtherActor->IsA(ATestMonster::StaticClass()) && OtherActor != this)
    {
        ApplyCorruption(Cast<ATestMonster>(OtherActor));
    }
    else if (OtherActor->IsA(ALightBulbs::StaticClass()) && OtherActor != this)
    {
        ApplyCorruption(Cast<ALightBulbs>(OtherActor));
    }
}

