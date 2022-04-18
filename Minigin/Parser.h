#pragma once
#include <iostream>
#include <map>
#include <memory>
namespace dae {
	class ParserException : public std::runtime_error
	{
	public:
		~ParserException() {}
		ParserException(const std::string msg)
			: std::runtime_error(msg)
		{}
	};

	class Parser
	{
	public:
		Parser(std::string path);
		~Parser() { delete m_pPimpl; }
		std::map<std::string, std::vector<glm::vec2>>& GeLevelObject();
	public:
		Parser(const Parser& other) = delete;
		Parser(Parser&& other) = delete;
		Parser& operator=(const Parser& other) = delete;
		Parser& operator=(Parser&& other) = delete;
	private:
		class ParserImpl;
		ParserImpl* m_pPimpl;
	};

}
