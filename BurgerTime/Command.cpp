#include "MiniginPCH.h"

#include "HealthComponent.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "AttackComponent.h"
#include "PetterPepperComponent.h"
#include "Command.h"
//Enter
class MoveRightEnterCommand : public dae::Command {
public:
	MoveRightEnterCommand(Burger::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {

	};
	virtual void Excecute() {
		m_PeterComp->MoveRightEnter();
	}
private:
	Burger::PetterPepperComponent* m_PeterComp;
};
class MoveUpEnterCommand : public dae::Command {
public:
	MoveUpEnterCommand(Burger::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveUpEnter();
		//sprite
	
	}
private:
	Burger::PetterPepperComponent* m_PeterComp;
};
class MoveDownEnterCommand : public dae::Command {
public:
	MoveDownEnterCommand(Burger::PetterPepperComponent* peterComp)
	: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveDownEnter();
	}
private:
	Burger::PetterPepperComponent* m_PeterComp;
};
class MoveLeftEnterCommand : public dae::Command {
public:
	MoveLeftEnterCommand(Burger::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveLeftEnter();
	}
private:
	Burger::PetterPepperComponent* m_PeterComp;

};

//Exit commanbds
class MoveRightExitCommand : public dae::Command {
public:
	MoveRightExitCommand(Burger::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {

	};
	virtual void Excecute() {
		m_PeterComp->MoveRightExit();
	}
private:
	Burger::PetterPepperComponent* m_PeterComp;
};
class MoveUpExitCommand : public dae::Command {
public:
	MoveUpExitCommand(Burger::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveUpExit();
		//sprite

	}
private:
	Burger::PetterPepperComponent* m_PeterComp;
};
class MoveDownExitCommand : public dae::Command {
public:
	MoveDownExitCommand(Burger::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveDownExit();
	}
private:
	Burger::PetterPepperComponent* m_PeterComp;
};
class MoveLeftExitCommand : public dae::Command {
public:
	MoveLeftExitCommand(Burger::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveLeftExit();
	}
private:
	Burger::PetterPepperComponent* m_PeterComp;

};


//Attack
class AttackCommand : public dae::Command {
public:
	AttackCommand(Burger::AttackComponent* attackComp) { m_pAttackComp = attackComp; }
	virtual void Excecute() {
		if (m_pAttackComp != nullptr) {
			m_pAttackComp->Fire();

		}
	}
private:
	Burger::AttackComponent* m_pAttackComp;
};
