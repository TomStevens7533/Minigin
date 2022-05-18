#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include <vector>
#include "SceneColliders.h"
namespace dae {
	class MovementComponent;
	class HotDoggBehaviourComponent final : public BaseComponent
	{
	public:
		HotDoggBehaviourComponent(std::string tagToFollow);
		~HotDoggBehaviourComponent() = default;


		HotDoggBehaviourComponent(const HotDoggBehaviourComponent& other) = delete;
		HotDoggBehaviourComponent(HotDoggBehaviourComponent&& other) = delete;
		HotDoggBehaviourComponent& operator=(const HotDoggBehaviourComponent& other) = delete;
		HotDoggBehaviourComponent& operator=(HotDoggBehaviourComponent&& other) = delete;


		virtual void Start() override;
		virtual void Render() const override {};
		virtual void Update() override;
		virtual void LateUpdate() override {};
	private:
		int GetPlayerQuadrant();
	private:
		std::vector<std::shared_ptr<dae::ColliderInfo>> m_PlayerVec;
		std::string m_TagToFollow;
		dae::MovementComponent* m_HotDogMovement = nullptr;
	
	};
}


