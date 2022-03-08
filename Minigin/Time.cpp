#include "MiniginPCH.h"
#include "Time.h"

namespace dae {
	Time::Time()
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}
	float Time::GetDeltaTime()
	{
		return m_DeltaTime;
	}
	void Time::Update()
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		m_DeltaTime = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - m_StartTime).count();
		m_StartTime = currentTime;
	}
}