#include "IInput.h"
#include <iostream>
#include <math.h>
#include <windows.h>

IInput::IInput() : CurrentState(), PreviousState(), KeyboardCurrentState(),KeyboardPreviousState()
{
}

void IInput::Update()
{
    std::memcpy(&PreviousState, &CurrentState, sizeof(float) * NumInputActions);
   std::memcpy(&KeyboardPreviousState, &KeyboardCurrentState, sizeof(float) * KeyboardNumInputActions);
}

float IInput::GetValue(InputAction action) const
{
    return CurrentState[static_cast<unsigned int>(action)];
}

bool IInput::IsPressed(InputAction action, float threshold) const
{
    return abs(CurrentState[static_cast<unsigned int>(action)]) > threshold && abs(PreviousState[static_cast<unsigned int>(action)]) < threshold;
}

bool IInput::IsReleased(InputAction action, float threshold) const
{
    return abs(CurrentState[static_cast<unsigned int>(action)]) < threshold && abs(PreviousState[static_cast<unsigned int>(action)]) > threshold;
}

bool IInput::IsHeld(InputAction action, float threshold) const
{
    return abs(CurrentState[static_cast<unsigned int>(action)]) > threshold && abs(PreviousState[static_cast<unsigned int>(action)]) > threshold;
}

float IInput::KeyboardGetValue(KeyboardInputAction action) const
{

 
        return KeyboardCurrentState[static_cast<unsigned int>(action)];
  

}

bool IInput::KeyboardButtonIsPressed(KeyboardInputAction action, float threshold) const
{
    return abs(KeyboardCurrentState[static_cast<unsigned int>(action)]) > threshold && abs(KeyboardPreviousState[static_cast<unsigned int>(action)]) < threshold;
}

bool IInput::KeyboardButtonIsHeld(KeyboardInputAction action, float threshold) const
{
    return abs(KeyboardCurrentState[static_cast<unsigned int>(action)]) > threshold && abs(KeyboardPreviousState[static_cast<unsigned int>(action)]) > threshold;
}

//bool IInput::KeyboardButtonIsReleased(KeyboardInputAction action, float threshold) const
//{
//    return abs(KeyboardCurrentState[static_cast<unsigned int>(action)]) < threshold && abs(KeyboardPreviousState[static_cast<unsigned int>(action)]) > threshold;
//}
