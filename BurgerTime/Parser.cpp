
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
private:
	void ParseLevelFileImpl(std::string path);
private:
	std::map<std::string, std::vector<point>> m_ObjectMap;
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
		std::string objName;
		std::vector<point> posVec;
		for (auto memIt = ElementObj.MemberBegin(); memIt != ElementObj.MemberEnd(); memIt++)
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
				throw ParserException("Unsupported type");
			}
		}
		m_ObjectMap.insert(std::make_pair(objName, posVec));
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

