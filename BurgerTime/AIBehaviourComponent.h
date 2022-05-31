#pragma once
#include "BaseComponent.h"
#include <vector>
#include "structs.h"
#include "Subject.h"

namespace dae { 
class SpriteComponent;
class BoxColliderComponent;
}

namespace Burger {

	class AIBehaviourComponent;
	class AIState {
	public:
		virtual ~AIState() {};
		virtual void Entry(AIBehaviourComponent&) = 0;
		virtual  AIState* UpdateState(AIBehaviourComponent& ) = 0;
		virtual void Exit(AIBehaviourComponent&) = 0;
		friend AIBehaviourComponent;
	};



	class HorizontalState final : public AIState {
	public:
		virtual void Entry(AIBehaviourComponent& ai) override;;
		virtual AIState* UpdateState(AIBehaviourComponent& ai) override;
		virtual void Exit(AIBehaviourComponent&) override;



	private:
		float m_MinExitTime = 1.f;
		float m_CurrentTime = 0.f;
	};
	class VerticalState final : public AIState {
	public:
		virtual void Entry(AIBehaviourComponent& ai) override;
		virtual  AIState* UpdateState(AIBehaviourComponent& ai)  override;
		virtual void Exit(AIBehaviourComponent&) override;

	private:
		float m_MinExitTime = 1.0f;
		float m_CurrentTime = 0.f;

	};
	class HitState final : public AIState {
	public:
		virtual void Entry(AIBehaviourComponent&) override;
		virtual  AIState* UpdateState(AIBehaviourComponent& ai)  override;
		virtual void Exit(AIBehaviourComponent&) override;


	private:
		float m_MinExitTime = 5.f;
		float m_CurrentTime = 0.f;

	};
	class DeathState final : public AIState {
	public:
		virtual void Entry(AIBehaviourComponent&) override;
		virtual  AIState* UpdateState(AIBehaviourComponent& ai)  override;
		virtual void Exit(AIBehaviourComponent&) override;


	private:
		float m_MinExitTime = 5.f;
		float m_CurrentTime = 0.f;
		bool m_IsSpawning = false;

	};

	struct EnemyArgs : public dae::EventArgs
	{
		std::string name = "";
		int points{};
	};

	class MovementComponent;
	class AIBehaviourComponent final : public dae::BaseComponent, public dae::Subject
	{
	public:
		AIBehaviourComponent(std::string tagToFollow, std::string enemyName, int score);
		~AIBehaviourComponent();


		AIBehaviourComponent(const AIBehaviourComponent& other) = delete;
		AIBehaviourComponent(AIBehaviourComponent&& other) = delete;
		AIBehaviourComponent& operator=(const AIBehaviourComponent& other) = delete;
		AIBehaviourComponent& operator=(AIBehaviourComponent&& other) = delete;


		virtual void Start() override;
		virtual void Render() const override;
		virtual void Update() override;
		virtual void LateUpdate() override {};

		void SetHorizontalDir(dae::HorizontalDirection horizon);
		void SetVerticalDir(dae::VerticalDirection vertical);
		glm::vec2 GetClosestPlayerPos() const;

		friend class HorizontalState;
		friend class VerticalState;
		friend class HitState;
		friend class DeathState;



		void OnCollisionStay (const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionExit (const std::shared_ptr<dae::ColliderInfo> otherInfo);

	private:
		AIState* m_CurrState = nullptr;
		std::vector < const dae::ColliderInfo* > m_PlayerVec;
		std::string m_TagToFollow;
		MovementComponent* m_HotDogMovement = nullptr;
		dae::SpriteComponent* m_SpriteComponent = nullptr;
		dae::BoxColliderComponent* m_ColliderComponent = nullptr;

		bool m_IsOnLadder = false;
		bool m_IsOnFloor = false;
		bool m_IsDeath = false;
		bool m_IsSpawning = true;

		int m_Score{};
		std::string m_Name;
	};




}


