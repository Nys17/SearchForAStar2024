#include "TitleScreen.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"

#include "Game/LevelChanger.h"
#include <iostream>
#include <ctime>
#include <math.h>
#include <string>
#include <Game.h>


IApplication* GetMainMenu(IGraphics* Graphics, IInput* Input)
{
	
		return new TitleScreen(Graphics, Input);
	


}


TitleScreen::TitleScreen(IGraphics* GraphicsAn, IInput* InputAn) : IApplication(GraphicsAn, InputAn),BackGround(nullptr)
{

}


TitleScreen::~TitleScreen()
{
	BackGround = NULL;
	delete(BackGround);
}

bool TitleScreen::IsValid()
{
	return true;
}

bool TitleScreen::Load()
{
	ITexture* BackGroundTexture = Graphics->CreateTexture(L"Resource/Textures/MainMenu.dds");
	IShader* BackGroundShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", BackGroundTexture);
	BackGround = Graphics->CreateBillboard(BackGroundShader);

	
	return true; 
}

void TitleScreen::Update()
{
	StartPuzzle();
}

void TitleScreen::Cleanup()
{
	
}

void TitleScreen::StartPuzzle()
{
////std:string NextLevel = "Puzzle";
////	if (Input->KeyboardButtonIsPressed(KeyboardInputAction::KeyboardSpaceBar))
////	{
////		LCTRef->LevelChangerMessage = &NextLevel;
////    		printf("how");
////	}
}
