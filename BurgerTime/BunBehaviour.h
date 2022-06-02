#pragma once
#include "BaseComponent.h"
#include "structs.h"
#include "Subject.h"
namespace Burger {
	struct ColliderInfo;
	class BoxColliderComponent;
	class BunBehaviour : public dae::BaseComponent, public dae::Subject
	{
	public:
		BunBehaviour() = default;
		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		virtual void Start() override;

		bool GetFinalPos() { return m_IsInFinalPos; };
		BunBehaviour(const BunBehaviour& other) = delete;
		BunBehaviour(BunBehaviour&& other) = delete;
		BunBehaviour& operator=(const BunBehaviour& other) = delete;
		BunBehaviour& operator=(BunBehaviour&& other) = delete;

		void OnCollisionStay(const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionExit(const std::shared_ptr<dae::ColliderInfo> otherInfo);

	private:

		bool m_IsInEndPos = false;
		bool m_IsFalling = false;
		float m_Velocity = 60.f;
		int m_IncreaseScore = 50;
		bool m_IsPeterInCollFirst = false;
		bool m_IsInFinalPos = false;
		float m_EnterPeterPosX;
		int m_ScoreToThrow = 0;
		bool m_EnemyOnBun = false;
	};
}
