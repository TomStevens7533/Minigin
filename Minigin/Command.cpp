#include "MiniginPCH.h"
#include "Command.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
class MoveRightEnterCommand : public Command {
public:
	MoveRightEnterCommand(dae::MovementComponent* peterComp)
		: m_PeterComp{ peterComp } {
		m_PeterSprite = m_PeterComp->GetAttachedGameObject()->GetComponent<dae::SpriteComponent>();

	};
	virtual void Excecute() {
		m_PeterComp->SetNewHorizontalDirection(dae::HorizontalDirection::RIGHT);


		//sprite
		if (m_PeterSprite != nullptr) {
			m_PeterSprite->SetActiveAnimation("Move");
			m_PeterSprite->SetFlipState(true);
		}
	}
private:
	dae::SpriteComponent* m_PeterSprite;
	dae::MovementComponent* m_PeterComp;
};
class MoveUpEnterCommand : public Command {
public:
	MoveUpEnterCommand(dae::MovementComponent* peterComp)
		: m_PeterComp{ peterComp } {
		m_PeterSprite = m_PeterComp->GetAttachedGameObject()->GetComponent<dae::SpriteComponent>();

	};
	virtual void Excecute() {
		m_PeterComp->SetNewVerticalDirection(dae::VerticalDirection::UP);

		//sprite
		if (m_PeterSprite != nullptr) {
			m_PeterSprite->SetActiveAnimation("MoveForward");
			m_PeterSprite->SetFlipState(false);

		}
	}
private:
	dae::SpriteComponent* m_PeterSprite;
	dae::MovementComponent* m_PeterComp;
};
class MoveDownEnterCommand : public Command {
public:
	MoveDownEnterCommand(dae::MovementComponent* peterComp)
	: m_PeterComp{ peterComp } {
		//Get sprite component
		m_PeterSprite = m_PeterComp->GetAttachedGameObject()->GetComponent<dae::SpriteComponent>();
	
	};
	virtual void Excecute() {
		
		m_PeterComp->SetNewVerticalDirection(dae::VerticalDirection::DOWN);

		//Sprite
		if (m_PeterSprite != nullptr) {
			m_PeterSprite->SetActiveAnimation("MoveBackwards");
			m_PeterSprite->SetFlipState(false);
		}
	
		
	}
private:
	dae::SpriteComponent* m_PeterSprite;
	dae::MovementComponent* m_PeterComp;
};
class MoveLeftEnterCommand : public Command {
public:
	MoveLeftEnterCommand(dae::MovementComponent* peterComp)
		: m_PeterComp{ peterComp } {
		m_PeterSprite = m_PeterComp->GetAttachedGameObject()->GetComponent<dae::SpriteComponent>();
	};
	virtual void Excecute() {
		m_PeterComp->SetNewHorizontalDirection(dae::HorizontalDirection::LEFT);

		///sprite
 		if (m_PeterSprite != nullptr) {
			m_PeterSprite->SetActiveAnimation("Move");
			m_PeterSprite->SetFlipState(false);
		}

	}
private:
	dae::MovementComponent* m_PeterComp;
	dae::SpriteComponent* m_PeterSprite;

};

//----------EXIT
class MoveHorizontalExitCommand : public Command {
public:
	MoveHorizontalExitCommand(dae::MovementComponent* peterComp)
		: m_PeterComp{ peterComp } {
		m_PeterSprite = m_PeterComp->GetAttachedGameObject()->GetComponent<dae::SpriteComponent>();
	};
	virtual void Excecute() {
		m_PeterComp->SetNewHorizontalDirection(dae::HorizontalDirection::NONE);

		//Sprite
		if (m_PeterSprite != nullptr) {
			m_PeterSprite->SetActiveAnimation("MoveBackwards");
			m_PeterSprite->SetFlipState(false);

		}
	}
private:
	dae::MovementComponent* m_PeterComp;
	dae::SpriteComponent* m_PeterSprite;

};
//----------EXIT
class MoveVerticalExitCommand : public Command {
public:
	MoveVerticalExitCommand(dae::MovementComponent* peterComp)
		: m_PeterComp{ peterComp } {
		m_PeterSprite = m_PeterComp->GetAttachedGameObject()->GetComponent<dae::SpriteComponent>();
	};
	virtual void Excecute() {
		m_PeterComp->SetNewVerticalDirection(dae::VerticalDirection::NONE);

		//Sprite
		if (m_PeterSprite != nullptr) {
			m_PeterSprite->SetActiveAnimation("MoveBackwards");
			m_PeterSprite->SetFlipState(false);

		}
	}
private:
	dae::MovementComponent* m_PeterComp;
	dae::SpriteComponent* m_PeterSprite;

};

class DamageCommand : public Command {
public:
	DamageCommand(dae::HealthComponent* componentToDamage, int damage) : m_ComponentToDamage{ componentToDamage }, m_Damage{ damage } {};
	virtual void Excecute() {
		m_ComponentToDamage->DecreaseHealth(m_Damage);

	
	}
private:
	dae::HealthComponent* m_ComponentToDamage;

	int m_Damage;
};
