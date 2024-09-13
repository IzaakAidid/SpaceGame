// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestMonster.generated.h"

UCLASS()
class TRIGGERSDEMO_API ATestMonster : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float GetCorruptionSpread() { return m_corruptionSpread; };

protected:
	float m_corruptionSpread;

};
