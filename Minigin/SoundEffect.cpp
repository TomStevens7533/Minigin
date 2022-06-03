#include "MiniginPCH.h"
#include "SoundEffect.h"
#include <iostream>

SoundEffect::SoundEffect(std::string path, float volume, int) : m_path{path}, m_Volume{volume}
{
	m_Channel = Mix_ReserveChannels(1);
}

SoundEffect::~SoundEffect()
{

	
}

void SoundEffect::Play()
{
	m_SoundEffect->volume = static_cast<uint8_t>(m_Volume);
	m_Channel = Mix_PlayChannel(m_Channel, m_SoundEffect, 0);
}



void SoundEffect::set_volume(float volume)
{
	m_Volume = volume;
}

bool SoundEffect::GetIsPlaying() const
{
	return Mix_Playing(m_Channel);
}

void SoundEffect::load()
{
	//"../Data/gustavo.wav", "rb"
	Mix_Chunk* currLoaded;
	currLoaded = Mix_LoadWAV(m_path.c_str());
	if (currLoaded == nullptr) {
		std::cerr << Mix_GetError() << std::endl;
	}
	m_SoundEffect = currLoaded;
}

void SoundEffect::ReleaseSound()
{
	Mix_FreeChunk(m_SoundEffect);
	m_SoundEffect = NULL;
}


