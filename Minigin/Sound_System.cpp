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
	void PlaySoundQueue();
	//void loadImpl(std::string path);
	unsigned int RegisterSoundImpl(const std::string& path);
	void AddToQueue(const unsigned int id, float volume);
private:
	std::jthread m_Thread;
	std::condition_variable m_Variable;
	Mix_Chunk* losPollos;
	std::deque<SoundEffect> m_SoundQueue;
	std::deque<SoundEffect> m_DeletionQueue;
	std::mutex m_Mutex;
	std::condition_variable m_Cv;
	int m_Channels = 4;

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
	m_Thread = std::jthread{ &SDL_SoundSystemImpl::PlaySoundQueue, this };
}
SDL_Sound_System::SDL_SoundSystemImpl::~SDL_SoundSystemImpl()
{
	std::unique_lock lock(m_Mutex);
	m_IsRunning = false;
}
void SDL_Sound_System::SDL_SoundSystemImpl::PlaySoundQueue()
{

	std::unique_lock lock(m_Mutex);
	while (m_IsRunning) {
		m_Cv.wait(lock);
		while (!m_SoundQueue.empty())
		{
			lock.unlock();
			SoundEffect& currChunk = m_SoundQueue.front();
			if (!currChunk.IsLoaded() && !currChunk.GetIsPlaying()) {
				currChunk.load();
				currChunk.Play();
			}

			lock.lock();
			if (!currChunk.GetIsPlaying()) {
				currChunk.ReleaseSound();
				m_SoundQueue.pop_front();
			}
			else
				std::swap(m_SoundQueue.front(), m_SoundQueue.back());


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

void SDL_Sound_System::SDL_SoundSystemImpl::AddToQueue(const unsigned int id, float volume)
{
	if (id < m_PathMap.size()) {
		//Contains ID
		std::unique_lock lock(m_Mutex);
		int channel = id % m_PathMap.size();
		if (!Mix_Playing(channel)) {
			SoundEffect curr(m_PathMap[id], volume, channel);
			m_SoundQueue.push_back(curr);
			m_Cv.notify_one();
			std::cout << "aq\n";

		}

	}
	
}

SDL_Sound_System::SDL_Sound_System() 
	: m_pPimpl{ std::make_unique<SDL_SoundSystemImpl>() }
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

unsigned int SDL_Sound_System::load(const std::string path)
{
	return m_pPimpl->RegisterSoundImpl(path);
}


