#pragma once
#include "Engine/IApplication.h"
#pragma once
#include<vector>
class IGraphics;
class ITexture;
class IShader;
class IRenderable;

enum SceneState{StartScreen,Puzzle,StatAssign,TutorialLev,Battle};

class SceneManager :   public IApplication
{
public:
	SceneManager(IGraphics* GraphicsIn, IInput* InputIn);
	virtual ~SceneManager();

	virtual bool IsValid();
	virtual bool Load();
	virtual void Update();
	virtual void Cleanup();

	void DeleteGraphics();
	void LeaveStartScreen();

private:
	SceneState State;
};

