
#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <fstream>
#include <vector>
#include "document.h"
#include "Parser.h"

using namespace Burger;
using namespace rapidjson;

class Parser::ParserImpl
{
public:
	ParserImpl(std::string path);
	std::map<std::string, std::vector<point>>& GetObjectMapImpl()  { return m_ObjectMap; };
	std::map<std::string, EnemySpawnInfo>& GetEnemyInfoMap() { return m_EnemyInfoMap; };

private:
	void ParseLevelFileImpl(std::string path);
private:
	std::map<std::string, std::vector<point>> m_ObjectMap;
	std::map<std::string, EnemySpawnInfo> m_EnemyInfoMap;

};

Parser::ParserImpl::ParserImpl(std::string path)
{
	ParseLevelFileImpl(path);
}
void Parser::ParserImpl::ParseLevelFileImpl(std::string path)
{
	std::ifstream file{ path };
	if (!file.is_open())
		throw ParserException("Unable to open file " + path);

	// read the file contents
	std::stringstream contents;
	contents << file.rdbuf();

	Document document;
	document.Parse(contents.str().c_str());

	assert(document.IsArray());
	auto jsonArray = document.GetArray();
	
	


	std::cout << "object amount in array: " << jsonArray.Size() << std::endl;
	for (SizeType i = 0; i < jsonArray.Size(); i++)
	{
		GenericObject ElementObj = jsonArray[i].GetObj();

		for (auto memIt = ElementObj.MemberBegin(); memIt != ElementObj.MemberEnd(); memIt++)
		{
			if (memIt->name == "Positions") {
				GenericArray posArray = memIt->value.GetArray();
				for (SizeType x = 0; x < posArray.Size(); x++)
				{
					std::string objName;
					std::vector<point> posVec;
					GenericObject obj = posArray[x].GetObj();

					for (auto memIt = obj.MemberBegin(); memIt != obj.MemberEnd(); memIt++)
					{

						if (memIt->value.IsArray() == true) {
							//Read in pos
							GenericArray posArray = memIt->value.GetArray();
							posVec.reserve(posArray.Size());


							for (SizeType x = 0; x < posArray.Size(); x++)
							{
								if (posArray[x].Size() != 2)
									throw ParserException("Not correct format for needed positions: size of pos array needs to be 2");

								point newPos;
								newPos.x = posArray[x][0].GetFloat();
								newPos.y = posArray[x][1].GetFloat();
								posVec.push_back(newPos);
							}
						}
						else if (memIt->value.IsString() == true) {
							objName = memIt->value.GetString();
						}
						else {
							throw ParserException("Unsupported type No array found");
						}
					}
					m_ObjectMap.insert(std::make_pair(objName, posVec));
				}

				
			}
			else if (memIt->name == "Enemies") {
				if (memIt->value.IsArray() == true) {
					GenericArray enemyArr = memIt->value.GetArray();
					for (SizeType i = 0; i < enemyArr.Size(); i++)
					{
						EnemySpawnInfo inf;
						std::string name;
						GenericObject obj = enemyArr[i].GetObj();

						for (auto memIt = obj.MemberBegin(); memIt != obj.MemberEnd(); memIt++)
						{
							if (memIt->name == "idx") {
								inf.id = memIt->value.GetInt();
							}
							else if (memIt->name == "maxLevel") {
								inf.MaxInStage = memIt->value.GetInt();
							}
							else if (memIt->name == "name") {
								name = memIt->value.GetString();
							}
						}
						m_EnemyInfoMap.insert(std::make_pair(name, inf));
					}

				}
				else {
					throw ParserException("Unsupported type No array found");
				}
			}
			
		}
	}
}

Parser::Parser(std::string path) : m_pPimpl { new ParserImpl(path)}
{

}

std::map<std::string, std::vector<point>>& Parser::GeLevelObject()
{
	return m_pPimpl->GetObjectMapImpl();
}

Parser::~Parser()
{
	delete m_pPimpl;
}

std::map<std::string, EnemySpawnInfo>& Parser::GetEnemyInfo()
{
	return m_pPimpl->GetEnemyInfoMap();
}

