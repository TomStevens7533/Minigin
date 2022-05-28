#pragma once
#pragma once
namespace dae {
	class Command
	{
	public:
		virtual ~Command() {};
		virtual void Excecute() = 0;
	};
}

