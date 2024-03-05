#pragma once
#include "IApplication.h"
class IGraphics;
class ITexture;
class IShader;
class IRenderable;
#include <vector>

enum PlayerWalkingAnimEnum {FrameOne,FrameTwo,FrameThree,NumFramesWalking};
enum TutorialState{Active,EngageBattle};
static const unsigned int NumberOfFramesWalking = static_cast<int>(NumFramesWalking);

class TutorialLevel : public IApplication
{
public:
	TutorialLevel(IGraphics* GraphicsIn, IInput* InputIn);
	virtual ~TutorialLevel();

	virtual bool IsValid();
	virtual bool Load();
	virtual void Update();
	virtual void Cleanup();

	void PlayerWalking();
	void DeleteRender(IShader* render);
	void EngageBattle();
	TutorialState State;
private :
	IRenderable* Player;
	IRenderable* Enemy;
	IRenderable* BackGround;
	IShader* PlayerWalkingAnimation[NumberOfFramesWalking];
	ITexture* PlayerTex;

	

};

