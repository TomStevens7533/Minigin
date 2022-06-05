#pragma warning(disable:4201)
#include "MovementComponent.h"
#include "Command.h"
#include "AttackComponent.h"
//Enter
class MoveRightEnterCommand : public dae::Command {
public:
	MoveRightEnterCommand(Burger::MovementComponent* moveComp)
		: m_MoveComp{ moveComp } {

	};
	virtual void Excecute() {
		m_MoveComp->SetNewDirection(Direction::RIGHT);
	}
private:
	Burger::MovementComponent* m_MoveComp;
};
class MoveUpEnterCommand : public dae::Command {
public:
	MoveUpEnterCommand(Burger::MovementComponent* moveComp)
		: m_MoveComp{ moveComp } {
	};
	virtual void Excecute() {
		m_MoveComp->SetNewDirection(Direction::UP);
		//sprite
	
	}
private:
	Burger::MovementComponent* m_MoveComp;
};
class MoveDownEnterCommand : public dae::Command {
public:
	MoveDownEnterCommand(Burger::MovementComponent* moveComp)
	: m_MoveComp{ moveComp } {
	};
	virtual void Excecute() {
		m_MoveComp->SetNewDirection(Direction::DOWN);
	}
private:
	Burger::MovementComponent* m_MoveComp;
};
class MoveLeftEnterCommand : public dae::Command {
public:
	MoveLeftEnterCommand(Burger::MovementComponent* moveComp)
		: m_MoveComp{ moveComp } {
	};
	virtual void Excecute() {
		m_MoveComp->SetNewDirection(Direction::LEFT);
	}
private:
	Burger::MovementComponent* m_MoveComp;

};

//Exit commanbds
class MoveRightExitCommand : public dae::Command {
public:
	MoveRightExitCommand(Burger::MovementComponent* moveComp)
		: m_MoveComp{ moveComp } {

	};
	virtual void Excecute() {
		m_MoveComp->SetNewDirection(Direction::NONE);
	}
private:
	Burger::MovementComponent* m_MoveComp;
};
class MoveUpExitCommand : public dae::Command {
public:
	MoveUpExitCommand(Burger::MovementComponent* moveComp)
		: m_MoveComp{ moveComp } {
	};
	virtual void Excecute() {
		m_MoveComp->SetNewDirection(Direction::NONE);
		//sprite

	}
private:
	Burger::MovementComponent* m_MoveComp;
};
class MoveDownExitCommand : public dae::Command {
public:
	MoveDownExitCommand(Burger::MovementComponent* moveComp)
		: m_MoveComp{ moveComp } {
	};
	virtual void Excecute() {
		m_MoveComp->SetNewDirection(Direction::NONE);
	}
private:
	Burger::MovementComponent* m_MoveComp;
};
class MoveLeftExitCommand : public dae::Command {
public:
	MoveLeftExitCommand(Burger::MovementComponent* moveComp)
		: m_MoveComp{ moveComp } {
	};
	virtual void Excecute() {
		m_MoveComp->SetNewDirection(Direction::NONE);
	}
private:
	Burger::MovementComponent* m_MoveComp;

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
