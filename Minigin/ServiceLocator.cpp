#include "MiniginPCH.h"
#include "ServiceLocator.h"
Null_Sound_System ServiceLocator::m_DefaultSoundSystem;
Base_Sound_System* ServiceLocator::m_SoundInstance = &m_DefaultSoundSystem;

void ServiceLocator::Delete()
{

	delete m_SoundInstance;
}



void ServiceLocator::RegisterSoundSystem(Base_Sound_System* ss)
{
	m_SoundInstance = (ss == nullptr) ? &m_DefaultSoundSystem : ss;
}

Base_Sound_System& ServiceLocator::GetSoundSystem()
{
	return *m_SoundInstance; 
}


