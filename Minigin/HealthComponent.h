#include "BaseComponent.h"
#include "Subject.h"

namespace dae {

	struct HealthArgs : public EventArgs
	{
		int health;
		int lives;
	};

	class HealthComponent final : public BaseComponent, public Subject
	{
	public:
		HealthComponent(int health = 10, int lives = 1);
		~HealthComponent() = default;

		void Render() const override {};
		void Update() override {};
		void LateUpdate() override {};

		void DecreaseHealth(int healthDecrease);
		void IncreaseHealth(int healthIncrease);

		int GetHealth() const;
		void SetHealth(int newHealth);

		int GetLives() const;
		void SetLives(int lives);

	private:
		int m_Health{};
		int m_Lives{};
		bool m_IsDeath = false;
	};
}


