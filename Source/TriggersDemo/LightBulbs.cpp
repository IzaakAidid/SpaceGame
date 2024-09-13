// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBulbs.h"
#include "TestMonster.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

// Sets default values
ALightBulbs::ALightBulbs()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	LightBulbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightBulbMesh"));
	RootComponent = LightBulbMesh;
	LightBulbMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CorruptionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("CorruptionRadius"));
	CorruptionRadius->SetSphereRadius(200);
	CorruptionRadius->SetupAttachment(RootComponent);
	CorruptionRadius->SetCollisionProfileName("OverlapAll");
	CorruptionRadius->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CorruptionRadius->SetRelativeLocation(FVector(0, 0, 50));


}

// Called when the game starts or when spawned
void ALightBulbs::BeginPlay()
{
	Super::BeginPlay();

	CorruptionRadius->OnComponentBeginOverlap.AddDynamic(this, &ALightBulbs::HitboxOverlapBegin);
}

// Called every frame
void ALightBulbs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

float ALightBulbs::SpreadCorruption(AActor* actorHit)
{
	//find the distance between the bulbs
	float distanceFrom = GetDistanceTo(actorHit);

	// Using the max fall of range(the size of the hitbox), then turning it into a percentage, we can find

	float spreadAmount = 1.0 - (distanceFrom / CorruptionRadius->GetScaledSphereRadius()) / 100.0;

	return spreadAmount;
}

void ALightBulbs::CheckCorruption(AActor* actorHit)
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
			m_isCorrrupted = true;
			m_corruptionAmount = SpreadCorruption(corruptLightBulb);
		}
	}
}

void ALightBulbs::HitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, (TEXT("Something Was Hit By Actor: %s"), GetActorNameOrLabel()));
	if (OtherActor->IsA(ATestMonster::StaticClass()) && OtherActor != this)
	{
		CheckCorruption(Cast<ATestMonster>(OtherActor));
	}
	else if (OtherActor->IsA(ALightBulbs::StaticClass()) && OtherActor != this)
	{
		ALightBulbs* hitLightBulb = Cast<ALightBulbs>(OtherActor);

		if (hitLightBulb)
			CheckCorruption(Cast<ALightBulbs>(OtherActor));
	}
}

