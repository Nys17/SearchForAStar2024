#pragma once
#include "Engine/IApplication.h"
#include <vector>
class IGraphics;
class ITexture;
class IShader;
class IRenderable;
class TitleScreen :    public IApplication
{

public:
	TitleScreen(IGraphics* GraphicsAn, IInput* InputAn);
	virtual ~TitleScreen();

	virtual bool IsValid();
	virtual bool Load();
	virtual void Update();
	virtual void Cleanup();

	void StartPuzzle();

	
private:
	IRenderable* BackGround;
	
};

