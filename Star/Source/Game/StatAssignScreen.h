#pragma once

#include "Engine/IApplication.h"
#include <vector>
class IGraphics;
class ITexture;
class IShader;
class IRenderable;


enum TypeStats{Health, AttackPower, Speed,Luck, AttackSpeed,MagicPower, Mana, None, NumStats}; 
static const unsigned int NumberOfStats = static_cast<int>(NumStats);

enum LevelState{PointAssign, NextLevel};

class StatAssignScreen : public IApplication
{

public:
	StatAssignScreen(IGraphics* GraphicsIn, IInput* InputIn);
		virtual ~StatAssignScreen();

	virtual bool IsValid();
	virtual bool Load();
	virtual void Update();
	virtual void Cleanup();

	void ChooseSkillToInvest();
	void InvestPoints();
	void DeleteGraphics();
	void ShowStatAmount();
	LevelState LState= PointAssign;
	TypeStats CurrentStat = TypeStats::None;

private:
	IRenderable* StatsInvestText;
	IRenderable* Stats[NumberOfStats - 1]; // so it doesn't include none state
	IRenderable* StatsPoints;
	IRenderable* Explanation;
	
};

