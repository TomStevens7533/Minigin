#include "MiniginPCH.h"
#include "Command.h"
#include "PetterPepperComponent.h"
#include "HealthComponent.h"
class MoveRightCommand : public Command {
public:
	MoveRightCommand(dae::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {};
	virtual void Excecute() {
		m_PeterComp->MoveRight();
	}
private:
	dae::PetterPepperComponent* m_PeterComp;
};
class MoveUpCommand : public Command {
public:
	MoveUpCommand(dae::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {};
	virtual void Excecute() {
		m_PeterComp->MoveUp();
	}
private:
	dae::PetterPepperComponent* m_PeterComp;
};
class MoveDownCommand : public Command {
public:
	MoveDownCommand(dae::PetterPepperComponent* peterComp)
	: m_PeterComp{ peterComp } {};
	virtual void Excecute() {
		m_PeterComp->MoveDown();
	}
private:
	dae::PetterPepperComponent* m_PeterComp;
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
class MoveLeftCommand : public Command {
public:
	MoveLeftCommand(dae::PetterPepperComponent* peterComp)
		: m_PeterComp{ peterComp } {};
	virtual void Excecute() {
		m_PeterComp->MoveLeft();
	}
private:
	dae::PetterPepperComponent* m_PeterComp;
};
