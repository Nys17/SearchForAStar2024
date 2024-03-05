
#pragma once

#include "Engine/IApplication.h"
#include <vector>
class IGraphics;
class ITexture;
class IShader;
class IRenderable;

enum RingLayer { Outer, Middle, Inner, NumRings };
enum GameState { Setup, Playing, Test, PuzzleFinished,TransitionToNextLevel,NumModes };
static const unsigned int NumberOfRings = static_cast<int>(NumRings);


class Game : public IApplication
{
public:

	Game(IGraphics* Graphics, IInput* InputIn);
	virtual ~Game();
	
	virtual bool IsValid();
	virtual bool Load();
	virtual void Update();
	virtual void Cleanup();
	bool& PuzzleSolvedRef{ PuzzleSolved }; // reference to bool
	float& ElapsedTimeRef{ ElapsedTime };
	GameState GetPuzzleState();
	std::vector< int> PuzzleRounds;// array used to keep track of the rounds passed
private:

	void SetupEachRing();
	void UpdateRingSelection();
	void UpdateSelectedRingRotation();
	void UpdateRingTestSelection();
	void TestRingSolution();
	void DeletePuzzle();// load new game
	//bool LoadMainMenu();//load main muny
	
	IRenderable* Rings[NumberOfRings];
	IRenderable* Arrow;
	IRenderable* StatPointsText;
	IRenderable* StatPointAmount;
	
	RingLayer SelectedRing;
	GameState State;
	
	bool PuzzleSolved = false;// determine if the rings are correctly aligned
	int RingRotationDirection = 0;// will be used to determine the direction of rotation for rings -> if 1 == turn clockwise / if -> -1 == turn anticlockwise
	float DirectionalDelta = 0; //used to substitue delta  value
	float ModuloRingRotation = 0;
	float StartTimerCount = 0; // start counting solve time
	float ElapsedTime = 0;

	bool startGame = false;
};

