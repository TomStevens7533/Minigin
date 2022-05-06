#pragma once
#include <string>
#include "SDL_mixer.h"

class SoundEffect {
public:
	SoundEffect(std::string path, float volume);
	~SoundEffect();
	bool Play();
	bool IsLoaded();
	void set_volume(float volume);
	void load();
	void ReleaseSound();
private:
	std::string m_path{};
	bool m_IsLoaded = false;
	bool m_IsReleased = false;
	float m_Volume{};
	Mix_Chunk* m_SoundEffect{};
	int m_Channel = 0;

};