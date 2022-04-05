#pragma once
#include "SceneObject.h"
#include "Singleton.h"
#include <map>
#include "Command.h"
#include "BaseComponent.h"
namespace dae {
	enum class EventType
	{	//TODO Change to customizable system
		ENTITY_DIED, SCORE_INCREASE, WIN_GAME
	};
	class EventManager final : public Singleton<EventManager>
	{
	public:
		~EventManager() {}
		//when even is thrown call FP but with what
		void AddListener(Command* command, EventType type);
		void ThrowEvent(EventType event);
	private:
		void HandleEvent(EventType event);
		friend class Singleton<EventManager>;
		std::map<EventType, Command*> m_EventMap;
	};



	


}
