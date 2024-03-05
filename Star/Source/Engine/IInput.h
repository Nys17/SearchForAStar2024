
#pragma once




enum InputAction
{
	ButtonLeft,
	ButtonRight,
	ButtonTop,
	ButtonBottom,

	DirectionPadLeft,
	DirectionPadRight,
	DirectionPadTop,
	DirectionPadBottom,

	LeftStickXAxis,
	LeftStickYAxis,
	LeftStickPress,

	RightStickXAxis,
	RightStickYAxis,
	RightStickPress,

	TriggerLeft,
	TriggerRight,
	ShoulderButtonLeft,
	ShoulderButtonRight,

	SpecialLeft,
	SpecialRight,

	NumActions,

	DefaultSelect = ButtonBottom,
	DefaultBack = ButtonRight,

	

};

enum KeyboardInputAction {
	KeyboardMoveLeft,
	KeyboardMoveRight,
	KeyboardMoveForward,
	KeyboardMoveBackwards,
	KeyboardSelect,
	KeyboardSpaceBar,
	KeyboardOne,
	KeyboardTwo,
	KeyboardThree,
	KeyboardFour,
	KeyboardFive,
	KeyboardSix,
	KeyboardSeven,
	KeyboardEight,
	KeyboardNine,
	KeyboardJ,
	KeyboardK,
	KeyboardL,

	KeyboardNumActions,
};

class IInput
{
public:

	IInput();

	virtual void Update();

	virtual float GetValue(InputAction action) const;
	virtual bool IsPressed(InputAction action, float threshold = 0.5f) const;
	virtual bool IsReleased(InputAction action, float threshold = 0.5f) const;
	virtual bool IsHeld(InputAction action, float threshold = 0.5f) const;

	virtual float KeyboardGetValue(KeyboardInputAction action) const;
	virtual bool KeyboardButtonIsPressed(KeyboardInputAction action, float threshold = 0.5f) const;
	virtual bool KeyboardButtonIsHeld(KeyboardInputAction action, float threshold = 0.5f) const;
	//virtual bool KeyboardButtonIsReleased(KeyboardInputAction action, float threshold= 0.5f) const;
	

	static const unsigned int NumInputActions = static_cast<unsigned int>(NumActions);
	static const unsigned int KeyboardNumInputActions = static_cast<unsigned int>(KeyboardNumActions);
	
protected:
	
	float CurrentState[NumInputActions];
	float PreviousState[NumInputActions];
	
	float KeyboardCurrentState[KeyboardNumActions];
	float KeyboardPreviousState[KeyboardNumActions];

};

