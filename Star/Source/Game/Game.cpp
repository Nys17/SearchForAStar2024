#include "Game.h"

#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"
#include "Game/PlayerStats.h"
#include "Game/LevelChanger.h"
#include "Game/StatAssignScreen.h"
#include "RenderNumbers.h"
#include "Game/TitleScreen.h"


#include <iostream>
#include <ctime>
#include <math.h>
#include <string>


#define CLAMP(v, x, y) fmin(fmax(v, x), y)


constexpr float Pie = 3.14159265359f;
constexpr float TwoPies = Pie * 2.0f;
constexpr float DeltaTime = 0.016f;
constexpr float SpinSpeed = 0.1f;
constexpr float WinTolerance = Pie / 10.0f;
float PuzzleSizeMultiplayer = 1.2;
PlayerStats* PlayerStatsRef = new PlayerStats;
clock_t timer;
RenderNumbers* NumbersRef;
//TitleScreen* TitleScreenRef;

//StatAssignScreen StatAssignScreenRef;

IApplication* GetApplication(IGraphics* Graphics, IInput* Input)
{
	NumbersRef = new RenderNumbers(Graphics, Input);
	return new Game(Graphics, Input);
	
}

Game::Game(IGraphics* GraphicsIn, IInput* InputIn) : IApplication(GraphicsIn, InputIn), Rings(), Arrow(nullptr), SelectedRing(), State(), StatPointsText(nullptr), StatPointAmount(nullptr)
{
}

Game::~Game()
{
	NumbersRef = NULL;
	PlayerStatsRef = NULL;
	

	for (size_t i = 0; i < NumberOfRings; i++) {
		Rings[i] = NULL;
	}

	 Arrow = NULL;
	StatPointsText = NULL;
	StatPointAmount = NULL;
	delete[]Rings;
	delete(NumbersRef);
	delete(Arrow);
	delete(StatPointsText);
	delete(StatPointAmount);
	
	delete(PlayerStatsRef);
}


bool Game::IsValid()
{
	return true;
}

bool Game::Load()
{
	 
	ITexture* InnerTexture = Graphics->CreateTexture(L"Resource/Textures/InnerRing.dds");
	ITexture* MiddleTexture = Graphics->CreateTexture(L"Resource/Textures/MiddleRing.dds");
	ITexture* OuterTexture = Graphics->CreateTexture(L"Resource/Textures/OuterRing.dds");
	ITexture* ArrowTexture = Graphics->CreateTexture(L"Resource/Textures/Arrow.dds");
	ITexture* TextTexture = Graphics->CreateTexture(L"Resource/Textures/Explanation.dds");
	ITexture* StatPointsTexture = Graphics->CreateTexture(L"Resource/Textures/StatPointAmount.dds");
	IShader* InnerShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", InnerTexture);
	IShader* MiddleShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", MiddleTexture);
	IShader* OuterShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", OuterTexture);
	 IShader* ArrowShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", ArrowTexture);
	IShader* TextShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", TextTexture);
	IShader* StatPointsShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", StatPointsTexture);
	Rings[static_cast<unsigned int>(RingLayer::Inner)] = Graphics->CreateBillboard(InnerShader);
	Rings[static_cast<unsigned int>(RingLayer::Middle)] = Graphics->CreateBillboard(MiddleShader);
	Rings[static_cast<unsigned int>(RingLayer::Outer)] = Graphics->CreateBillboard(OuterShader);
	Arrow = Graphics->CreateBillboard(ArrowShader);
	StatPointAmount = Graphics->CreateBillboard(StatPointsShader);
	StatPointsText = Graphics->CreateBillboard(TextShader);
	StatPointsText->SetPosition(-500, 250);
	StatPointAmount->SetPosition(-650, -150);

	std::srand(static_cast<unsigned int>(std::time(0)));

	for (int i = 0; i < 3;  i++)
	{
		Rings[i]->SetPosition(200, 0);
	}
	Arrow->SetPosition(200, 0);
	SelectedRing = RingLayer::Outer;
	State = GameState::Setup;

	
	NumbersRef->Load();// prepare to render numbers
	return true;
}


void Game::Update()
{
	// If mode is Setup game then set each ring to a random rotation
	if (State == GameState::Setup)
	{
		
		SetupEachRing();
		State = GameState::Playing;
	}

	// If mode is Playing then read controller input and manage which ring is selected, the rotation of each ring and waiting for select to confirm positions 
	if (State == GameState::Playing)
	{
		
		UpdateRingSelection();
		UpdateSelectedRingRotation();
		UpdateRingTestSelection();

			
	}

	// If mode is Test then check to see if the rings are in their correct positions, play a noise corresponding to how close the player is 
	if (State == GameState::Test)
	{
		TestRingSolution();
		

		if (PuzzleSolvedRef == true)
		{
			//PlayerStatsRef->DeterminStatPointsAmount(ElapsedTimeRef, PuzzleRounds.size(), PlayerStatsRef->PlayerStatPoints); // USE THE ELAPSED TIME TO DETERMINE THE AMOUNT OF STAT POINTS
			
			//*PlayerStatsRef->PlayerStatPoints = *PlayerStatsRef->PlayerStatPoints + PlayerStatsRef->EarnedPoints(ElapsedTimeRef, PuzzleRounds.size());
			PlayerStatsRef->SetPlayerStatPoints(PlayerStatsRef->EarnedPoints(ElapsedTimeRef, PuzzleRounds.size()));
			ElapsedTime = 0; /// RESET TIMER IF SUCCESFUSSL

			
		}
		
		PuzzleRounds.push_back(1);

		switch (PuzzleRounds.size())
		{
		case 1:
			for (int i = 0; i < 3; i++)
			{
				Rings[i]->SetScale(Rings[i]->GetScaleX() * PuzzleSizeMultiplayer, Rings[i]->GetScaleY() * PuzzleSizeMultiplayer);
			}
			Arrow->SetScale(Arrow->GetScaleX()*PuzzleSizeMultiplayer, Arrow->GetScaleY()*PuzzleSizeMultiplayer);
			break;

		case 2:
			for (int i = 0; i < 3; i++)
			{
				Rings[i]->SetScale(Rings[i]->GetScaleX() * PuzzleSizeMultiplayer, Rings[i]->GetScaleY() * PuzzleSizeMultiplayer);
			}
			Arrow->SetScale(Arrow->GetScaleX() * PuzzleSizeMultiplayer, Arrow->GetScaleY() * PuzzleSizeMultiplayer);
			break;
		default:
			break;

			
		}

		if (PuzzleRounds.size() == 3)
		{
			State = GameState::PuzzleFinished;
 			
		}
		else {
			SelectedRing = RingLayer::Outer;
			State = GameState::Setup;

		}
	}

	if (State == GameState::PuzzleFinished) {
		// render the number of accumilated stat points -> better way to do it is after each round(tested and works) but can't delete just the numbers so this is how it is gonna go
		if (*PlayerStatsRef->PlayerStatPoints < 10)
		{
			NumbersRef->RenderTheNumbers(0, *PlayerStatsRef->PlayerStatPoints, 250.f, 0.f, StatPointAmount);
		}
		else if (*PlayerStatsRef->PlayerStatPoints>10)
		{
			NumbersRef->RenderTheNumbers(floor(*PlayerStatsRef->PlayerStatPoints / 10), *PlayerStatsRef->PlayerStatPoints % 10, 250.f, 0.f, StatPointAmount);
		}

		ITexture* ContinueTexture = Graphics->CreateTexture(L"Resource/Textures/SpacebarToContinue.dds");
		IShader* ContinueShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", ContinueTexture);
		IRenderable* Continue = Graphics->CreateBillboard(ContinueShader);
		Continue->	SetPosition(-650, -350);
		if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardSpaceBar))
		{
			State = GameState::TransitionToNextLevel; /// add text image saying to press spacbar to continue
		}
	}
}



void Game::Cleanup()
{
	
}

GameState Game::GetPuzzleState()
{
	return State;
}


void Game::SetupEachRing()
{
	for (unsigned int Ring = 0; Ring < NumberOfRings; ++Ring)
	{
		Rings[Ring]->SetRotation(static_cast<float>(fmod(rand(), Pie)));
	}

	Arrow->SetRotation(static_cast<float>(fmod(rand(), Pie)));

	StartTimerCount = clock() / CLOCKS_PER_SEC; // START COUNTING TIME 
	//StartTimerCount = clock() / CLOCKS_PER_SEC; // START COUNTING TIME 
	
}

void Game::UpdateRingSelection()
{
	int selectionChange = 0;

	//if (Input->IsPressed(InputAction::ShoulderButtonLeft))

	if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardMoveForward))
	{
		// Change ring selection towards outer
		selectionChange = -1;
		
	}
	else if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardMoveBackwards))
	{
		// Change ring selection towards inner
		selectionChange = 1;
	}
		
	SelectedRing = static_cast<RingLayer>(CLAMP(static_cast<int>(SelectedRing) + selectionChange, 0, NumberOfRings - 1));
}

void Game::UpdateSelectedRingRotation()
{
	
	//float delta = Input->GetValue(InputAction::RightStickXAxis) * SpinSpeed * DeltaTime;

	
		if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardMoveLeft))
		{
			DirectionalDelta  = (Input->KeyboardGetValue(KeyboardInputAction::KeyboardMoveLeft) * SpinSpeed * DeltaTime) / 500000;
			RingRotationDirection = -1;
		}
		if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardMoveRight))
		{
			DirectionalDelta = (Input->KeyboardGetValue(KeyboardInputAction::KeyboardMoveRight) * SpinSpeed * DeltaTime) / 500000;
			RingRotationDirection = 1;
		} 
		if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardSpaceBar))
		{
			DirectionalDelta = 0;
		}
		float delta = DirectionalDelta;
	//float delta = Input->KeyboardGetValue(KeyboardInputAction::KeyboardMoveLeft) * SpinSpeed * DeltaTime / 500000;
	float rotation = Rings[static_cast<int>(SelectedRing)]->GetTransform().Rotation;
	float newRotation = static_cast<float>(fmod(rotation + ( delta* RingRotationDirection), TwoPies)); /// *delta by 1/-1 to affect if we add or remove delta to/from rotation to affect the direction or rotation
	Rings[static_cast<int>(SelectedRing)]->SetRotation(newRotation);
}

void Game::UpdateRingTestSelection()
{
	//if (Input->IsPressed(InputAction::DefaultSelect))
	if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardSelect))
	{
		State = GameState::Test;
	}
}

void Game::TestRingSolution()
{
	
	float totalRotationDifference = 0.0f;
	float arrowRotation = Arrow->GetTransform().Rotation + TwoPies;

	for (unsigned int Ring = 0; Ring < NumberOfRings; ++Ring)
	{
		 ModuloRingRotation = (remainder(Rings[Ring]->GetTransform().Rotation, TwoPies));
		
		totalRotationDifference += abs(arrowRotation - (ModuloRingRotation + TwoPies));
		
	}

	float averageRotationDifference = totalRotationDifference / NumberOfRings;

	if (averageRotationDifference < WinTolerance)
	{
		// Win

		PuzzleSolvedRef = true;// so it can procced to next stage
		ElapsedTimeRef = (clock() / CLOCKS_PER_SEC) - StartTimerCount;
		
	}
	else
	{
		PuzzleSolvedRef = false;// repeat puzzle

	}
}

void Game::DeletePuzzle()
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




