#pragma once
#include <deque>
#include <memory>
#include <iostream>
class Base_Sound_System
{
public:
	virtual ~Base_Sound_System() = default;
	virtual void play(const std::string& path , const float volume = 0.f) = 0;
	virtual void SetGlobalVolumeLevel(float volume) = 0;
	virtual  unsigned int load(const std::string path) = 0;
	virtual void StopAll() = 0;

};
class SDL_Sound_System  final :public Base_Sound_System
{
public:
	SDL_Sound_System();
	virtual ~SDL_Sound_System();
	virtual void play(const std::string& path, const float volume = 0.f) override;
	virtual void SetGlobalVolumeLevel(float volume) override;
	virtual void StopAll() override;

	virtual unsigned int load(const std::string path) override;
private:
	class SDL_SoundSystemImpl;
	std::unique_ptr<SDL_SoundSystemImpl> m_pPimpl;
};
class Null_Sound_System final : public Base_Sound_System
{
	virtual void play(const std::string&, const float) override{};
	virtual void SetGlobalVolumeLevel(float) override{};

	virtual unsigned int load(const std::string ) override {
	
		throw std::exception("No sound system loaded");
		return 0;
	};
	virtual void StopAll() override {
		throw std::exception("No sound system loaded");
	}
};
class LogginSoundSystem final : public Base_Sound_System {
public:
	LogginSoundSystem(SDL_Sound_System* ss) : m_RealSoundSystem(ss) {};
	~LogginSoundSystem() { delete m_RealSoundSystem; }
	virtual  unsigned int load(const std::string path) override {
		unsigned int idx =  m_RealSoundSystem->load(path);
		std::cout << "loading " << idx << " at path " << path << std::endl;
		return idx;
	}
	virtual void play(const std::string& path, const float volume) {
		m_RealSoundSystem->play(path, volume);
	}
	virtual void StopAll() override {
		m_RealSoundSystem->StopAll();
	}
	virtual void SetGlobalVolumeLevel(float volume) override 
	{
		m_RealSoundSystem->SetGlobalVolumeLevel(volume);
	};

private:
	SDL_Sound_System* m_RealSoundSystem;
};

