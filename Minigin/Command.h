#pragma once
class Command
{
public:
	virtual ~Command() {};
	virtual void Excecute() = 0;
};