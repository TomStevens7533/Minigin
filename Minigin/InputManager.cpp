#include "MiniginPCH.h"
#include "InputManager.h"
#define WIN32_LEAN_AND_MEAN
#include  <windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

using namespace dae;


//Pimpl
class InputManager::InputManagerImpl
{
public:
	InputManagerImpl();
	void ProcessInputImpl();

	bool IsKeyDownImpl(ControllerButton button) const;
	bool IsKeyPressedImpl(ControllerButton button) const;
	bool IsKeyReleasedImpl(ControllerButton button) const;

private:
	XINPUT_STATE m_PreviousState;
	XINPUT_STATE m_CurrentState;
};

InputManager::InputManagerImpl::InputManagerImpl()
{
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
}
void InputManager::InputManagerImpl::ProcessInputImpl()
{
	// todo: read the input
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

	XInputGetState(0, &m_CurrentState);

}



bool InputManager::InputManagerImpl::IsKeyDownImpl(ControllerButton button) const
{	//check if key is pressed down
	if (m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) {
		return true;
	}
	return false;

}

bool InputManager::InputManagerImpl::IsKeyPressedImpl(ControllerButton button) const
{  //Check if key is pressed this frame
	if ((m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) && !(m_PreviousState.Gamepad.wButtons & static_cast<unsigned int>(button))) {
		return true;
	}
	return false;
}

bool InputManager::InputManagerImpl::IsKeyReleasedImpl(ControllerButton button) const
{ //Check if key is released this frame
	if (!(m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) && (m_PreviousState.Gamepad.wButtons & static_cast<unsigned int>(button))) {
		return true;
	}
	return false;
}



//InputManager
InputManager::InputManager() : m_pPimpl{ std::make_unique<InputManagerImpl>() } {
}
//destructor visibility
InputManager::~InputManager() {
	for (auto& pair : m_CommandMap)
	{
		pair.second.reset();
	}
}
void InputManager::HandleCommands()
{
	for (auto& mapElement : m_CommandMap)
	{
		HandleCommand(mapElement.first.first, mapElement.first.second, mapElement.second.get());
	}
}

void InputManager::ProcessInput()
{
	m_pPimpl->ProcessInputImpl();
}
void InputManager::AddCommand(ControllerButton button, Command* command, KeyState state)
{	//Add command
	//overwite previous command when key is the same
	m_CommandMap[std::make_pair(button, state)].reset(command);
}
bool InputManager::RemoveCommand(ControllerButton button, KeyState state)
{
	//return 0 or 1 if element is erased
	return m_CommandMap.erase(std::make_pair(button, state));
}
bool InputManager::HandleCommand(ControllerButton button, KeyState state, Command* command)
{
	//at throws exception when element is not in map
	switch (state)
	{
	case KeyState::DOWN:
		if (IsKeyDown(button)) {
			command->Excecute();
			return true;
		}
		break;
	case KeyState::PRESSED:
		if (IsKeyPressed(button)) {
			command->Excecute();
			return true;
		}
		break;
	case KeyState::RELEASED:
		if (IsKeyReleased(button)) {
			command->Excecute();
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}


bool InputManager::IsKeyDown(ControllerButton button) const
{
	return m_pPimpl->IsKeyDownImpl(button);
}

bool InputManager::IsKeyPressed(ControllerButton button) const
{
	return m_pPimpl->IsKeyPressedImpl(button);
}
bool InputManager::IsKeyReleased(ControllerButton button) const
{
	return m_pPimpl->IsKeyReleasedImpl(button);
}

