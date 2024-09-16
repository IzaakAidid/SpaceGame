// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMonster.h"
#include "LightBulbs.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

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


	CorruptionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("CorruptionRadius"));
	CorruptionRadius->InitSphereRadius(200);
	CorruptionRadius->SetupAttachment(RootComponent);
	CorruptionRadius->SetCollisionProfileName("OverlapAll");
	CorruptionRadius->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CorruptionRadius->SetRelativeLocation(FVector(0, 0, 50));

	m_movingForward = true;
}

// Called when the game starts or when spawned
void ATestMonster::BeginPlay()
{
	Super::BeginPlay();

	CorruptionRadius->OnComponentBeginOverlap.AddDynamic(this, &ATestMonster::CorruptionOverlapBegin);
}

// Called every frame
void ATestMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveMonster(DeltaTime);


}

void ATestMonster::MoveMonster(float DeltaTime)
{

	if (m_movingForward)
	{
		FVector newPossition = MonsterMesh->GetRelativeLocation() + FVector(0, 100, 0) * DeltaTime;
		MonsterMesh->SetRelativeLocation(newPossition);
	}
	else
	{
		FVector newPossition = MonsterMesh->GetRelativeLocation() + FVector(0, -100, 0) * DeltaTime;
		MonsterMesh->SetRelativeLocation(newPossition);
	}

	if (MonsterMesh->GetRelativeLocation().Y > 1000)
	{
		m_movingForward = false;
	}
	else if (MonsterMesh->GetRelativeLocation().Y < -1000)
	{
		m_movingForward = true;
	}
}

void ATestMonster::CorruptionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check For Actors that can be corrupted

	if (OtherActor->IsA(ALightBulbs::StaticClass()) && OtherActor != this)
	{
		ALightBulbs* HitBulb = Cast<ALightBulbs>(OtherActor);

		if (HitBulb)//nullptr check
			HitBulb->BecomeCorrupt(this);
	}
}

