#pragma once
#include "BaseComponent.h"
namespace dae {
	struct ColliderInfo;
	class BoxColliderComponent;
	class BunBehaviour : public BaseComponent
	{
	public:
		BunBehaviour() = default;
		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		virtual void Start() override;

		void SetFalling();
		BunBehaviour(const BunBehaviour& other) = delete;
		BunBehaviour(BunBehaviour&& other) = delete;
		BunBehaviour& operator=(const BunBehaviour& other) = delete;
		BunBehaviour& operator=(BunBehaviour&& other) = delete;
	private:
		BoxColliderComponent* m_pBoxColliderComponent;
		std::shared_ptr<ColliderInfo> m_pPeterCollision;
		bool m_IsFalling = false;
		float m_Velocity = 10.f;
		GameObject* m_pInfoGround{};
	};
}
