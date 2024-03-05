#include "DirectXInput.h"
#include <math.h>

DirectXInput::DirectXInput() : IInput(), State()
{
}

DirectXInput::~DirectXInput()
{
}

void DirectXInput::Update()
{
	IInput::Update();

	unsigned int result = XInputGetState(0, &State);

	// Buttons
	CurrentState[static_cast<unsigned int>(InputAction::ButtonLeft)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_X ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::ButtonRight)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_B ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::ButtonTop)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_Y ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::ButtonBottom)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_A ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::DirectionPadLeft)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::DirectionPadRight)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::DirectionPadTop)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::DirectionPadBottom)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::LeftStickPress)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::RightStickPress)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::ShoulderButtonLeft)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::ShoulderButtonRight)] =  State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::SpecialLeft)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK ? 1.0f : 0.0f;
	CurrentState[static_cast<unsigned int>(InputAction::SpecialRight)] = State.Gamepad.wButtons & XINPUT_GAMEPAD_START ? 1.0f : 0.0f;

	// Triggers
	CurrentState[static_cast<unsigned int>(InputAction::TriggerLeft)] = CalculateTriggerValue(State.Gamepad.bLeftTrigger);
	CurrentState[static_cast<unsigned int>(InputAction::TriggerRight)] = CalculateTriggerValue(State.Gamepad.bRightTrigger);

	// Stick Axis
	CurrentState[static_cast<unsigned int>(InputAction::LeftStickXAxis)] = CalculateAxisValue(State.Gamepad.sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	CurrentState[static_cast<unsigned int>(InputAction::LeftStickYAxis)] = CalculateAxisValue(State.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	CurrentState[static_cast<unsigned int>(InputAction::RightStickXAxis)] = CalculateAxisValue(State.Gamepad.sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
	CurrentState[static_cast<unsigned int>(InputAction::RightStickYAxis)] = CalculateAxisValue(State.Gamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);

	//Keyboard#
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardMoveLeft)] = GetAsyncKeyState( 0x41);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardMoveRight)] = GetAsyncKeyState( 0x44);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardMoveForward)] = GetAsyncKeyState(0x57);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardMoveBackwards)] = GetAsyncKeyState(0x53);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardSelect)] = GetAsyncKeyState(VK_RETURN);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardSpaceBar)] = GetAsyncKeyState(VK_SPACE);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardOne)] = GetAsyncKeyState(0x31);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardTwo)] = GetAsyncKeyState(0x32);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardThree)] = GetAsyncKeyState(0x33);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardFour)] = GetAsyncKeyState(0x34);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardFive)] = GetAsyncKeyState(0x35);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardSix)] = GetAsyncKeyState(0x36);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardSeven)] = GetAsyncKeyState(0x37);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardEight)] = GetAsyncKeyState(0x38);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardNine)] = GetAsyncKeyState(0x39);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardK)] = GetAsyncKeyState(0x4B);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardJ)] = GetAsyncKeyState(0x4A);
	KeyboardCurrentState[static_cast<unsigned int>(KeyboardInputAction::KeyboardL)] = GetAsyncKeyState(0x4C);
}

float DirectXInput::CalculateTriggerValue(BYTE rawValue, float threshold, float max)
{
	return rawValue > threshold ? rawValue / max : 0.0f;
}

float DirectXInput::CalculateAxisValue(SHORT rawValue, float deadzone, float left, float right)
{
	return abs(rawValue) > deadzone ? (-1.0f + (rawValue - left) * (2.0f / (right - left))) : 0.0f;
}

