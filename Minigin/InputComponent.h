#include "BaseComponent.h"
#include "InputManager.h"
namespace dae {
	class InputComponent final : public BaseComponent
	{
	public:
		InputComponent() = default;
		~InputComponent() = default;

		void AddCommand(ControllerButton button, Command* command, KeyState state);
		
		void Render() const override {};
		void Update() override;
		void LateUpdate() override {};
	};
}


