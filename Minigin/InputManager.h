#pragma once
#include <iostream>
#include <map>
#include <memory>
#include "Singleton.h"
#include "Command.h"
namespace dae
{

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

		bool ProcessInput();
		void AddCommand(ControllerButton button, unsigned char key, Command* command, KeyState state, int playerIdx);
		bool RemoveCommand(ControllerButton button, unsigned char key, KeyState state, int playerIdx);
		bool HandleCommands(int playerIdx);

		void SetNewPlayerAmount(int playerAmount);
		int GetDeviceAmount();

		InputManager(const InputManager&& e) = delete;
		InputManager& operator=(InputManager e) = delete;

	public:
		friend class Singleton<InputManager>;
		bool IsKeyDown(ControllerButton button, int deviceIdx) const;
		bool IsKeyDown(unsigned char key) const;

		bool IsKeyPressed(ControllerButton button, int deviceIdx) const;
		bool IsKeyPressed(unsigned char key) const;

		bool IsKeyReleased(ControllerButton button, int deviceIdx) const;
		bool IsKeyReleased(unsigned char key) const;

		bool HandleCommand(ControllerButton button, unsigned char key, KeyState state, Command* command, int playerIdx);



	private:
		class InputManagerImpl;
		std::unique_ptr<InputManagerImpl> m_pPimpl;
	private:
		bool m_KeyBoardKeys[322];
		//TODO: find way to make value(command) unique pointer while stil being able to dynamically add players
		std::vector<std::map<std::pair<std::pair<ControllerButton, unsigned char>, KeyState>, std::shared_ptr<Command>>> m_CommandContainer;
	};
}