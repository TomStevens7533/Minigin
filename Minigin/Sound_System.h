#pragma once
#include <deque>
#include <memory>
#include <iostream>
class Base_Sound_System
{
public:
	virtual ~Base_Sound_System() = default;
	virtual void play(const unsigned int id, const float volume) = 0;
	virtual void load(const unsigned int id, const std::string path) = 0;
};
class SDL_Sound_System  final :public Base_Sound_System
{
public:
	SDL_Sound_System();
	virtual ~SDL_Sound_System();
	virtual void play(const unsigned int id, const float volume) override;
	virtual void load(const unsigned int id, const std::string path) override;
private:
	class SDL_SoundSystemImpl;
	std::unique_ptr<SDL_SoundSystemImpl> m_pPimpl;
};
class Null_Sound_System final : public Base_Sound_System
{
	virtual void play(const unsigned int , const float) override{};
	virtual void load(const unsigned int , const std::string ) override {};
};
class LogginSoundSystem final : public Base_Sound_System {
public:
	LogginSoundSystem(SDL_Sound_System* ss) : m_RealSoundSystem(ss) {};
	~LogginSoundSystem() { delete m_RealSoundSystem; }
	virtual void load(const unsigned int id, const std::string path) override {
		m_RealSoundSystem->load(id, path);
		std::cout << "loading " << id << " at path " << path << std::endl;
	}
	virtual void play(const unsigned int id, const float volume) {
		m_RealSoundSystem->play(id, volume);
	}
private:
	SDL_Sound_System* m_RealSoundSystem;
};

