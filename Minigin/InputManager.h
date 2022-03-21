#pragma once
#include <iostream>
#include <map>
#include <memory>
#include "Singleton.h"
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() { std::cout << "deleting command\n"; };
		virtual void Excecute() = 0;
	};
	enum class ControllerButton
	{
		GAMEPAD_DPAD_UP = 0x0001,
		GAMEPAD_DPAD_DOWN = 0x0002,
		GAMEPAD_DPAD_LEFT = 0x0004,
		GAMEPAD_DPAD_RIGHT = 0x0008,
		GAMEPAD_START = 0x0010,
		GAMEPAD_BACK = 0x0020,
		GAMEPAD_LEFT_THUMB = 0x0040,
		GAMEPAD_RIGHT_THUMB = 0x0080,
		GAMEPAD_LEFT_SHOULDER = 0x0100,
		GAMEPAD_RIGHT_SHOULDER = 0x0200,
		GAMEPAD_BUTTON_SOUTH = 0x1000,
		GAMEPAD_BUTTON_EAST = 0x2000,
		GAMEPAD_BUTTON_WEST = 0x4000,
		GAMEPAD_BUTTON_NORTH = 0x8000
	};
	enum class KeyState {
		DOWN,
		PRESSED,
		RELEASED
	};

	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		void ProcessInput();
		void AddCommand(ControllerButton button, Command* command, KeyState state);
		bool RemoveCommand(ControllerButton button, KeyState state);
		void HandleCommands();

		InputManager(const InputManager&& e) = delete;
		InputManager& operator=(InputManager e) = delete;

	public:
		friend class Singleton<InputManager>;
		bool IsKeyDown(ControllerButton button) const;
		bool IsKeyPressed(ControllerButton button) const;
		bool IsKeyReleased(ControllerButton button) const;
		bool HandleCommand(ControllerButton button, KeyState state, Command* command);



	private:
		class InputManagerImpl;
		std::unique_ptr<InputManagerImpl> m_pPimpl;


	private:

		std::map<std::pair<ControllerButton, KeyState>, std::unique_ptr<Command>> m_CommandMap;

	};
}