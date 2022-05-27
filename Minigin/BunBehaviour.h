#pragma once
#include "BaseComponent.h"
#include "structs.h"
#include "Subject.h"
namespace dae {
	struct ColliderInfo;
	class BoxColliderComponent;
	class BunBehaviour : public BaseComponent, public Subject, public Observer
	{
	public:
		BunBehaviour() = default;
		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		virtual void Start() override;

		void SetFalling();
		bool GetFinalPos() { return m_IsInFinalPos; };
		BunBehaviour(const BunBehaviour& other) = delete;
		BunBehaviour(BunBehaviour&& other) = delete;
		BunBehaviour& operator=(const BunBehaviour& other) = delete;
		BunBehaviour& operator=(BunBehaviour&& other) = delete;

		virtual void onNotify(const BaseComponent* entity, int event, EventArgs* args = nullptr);
	private:

		bool m_IsFalling = false;
		float m_Velocity = 30.f;
		int m_IncreaseScore = 50;
		bool m_IsPeterInCollFirst = false;
		bool m_IsInFinalPos = false;
		float m_EnterPeterPosX;
	};
}
