#pragma once
#include <iostream>
#include <map>
#include <memory>
#include "BurgerStructs.h"

namespace Burger {
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
		~Parser();
		std::map<std::string, std::vector<point>>& GeLevelObject();
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
