#include "MiniginPCH.h"
#include "Command.h"
#include "RigidbodyComponent.h"
#include "SpriteComponent.h"
#include "HealthComponent.h"
class MoveRightCommand : public Command {
public:
	MoveRightCommand(dae::RigidbodyComponent* componentToDamage, dae::SpriteComponent* spriteComp)
		: m_Component{ componentToDamage }, m_SpriteComp{ spriteComp } {};
	virtual void Excecute() {
		m_Component->SetVelocityX(500.f);
		m_SpriteComp->SetActiveAnimation("Move");
		m_SpriteComp->SetFlipState(true);
	}
private:
	dae::SpriteComponent* m_SpriteComp;
	dae::RigidbodyComponent* m_Component;
};
class MoveUpCommand : public Command {
public:
	MoveUpCommand(dae::RigidbodyComponent* componentToDamage, dae::SpriteComponent* spriteComp)
		: m_Component{ componentToDamage }, m_SpriteComp{ spriteComp }{};
	virtual void Excecute() {
		m_Component->SetVelocityY(-500.f);
		m_SpriteComp->SetActiveAnimation("MoveForward");

	}
private:
	dae::SpriteComponent* m_SpriteComp;
	dae::RigidbodyComponent* m_Component;
};
class MoveDownCommand : public Command {
public:
	MoveDownCommand(dae::RigidbodyComponent* componentToDamage, dae::SpriteComponent* spriteComp)
		: m_Component{ componentToDamage }, m_SpriteComp{ spriteComp }{};
	virtual void Excecute() {
		m_Component->SetVelocityY(500.f);
		m_SpriteComp->SetActiveAnimation("MoveBackwards");

	}
private:
	dae::RigidbodyComponent* m_Component;
	dae::SpriteComponent* m_SpriteComp;
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
	MoveLeftCommand(dae::RigidbodyComponent* componentToDamage, dae::SpriteComponent* spriteComp)
		: m_Component{ componentToDamage }, m_SpriteComp{ spriteComp } {};
	virtual void Excecute() {
		m_Component->SetVelocityX(-500.f);
		m_SpriteComp->SetActiveAnimation("Move");
		m_SpriteComp->SetFlipState(false);
	}
private:
	dae::SpriteComponent* m_SpriteComp;
	dae::RigidbodyComponent* m_Component;
};
