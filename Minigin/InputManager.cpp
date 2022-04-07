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

	void SetNewPlayerAmountImpl(int playerAmount) {
		m_PreviousStateVec.resize(playerAmount);
		m_CurrentStateVec.resize(playerAmount);
		m_PlayerAmount = playerAmount;
	}

	bool IsKeyDownImpl(ControllerButton button, int deviceIdx) const;
	bool IsKeyPressedImpl(ControllerButton button, int deviceIdx) const;
	bool IsKeyReleasedImpl(ControllerButton button, int deviceIdx) const;

private:
	std::vector<XINPUT_STATE> m_PreviousStateVec{};
	std::vector<XINPUT_STATE> m_CurrentStateVec{};
	int m_PlayerAmount = 0;
};

InputManager::InputManagerImpl::InputManagerImpl()
{
	for (size_t i = 0; i < m_PlayerAmount; i++)
	{
		ZeroMemory(&m_PreviousStateVec[i], sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentStateVec[i], sizeof(XINPUT_STATE));
	}

}
void InputManager::InputManagerImpl::ProcessInputImpl()
{
	// todo: read the input
	for (int i = 0; i < m_PlayerAmount; i++)
	{
		CopyMemory(&m_PreviousStateVec[i], &m_CurrentStateVec[i], sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentStateVec[i], sizeof(XINPUT_STATE));

		XInputGetState(i, &m_CurrentStateVec[i]);
	}
}
bool InputManager::InputManagerImpl::IsKeyDownImpl(ControllerButton button, int deviceIdx) const
{	//check if key is pressed down
	if (m_CurrentStateVec[deviceIdx].Gamepad.wButtons & static_cast<unsigned int>(button)) {
		return true;
	}
	return false;

}

bool InputManager::InputManagerImpl::IsKeyPressedImpl(ControllerButton button, int deviceIdx) const
{  //Check if key is pressed this frame
	if ((m_CurrentStateVec[deviceIdx].Gamepad.wButtons & static_cast<unsigned int>(button)) && !(m_PreviousStateVec[deviceIdx].Gamepad.wButtons & static_cast<unsigned int>(button))) {
		return true;
	}
	return false;
}

bool InputManager::InputManagerImpl::IsKeyReleasedImpl(ControllerButton button, int deviceIdx) const
{ //Check if key is released this frame
	if (!(m_CurrentStateVec[deviceIdx].Gamepad.wButtons & static_cast<unsigned int>(button)) && (m_PreviousStateVec[deviceIdx].Gamepad.wButtons & static_cast<unsigned int>(button))) {
		return true;
	}
	return false;
}



//InputManager
InputManager::InputManager() : m_pPimpl{ std::make_unique<InputManagerImpl>() } {
	SetNewPlayerAmount(1);
}
//destructor visibility
InputManager::~InputManager() {
	for (auto& playerVec : m_CommandContainer)
	{
		for (auto& pair : playerVec) {
			pair.second.reset();
		}
	}
}
void InputManager::HandleCommands(int playerIdx)
{
	for (auto& mapElement : m_CommandContainer[playerIdx])
	{
		HandleCommand(mapElement.first.first, mapElement.first.second, mapElement.second.get(), playerIdx);
	}
}

void dae::InputManager::SetNewPlayerAmount(int playerAmount)
{
	for (size_t i = 0; i < (playerAmount - GetDeviceAmount()); i++)
	{
		//TODO: change if uniqueptr
		m_CommandContainer.emplace_back();
	}
	m_pPimpl->SetNewPlayerAmountImpl(playerAmount);
}

int InputManager::GetDeviceAmount()
{
	return static_cast<int>(m_CommandContainer.size());
}

void InputManager::ProcessInput()
{
	m_pPimpl->ProcessInputImpl();
}
void InputManager::AddCommand(ControllerButton button, Command* command, KeyState state, int playerIdx)
{	//Add command
	//overwite previous command when key is the same
	m_CommandContainer[playerIdx][std::make_pair(button, state)].reset(command);
}
bool InputManager::RemoveCommand(ControllerButton button, KeyState state, int playerIdx)
{
	//return 0 or 1 if element is erased
	return m_CommandContainer[playerIdx].erase(std::make_pair(button, state));
}
bool InputManager::HandleCommand(ControllerButton button, KeyState state, Command* command, int deviceIdx)
{
	switch (state)
	{
	case KeyState::DOWN:
		if (IsKeyDown(button, deviceIdx)) {
			command->Excecute();
			return true;
		}
		break;
	case KeyState::PRESSED:
		if (IsKeyPressed(button, deviceIdx)) {
			command->Excecute();
			return true;
		}
		break;
	case KeyState::RELEASED:
		if (IsKeyReleased(button, deviceIdx)) {
			command->Excecute();
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}


bool InputManager::IsKeyDown(ControllerButton button, int deviceIdx) const
{
	return m_pPimpl->IsKeyDownImpl(button, deviceIdx);
}

bool InputManager::IsKeyPressed(ControllerButton button, int deviceIdx) const
{
	return m_pPimpl->IsKeyPressedImpl(button, deviceIdx);
}
bool InputManager::IsKeyReleased(ControllerButton button, int deviceIdx) const
{
	return m_pPimpl->IsKeyReleasedImpl(button, deviceIdx);
}

