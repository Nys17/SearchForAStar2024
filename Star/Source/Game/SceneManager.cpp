#include "SceneManager.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"
#include "Game/PlayerStats.h"
#include "Game/StatAssignScreen.h"
#include "Game/Game.h"
#include "Game/TitleScreen.h"
#include "Game/TutorialLevel.h"
// ref to scenes
TitleScreen* TitleScreenRef;
Game* PuzzleRef;
StatAssignScreen* StatAssignScreenRef;
TutorialLevel* TutorialLevelRef;
IApplication* GetSceneManager(IGraphics* Graphics, IInput* Input)
{
	TitleScreenRef = new TitleScreen(Graphics,Input);
	PuzzleRef = new Game(Graphics, Input);
StatAssignScreenRef = new StatAssignScreen(Graphics, Input);
TutorialLevelRef = new TutorialLevel(Graphics, Input);
	return new SceneManager(Graphics, Input);
}

SceneManager::SceneManager(IGraphics* GraphicsIn, IInput* InputIn) :IApplication(GraphicsIn,InputIn),State()
{
	
}


SceneManager::~SceneManager()
{
	TitleScreenRef = NULL;
	PuzzleRef = NULL;
	StatAssignScreenRef = NULL;;
	TutorialLevelRef = NULL;
}

bool SceneManager::IsValid()
{
	return true;
}

bool SceneManager::Load()
{
	TitleScreenRef->Load();
	State = SceneState::StartScreen;

	
	return true;
}

void SceneManager::Update()
{
	switch (State)
	{
	case StartScreen:
		LeaveStartScreen();
		break;

	case Puzzle:
		/// call distructor of previous scene??
		if (Graphics->GetRendarables().empty() == true)
		{
			PuzzleRef->Load();
		}

		PuzzleRef->Update();


		if (PuzzleRef->GetPuzzleState() == GameState::TransitionToNextLevel)
		{
			State = SceneState::StatAssign;
				DeleteGraphics();
		}
		break;
	case StatAssign:
		
		if (Graphics->GetRendarables().empty() == true)
		{
			StatAssignScreenRef->Load();
		}
		StatAssignScreenRef->Update();
		if (StatAssignScreenRef->LState == LevelState::NextLevel)
		{
			DeleteGraphics();
			State = SceneState::TutorialLev;
		}
	
		
		break;
	case TutorialLev:
		if (Graphics->GetRendarables().empty() == true)
		{
			TutorialLevelRef->Load();
		}
	
		
		TutorialLevelRef->Update();
		break;
	case Battle:

		break;
	default:
		break;
	}
}

void SceneManager::Cleanup()
{
}

void SceneManager::DeleteGraphics()
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

void SceneManager::LeaveStartScreen()
{

	if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardSpaceBar))
	{
		DeleteGraphics();
		State = static_cast<SceneState>(State + 1);
		printf("dsdd");
	}
}


