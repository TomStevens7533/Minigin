#pragma once
#include <iostream>
#include <map>
namespace dae {
	class JsonParserException : public std::runtime_error
	{
	public:
		~JsonParserException() {}
		JsonParserException(const std::string msg)
			: std::runtime_error(msg)
		{}
	};
	class JsonParser
	{
	public:
		JsonParser(std::string jsonPath);
		const std::map<std::string, std::vector<glm::vec2>>& GetObjectMap() { return m_ObjectMap; };
	public:
		JsonParser(const JsonParser& other) = delete;
		JsonParser(JsonParser&& other) = delete;
		JsonParser& operator=(const JsonParser& other) = delete;
		JsonParser& operator=(JsonParser&& other) = delete;
	private:
		void ParseLevelFile(std::string jsonPath);
	private:
		std::map<std::string, std::vector<glm::vec2>> m_ObjectMap;
	};

}
