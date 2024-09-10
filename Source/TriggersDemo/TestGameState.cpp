// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameState.h"

void ATestGameState::ManageWorldState()
{
	if (nullptr)//Something triggers a increase in world unstabillity
	{
		m_WorldState++;
		if (m_WorldState > 3) { m_WorldState = 3; };
	}
	if (nullptr)//Something triggers a decrease in world unstabillity
	{
		m_WorldState--;
		if (m_WorldState < 0) { m_WorldState = 0; };
	}

	switch (m_WorldState)
	{
	case 0: //Calming world
		m_MonsterMultiplier = 0.8;
		break;
	case 1://Default State
		m_MonsterMultiplier = 1.0;
		break;
	case 2://Troubled State
		m_MonsterMultiplier = 1.2;
		break;
	case 3://Dire State
		m_MonsterMultiplier = 1.5;
		break;
	}
}

void ATestGameState::ManageMonsterState()
{
	//Get Monster Hearing Radius
}
