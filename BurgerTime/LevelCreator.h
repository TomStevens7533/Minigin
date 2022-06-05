#pragma once
#include <iostream>
#include <map>
#include <memory>
#include "BurgerStructs.h"

namespace dae { class Scene; }

namespace Burger {
	class ParserException : public std::runtime_error
	{
	public:
		~ParserException() {}
		ParserException(const std::string msg)
			: std::runtime_error(msg)
		{}
	};

	class LevelCreator final
	{
	public:
		static void CreateLevel(std::string path, dae::Scene* sceneToLoad);
		LevelCreator(const LevelCreator& other) = delete;
		LevelCreator(LevelCreator&& other) = delete;
		LevelCreator& operator=(const LevelCreator& other) = delete;
		LevelCreator& operator=(LevelCreator&& other) = delete;
	private:
		static void AddPrefabToScene(const std::string& name, const std::vector<point>& posVec, dae::Scene* currScene);
	};

}
