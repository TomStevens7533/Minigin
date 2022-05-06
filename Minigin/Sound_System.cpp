#include "MiniginPCH.h"
#include "Sound_System.h"
#include <SDL_mixer.h>
#include <thread>
#include <mutex>
#include "SoundEffect.h"
#include <map>

class SDL_Sound_System::SDL_SoundSystemImpl {
public:
	SDL_SoundSystemImpl();
	~SDL_SoundSystemImpl();
	void playImpl();
	//void loadImpl(std::string path);
	void RegisterSoundImpl(const unsigned int id,const std::string& path);
	void AddToQueue(const unsigned int id, float volume);
private:
	std::jthread m_Thread;
	std::condition_variable m_Variable;
	Mix_Chunk* losPollos;
	std::deque<SoundEffect> m_SoundQueue;
	std::deque<SoundEffect> m_DeletionQueue;

	bool m_IsRunning;
	std::map<unsigned int, std::string> m_PathMap;
};
SDL_Sound_System::SDL_SoundSystemImpl::SDL_SoundSystemImpl() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
	m_IsRunning = true;
	if (Mix_AllocateChannels(4) < 0)
	{
		fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
		exit(-1);
	}
	m_Thread = std::jthread{ &SDL_SoundSystemImpl::playImpl, this };
}
SDL_Sound_System::SDL_SoundSystemImpl::~SDL_SoundSystemImpl()
{
	m_IsRunning = false;
	for (size_t i = 0; i < m_DeletionQueue.size(); i++)
	{
		m_DeletionQueue[i].ReleaseSound();
	}

}
void SDL_Sound_System::SDL_SoundSystemImpl::playImpl()
{
	while (m_IsRunning) {


		while (!m_SoundQueue.empty())
		{
			SoundEffect currChunk = m_SoundQueue.front();
			if (!currChunk.IsLoaded())
				currChunk.load();

			if (!currChunk.Play())
				m_SoundQueue.pop_front();
		}
		
			
	}	
}

//void SDL_Sound_System::SDL_SoundSystemImpl::loadImpl(std::string path)
//{
//
//}

void SDL_Sound_System::SDL_SoundSystemImpl::RegisterSoundImpl(const unsigned int id, const std::string& path)
{
	m_PathMap.insert(std::make_pair(id, path));
}

void SDL_Sound_System::SDL_SoundSystemImpl::AddToQueue(const unsigned int id, float volume)
{
	
	if (m_PathMap.contains(id)) {
		//Contains ID
		SoundEffect curr(m_PathMap[id], volume);
		m_SoundQueue.push_back(curr);
	}
	
}

SDL_Sound_System::SDL_Sound_System() : m_pPimpl{ std::make_unique<SDL_SoundSystemImpl>() }
{

}

SDL_Sound_System::~SDL_Sound_System()
{
	m_pPimpl.reset();
}


void SDL_Sound_System::play(const unsigned int id, const float volume)
{
	m_pPimpl->AddToQueue(id, volume);
}

void SDL_Sound_System::load(const unsigned int id, const std::string path)
{
	m_pPimpl->RegisterSoundImpl(id, path);
}


