// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TestGameState.generated.h"

/**
 *
 */
UCLASS()
class TRIGGERSDEMO_API ATestGameState : public AGameStateBase
{
	GENERATED_BODY()


protected:
	int m_WorldState;
	int m_MonsterTolerance;
	float m_MonsterMultiplier;

public:
	void ManageWorldState();
	void ManageMonsterState();
	void IncrementMonsterMultiplier(float IncrementAmount) { m_MonsterMultiplier + IncrementAmount; };
};
