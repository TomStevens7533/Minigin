#include "BaseComponent.h"
#include "InputManager.h"
namespace dae {
	class InputComponent final : public BaseComponent
	{
	public:
		InputComponent(int deviceIdx);
		~InputComponent();

		void AddCommand(ControllerButton button, unsigned char key, Command* command, KeyState state);
		int GetDeviceIdx() { return m_deviceIdx; };
		bool IsTriggered() { return m_IsTriggered; }
		virtual void Start() override {};
		virtual void Render() const override {};
		virtual void Update() override;
		virtual void FixedUpdate() override {};

		InputComponent(const InputComponent& other) = delete;
		InputComponent(InputComponent&& other) = delete;
		InputComponent& operator=(const InputComponent& other) = delete;
		InputComponent& operator=(InputComponent&& other) = delete;
	private:
		int m_deviceIdx{};
		bool m_IsTriggered = false;
	};
}


