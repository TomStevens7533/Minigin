#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "glm/glm.hpp"


namespace dae {
	GameObject::~GameObject() = default;

	void GameObject::SetParent(GameObject* parent)
	{
		m_Parent = parent;

		//Reshuffle root pos for all children
		ChangeRootPos((parent->GetPosFromRoot() + static_cast<int>(parent->GetChildCount()) ));

	}

	void GameObject::ChangeRootPos(int newRootPos)
	{
		m_PositionFromRoot = newRootPos;

		for (auto& child : m_Children)
		{
			newRootPos++;
			assert(child->GetPosFromRoot() > this->GetPosFromRoot()); //assert if circular included 
			child->ChangeRootPos(newRootPos);
			RemoveChild(child->GetPosFromRoot());
			
		}
	}


	int GameObject::GetPosFromRoot()
	{
		return m_PositionFromRoot;
	}

	GameObject* GameObject::GetParent() const
	{
		return m_Parent;
	}

	size_t GameObject::GetChildCount() const
	{
		return m_Children.size();
	}

	std::shared_ptr<GameObject> GameObject::GetChildAt(INT Index) const
	{
		if (Index <= static_cast<int>(m_Children.size()))
			return m_Children[Index];
		else {
			return nullptr;
		}

	}

	void GameObject::RemoveChild(int index)
	{
		std::cout << "Child gameobject removed at index: " << index << std::endl;
 		m_Children.erase(std::next(m_Children.begin(), glm::clamp(index, 0, static_cast<int>(m_Children.size() - 1))));
	}

	void GameObject::AddChild(std::shared_ptr<GameObject>& go)
	{
		m_Children.push_back(go);
		go->SetParent(this);
	}

	void GameObject::Update()
	{

		for (auto& child : m_Children)
		{
			child->Update();
		}

		m_EntityManager.Update();
				  
		auto fpsComponent =  m_EntityManager.GetComponent<FPSComponent>();
		auto textComponent = m_EntityManager.GetComponent<TextComponent>();

		if (fpsComponent != nullptr && textComponent != nullptr) {
			textComponent->SetText(std::to_string(fpsComponent->GetFpsCount()));
		}

	

	}

	void GameObject::LateUpdate()
	{
		m_EntityManager.LateUpdate();

		for (auto& child : m_Children)
		{
			child->LateUpdate();
		}
	}

	void GameObject::Render() const
	{
		m_EntityManager.Render();

		for (auto& child : m_Children)
		{
			child->Render();
		}

	}
	void GameObject::SetPosition(float x, float y)
	{
		m_Transform.SetPosition(x, y, 0.0f);
	}

}
