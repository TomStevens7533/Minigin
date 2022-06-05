#include "MiniginPCH.h"
#include "Sound_System.h"
#include <SDL_mixer.h>
#include <thread>
#include <mutex>
#include "SoundEffect.h"
#include <map>
#include <memory>

class SDL_Sound_System::SDL_SoundSystemImpl {
public:
	SDL_SoundSystemImpl();
	~SDL_SoundSystemImpl();
	//void loadImpl(std::string path);
	unsigned int RegisterSoundImpl(const std::string& path);
	void AddToQueue(const std::string& path, float volume = 0.f);
	void StopAllImpl();
	void SetGlobalVolumeLevel(float volume);
private:
	void PlaySoundQueue();
	void RemoveSoundCheck();

private:
	std::jthread m_PlayThread;
	std::jthread m_StopThread;

	std::condition_variable m_Variable;
	std::deque<SoundEffect> m_SoundQueue;
	std::vector<SoundEffect> m_DeleteionCheckVec; //random acces it

	std::mutex m_Mutex;
	std::condition_variable m_Cv;
	int m_Channels = 8;
	float m_GlobalVolume{};
	std::atomic<bool> m_IsRunning;
	std::vector<std::string> m_PathMap;
};
SDL_Sound_System::SDL_SoundSystemImpl::SDL_SoundSystemImpl() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
	m_IsRunning = true;
	if (Mix_AllocateChannels(m_Channels) < 0)
	{
		fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
		exit(-1);
	}
	m_PlayThread = std::jthread{ &SDL_SoundSystemImpl::PlaySoundQueue, this };
	m_StopThread = std::jthread{ &SDL_SoundSystemImpl::RemoveSoundCheck, this };

}
SDL_Sound_System::SDL_SoundSystemImpl::~SDL_SoundSystemImpl()
{
	m_Cv.notify_all();
	m_IsRunning = false;
	if (m_PlayThread.joinable())
		m_PlayThread.join();


	if (m_StopThread.joinable())
		m_StopThread.join();
}
//Threads
void SDL_Sound_System::SDL_SoundSystemImpl::PlaySoundQueue()
{

	while (m_IsRunning) {
		std::unique_lock lock(m_Mutex);
		while (!m_SoundQueue.empty())
		{
			SoundEffect& currChunk = m_SoundQueue.front();
			currChunk.load();
			currChunk.Play();
			m_SoundQueue.pop_front();
			m_DeleteionCheckVec.push_back(currChunk);
		}
		//Notify deletion queue
		m_Cv.notify_all();
		m_Cv.wait(lock);


	}
	
}

void SDL_Sound_System::SDL_SoundSystemImpl::RemoveSoundCheck()
{
	while (m_IsRunning) {

		std::unique_lock lock(m_Mutex);
		m_Cv.wait(lock); //wait for PlaySoundQueue thread
		for (size_t i = 0; i < m_DeleteionCheckVec.size(); i++)
		{
			SoundEffect& currChunk = m_DeleteionCheckVec[i];
			if (currChunk.GetIsPlaying() == false) {
				currChunk.ReleaseSound();

				//Delete sound
				auto deletionIt = m_DeleteionCheckVec.begin();
				std::advance(deletionIt, i);
				m_DeleteionCheckVec.erase(deletionIt);
			}
		}


	}
}

unsigned int SDL_Sound_System::SDL_SoundSystemImpl::RegisterSoundImpl(const std::string& path)
{
	auto it = std::find(m_PathMap.begin(), m_PathMap.end(), path);

	if (it != m_PathMap.end()) {
		//if already exist;
		unsigned int distandIdx = static_cast<unsigned int>(std::distance(m_PathMap.begin(), it));
		return distandIdx;
	}
	else
	{
		//Not in path vec
		m_PathMap.push_back(path);
		return static_cast<unsigned int>(m_PathMap.size() - 1);
	}

}

void SDL_Sound_System::SDL_SoundSystemImpl::AddToQueue(const std::string& path, float volume)
{
	std::unique_lock lock(m_Mutex);
	SoundEffect curr(path, volume == 0.f ? m_GlobalVolume : volume);
	m_SoundQueue.push_back(curr);
	m_Cv.notify_all();

	
}

void SDL_Sound_System::SDL_SoundSystemImpl::StopAllImpl()
{
	Mix_HaltChannel(-1);
}

void SDL_Sound_System::SDL_SoundSystemImpl::SetGlobalVolumeLevel(float volume)
{
	m_GlobalVolume = volume;
}



SDL_Sound_System::SDL_Sound_System() 
	: m_pPimpl{ std::make_unique<SDL_SoundSystemImpl>() }
{

}

SDL_Sound_System::~SDL_Sound_System()
{
	m_pPimpl.reset();
}


void SDL_Sound_System::play(const std::string& path, const float volume)
{
	m_pPimpl->AddToQueue(path, volume);
}

void SDL_Sound_System::SetGlobalVolumeLevel(float volume)
{
	m_pPimpl->SetGlobalVolumeLevel(volume);
}

void SDL_Sound_System::StopAll()
{
	m_pPimpl->StopAllImpl();
}

unsigned int SDL_Sound_System::load(const std::string path)
{
	return m_pPimpl->RegisterSoundImpl(path);
}


