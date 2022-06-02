#pragma once
#include <deque>
#include <memory>
#include <iostream>
class Base_Sound_System
{
public:
	virtual ~Base_Sound_System() = default;
	virtual void play(const unsigned int id, const float volume) = 0;
	virtual  unsigned int load(const std::string path) = 0;
	virtual void stop() = 0;

};
class SDL_Sound_System  final :public Base_Sound_System
{
public:
	SDL_Sound_System();
	virtual ~SDL_Sound_System();
	virtual void play(const unsigned int id, const float volume) override;
	virtual void stop() override;

	virtual unsigned int load(const std::string path) override;
private:
	class SDL_SoundSystemImpl;
	std::unique_ptr<SDL_SoundSystemImpl> m_pPimpl;
};
class Null_Sound_System final : public Base_Sound_System
{
	virtual void play(const unsigned int , const float) override{};
	virtual unsigned int load(const std::string ) override {
	
		throw std::exception("No sound system loaded");
		return 0;
	};
	virtual void stop() override {
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
	virtual void play(const unsigned int id, const float volume) {
		m_RealSoundSystem->play(id, volume);
	}
	virtual void stop() override {
		m_RealSoundSystem->stop();
	}
private:
	SDL_Sound_System* m_RealSoundSystem;
};

