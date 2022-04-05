#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include <chrono>
#include <steam_api.h>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "HealthComponent.h"
#include "InputComponent.h"
#include "Time.h"
#include "RenderComponent.h"
#include "Achievment.h"

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
	std::cout << "FACEBUTTON NORTH: INCREASE SCORE PLAYER 1 (RED) \n";
	std::cout << "FACEBUTTON EAST: DECREASE LIVES PLAYER 1  (RED)  \n";
	std::cout << "FACEBUTTON SOUTH:  INCREASE SCORE PLAYER 2 (GREEN) \n";
	std::cout << "FACEBUTTON WEST: DECREASE LIVES PLAYER 2 (GREEN) \n";
	std::cout << "ACHIEVMENT: ACH_WIN_ONE_GAME ONLY GETS CALLED FOR PLAYER 2\n";

	std::cout << std::endl;

	PrintSDLVersion();


	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
	}
	else
		std::cout << "Successfully initialized steam." << std::endl;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

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



}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	//Background
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();

	auto texComp = std::make_shared<TextureComponent>();
	texComp->SetTexture("background.jpg");
	texComp->SetPosition({ 0,0 });

	go->AddComponent<TextureComponent>(texComp);
	scene.Add(go);

	auto goChild = std::make_shared<dae::GameObject>();
	texComp = std::make_shared<TextureComponent>();
	texComp->SetTexture("logo.png");
	texComp->SetPosition(glm::vec2{ 216, 180 });
	goChild->AddComponent<TextureComponent>(texComp);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 22);


	//UI elemet
	//p1
	glm::vec3 p1Color = { 255.f, 0.f, 0.f };
	auto p1LivesUI = std::make_shared<dae::GameObject>();
	auto textComponent = std::make_shared<TextComponent>("P1 Lives: ", font, p1Color);
	textComponent->SetPosition(glm::vec2{ 40.f, 70.f });
	p1LivesUI->AddComponent<TextComponent>(textComponent);
	scene.Add(p1LivesUI);

	auto p1ScoreUI = std::make_shared<dae::GameObject>();
	textComponent = std::make_shared<TextComponent>("P1 Score: ", font, p1Color);
	textComponent->SetPosition(glm::vec2{ 40.f, 110.f });
	p1ScoreUI->AddComponent<TextComponent>(textComponent);
	scene.Add(p1ScoreUI);

	//p2
	glm::vec3 p2Color = { 0.f, 255.f, 0.f };
	auto p2LivesUI = std::make_shared<dae::GameObject>();
	textComponent = std::make_shared<TextComponent>("P2 Lives: ", font, p2Color);
	textComponent->SetPosition(glm::vec2{ 40.f, 150.f });
	p2LivesUI->AddComponent<TextComponent>(textComponent);
	scene.Add(p2LivesUI);

	auto p2ScoreUI = std::make_shared<dae::GameObject>();
	textComponent = std::make_shared<TextComponent>("P2 Score: ", font, p2Color);
	textComponent->SetPosition(glm::vec2{ 40.f, 190.f });
	p2ScoreUI->AddComponent<TextComponent>(textComponent);
	scene.Add(p2ScoreUI);

	//Observers & event queues assignemnt;
	//score display
	//p1
	auto scoreDisplayGo = std::make_shared<GameObject>();
	auto scoreTextComponent = std::make_shared<TextComponent>("0", font, p1Color);
	scoreTextComponent->SetPosition(glm::vec2{ 140.f, 110.f });
	scoreDisplayGo->AddComponent<TextComponent>(scoreTextComponent);
	scene.Add(scoreDisplayGo);
	auto PeterPepper1 = std::make_shared<GameObject>();
	auto healthComponent = std::make_shared<HealthComponent>(10);
	auto inputComponent = std::make_shared<InputComponent>();

	PeterPepper1->AddComponent<HealthComponent>(healthComponent);
	PeterPepper1->AddComponent<InputComponent>(inputComponent);

	class DamageCommand : public Command {
	public:
		DamageCommand(std::shared_ptr<HealthComponent> componentToDamage, int damage) : m_ComponentToDamage{ componentToDamage }, m_Damage{ damage } {};
		virtual void Excecute() {
			m_ComponentToDamage->DecreaseHealth(m_Damage);
		}
	private:
		std::shared_ptr<HealthComponent> m_ComponentToDamage;
		int m_Damage;
	};
	inputComponent->AddCommand(ControllerButton::GAMEPAD_BUTTON_EAST, new DamageCommand(healthComponent, 10), KeyState::PRESSED);
	//Lives counter
	int lives = 5;
	textComponent = std::make_shared<TextComponent>(std::to_string(lives), font, p1Color);
	textComponent->SetPosition(glm::vec2{ 140.f, 70.f });
	PeterPepper1->AddComponent<TextComponent>(textComponent);
	healthComponent->addObserver(textComponent);

	//Increase Score simulation 
	class IncreaseScoreCommand : public Command,  public Subject {
	public:
		IncreaseScoreCommand(int score, std::shared_ptr<TextComponent> scoreComp) : m_Score{ score }, m_ScoreComponent{scoreComp} {};
		virtual void Excecute() {
			notify(m_ScoreComponent.get(), EventType::SCORE_INCREASE);
		}
	private:
		std::shared_ptr<TextComponent> m_ScoreComponent; //Just used to simulate baseComponent
		int m_Score;
	};
	IncreaseScoreCommand* scoreCommand = new IncreaseScoreCommand(100, textComponent);
	scoreCommand->addObserver(scoreTextComponent);
	inputComponent->AddCommand(ControllerButton::GAMEPAD_BUTTON_NORTH, scoreCommand, KeyState::PRESSED);
	//add peterpepper1 to scene
	scene.Add(PeterPepper1);

	//p2
	scoreDisplayGo = std::make_shared<GameObject>();
	scoreTextComponent = std::make_shared<TextComponent>("0", font, p2Color);
	scoreTextComponent->SetPosition(glm::vec2{ 140.f, 190.f });
	scoreTextComponent->addObserver(&Achievements::GetInstance());
	
	scoreDisplayGo->AddComponent<TextComponent>(scoreTextComponent);
	scene.Add(scoreDisplayGo);
	auto PeterPepper2 = std::make_shared<GameObject>();
	healthComponent = std::make_shared<HealthComponent>(10);
	inputComponent = std::make_shared<InputComponent>();

	inputComponent->AddCommand(ControllerButton::GAMEPAD_BUTTON_WEST, new DamageCommand(healthComponent, 10), KeyState::PRESSED);
	//Lives counter
	textComponent = std::make_shared<TextComponent>(std::to_string(lives), font, p2Color);
	textComponent->SetPosition(glm::vec2{ 140.f, 150.f });
	PeterPepper2->AddComponent<TextComponent>(textComponent);
	healthComponent->addObserver(textComponent);

	scoreCommand = new IncreaseScoreCommand(100, textComponent);
	scoreCommand->addObserver(scoreTextComponent);
	inputComponent->AddCommand(ControllerButton::GAMEPAD_BUTTON_SOUTH, scoreCommand, KeyState::PRESSED);


	//add peterpepper2 to scene
	scene.Add(PeterPepper2);





}

void dae::Minigin::Cleanup()
{
	SteamAPI_Shutdown();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();


	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

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

		SDL_Event e;
		while (doContinue)
		{
			//TODO add proper event system to catch user events
			SDL_PollEvent(&e);
			SteamAPI_RunCallbacks();

			if (e.type == SDL_QUIT) {
				doContinue = false;
			}

			input.ProcessInput();
			sceneManager.Update();
			time.Update();

			lag += time.GetDeltaTime();
			while (lag >= m_FixedTimeStep)
			{
				sceneManager.LateUpdate();
				lag -= m_FixedTimeStep;
			}
			renderer.Render();
		}
	}

	Cleanup();
}
