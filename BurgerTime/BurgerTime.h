#pragma once

namespace Burger {
	class BurgerTime {
	public:
		void Initialize();
		void CreateLevel1();
	private:
		void LoadLevel(const std::string& path);
	};
}
