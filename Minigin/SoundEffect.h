#pragma once
#include <string>
#include "SDL_mixer.h"

class SoundEffect final {
public:
	SoundEffect(std::string path, float volume, int channel = -1);
	~SoundEffect() = default;
	void Play();
	void set_volume(float volume);
	bool GetIsPlaying() const;
	inline int GetChannel() { return m_Channel; }
	void load();
	void ReleaseSound();

	SoundEffect(const SoundEffect& other) = default;
	SoundEffect(SoundEffect&& other) = default;
	SoundEffect& operator=(const SoundEffect& other) = delete;
	SoundEffect& operator=(SoundEffect&& other) = default;
private:
	std::string m_path{};
	float m_Volume{};
	Mix_Chunk* m_SoundEffect{};
	int m_Channel = 0;
};