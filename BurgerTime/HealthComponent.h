#include "BaseComponent.h"
#include "Subject.h"

namespace Burger {

	struct HealthArgs : public dae::EventArgs
	{
		int health;
		int lives;
	};

	class HealthComponent final : public dae::BaseComponent, public dae::Subject
	{
	public:
		HealthComponent(int health = 1, int lives = 5);
		~HealthComponent() = default;

		void Render() const override {};
		void Update() override {};
		void LateUpdate() override {};
		virtual void Start() override;

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


