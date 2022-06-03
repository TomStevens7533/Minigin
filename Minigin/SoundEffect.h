#pragma once
#include <string>
#include "SDL_mixer.h"

class SoundEffect {
public:
	SoundEffect(std::string path, float volume, int channel = -1);
	~SoundEffect();
	void Play();
	void set_volume(float volume);
	bool GetIsPlaying() const;
	inline int GetChannel() { return m_Channel; }
	void load();
	void ReleaseSound();
private:
	std::string m_path{};
	float m_Volume{};
	Mix_Chunk* m_SoundEffect{};
	int m_Channel = 0;

};