#include "MiniginPCH.h"
#include "SoundEffect.h"
#include <iostream>

SoundEffect::SoundEffect(std::string path, float volume) : m_path{path}, m_Volume{volume}
{

}

SoundEffect::~SoundEffect()
{

	if (!Mix_Playing(m_Channel)) {
		ReleaseSound();
	}
}

bool SoundEffect::Play()
{
	if (!Mix_Playing(m_Channel)) {
		m_SoundEffect->volume = static_cast<uint8_t>(m_Volume);
		m_Channel = Mix_PlayChannel(-1, m_SoundEffect, 0);
		return true;
	}
	return false;
}

bool SoundEffect::IsLoaded()
{
	return m_IsLoaded;
}

void SoundEffect::set_volume(float volume)
{
	m_Volume = volume;
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
	m_IsLoaded = true;
}

void SoundEffect::ReleaseSound()
{
	Mix_FreeChunk(m_SoundEffect);
	m_SoundEffect = NULL;
	m_IsReleased = true;
}


