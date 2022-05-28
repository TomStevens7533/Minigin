#include "MiniginPCH.h"
#include "Command.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "AttackComponent.h"
#include "PetterPepperComponent.h"
//Enter
class MoveRightEnterCommand : public Command {
public:
	MoveRightEnterCommand(dae::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {

	};
	virtual void Excecute() {
		m_PeterComp->MoveRightEnter();
	}
private:
	dae::PetterPepperComponent* m_PeterComp;
};
class MoveUpEnterCommand : public Command {
public:
	MoveUpEnterCommand(dae::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveUpEnter();
		//sprite
	
	}
private:
	dae::PetterPepperComponent* m_PeterComp;
};
class MoveDownEnterCommand : public Command {
public:
	MoveDownEnterCommand(dae::PetterPepperComponent* peterComp)
	: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveDownEnter();
	}
private:
	dae::PetterPepperComponent* m_PeterComp;
};
class MoveLeftEnterCommand : public Command {
public:
	MoveLeftEnterCommand(dae::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveLeftEnter();
	}
private:
	dae::PetterPepperComponent* m_PeterComp;

};

//Exit commanbds
class MoveRightExitCommand : public Command {
public:
	MoveRightExitCommand(dae::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {

	};
	virtual void Excecute() {
		m_PeterComp->MoveRightExit();
	}
private:
	dae::PetterPepperComponent* m_PeterComp;
};
class MoveUpExitCommand : public Command {
public:
	MoveUpExitCommand(dae::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveUpExit();
		//sprite

	}
private:
	dae::PetterPepperComponent* m_PeterComp;
};
class MoveDownExitCommand : public Command {
public:
	MoveDownExitCommand(dae::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveDownExit();
	}
private:
	dae::PetterPepperComponent* m_PeterComp;
};
class MoveLeftExitCommand : public Command {
public:
	MoveLeftExitCommand(dae::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {
	};
	virtual void Excecute() {
		m_PeterComp->MoveLeftExit();
	}
private:
	dae::PetterPepperComponent* m_PeterComp;

};


//Attack
class AttackCommand : public Command {
public:
	AttackCommand(dae::AttackComponent* attackComp) { m_pAttackComp = attackComp; }
	virtual void Excecute() {
		if (m_pAttackComp != nullptr) {
			m_pAttackComp->Fire();

		}
	}
private:
	dae::AttackComponent* m_pAttackComp;
};
