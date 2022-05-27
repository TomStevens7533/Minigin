#pragma once
#include "BaseComponent.h"
#include "Observer.h"




namespace dae {
	class InputComponent;
	class SpriteComponent;
	class BoxColliderComponent;
	class MovementComponent;
	//

	//class PepperState {
	//public:
	//	virtual ~PepperState() {};
	//	virtual void Entry(PetterPepperComponent& pepper) = 0;
	//	virtual  PepperState* UpdateState(PetterPepperComponent& pepper) = 0;
	//	virtual void Exit(PetterPepperComponent& pepper) = 0;

	//	static MoveState m_MoveState;
	//	static AttackState m_AttackState;


	//};

	//class MoveState final : public PepperState {
	//public:
	//	virtual void Entry(PetterPepperComponent& ai) override;
	//	virtual  PepperState* UpdateState(PetterPepperComponent& pepper) override;
	//	virtual void Exit(PetterPepperComponent&) override;
	//private:
	//	float m_MinExitTime = 0.5f;
	//	float m_CurrentTime = 0.f;
	//};
	//class AttackState final : public PepperState {
	//public:
	//	virtual void Entry(PetterPepperComponent& ai) override;
	//	virtual  PepperState* UpdateState(PetterPepperComponent& pepper) override;
	//	virtual void Exit(PetterPepperComponent&) override;
	//private:
	//	float m_MinExitTime = 0.2f;
	//	float m_CurrentTime = 0.f;
	//};


	class PetterPepperComponent final : public BaseComponent, public Observer
	{
	public:
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() const override;

		void onNotify(const BaseComponent* entity, int event, EventArgs* args = nullptr) override;


		void MoveLeftEnter();
		void MoveRightEnter();
		void MoveUpEnter();
		void MoveDownEnter();


		void MoveLeftExit();
		void MoveRightExit();
		void MoveUpExit();
		void MoveDownExit();

		friend class MoveState;
		friend class AttackState;

	protected:

	private:



		InputComponent* m_InputComponent;
		SpriteComponent* m_SpriteComponent;
		BoxColliderComponent* m_ColliderComponent = nullptr;
		MovementComponent* m_MovementComp = nullptr;

		bool m_IsOnLadderUp = false;
		bool m_IsOnLadderDown = false;

		bool m_IsOnFloorRight = false;
		bool m_IsOnFloorLeft = false;

	};

}

