#include "MiniginPCH.h"
#include "InputComponent.h"
namespace dae {
	void InputComponent::AddCommand(ControllerButton button, Command* command, KeyState state)
	{
		InputManager::GetInstance().AddCommand(button, command, state);
	}
	void InputComponent::Update()
	{
		InputManager::GetInstance().HandleCommands();
	}
}