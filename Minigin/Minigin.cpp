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
	std::cout << "---USER INFO----\n";
	std::cout << "WASD to move and play sounds :D \n";

	std::cout << std::endl;

	PrintSDLVersion();
	Renderer::GetInstance().Init(640, 480);


}
void dae::Minigin::LoadGame() const
{	
	//Init Sound
	ServiceLocator::RegisterSoundSystem(new LogginSoundSystem(new SDL_Sound_System()));
	
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	ServiceLocator::Delete();
	SDL_Quit();
}

void dae::Minigin::Run()
{

	LoadGame();

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
				sceneManager.LateUpdate();
				lag -= m_FixedTimeStep;
			}
			renderer.Render();

			sceneManager.DestroyFlaggedScenes();
		}
	}

	Cleanup();
}
