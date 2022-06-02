#include "MiniginPCH.h"
#include "InputManager.h"
#define WIN32_LEAN_AND_MEAN
#include  <windows.h>
#include <Xinput.h>
#include <algorithm>
#include "imgui_impl_sdl.h"
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

	bool IsKeyDownImpl(unsigned char key) const;
	bool IsKeyPressedImpl(unsigned char key) const;
	bool IsKeyReleasedImpl(unsigned char keyx) const;

private:
	//Controller
	std::vector<XINPUT_STATE> m_PreviousStateVec{};
	std::vector<XINPUT_STATE> m_CurrentStateVec{};
	int m_PlayerAmount = 0;
	BYTE m_CurrentKeyboardState[256] = {};
	BYTE m_PreviousKeyboardState[256] = {};


	//Keyboard
};

InputManager::InputManagerImpl::InputManagerImpl()
{
	for (int i = 0; i < m_PlayerAmount; i++)
	{
		ZeroMemory(&m_PreviousStateVec[i], sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentStateVec[i], sizeof(XINPUT_STATE));
	}
	memset(m_CurrentKeyboardState, 0,256 * sizeof(SHORT));
	memset(m_PreviousKeyboardState, 0, 256 * sizeof(BYTE));


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
	memcpy(m_PreviousKeyboardState, m_CurrentKeyboardState, 256 * sizeof(BYTE));
	if (!GetKeyboardState(m_CurrentKeyboardState)) {
		GetLastError();
	}

}
bool InputManager::InputManagerImpl::IsKeyDownImpl(ControllerButton button, int deviceIdx) const
{	//check if key is pressed down
	if (m_CurrentStateVec[deviceIdx].Gamepad.wButtons & static_cast<unsigned int>(button)) {
		return true;
	}
	return false;

}

bool InputManager::InputManagerImpl::IsKeyDownImpl(unsigned char key) const
{
	BYTE curByte = m_CurrentKeyboardState[(unsigned int)key];
	curByte >>= 7;
	if (curByte == 1) {
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

bool InputManager::InputManagerImpl::IsKeyPressedImpl(unsigned char key) const
{
	BYTE curByte = m_CurrentKeyboardState[key];
	BYTE prevByte = m_PreviousKeyboardState[key];
	curByte >>= 7;
	prevByte >>= 7;

	if (curByte == 1 && prevByte != 1) {
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

bool InputManager::InputManagerImpl::IsKeyReleasedImpl(unsigned char key) const
{
	BYTE curByte = m_CurrentKeyboardState[key];
	BYTE prevByte = m_PreviousKeyboardState[key];
	curByte >>= 7;
	prevByte >>= 7;

	if (curByte != 1 && prevByte == 1) {
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
bool InputManager::HandleCommands(int playerIdx)
{
	bool isTriggered = false;

	for (auto& mapElement : m_CommandContainer[playerIdx])
	{
		if (HandleCommand(mapElement.first.first.first, mapElement.first.first.second, mapElement.first.second, mapElement.second.get(), playerIdx)) {
			isTriggered = true;
		}
	}
	return isTriggered;
}

void dae::InputManager::SetNewPlayerAmount(int playerAmount)
{
	for (int i = 0; i < (playerAmount - GetDeviceAmount()); i++)
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

bool InputManager::ProcessInput()
{
	m_pPimpl->ProcessInputImpl();

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) {
			return false;
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	return true;
}
void InputManager::AddCommand(ControllerButton button, unsigned char key, Command* command, KeyState state, int playerIdx)
{	//Add command
	//overwite previous command when key is the same
	m_CommandContainer[playerIdx][std::make_pair(std::make_pair(button, key), state)].reset(command);
}
bool InputManager::RemoveCommand(ControllerButton button, unsigned char key, KeyState state, int playerIdx)
{
	//return 0 or 1 if element is erased
	return m_CommandContainer[playerIdx].erase(std::make_pair(std::make_pair(button, key), state));
}
bool InputManager::HandleCommand(ControllerButton button, unsigned char key, KeyState state, Command* command, int deviceIdx)
{

	switch (state)
	{
	case KeyState::DOWN:
		if (IsKeyDown(button, deviceIdx) || IsKeyDown(key)) {
			command->Excecute();
			return true;
		}
		break;
	case KeyState::PRESSED:
		if (IsKeyPressed(button, deviceIdx) || IsKeyPressed(key)) {
			command->Excecute();
			return true;
		}
		break;
	case KeyState::RELEASED:
		if (IsKeyReleased(button, deviceIdx) || IsKeyReleased(key)) {
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

bool InputManager::IsKeyReleased(unsigned char key) const
{
	return m_pPimpl->IsKeyReleasedImpl(key);
}

bool InputManager::IsKeyPressed(unsigned char key) const
{
	return m_pPimpl->IsKeyPressedImpl(key);
}

bool InputManager::IsKeyDown(unsigned char key) const
{
	return m_pPimpl->IsKeyDownImpl(key);
}