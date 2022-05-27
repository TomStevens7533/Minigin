#pragma once
#include "BaseComponent.h"
#include <vector>
#include "structs.h"
#include "Observer.h"

namespace dae {

	class AIBehaviourComponent;

	class VerticalState;
	class HorizontalState;
	class HitState;

	class AIState {
	public:
		virtual ~AIState() {};
		virtual void Entry(AIBehaviourComponent&) = 0;
		virtual  AIState* UpdateState(AIBehaviourComponent& ) = 0;
		virtual void Exit(AIBehaviourComponent&) = 0;
		friend AIBehaviourComponent;

		static HorizontalState m_HorizontalState;
		static VerticalState m_VerticalState;
		static HitState m_HitState;


	};



	class HorizontalState final : public AIState {
	public:
		virtual void Entry(AIBehaviourComponent& ai) override;;
		virtual AIState* UpdateState(AIBehaviourComponent& ai) override;
		virtual void Exit(AIBehaviourComponent&) override;



	private:
		float m_MinExitTime = 0.5f;
		float m_CurrentTime = 0.f;
	};
	class VerticalState final : public AIState {
	public:
		virtual void Entry(AIBehaviourComponent& ai) override;
		virtual  AIState* UpdateState(AIBehaviourComponent& ai)  override;
		virtual void Exit(AIBehaviourComponent&) override;

	private:
		float m_MinExitTime = 0.5f;
		float m_CurrentTime = 0.f;

	};
	class HitState final : public AIState {
	public:
		virtual void Entry(AIBehaviourComponent&) override;
		virtual  AIState* UpdateState(AIBehaviourComponent& ai)  override;
		virtual void Exit(AIBehaviourComponent&) override {};


	private:
		float m_MinExitTime = 3.f;
		float m_CurrentTime = 0.f;

	};

	class BoxColliderComponent;
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
		virtual void Render() const override;
		virtual void Update() override;
		virtual void LateUpdate() override {};

		void SetHorizontalDir(HorizontalDirection horizon);
		void SetVerticalDir(VerticalDirection vertical);
		glm::vec2 GetClosestPlayerPos() const;

		void onNotify(const BaseComponent* entity, int event, EventArgs* args = nullptr) override;

		friend class HorizontalState;
		friend class VerticalState;
		friend class HitState;




	private:


		AIState* m_CurrState = nullptr;
		std::vector<std::shared_ptr<ColliderInfo>> m_PlayerVec;
		std::string m_TagToFollow;
		dae::MovementComponent* m_HotDogMovement = nullptr;
		SpriteComponent* m_SpriteComponent = nullptr;
		BoxColliderComponent* m_ColliderComponent = nullptr;
		bool m_IsOnLadder = false;
		bool m_IsOnFloor = false;
	
	};




}


