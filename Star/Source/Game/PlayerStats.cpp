#include "PlayerStats.h"
#include <iostream>
#include <Game.h>


bool PlayerStats::Dodge(int EnemyAttackSpeed, int EnemyLuck)
{
int DodgeSuccessRate =	abs((this->Luck + this->Speed + rand() % 20) / 3); // combine  player stats and if they are higher than the attacking enemy's attack speed and luck dodge will succeed

int EnemyAttackSuccessRate = abs((EnemyAttackSpeed + EnemyLuck + rand() % 15) / 3); 
if (DodgeSuccessRate > EnemyAttackSuccessRate) {

	return true; /// meaning player has dodged the atttack
 }

else
	return false;
}

void PlayerStats::Attack()
{
}

void PlayerStats::TakeDamage(int EnemyAttackPower)
{
	PlayerHealth = PlayerHealth - EnemyAttackPower;
}

void PlayerStats::EnterPlayerName()
{
	std::string EnterName;

	cin >> EnterName;

	*PlayerName = EnterName;
}
int* PlayerStats::DeterminePointsForRound(int  Round, int Points)
{
	
	if (Round <= 1)
	{
		Points = Points * 1.5;
	}
else if (Round == 2)
	{
		Points = Points;
	}

	else 
	{
		Points = Points / 2;
	}
	return &Points;
}

void PlayerStats::DeterminStatPointsAmount(float CompletionTime, int Round, int* PStats) // structure not final values
{
	

	//if (CompletionTime > 1 && CompletionTime <= 30) // the fastest
	//{
	//	*PlayerStatPoints = *PlayerStatPoints+*DeterminePointsForRound(Round,HighTierStatPoints);

	//}
	//else if (CompletionTime > 16 && CompletionTime < 160) { // normnal speed
	//	*PlayerStatPoints = *PlayerStatPoints + *DeterminePointsForRound(Round, MiddleTirStatPoints);
	//}
	//else if (CompletionTime > 160) { // slow solving speed
	//	*PlayerStatPoints = *PlayerStatPoints + *DeterminePointsForRound(Round, LowTierStatPoints);
	//}
	//
	if (CompletionTime > 1 && CompletionTime <= 30) // the fastest
	{
	*Points=	*DeterminePointsForRound(Round, HighTierStatPoints);

	}
	else if (CompletionTime > 16 && CompletionTime < 160) { // normnal speed
		*Points= *DeterminePointsForRound(Round, MiddleTirStatPoints);
	}
	else if (CompletionTime > 160) { // slow solving speed
		*Points = *DeterminePointsForRound(Round, LowTierStatPoints);
	}
	*PStats = *PStats + *Points;

	
}

int PlayerStats::AssignStatPoints(int* Stat, int PointAmount)
{
	/// potentially use buttons with cin that will determine the number of points used
	int ChanceForBonusPoints = rand() % 50;

	if (*PlayerStatPoints > 0 && *Stat <90 )
	{


		if (ChanceForBonusPoints >= 17 || ChanceForBonusPoints <= 26) {
			*Stat = *Stat +PointAmount * 2; // if lucky gets double points
		}
		else {
			*Stat = *Stat +PointAmount;
		}
		*PlayerStatPoints = *PlayerStatPoints- PointAmount;
		if (*Stat <=90)
		{
			return *Stat;
		}
		else
		{
			return *Stat - (*Stat - 90);
		}
	}
	else
		return *Stat;
}

int PlayerStats::EarnedPoints(float CompletionTime, int Round)
{
	int Points = 0;
	if (CompletionTime > 1 && CompletionTime <= 30) // the fastest
	{
		Points = *DeterminePointsForRound(Round, HighTierStatPoints);

	}
	else if (CompletionTime > 16 && CompletionTime < 160) { // normnal speed
		Points = *DeterminePointsForRound(Round, MiddleTirStatPoints);
	}
	else if (CompletionTime > 160) { // slow solving speed
		Points = *DeterminePointsForRound(Round, LowTierStatPoints);
	}
	

	return Points;
}

PlayerStats::~PlayerStats()
{
	/* PlayerAttackPower = NULL;
	 PlayerHealth = NULL;
	 PlayerSpeed = NULL;
	PlayerLuck = NULL;
	 PlayerIntelligence = NULL;
	 PlayerMana = NULL;
	 PlayerMagicPower = NULL;
	 PlayerAttackSpeed = NULL;
	 PlayerStatPoints = NULL;*/
}


