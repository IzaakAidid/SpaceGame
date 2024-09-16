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
	CorruptionRadius->InitSphereRadius(0);
	CorruptionRadius->SetupAttachment(RootComponent);
	CorruptionRadius->SetCollisionProfileName("OverlapAll");
	CorruptionRadius->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CorruptionRadius->SetRelativeLocation(FVector(0, 0, 50));

	m_isCorrrupted = false;
	m_maxCorruptionRadius = 200.0f;
	m_corruptionAmount = 0.0f;

}

// Called when the game starts or when spawned
void ALightBulbs::BeginPlay()
{
	Super::BeginPlay();

	CorruptionRadius->OnComponentBeginOverlap.AddDynamic(this, &ALightBulbs::CorruptionOverlapBegin);

}

// Called every frame
void ALightBulbs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isCorrrupted)
	{
		float newRadius = CorruptionRadius->GetUnscaledSphereRadius() + 100.0 * DeltaTime;

		if (newRadius > m_maxCorruptionRadius)
			CorruptionRadius->SetSphereRadius(m_maxCorruptionRadius);
		else
			CorruptionRadius->SetSphereRadius(newRadius);
	}
	currentRadius = CorruptionRadius->GetUnscaledSphereRadius();
}

float ALightBulbs::SpreadCorruption(AActor* corruptedActor)
{
	//Use To find the "corruption" passed onto this bulb from the corruptActor

	//find the distance between the corrupt Bulb and this one
	float distanceFrom = GetDistanceTo(corruptedActor);

	// Using the max fall of range of corruption (the size of the corruption radius), then turning it into a percentage, we can find the amount of corruption spread
	float spreadAmount = 0; //fix this shit

	return spreadAmount;
}


void ALightBulbs::ApplyCorruption(AActor* corruptedActor)
{
	//This bulb was hit by a corrupt bulb

	ALightBulbs* corruptLightBulb = Cast<ALightBulbs>(corruptedActor);

	if (corruptLightBulb)//nullptr check
	{
		m_corruptionAmount = SpreadCorruption(corruptLightBulb);//Get the amout of corruption from the corrupt light bulb
		m_isCorrrupted = corruptLightBulb->m_isCorrrupted; //this function will only be called when the corrupt Actor is corrutp but better safe then sorry
	}
}

void ALightBulbs::CorruptionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if the corrupt lightbulb is hitting something else that can be corrupted

	if (OtherActor->IsA(ALightBulbs::StaticClass()) && OtherActor != this)
	{
		ALightBulbs* hitBulb = Cast<ALightBulbs>(OtherActor);
		if (hitBulb != nullptr && hitBulb->m_isCorrrupted == false)//make sure bulb isn't already corrupted
			hitBulb->ApplyCorruption(Cast<ALightBulbs>(this));
	}
}

void ALightBulbs::BecomeCorrupt(AActor* corruptActor)
{
	//Only Call when corrupted by main source of corruption

	ATestMonster* corruptedMonster = Cast<ATestMonster>(corruptActor);
	if (corruptedMonster)
	{
		m_isCorrrupted = true;
		m_corruptionAmount = 2.0;
	}
}
