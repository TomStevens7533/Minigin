#include "MiniginPCH.h"
#include "BunBehaviour.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Scene.h"
#include "Time.h"
#include "ScoreDisplayComponent.h"
#include "ServiceLocator.h"


void dae::BunBehaviour::Render() const
{

}

void dae::BunBehaviour::Update()
{
	//Set burger falling
	if (m_IsFalling && m_IsInFinalPos == false) {
		glm::vec3 newPos = m_pParent->GetTransform().GetPosition();
		newPos.y += m_Velocity * Time::GetInstance().GetDeltaTime();
		m_pParent->GetTransform().SetPosition(newPos.x, newPos.y, newPos.z);
	}


}

void dae::BunBehaviour::LateUpdate()
{
	if (!m_IsFalling) {
		//Check if player is colliding
		auto peterCollision = m_pParent->GetScene()->IsRectColliding(m_pBoxColliderComponent->GetColliderInfo()->m_ColliderRect, "Pepper");
		if (peterCollision) {

			if (m_IsPeterInCollFirst == false) {
				m_BunEnterPosX = peterCollision->m_ColliderRect.x;
				m_IsPeterInCollFirst = true;
				std::cout << "entered bun\n";
			}
			//Play burger pass sound effect
			//ServiceLocator::GetSoundSystem().play(m_BurgerPassSoundIdx, 10.f);
			m_pExitPeterCollision = peterCollision;
		}
		else if(m_IsPeterInCollFirst == true) {
			//Check if peter pepper has walked the bun

			std::cout << "exit bun\n";
			float currentBunXPos = m_pBoxColliderComponent->GetColliderInfo()->m_ColliderRect.x;
			float currentBunWith = m_pBoxColliderComponent->GetColliderInfo()->m_ColliderRect.width;

			if (m_BunEnterPosX < (currentBunXPos + (currentBunWith / 2.f))) {
				//entered left side check
				if (m_pExitPeterCollision->m_ColliderRect.x > (currentBunXPos + (currentBunWith / 2.f)))
				{
					//Pepper has wallked the entirty of the bun
					m_IsFalling = true;
					m_IsPeterInCollFirst = false;
					std::cout << "start fall\n";
					m_pPepperGameobject = m_pExitPeterCollision->m_pAttachedGameObject;

				}
			}
			else
			{//entered right side check
				if (m_pExitPeterCollision->m_ColliderRect.x < (currentBunXPos + (currentBunWith / 2.f)))
				{
					//Pepper has wallked the entirty of the bun
					m_IsFalling = true;
					std::cout << "start fall\n";
					m_pPepperGameobject = m_pExitPeterCollision->m_pAttachedGameObject;

				}
			}
			m_pExitPeterCollision = nullptr;
			m_IsPeterInCollFirst = false;
		}
	

	}
	else {
		//stop falling if hitting ground
		glm::vec2 pos = m_pParent->GetTransform().GetPosition();

		//Check if other bun is in the way if true move other bun
		std::shared_ptr<ColliderInfo> info = (m_pParent->GetScene()
			->SceneRaycast(pos, glm::vec2{ 0, 1 }, 11.f, "Bun",10, m_pBoxColliderComponent->GetColliderInfo()));

		if (info && m_IsFalling) {
			//Has hit other burgerpiece
			auto pBun = info->m_pAttachedGameObject->GetComponent<BunBehaviour>();
			if (pBun != nullptr) {
				//Collided buger piece falling
				pBun->SetFalling();

				//If falled on bun is in on top stop other bun piece
				m_IsInFinalPos = pBun->GetFinalPos();
			}
		}

		pos.x += m_pBoxColliderComponent->GetDimension().x / 2.f;
		pos.y += m_pBoxColliderComponent->GetDimension().y / 2.f;

		std::shared_ptr<ColliderInfo> infoGroud = (m_pParent->GetScene()->IsPointInCollider(pos, "Floor"));
		//stop if hitting floor
		if (infoGroud) {
			if (m_pInfoGround == nullptr) {
				m_pInfoGround = infoGroud->m_pAttachedGameObject;
				return;
			}
			//if hitting different collider
			else if (m_pInfoGround != infoGroud->m_pAttachedGameObject) {
				std::cout << "stop fall floor\n";
				//Throw ScoreEvent
				//Check enemies
				ScoreArgs args;
				args.scoreIncrease = m_IncreaseScore;
				notify(this, PepperEvent::SCORE_INCREASE, &args);

				m_IsFalling = false;
				m_pInfoGround = nullptr;
			}
		}
		infoGroud = (m_pParent->GetScene()->IsRectColliding(m_pBoxColliderComponent->GetColliderInfo()->m_ColliderRect, "BunEnd"));
		if (infoGroud) {
			//if hitting end of screen turn off all velocity
			m_IsInFinalPos = true;
		}
	}
}

void dae::BunBehaviour::Start()
{
	m_pBoxColliderComponent = m_pParent->GetComponent<BoxColliderComponent>();
	assert(m_pBoxColliderComponent);

	//Sounds
	m_BurgerPassSoundIdx = ServiceLocator::GetSoundSystem().load("../Data/BurgerTime/BurgerPass.mp3");

}

void dae::BunBehaviour::SetFalling()
{
	if (m_IsFalling == false && m_pInfoGround == nullptr) {
		m_IsFalling = true;
		std::cout << "start fall trigger\n";
	}
		

}

