#pragma once
#include <string>
using namespace std;
class RPGStats
{

public:
	string Name;
	int Health;
	int AttackPower;
	int Speed;
	int Luck;
	int Intelligence;
	int AttackSpeed;


	virtual bool Dodge();

	virtual void Attack();
	virtual void TakeDamage();
	RPGStats() {
		Name = "Blank";
		Health = 90;
		AttackPower = 1;
		Speed = 1;
		Luck = 1;
		Intelligence = 1;
		AttackSpeed = 1;
	}
};

