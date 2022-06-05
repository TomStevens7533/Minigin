#pragma warning(disable:4201)

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <fstream>
#include <vector>
#include "document.h"
#include "LevelCreator.h"
#include <vcruntime_typeinfo.h>
#include "Scene.h"
#include "PrefabCreator.h"
#include "BurgerTimeManager.h"


using namespace rapidjson;
void Burger::LevelCreator::CreateLevel(std::string path, dae::Scene* currSceneToLoad)
{
	std::ifstream file{ path };

	if (!file.is_open())
		throw ParserException("Unable to open file " + path);

	std::stringstream contents;
	contents << file.rdbuf();

	//Read in json file
	Document document;
	document.Parse(contents.str().c_str());

	assert(document.IsArray());
	auto jsonArray = document.GetArray();


	for (SizeType i = 0; i < jsonArray.Size(); i++)
	{
		
		GenericObject ElementObj = jsonArray[i].GetObj();

		for (auto memIt = ElementObj.MemberBegin(); memIt != ElementObj.MemberEnd(); memIt++)
		{
			if (memIt->name == "LevelInfo") {
				LevelInfo currLevelInfo{};
				GenericObject obj = memIt->value.GetObj();
				for (auto levelIt = obj.MemberBegin(); levelIt != obj.MemberEnd(); levelIt++)
				{
					if (levelIt->name == "MaxLives") {
						currLevelInfo.MaxLives = levelIt->value.GetInt();
					}
					else if (levelIt->name == "MaxPepper") {
						currLevelInfo.MaxPepper = levelIt->value.GetInt();
					}
					else if (levelIt->name == "BunsToWin") {
						currLevelInfo.BunWinCoun = levelIt->value.GetInt();
					}
				}
				GameManager::GetInstance().SetNewLevelInfo(currLevelInfo);

			}

			else if (memIt->name == "Positions") {
				GenericArray posArray = memIt->value.GetArray();
				for (SizeType x = 0; x < posArray.Size(); x++)
				{
					std::string objName;
					std::vector<point> posVec;
					GenericObject posObj = posArray[x].GetObj();

					for (auto localMemIt = posObj.MemberBegin(); localMemIt != posObj.MemberEnd(); localMemIt++)
					{
						

						if (localMemIt->name == "Positions") {
							//Read in pos
							GenericArray enemyPosArray = localMemIt->value.GetArray();
							posVec.reserve(enemyPosArray.Size());


							for (SizeType posIdx = 0; posIdx < enemyPosArray.Size(); posIdx++)
							{
								if (enemyPosArray[posIdx].Size() != 2)
									throw ParserException("Not correct format for needed positions: size of pos array needs to be 2");

								point newPos;
								newPos.x = enemyPosArray[posIdx][0].GetFloat();
								newPos.y = enemyPosArray[posIdx][1].GetFloat();
								posVec.push_back(newPos);
							}
						}
						else if (localMemIt->value.IsString() == true) {
							objName = localMemIt->value.GetString();
						}
						else if (localMemIt->name == "EnemyInfo") {
							EnemySpawnInfo inf;
							EnemyType type;
							std::map<EnemyType, EnemySpawnInfo> enemyInfo;

							if (objName != "EnemySpawnPoints" && posVec.size() <= 0) {
								throw ParserException("EnemyInfo not in right position positions need to be loaded first!");
							}

							//Read in Enemy spawn information
							if (localMemIt->value.IsArray() == true) {
								GenericArray enemyArr = localMemIt->value.GetArray();
								for (SizeType enemyIdx = 0; enemyIdx < enemyArr.Size(); enemyIdx++)
								{
									GenericObject obj = enemyArr[enemyIdx].GetObj();

									for (auto memEnemyIt = obj.MemberBegin(); memEnemyIt != obj.MemberEnd(); memEnemyIt++)
									{
										if (memEnemyIt->name == "idx") {
											int id = memEnemyIt->value.GetInt();


											//Get Enemy Type
											if (id >= static_cast<int>(EnemyType::Begin) && id <= static_cast<int>(EnemyType::END)) {
												type = static_cast<EnemyType>(id);
											}
											else
												throw std::bad_cast();

										}
										else if (memEnemyIt->name == "maxLevel") {
											inf.MaxInStage = memEnemyIt->value.GetInt();
										}
										else if (memEnemyIt->name == "KillScore") {
											inf.Score = memEnemyIt->value.GetInt();
										}
										else {
											std::string exeptionStr = std::string("Unknown in enemyinfo!! Name of faulty obj: ") + memIt->name.GetString();
											throw ParserException(exeptionStr);
										}

									}
								
									enemyInfo.insert(std::make_pair(type, inf));
								}
							}
							else {
								throw ParserException("Unsupported type No array found in EnemyInfo");
							}
							//Create spawner;
							auto spawner = PrefabCreator::CreateEnemySpawner(posVec, enemyInfo);
							currSceneToLoad->Add(spawner);
						}
						else {
							throw ParserException("Unsupported type");
						}
					}
					LevelCreator::AddPrefabToScene(objName, posVec, currSceneToLoad);
				}


			}

		}

	}

}
void Burger::LevelCreator::AddPrefabToScene(const std::string& name, const std::vector<point>& posVec, dae::Scene* currScene)
{

	if (name == "ScoreUI") {

		for (point elementPos : posVec)
		{
			auto scoreUI = PrefabCreator::CreateScoreUI(elementPos);
			currScene->Add(scoreUI);
		}
	}
	else if (name == "LiveUI") {

		for (point elementPos : posVec)
		{
			auto liveUi = PrefabCreator::CreateLivesUI(elementPos);
			currScene->Add(liveUi);

		}
	}
	else if (name == "PepperUI") {

		for (point elementPos : posVec)
		{
			auto pepperUI = PrefabCreator::CreatePepperUI(elementPos);
			currScene->Add(pepperUI);


		}
	}
	
	else if (name == "PlatformSoloPrefab") {

		for (point elementPos : posVec)
		{
			auto pepper = PrefabCreator::CreatePlatformPrefab(elementPos, 2);
			currScene->Add(pepper);
		}
	}
	else if (name == "PlatformLongPrefab") {
		for (point elementPos : posVec)
		{
			auto pepper = PrefabCreator::CreatePlatformPrefab(elementPos, 10);
			currScene->Add(pepper);
		}
	}
	else if (name == "LadderLongPrefab") {

		for (point elementPos : posVec)
		{
			auto pepper = PrefabCreator::CreateLadderPrefab(elementPos, 12);
			currScene->Add(pepper);
		}
	}
	else if (name == "LadderShortPrefab") {
		for (point elementPos : posVec)
		{
			auto pepper = PrefabCreator::CreateLadderPrefab(elementPos, 10);
			currScene->Add(pepper);
		}
	}
	else if (name == "TopBun") {
		for (point elementPos : posVec)
		{
			auto topBurger = PrefabCreator::CreatTopBurgerPrefab(elementPos);
			currScene->Add(topBurger);
		}
	}
	else if (name == "Lettuce") {
		for (point elementPos : posVec)
		{
			auto letuce = PrefabCreator::CreatLettuceBurgerPrefab(elementPos);
			currScene->Add(letuce);
		}
	}
	else if (name == "Tomato") {
		for (point elementPos : posVec)
		{
			auto tomato = PrefabCreator::CreatTomatoBurgerPrefab(elementPos);
			currScene->Add(tomato);
		}
	}
	else if (name == "LowerBun") {
		for (point elementPos : posVec)
		{
			auto lowerbun = PrefabCreator::CreatLowerBurgerPrefab(elementPos);
			currScene->Add(lowerbun);
		}
	}
	else if (name == "BurgerCatcher") {
		for (point elementPos : posVec)
		{
			auto burerCatch = PrefabCreator::CreatBurgerCathcherPrefab(elementPos);
			currScene->Add(burerCatch);
		}
	}
	else if (name == "PeterPepperPrefab") {

		Gamemode curMode = GameManager::GetInstance().GetCurrentGamemode();
		switch (curMode)
		{
		case Gamemode::COOP:
			for (size_t i = 0; i < posVec.size(); i++)
			{
				auto pepper = PrefabCreator::CreatePlayerPrefab(posVec[i], static_cast<int>(i));
				//Set Score UI
				currScene->Add(pepper);
			}
			break;
		case Gamemode::PVP:
			if (posVec.size() >= 2) {
				auto pepper = PrefabCreator::CreatePlayerPrefab(posVec[0], 0);
				currScene->Add(pepper);
				pepper = PrefabCreator::CreatePlayableWorstPrefab(posVec[1], 500, 1);
				currScene->Add(pepper);
			}
			break;
		case Gamemode::SOLO:
			if (posVec.size() > 0) {
				auto pepper = PrefabCreator::CreatePlayerPrefab(posVec[0], 0);
				//Set Score UI
				currScene->Add(pepper);
			}

			break;
		default:
			break;
		}

	}

}


