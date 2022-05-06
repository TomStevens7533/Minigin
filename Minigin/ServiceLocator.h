#pragma once
#include "Sound_System.h"
class Base_Sound_System;
class ServiceLocator final
{
public:
	static void Delete();
	static void RegisterSoundSystem(Base_Sound_System* ss);
	static Base_Sound_System& GetSoundSystem();
private:
	static Base_Sound_System* m_SoundInstance;
	static Null_Sound_System m_DefaultSoundSystem;

};



