#include "MiniginPCH.h"
#include "BunBehaviour.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Scene.h"
#include "Time.h"

void dae::BunBehaviour::Render() const
{

}

void dae::BunBehaviour::Update()
{
	if (m_IsFalling) {
		//stop falling if hitting ground
		glm::vec2 pos = m_pParent->GetTransform().GetPosition();
		pos += m_pBoxColliderComponent->GetDimension();

		//Check if other bun is in the way if true move other bun
		std::shared_ptr<ColliderInfo> info = (m_pParent->GetScene()
			->SceneRaycast(pos, glm::vec2{0, -1}, 5.f, m_pBoxColliderComponent->GetColliderInfo()));

		if (info && m_IsFalling) {
			//Has hit other burgerpiece
			auto pBun = info->m_pAttachedGameObject->GetComponent<BunBehaviour>();
			if (pBun != nullptr ) {
				//Collided buger piece falling
				pBun->SetFalling();

			}
		}

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
				m_IsFalling = false;
				m_pInfoGround = nullptr;
			}


		}
		glm::vec3 newPos = m_pParent->GetTransform().GetPosition();
		newPos.y += m_Velocity * Time::GetInstance().GetDeltaTime();
		m_pParent->GetTransform().SetPosition(newPos.x, newPos.y, newPos.z);
	}

}

void dae::BunBehaviour::LateUpdate()
{
	if (!m_IsFalling) {
		//Check if player is colliding
		if (m_pParent->GetScene()->IsRectColliding(m_pBoxColliderComponent->GetColliderInfo()->m_ColliderRect, "Pepper")) {
			m_IsFalling = true;
			std::cout << "start fall\n";
		}
	}
	else
	{
	
	}
}

void dae::BunBehaviour::Start()
{
	m_pBoxColliderComponent = m_pParent->GetComponent<BoxColliderComponent>();
	assert(m_pBoxColliderComponent);

}

void dae::BunBehaviour::SetFalling()
{
	if (m_IsFalling == false && m_pInfoGround == nullptr) {
		m_IsFalling = true;
		std::cout << "start fall trigger\n";
	}
		

}

