#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae {
	class Time final : public Singleton<Time>
	{
	public:
		Time();
		~Time() = default;

		float GetDeltaTime();
		void Update();
	private:
		friend class Singleton<Time>;
		std::chrono::steady_clock::time_point  m_StartTime;
		float m_DeltaTime = 0.f;
	};
}
