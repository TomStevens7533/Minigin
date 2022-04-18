#include "MiniginPCH.h"
#include "JsonParser.h"
#include "document.h"
#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "PetterPepperComponent.h"
using namespace dae;
using namespace rapidjson;

JsonParser::JsonParser(std::string jsonPath) 
{
	ParseLevelFile(jsonPath);
}

void dae::JsonParser::ParseLevelFile(std::string jsonPath)
{
	std::ifstream file{ jsonPath };
	if (!file.is_open())
		throw JsonParserException("Unable to open file " + jsonPath);

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
		std::string objName;
		std::vector<glm::vec2> posVec;
		for (auto memIt = ElementObj.MemberBegin(); memIt != ElementObj.MemberEnd(); memIt++)
		{
			if (memIt->value.IsArray() == true) {
				//Read in pos
				GenericArray posArray = memIt->value.GetArray();
				posVec.reserve(posArray.Size());
				for (SizeType x = 0; x < posArray.Size(); x++)
				{
					if (posArray[x].Size() != 2)
						throw JsonParserException("Not correct format for needed positions: size of pos array needs to be 2");
					glm::vec2 newPos;
					newPos.x = posArray[x][0].GetFloat();
					newPos.y = posArray[x][1].GetFloat();
					posVec.push_back(newPos);
				}
			}
			else if (memIt->value.IsString() == true) {
				objName = memIt->value.GetString();
			}
			else {
				throw JsonParserException("Unsupported type");
			}
		}
		m_ObjectMap.insert(std::make_pair(objName, posVec));
	}
}

