#include "MiniginPCH.h"
#include "EntityManager.h"

namespace dae {

	EntityManager::~EntityManager()
	{
		for (auto mapPair : m_ComponentSet)
		{
			mapPair.reset();
		}
	}


	void EntityManager::Update()
	{
		for (auto mapPair : m_ComponentSet)
		{
			mapPair->Update();
		}
	}

	void EntityManager::LateUpdate()
	{
		for (auto mapPair : m_ComponentSet)
		{
			mapPair->LateUpdate();
		}
	}

	void EntityManager::Render() const
	{
		for (auto mapPair : m_ComponentSet)
		{
			mapPair->Render();
		}
	}

}
