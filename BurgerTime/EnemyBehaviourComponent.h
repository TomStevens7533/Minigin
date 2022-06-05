#pragma once
#include "BaseComponent.h"
#include <vector>
#include "structs.h"
#include "Subject.h"
#include "BurgerStructs.h"

namespace dae { 
class SpriteComponent;
class BoxColliderComponent;
}

namespace Burger {


	class GameObject;
	class MovementComponent;
	class EnemyBehaviourComponent final : public dae::BaseComponent, public dae::Subject
	{
	public:
		EnemyBehaviourComponent(std::string tagToFollow, EnemyType type, int score, bool isPlayerControlled = false);
		~EnemyBehaviourComponent();


		EnemyBehaviourComponent(const EnemyBehaviourComponent& other) = delete;
		EnemyBehaviourComponent(EnemyBehaviourComponent&& other) = delete;
		EnemyBehaviourComponent& operator=(const EnemyBehaviourComponent& other) = delete;
		EnemyBehaviourComponent& operator=(EnemyBehaviourComponent&& other) = delete;


		virtual void Start() override;
		virtual void Render() const override;
		virtual void Update() override;
		virtual void FixedUpdate() override {};

		void SetFallState(float velocity);

		void OnCollisionStay (const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionExit(const std::shared_ptr<dae::ColliderInfo> otherInfo);
	private:
		void UpdateSprite();
		point GetClosestPlayerPos() const;
		bool IsEnemyMutable();
	private:
		enum class EnemyState {
			Falling		 = (1 << 0),
			Spawning	 = (1 << 1),
			Ladder		 = (1 << 2),
			Floor		 = (1 << 3),
			Death		 = (1 << 4)

		};

	private: //AI STATES
		class AIState {
		public:
			virtual ~AIState() {};
			virtual void Entry(EnemyBehaviourComponent&) = 0;
			virtual  AIState* UpdateState(EnemyBehaviourComponent&) = 0;
			virtual void Exit(EnemyBehaviourComponent&) = 0;
		}; friend class AIState;
		class HorizontalState final : public AIState {
		public:
			virtual void Entry(EnemyBehaviourComponent& ai) override;
			virtual AIState* UpdateState(EnemyBehaviourComponent& ai) override;
			virtual void Exit(EnemyBehaviourComponent&) override;
		private:
			float m_MinExitTime = 1.f;
			float m_CurrentTime = 0.f;
		}; friend class HorizontalState;
		class VerticalState final : public AIState {
		public:
			virtual void Entry(EnemyBehaviourComponent& ai) override;
			virtual  AIState* UpdateState(EnemyBehaviourComponent& ai)  override;
			virtual void Exit(EnemyBehaviourComponent&) override;
		private:
			float m_MinExitTime = 1.0f;
			float m_CurrentTime = 0.f;
		}; friend class VerticalState;
		class HitState final : public AIState {
		public:
			virtual void Entry(EnemyBehaviourComponent&) override;
			virtual  AIState* UpdateState(EnemyBehaviourComponent& ai)  override;
			virtual void Exit(EnemyBehaviourComponent&) override;
		private:
			float m_MinExitTime = 5.f;
			float m_CurrentTime = 0.f;
		}; friend class HitState;
		class DeathState final : public AIState {
		public:
			virtual void Entry(EnemyBehaviourComponent&) override;
			virtual  AIState* UpdateState(EnemyBehaviourComponent& ai)  override;
			virtual void Exit(EnemyBehaviourComponent&) override;
		}; friend class DeathState;
		class FallingState final : public AIState {
		public:
			virtual void Entry(EnemyBehaviourComponent&) override;
			virtual  AIState* UpdateState(EnemyBehaviourComponent& ai)  override;
			virtual void Exit(EnemyBehaviourComponent&) override;
		}; friend class FallingState;
	private:
		AIState* m_CurrState = nullptr;
		std::vector <dae::GameObject*> m_PlayerVec;
		std::string m_TagToFollow;
		MovementComponent* m_MovementComponent = nullptr;
		dae::SpriteComponent* m_SpriteComponent = nullptr;
		dae::BoxColliderComponent* m_ColliderComponent = nullptr;

		EnemyState m_EnemyState = EnemyState::Spawning;

		bool m_IsPlayerControllerd = false;
		int m_Score{};
		EnemyType m_Type;
	};




}


