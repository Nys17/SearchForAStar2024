#pragma once
#include "RPGStats.h"
class PlayerStats :    public RPGStats
{
public:
	string* PlayerName = &Name ;
	int* PlayerAttackPower = &AttackPower ;
	int* PlayerHealth = &Health;
	int* PlayerSpeed = &Speed;
	int* PlayerLuck = &Luck ;
	int* PlayerIntelligence = &Intelligence;
	int* PlayerMana = &Mana ;
	int* PlayerMagicPower = &MagicPower ;
	int* PlayerAttackSpeed = &AttackSpeed;
	int* PlayerStatPoints = &StatPoints ;
	virtual bool Dodge(int EnemyAttackSpeed, int EnemyLuck);
	virtual void Attack();
	virtual void TakeDamage(int EnemyAttackPower);
	void EnterPlayerName();
	void DeterminStatPointsAmount(float CompletionTime, int Round, int* PStats); // determine the amout of stat pointsd recieved
	int AssignStatPoints(int* Stat, int PointAmount); // function for assigning the accumulated stat points
	int EarnedPoints(float CompletionTime, int Round);

	int SetPlayerStatPoints(int amount) { return StatPoints = StatPoints + amount; }
	int GetPlayerStatPoints() { return StatPoints; }
	 ~PlayerStats();
private:
	int Mana = 1;
	int MagicPower = 1;
	int StatPoints = 0;

	// variables determening how much stat points the playe can get
	int HighTierStatPoints = 10;

	int MiddleTirStatPoints = 5;

	int LowTierStatPoints = 1;

private:
	int* DeterminePointsForRound(int Round,int Points);
	int* Points = &P;
	int P = 0;
};

