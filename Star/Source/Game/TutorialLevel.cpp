#include "TutorialLevel.h"

#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"
#include "Game/PlayerStats.h"
#include "Game/LevelChanger.h"
#include "Game/StatAssignScreen.h"
#include <iostream>
#include <ctime>
#include <math.h>
#include <string>

PlayerStats* PlayerStatsReference = new PlayerStats;
constexpr float DeltaTime = 0.016f;

IApplication* GetTutorialLevel(IGraphics* Graphics, IInput* Input) {


	return new TutorialLevel(Graphics, Input);
}

TutorialLevel::TutorialLevel(IGraphics* GraphicsIn, IInput* InputIn) : IApplication(GraphicsIn, InputIn),State(), Player(nullptr), PlayerWalkingAnimation(), PlayerTex(), BackGround(nullptr), Enemy(nullptr)
{
}

TutorialLevel::~TutorialLevel()
{
}

bool TutorialLevel::IsValid()
{
	return true;
}

bool TutorialLevel::Load()
{
	/*ITexture* WalkFrameOneTexture= Graphics->CreateTexture(L"Resource/Textures/Player_Idle.dds");
	ITexture* WalkFrameTwoTexture = Graphics->CreateTexture(L"Resource/Textures/PlayerWalk1.dds");
	ITexture* WalkFrameThreeTexture = Graphics->CreateTexture(L"Resource/Textures/PlayerWalk1.dds");

	PlayerWalkingAnimation[0] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", WalkFrameOneTexture);
	PlayerWalkingAnimation[1] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", WalkFrameTwoTexture);
	PlayerWalkingAnimation[2] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", WalkFrameThreeTexture);*/
	
	PlayerTex = Graphics->CreateTexture(L"Resource/Textures/Player_Idle.dds");
	
IShader* PlayerShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", PlayerTex);
	

	ITexture* EnemyTexture = Graphics->CreateTexture(L"Resource/Textures/enemy.dds");
	IShader* EnemyShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", EnemyTexture);

	
	Player= Graphics->CreateBillboard(PlayerShader);
	Enemy = Graphics->CreateBillboard(EnemyShader);
	/*ITexture* BGTexture = Graphics->CreateTexture(L"Resource/Textures/BackGround.dds");
	IShader* BGShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", BGTexture);
	BackGround = Graphics->CreateBillboard(BGShader);*/
	Player->SetPosition(-700, -5);
	Enemy->SetPosition(700, -5);
	State = TutorialState::Active;
	return true;
}

void TutorialLevel::Update()
{
	PlayerWalking();
}

void TutorialLevel::Cleanup()
{
}

void TutorialLevel::PlayerWalking()
{
	bool IsMoving = false;
	float currentPlayerPosX = 0.0f;
	float currentPlayerPosY = 0.0f;
	float delta = PlayerStatsReference->Speed *10 * DeltaTime;
	if (Input->KeyboardButtonIsHeld(KeyboardInputAction::KeyboardMoveLeft)) {

		Player->SetPosition(Player->GetPosX() - delta, Player->GetPosY());
		IsMoving = true;
		
	}

	if (Input->KeyboardButtonIsHeld(KeyboardInputAction::KeyboardMoveRight))
	{
		Player->SetPosition(Player->GetPosX() + delta, Player->GetPosY());
		IsMoving = true;
		
	}

	else if (!Input->KeyboardButtonIsHeld(KeyboardInputAction::KeyboardMoveLeft) && !Input->KeyboardButtonIsHeld(KeyboardInputAction::KeyboardMoveRight)) {

		IsMoving = false;
	}
	/*if (IsMoving)
	{
		for (int i = 0; i < 3; i++)
		{
			currentPlayerPosX = Player->GetPosX();
			currentPlayerPosY= Player->GetPosY();
			delete(&Player);
			Player = Graphics->CreateBillboard(PlayerWalkingAnimation[i]);
			Player->SetPosition(currentPlayerPosX, currentPlayerPosY);
		}
	}*/
}

void TutorialLevel::DeleteRender(IShader* render)
{
	/*IRenderable* toBedeleted;
	//delete(*Graphics->GetRendarables().find(render));*/
}

void TutorialLevel::EngageBattle()
{
	if (Player->GetPosX()==699)
	{
		State = TutorialState::EngageBattle;
	}
}
