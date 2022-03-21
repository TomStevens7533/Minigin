#include "BaseComponent.h"
namespace dae {
	class HealthComponent final : public BaseComponent
	{
	public:
		HealthComponent(int health) : m_Health{health} {};
		~HealthComponent() = default;

		void Render() const override {};
		void Update() override {};
		void LateUpdate() override {};

		void DecreaseHealth(int healthDecrease);
		void IncreateHealth(int healthIncrease);

		int GetHealth() const;
		void SetHealth(int newHealth);

	private:
		int m_Health;
	};
}


