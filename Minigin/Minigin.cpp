#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include <chrono>
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
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"
#include "PetterPepperComponent.h"
#include "TillingComponent.h"
#include "BoxColliderComponent.h"
#include "Parser.h"
#include "SDL_mixer.h"
#include "ServiceLocator.h"
#include "Sound_System.h"
#include "MovementComponent.h"

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
static void CreateBurger() {
	auto scene = SceneManager::GetInstance().GetScene("Demo");
	auto goBurgerPiece = std::make_shared<dae::GameObject>();
	goBurgerPiece->GetTransform().SetPosition(50, 50,0);
	auto spriteComponent = std::make_shared<SpriteComponent>("SpiteSheet.png", 15, 11, 1.f);
	goBurgerPiece->AddComponent<SpriteComponent>(spriteComponent);
	spriteComponent->AddAnimation("Move", 3, 0, 6, 1);
	scene->Add(goBurgerPiece);

}
static void CreateLadder(std::vector<glm::vec2>& posVec, int tilling) {
	auto scene = SceneManager::GetInstance().GetScene("Demo");
	//lader creation

	for (size_t i = 0; i < posVec.size(); i++)
	{
		auto goLadder = std::make_shared<dae::GameObject>();
		auto ladderComp = std::make_shared<TillingComponent>(tilling, 5);
		auto texComp = std::make_shared<TextureComponent>();
		texComp->SetTexture("ladder.png");
		auto goBoxColl = std::make_shared<BoxColliderComponent>(texComp->GetDimensions(), "Ladder");

		goLadder->AddComponent<TillingComponent>(ladderComp);
		goLadder->AddComponent<TextureComponent>(texComp);
		goLadder->AddComponent<BoxColliderComponent>(goBoxColl);


		goLadder->SetPosition(posVec[i]);
		scene->Add(goLadder);
	}

}

static void CreatePlatform(std::vector<glm::vec2>& posVec, int tilling) {

	auto scene = SceneManager::GetInstance().GetScene("Demo");
	for (size_t i = 0; i < posVec.size(); i++)
	{
		auto goFloor = std::make_shared<dae::GameObject>();
		auto tillComp = std::make_shared<TillingComponent>(tilling, 0, false);
		auto texComp = std::make_shared<TextureComponent>();
		texComp->SetTexture("Walkable.png");
		auto goBoxColl = std::make_shared<BoxColliderComponent>(texComp->GetDimensions(), "Floor", 0);

		goFloor->AddComponent<TillingComponent>(tillComp);
		goFloor->AddComponent<TextureComponent>(texComp);
		goFloor->AddComponent<BoxColliderComponent>(goBoxColl);


		goFloor->SetPosition(posVec[i]);
		scene->Add(goFloor);
	}

}
/**
 * Code constructing the scene world starts here
 */
static void CreatePlayer(const std::vector<glm::vec2>& posVec) {
	auto scene = SceneManager::GetInstance().GetScene("Demo");
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 22);


	//Increase Score simulation 
	class IncreaseScoreCommand : public Command, public Subject {
	public:
		IncreaseScoreCommand(int score, std::shared_ptr<TextComponent> scoreComp) : m_Score{ score }, m_ScoreComponent{ scoreComp } {};
		virtual void Excecute() {
			ScoreArgs args;
			args.scoreIncrease = m_Score;
			notify(m_ScoreComponent.get(), EventType::SCORE_INCREASE, &args);
		}
	private:
		std::shared_ptr<TextComponent> m_ScoreComponent; //Just used to simulate baseComponent
		int m_Score;
	};

	glm::vec2 uiPos = glm::vec2{ 60.f, 20.f };
	//for (size_t i = 0; i < posVec.size(); i++)
	for (size_t i = 0; i < 1; i++)

	{
		glm::vec3 color = { static_cast<float>(rand() % 255), static_cast<float>(rand() % 255), static_cast<float>(rand() % 255) };
		//UI Creation
		auto scoreDisplayGo = std::make_shared<GameObject>();
		auto textComp = std::make_shared<TextComponent>("0", font, color);
		auto scoreDisplayComponent = std::make_shared<ScoreDisplayComponent>("Score: ");
		scoreDisplayGo->SetPosition(uiPos);
		scoreDisplayGo->AddComponent<TextComponent>(textComp);
		scoreDisplayGo->AddComponent<ScoreDisplayComponent>(scoreDisplayComponent);


		//UI translate
		uiPos.y += 40.f;

		auto liveDisplayGO = std::make_shared<GameObject>();
		textComp = std::make_shared<TextComponent>(" ", font, color);
		liveDisplayGO->SetPosition(uiPos);
		auto liveDisplaycomp = std::make_shared<LivesDisplayComponent>("Player " + std::to_string(i + 1) + ": ");

		liveDisplayGO->AddComponent<TextComponent>(textComp);
		liveDisplayGO->AddComponent<LivesDisplayComponent>(liveDisplaycomp);
		scoreDisplayGo->AddChild(liveDisplayGO);
		scene->Add(scoreDisplayGo);

		//Player Creation
		//--------------------------------------------------
		auto PeterPepper = std::make_shared<GameObject>();
		auto healthComponent = std::make_shared<HealthComponent>();
		auto inputComponent = std::make_shared<InputComponent>(static_cast<int>(i));
		auto spriteComponent = std::make_shared<SpriteComponent>("SpiteSheet.png",15, 11, 1.f);
		auto peterPepperComp = std::make_shared<PetterPepperComponent>();
		auto movementComp = std::make_shared<MovementComponent>(5.f);
		auto boxCollider = std::make_shared<BoxColliderComponent>("Pepper", 1);


		//Anims
		spriteComponent->AddAnimation("MoveBackwards", 0, 0, 3, 1);
		spriteComponent->AddAnimation("Move", 3, 0, 6, 1);
		spriteComponent->AddAnimation("MoveForward", 6, 0, 9, 1);


		PeterPepper->AddComponent<HealthComponent>(healthComponent);
		PeterPepper->AddComponent<InputComponent>(inputComponent);
		PeterPepper->AddComponent<SpriteComponent>(spriteComponent);
		PeterPepper->AddComponent<PetterPepperComponent>(peterPepperComp);
		PeterPepper->AddComponent<MovementComponent>(movementComp);
		PeterPepper->AddComponent<BoxColliderComponent>(boxCollider);


		auto* scoreCommand = new IncreaseScoreCommand(100, textComp);
		scoreCommand->addObserver(scoreDisplayComponent);
		inputComponent->AddCommand(ControllerButton::GAMEPAD_BUTTON_NORTH, 'Z', scoreCommand, KeyState::PRESSED);
		healthComponent->addObserver(liveDisplaycomp);
		healthComponent->SetHealth(10);
		healthComponent->SetLives(5);

		glm::vec2 pos = posVec[i];
		PeterPepper->SetPosition(pos.x, pos.y);


		scene->Add(PeterPepper);

		//UI translate
		uiPos.y += 40.f;
	}



}

void dae::Minigin::LoadGame() const
{
	//Background + SceneLoading
	//-------------------------------------------------------------
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto go = std::make_shared<dae::GameObject>();
	auto texComp = std::make_shared<TextureComponent>();
	texComp->SetTexture("background.jpg");
	go->SetPosition({ 0,0 });
	go->AddComponent<TextureComponent>(texComp);
	scene.Add(go);

	auto goChild = std::make_shared<dae::GameObject>();
	texComp = std::make_shared<TextureComponent>();
	texComp->SetTexture("logo.png");
	goChild->SetPosition(glm::vec2{ 216, 180 });
	goChild->AddComponent<TextureComponent>(texComp);
	ServiceLocator::RegisterSoundSystem(new LogginSoundSystem(new SDL_Sound_System()));



	Parser pr("../Data/Level_1.json");

	for (auto& mapElement : pr.GeLevelObject()) {
		//Player Creation
		if (mapElement.first == "PeterPepperPrefab") {
			CreatePlayer(mapElement.second);
		}
		else if (mapElement.first == "PlatformSoloPrefab") {
			CreatePlatform(mapElement.second, 2);
		}
		else if (mapElement.first == "PlatformLongPrefab") {
			CreatePlatform(mapElement.second, 10);
		}
		else if (mapElement.first == "LadderLongPrefab") {
			CreateLadder(mapElement.second, 12);
		}
		else if (mapElement.first == "LadderShortPrefab") {
			CreateLadder(mapElement.second, 10);
		}
	}
	CreateBurger();
	//Call start after everything is initialized
	scene.Start();
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

		ServiceLocator::GetSoundSystem().play(0, 50.f);
		SDL_Event e;
		while (doContinue)
		{

			//TODO add proper event system to catch user events
			SDL_PollEvent(&e);
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
