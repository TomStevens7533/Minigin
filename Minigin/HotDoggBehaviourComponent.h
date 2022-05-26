#pragma once
#include "BaseComponent.h"
#include <vector>
#include "structs.h"
#include "Observer.h"

namespace dae {

	class AIBehaviourComponent;

	class VerticalState;
	class HorizontalState;
	class IdleState;

	class AIState {
	public:
		virtual ~AIState() {};
		virtual void Entry(AIBehaviourComponent&) = 0;
		virtual  AIState* UpdateState(AIBehaviourComponent& ) = 0;
		virtual void Exit(AIBehaviourComponent&) = 0;
		friend AIBehaviourComponent;

		static HorizontalState m_HorizontalState;
		static VerticalState m_VerticalState;
		static IdleState m_IdleState;


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
		float m_MinExitTime = 1.f;
		float m_CurrentTime = 0.f;

	};
	class IdleState final : public AIState {
	public:
		virtual void Entry(AIBehaviourComponent&) override {};
		virtual  AIState* UpdateState(AIBehaviourComponent& ai)  override;
		virtual void Exit(AIBehaviourComponent&) override {};

	private:
		float m_MinExitTime = 1.f;
		float m_CurrentTime = 0.f;

	};


	class SpriteComponent;
	class MovementComponent;
	class AIBehaviourComponent final : public BaseComponent, public Observer
	{
	public:
		AIBehaviourComponent(std::string tagToFollow);
		~AIBehaviourComponent() = default;


		AIBehaviourComponent(const AIBehaviourComponent& other) = delete;
		AIBehaviourComponent(AIBehaviourComponent&& other) = delete;
		AIBehaviourComponent& operator=(const AIBehaviourComponent& other) = delete;
		AIBehaviourComponent& operator=(AIBehaviourComponent&& other) = delete;


		virtual void Start() override;
		virtual void Render() const override {};
		virtual void Update() override;
		virtual void LateUpdate() override {};

		void SetHorizontalDir(HorizontalDirection horizon);
		void SetVerticalDir(VerticalDirection vertical);
		glm::vec2 GetClosestPlayerPos() const;
		const MovementComponent* GetMovementComponent() const { return m_HotDogMovement; }
		SpriteComponent* GetSpriteComponent() const { return m_SpriteComponent; }

		void onNotify(const BaseComponent* entity, int event, EventArgs* args = nullptr) override;



	private:


		AIState* m_CurrState = nullptr;

		std::vector<std::shared_ptr<dae::ColliderInfo>> m_PlayerVec;
		std::string m_TagToFollow;
		dae::MovementComponent* m_HotDogMovement = nullptr;
		SpriteComponent* m_SpriteComponent = nullptr;
	
	};




}


