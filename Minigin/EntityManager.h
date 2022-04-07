#pragma once

#include "BaseComponent.h"
#include <unordered_set>
#include <typeinfo>

namespace dae 
{

	class EntityManager 
	{
	public:
		EntityManager() = default;
		~EntityManager();




		template<class TComponent>
		bool AddComponent(std::shared_ptr<BaseComponent>& component)
		{ //only support one type of each component in a gameobject no multiple for now
			//return false if map already contains component of that 
			auto insertPair = m_ComponentSet.insert(component);
			return insertPair.second;
		}

		template<class TComponent>
		bool RemoveComponent() 
		{
			//TODO Make use of buckets to not have to iterate over entire container
			//size_t bucket = m_ComponentMap.bucket(typeid(TComponent).hash_code())
			auto it = std::find_if(m_ComponentSet.begin(), m_ComponentSet.end(), [](std::shared_ptr<BaseComponent> element)
				{
					if (typeid(*element.get()).hash_code() == typeid(TComponent).hash_code())
						return true;
					else
						return false;
				});


			if (it != m_ComponentSet.end())
			{
				m_ComponentSet.erase(it);
				return true;
			}
			else
				return false;
		}

		template<class TComponent>
		std::shared_ptr<TComponent> GetComponent() const
		{
			//TODO Make use of buckets to not have to iterate over entire container
			//size_t bucket = m_ComponentMap.bucket(typeid(TComponent).hash_code());
			auto it = std::find_if(m_ComponentSet.begin(), m_ComponentSet.end(), [](std::shared_ptr<BaseComponent> element)
			{
					if (typeid(*element.get()).hash_code() == typeid(TComponent).hash_code())
						return true;
					else
						return false;
			});

			if (it != m_ComponentSet.end())
			{
				return std::static_pointer_cast<TComponent>(*it);
			}
			return nullptr;
		}

		void Start();
		void Update();
		void LateUpdate();
		void Render() const;

	private:
		struct BaseComponentHashCalculator {
		public:
			size_t operator()(const std::shared_ptr<BaseComponent>& str) const {
				auto& ti1 = typeid(str);
				return std::hash<size_t>()(ti1.hash_code());
			}
		};
		struct BaseConponentEqualityComparator {
			bool operator()(const std::shared_ptr<BaseComponent>& lhs, const std::shared_ptr<BaseComponent>& rhs) const
			{

				return typeid(*lhs.get()).hash_code() == typeid(*rhs.get()).hash_code();
			}
		};
		
	private:
		std::unordered_set<std::shared_ptr<BaseComponent>, BaseComponentHashCalculator, BaseConponentEqualityComparator> m_ComponentSet;
		int m_ComponentsRegistered = 0;
	};
}



