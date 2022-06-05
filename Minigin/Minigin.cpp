#include "MiniginPCH.h"
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "DeltaTime.h"
#include "SDL_mixer.h"
#include "ServiceLocator.h"
#include "Sound_System.h"

using namespace std;
using namespace dae;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	//Init Sound
	ServiceLocator::RegisterSoundSystem(new LogginSoundSystem(new SDL_Sound_System()));
}


void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	ServiceLocator::Delete();
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{


	{

		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();

		// todo: this update loop could use some work.
		bool doContinue = true;
		//FrameCounter


		float lag = 0.f;

		while (doContinue)
		{

			//TODO add proper event system to catch user events
			
			doContinue = input.ProcessInput();
		


			
			sceneManager.Update();
			time.Update();

			lag += time.GetDeltaTime();
			while (lag >= m_FixedTimeStep)
			{
				sceneManager.FixedUpdate();
				lag -= m_FixedTimeStep;
			}
			renderer.Render();
			//Add late update here

			sceneManager.DestroyFlaggedScenes();
		}
	}

	Cleanup();
}
