#include "MiniginPCH.h"
#include "InputComponent.h"
#include "BaseComponent.h"
#include "GameObject.h"
namespace dae {
	InputComponent::InputComponent(int deviceIdx) : m_deviceIdx{deviceIdx}
	{
		//if device amount exceeds the configuration of input manager reconfigure
		if (!(m_deviceIdx < InputManager::GetInstance().GetDeviceAmount())) {
			InputManager::GetInstance().SetNewPlayerAmount(m_deviceIdx + 1);
		}
		std::cout << m_deviceIdx << std::endl;
	}

	InputComponent::~InputComponent()
	{

	}

	void InputComponent::AddCommand(ControllerButton button, unsigned char key, Command* command, KeyState state)
	{
		InputManager::GetInstance().AddCommand(button, static_cast<unsigned char>(key), command, state, m_deviceIdx);
	}
	void InputComponent::Update()
	{
		m_IsTriggered = InputManager::GetInstance().HandleCommands(m_deviceIdx);
	}
}