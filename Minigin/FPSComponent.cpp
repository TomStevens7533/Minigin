#include "MiniginPCH.h"

#include "FPSComponent.h"
#include "Time.h"


namespace dae {


	FPSComponent::FPSComponent() : m_fpscount{0}, m_fps{0}
	{


	}

	void FPSComponent::Render() const
	{

	}

	void FPSComponent::Update()
	{
		m_fpscount++;
		m_TimePassed +=  Time::GetInstance().GetDeltaTime();
		
		if (m_TimePassed > 0.25 && m_fpscount > 10) {
			//1 sec has passed
			m_fps = static_cast<int>(static_cast<float>(m_fpscount) / m_TimePassed);

			//reset counter
			m_fpscount = 0;
			m_TimePassed = 0.f;
		}

	}

	void FPSComponent::LateUpdate()
	{

	}


}