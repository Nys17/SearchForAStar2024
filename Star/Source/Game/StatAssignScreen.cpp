#include "StatAssignScreen.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"
#include "Game/PlayerStats.h"
#include "Game/LevelChanger.h"
#include "RenderNumbers.h"
#include <iostream>
#include <ctime>
#include <math.h>
#include <string>

RenderNumbers* NumRef;


PlayerStats Player;
PlayerStats* PlayerRef = &Player;
IApplication* GetStatusAssignScreen(IGraphics* Graphics, IInput* Input)
{
	NumRef = new RenderNumbers(Graphics,Input);

	return new StatAssignScreen(Graphics, Input);



}
StatAssignScreen::StatAssignScreen(IGraphics* GraphicsIn, IInput* InputIn) : IApplication(GraphicsIn, InputIn), StatsPoints(nullptr), StatsInvestText(nullptr), Stats()
{
	PlayerRef->SetPlayerStatPoints(40);
}

StatAssignScreen::~StatAssignScreen()
{
	PlayerRef = NULL;
	NumRef = NULL;
	StatsInvestText = NULL;
	StatsPoints= NULL;
	for (size_t i = 0; i < 7; i++)
	{
		Stats[i] = NULL;
	}
}

bool StatAssignScreen::IsValid()
{
	return true;
}

bool StatAssignScreen::Load()
{
	
	ITexture* TitleTexture = Graphics->CreateTexture(L"Resource/Textures/InvestStatScreen.dds");
	IShader* TitleShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", TitleTexture);
	StatsInvestText = Graphics->CreateBillboard(TitleShader);
	StatsInvestText->SetPosition(StatsInvestText->GetPosX() - 500, 450);

	ITexture* StatPointsTexture = Graphics->CreateTexture(L"Resource/Textures/StatPointAmount.dds");
	IShader* StatPointsShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", StatPointsTexture);
	StatsPoints = Graphics->CreateBillboard(StatPointsShader);
	StatsPoints->SetPosition(StatsInvestText->GetPosX() + 900, 450);

	ITexture* ExplanationTexture = Graphics->CreateTexture(L"Resource/Textures/StatInvestExplanation.dds");
	IShader* ExplanationShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", ExplanationTexture);
	Explanation = Graphics->CreateBillboard(ExplanationShader);
	Explanation->SetPosition(StatsPoints->GetPosX(), StatsPoints->GetPosY() - 400);
	
	ITexture* StatsTexutres[NumberOfStats - 1];
	
	StatsTexutres[0] = Graphics->CreateTexture(L"Resource/Textures/Stats/Health.dds");
	StatsTexutres[1] = Graphics->CreateTexture(L"Resource/Textures/Stats/AttackPower.dds");
	StatsTexutres[2] = Graphics->CreateTexture(L"Resource/Textures/Stats/Speed.dds");
	StatsTexutres[3] = Graphics->CreateTexture(L"Resource/Textures/Stats/Luck.dds");
	StatsTexutres[4] = Graphics->CreateTexture(L"Resource/Textures/Stats/AttackSpeed.dds");
	StatsTexutres[5] = Graphics->CreateTexture(L"Resource/Textures/Stats/MagicPower.dds");
	StatsTexutres[6] = Graphics->CreateTexture(L"Resource/Textures/Stats/Mana.dds");
	
	IShader* StatsShaders[NumberOfStats - 1];

	for (int i = 0; i < 7; i++) 
	{
		StatsShaders[i] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", StatsTexutres[i]);
	}

	for (int i = 0; i < 7; i++)
	{
		Stats[i] = Graphics->CreateBillboard(StatsShaders[i]);
		if (i==0)
		{
			Stats[i]->SetPosition(StatsInvestText->GetPosX() - 150, StatsInvestText->GetPosY() - 100);
		}
		else {
			Stats[i]->SetPosition(StatsInvestText->GetPosX()- 150, Stats[i-1]->GetPosY() - 120);
		}
	
	}
	NumRef->Load();
	ShowStatAmount();

	LState = LevelState::PointAssign;
	
	return true;
}

void StatAssignScreen::Update()
{
	if (LState == LevelState::PointAssign)
	{
		ChooseSkillToInvest();
		if (CurrentStat != TypeStats::None)
		{
			InvestPoints();
		}
		
	}

	if (PlayerRef->GetPlayerStatPoints() <= 0 || *PlayerRef->PlayerStatPoints <= 0)/// just in case
	{
		LState = LevelState::NextLevel;
	}
	
}

void StatAssignScreen::Cleanup()
{
}

void StatAssignScreen::ChooseSkillToInvest()
{
	///this is how it is intended to be done but I can't get the currently pressed key
	/*KeyboardInputAction action{};
	switch (Input->KeyboardButtonIsPressed(action))
	{
	case KeyboardInputAction::KeyboardOne:
		CurrentStat = TypeStats::Health;

	case KeyboardInputAction::KeyboardTwo:
		CurrentStat = TypeStats::AttackPower;

	case KeyboardInputAction::KeyboardThree:
		CurrentStat = TypeStats::Speed;

	case KeyboardInputAction::KeyboardFour:
		CurrentStat = TypeStats::Luck;

	case KeyboardInputAction::KeyboardFive:
		CurrentStat = TypeStats::AttackSpeed;

	case KeyboardInputAction::KeyboardSix:
		CurrentStat = TypeStats::Intelligence;

	case KeyboardInputAction::KeyboardSeven:
		CurrentStat = TypeStats::Mana;
	default:
		break;
	}*/
	
	if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardOne)) {
		CurrentStat = TypeStats::Health;
	}
	else if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardTwo)) {
		CurrentStat = TypeStats::AttackPower;
	}
	else if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardThree)) {
		CurrentStat = TypeStats::Speed;
	}
	else if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardFour)) {
		CurrentStat = TypeStats::Luck;
	}
	else if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardFive)) {
		CurrentStat = TypeStats::AttackSpeed;
	}
	else if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardSix)) {
		CurrentStat = TypeStats::MagicPower;
	}
	else if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardSeven)) {
		CurrentStat = TypeStats::Mana;
	}
}

void StatAssignScreen::InvestPoints()
{
	int PointsToInvestAmount = 0;
	
	
		if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardJ))
		{
			PointsToInvestAmount = 2;
		}
		if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardK))
		{
		PointsToInvestAmount = 4;
		}
		if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardL))
		{
			PointsToInvestAmount = 6;
		}
		if (PointsToInvestAmount > *PlayerRef->PlayerStatPoints)
		{
			PointsToInvestAmount = *PlayerRef->PlayerStatPoints;
		}

		if (PointsToInvestAmount != 0)
		{
		switch (CurrentStat)
		{
		case AttackPower:
			PlayerRef->AssignStatPoints(PlayerRef->PlayerAttackPower, PointsToInvestAmount);
			
			break;
		case Health:
			PlayerRef->AssignStatPoints(PlayerRef->PlayerHealth, PointsToInvestAmount);
			
			break;
		case Speed:
			PlayerRef->AssignStatPoints(PlayerRef->PlayerSpeed, PointsToInvestAmount);
		
			break;
		case Luck:
			PlayerRef->AssignStatPoints(PlayerRef->PlayerLuck, PointsToInvestAmount);
			
			break;

		case Mana:
			PlayerRef->AssignStatPoints(PlayerRef->PlayerMana, PointsToInvestAmount);
			
			break;
		case MagicPower:
			PlayerRef->AssignStatPoints(PlayerRef->PlayerMagicPower,PointsToInvestAmount);
			
			break;
		case AttackSpeed:
			PlayerRef->AssignStatPoints(PlayerRef->PlayerAttackSpeed, PointsToInvestAmount);
			
			break;

		default:
			break;
		}
		DeleteGraphics();
		Load();

		ShowStatAmount();
		
	}
}

void StatAssignScreen::DeleteGraphics()
{

	for (auto bucket = Graphics->GetRendarables().begin(); bucket != Graphics->GetRendarables().end(); ++bucket)
	{
		for (auto renderable = bucket->second.begin(); renderable != bucket->second.end(); ++renderable)
		{
			delete (*renderable);
		}

		delete bucket->first;
	}

	Graphics->RenderablesRef.clear();
	for (auto texture = Graphics->TexturesRef.begin(); texture != Graphics->TexturesRef.end(); ++texture)
	{
		delete (*texture);
	}
	Graphics->TexturesRef.clear();
}

void StatAssignScreen::ShowStatAmount() {
	int SelectedStatPointsAmount = 0;
	int RenderedStat = 0;

	NumRef->RenderTheNumbers(floor(PlayerRef->GetPlayerStatPoints() / 10), PlayerRef->GetPlayerStatPoints() % 10, 250.f, 0.f, StatsPoints);
	for (int i = 0; i < TypeStats::NumStats - 1; i++) /// one less stat is being rendered
	{
		RenderedStat = i;
		switch (i)
		{
			
		case AttackPower:

			SelectedStatPointsAmount = *PlayerRef->PlayerAttackPower;
			break;
		case Health:

			SelectedStatPointsAmount = *PlayerRef->PlayerHealth;
			break;
		case Speed:

			SelectedStatPointsAmount = *PlayerRef->PlayerSpeed;
			break;
		case Luck:

			SelectedStatPointsAmount = *PlayerRef->PlayerLuck;
			break;

		case Mana:

			SelectedStatPointsAmount = *PlayerRef->PlayerMana;
			break;
		case MagicPower:

			SelectedStatPointsAmount = *PlayerRef->PlayerMagicPower;
			break;
		case AttackSpeed:

			SelectedStatPointsAmount = *PlayerRef->PlayerAttackSpeed;
			break;

		default:
			break;
		}

		if (SelectedStatPointsAmount < 10)
		{
			NumRef->RenderSingleDigitNumber(SelectedStatPointsAmount, 150, 0, Stats[RenderedStat]);
		}
		else {
			NumRef->RenderTheNumbers(floor(SelectedStatPointsAmount / 10), SelectedStatPointsAmount % 10, 150, 0, Stats[RenderedStat]);
		}
	}
	

}
