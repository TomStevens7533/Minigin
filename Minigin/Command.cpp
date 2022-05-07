#include "MiniginPCH.h"
#include "Command.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
class MoveRightEnterCommand : public Command {
public:
	MoveRightEnterCommand(dae::MovementComponent* peterComp)
		: m_PeterComp{ peterComp } {};
	virtual void Excecute() {
		m_PeterComp->SetNewDirection(dae::Direction::RIGHT);
	}
private:
	dae::MovementComponent* m_PeterComp;
};
class MoveUpEnterCommand : public Command {
public:
	MoveUpEnterCommand(dae::MovementComponent* peterComp)
		: m_PeterComp{ peterComp } {};
	virtual void Excecute() {
		m_PeterComp->SetNewDirection(dae::Direction::UP);
	}
private:
	dae::MovementComponent* m_PeterComp;
};
class MoveDownEnterCommand : public Command {
public:
	MoveDownEnterCommand(dae::MovementComponent* peterComp)
	: m_PeterComp{ peterComp } {};
	virtual void Excecute() {
		
		m_PeterComp->SetNewDirection(dae::Direction::DOWN);
		
	}
private:
	dae::MovementComponent* m_PeterComp;
};
class MoveLeftEnterCommand : public Command {
public:
	MoveLeftEnterCommand(dae::MovementComponent* peterComp)
		: m_PeterComp{ peterComp } {};
	virtual void Excecute() {
		m_PeterComp->SetNewDirection(dae::Direction::LEFT);

	}
private:
	dae::MovementComponent* m_PeterComp;
};

//----------EXIT
class MoveExitCommand : public Command {
public:
	MoveExitCommand(dae::MovementComponent* peterComp)
		: m_PeterComp{ peterComp } {};
	virtual void Excecute() {
		m_PeterComp->SetNewDirection(dae::Direction::NONE);
	}
private:
	dae::MovementComponent* m_PeterComp;
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
