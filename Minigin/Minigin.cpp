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
//static void CreateTopBurger(std::vector<glm::vec2>& posVec) {
//
//	
//	
//	
//	
//	
//	
//	
//	
//	
//	
//	
//	
//
//	
//	
//
//}
//static void CreateLettuce(std::vector<glm::vec2>& posVec) {
//
//	for (size_t i = 0; i < posVec.size(); i++)
//	{
//		glm::vec2 bunPos = posVec[i];
//		auto scene = SceneManager::GetInstance().GetScene("Demo");
//		auto goBurgerPiece = std::make_shared<dae::GameObject>();
//		goBurgerPiece->GetTransform().SetPosition(bunPos.x, bunPos.y, 0);
//		auto TexComp = std::make_shared<TextureComponent>("Lettuce.png");
//		auto boxComp = std::make_shared<BoxColliderComponent>("Bun");
//		auto bunComp = std::make_shared<BunBehaviour>();
//		goBurgerPiece->AddComponent<BoxColliderComponent>(boxComp);
//		goBurgerPiece->AddComponent<TextureComponent>(TexComp);
//		goBurgerPiece->AddComponent<BunBehaviour>(bunComp);
//
//		scene->Add(goBurgerPiece);
//	}
//
//}
//static void CreateLowerBun(std::vector<glm::vec2>& posVec) {
//
//	for (size_t i = 0; i < posVec.size(); i++)
//	{
//		glm::vec2 bunPos = posVec[i];
//		auto scene = SceneManager::GetInstance().GetScene("Demo");
//		auto goBurgerPiece = std::make_shared<dae::GameObject>();
//		goBurgerPiece->GetTransform().SetPosition(bunPos.x, bunPos.y, 0);
//		auto TexComp = std::make_shared<TextureComponent>("LowerBun.png");
//		auto boxComp = std::make_shared<BoxColliderComponent>("Bun");
//		auto bunComp = std::make_shared<BunBehaviour>();
//		goBurgerPiece->AddComponent<BoxColliderComponent>(boxComp);
//		goBurgerPiece->AddComponent<TextureComponent>(TexComp);
//		goBurgerPiece->AddComponent<BunBehaviour>(bunComp);
//
//		scene->Add(goBurgerPiece);
//	}
//
//}
//static void CreateTomato(std::vector<glm::vec2>& posVec) {
//
//	for (size_t i = 0; i < posVec.size(); i++)
//	{
//		glm::vec2 bunPos = posVec[i];
//		auto scene = SceneManager::GetInstance().GetScene("Demo");
//		auto goBurgerPiece = std::make_shared<dae::GameObject>();
//		goBurgerPiece->GetTransform().SetPosition(bunPos.x, bunPos.y, 0);
//		auto TexComp = std::make_shared<TextureComponent>("Tomato.png");
//		auto boxComp = std::make_shared<BoxColliderComponent>("Bun", 2);
//		auto bunComp = std::make_shared<BunBehaviour>();
//		goBurgerPiece->AddComponent<BoxColliderComponent>(boxComp);
//		goBurgerPiece->AddComponent<TextureComponent>(TexComp);
//		goBurgerPiece->AddComponent<BunBehaviour>(bunComp);
//
//		scene->Add(goBurgerPiece);
//	}
//
//}
//static void CreateLadder(std::vector<glm::vec2>& posVec, int tilling) {
//	auto scene = SceneManager::GetInstance().GetScene("Demo");
//	//lader creation
//	for (size_t i = 0; i < posVec.size(); i++)
//	{
//		
//		
//		
//
//
//		
//		
//		
//
//		
//		scene->Add(goLadder);
//	}
//
//}
//
//static void CreatePlatform(std::vector<glm::vec2>& posVec, int tilling) {
//

//
//}
//static void CreateBurgerCatcher(std::vector<glm::vec2>& posVec) {
//
//	for (size_t i = 0; i < posVec.size(); i++)
//	{
//		glm::vec2 bunPos = posVec[i];
//		auto scene = SceneManager::GetInstance().GetScene("Demo");
//		auto goBurgerPiece = std::make_shared<dae::GameObject>();
//		goBurgerPiece->GetTransform().SetPosition(bunPos.x, bunPos.y, 0);
//		auto TexComp = std::make_shared<TextureComponent>("BurgerCatcher.png");
//		auto boxComp = std::make_shared<BoxColliderComponent>("BunEnd");
//
//		goBurgerPiece->AddComponent<BoxColliderComponent>(boxComp);
//		goBurgerPiece->AddComponent<TextureComponent>(TexComp);
//
//		scene->Add(goBurgerPiece);
//	}
//	
//}
///**
// * Code constructing the scene world starts here
// */
//static void CreatePlayer(const std::vector<glm::vec2>& posVec) {
//	auto scene = SceneManager::GetInstance().GetScene("Demo");
//	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 22);
//
//
//	glm::vec2 uiPos = glm::vec2{ 60.f, 20.f };
//	glm::vec3 color = { 255, 0, 0 };
//
//	//UI Creation
//	auto scoreDisplayGo = std::make_shared<GameObject>();
//	auto textComp = std::make_shared<TextComponent>("0", font, color);
//	auto scoreDisplayComponent = std::make_shared<ScoreDisplayComponent>("Score: ");
//	scoreDisplayGo->SetPosition(uiPos);
//	scoreDisplayGo->AddComponent<TextComponent>(textComp);
//	scoreDisplayGo->AddComponent<ScoreDisplayComponent>(scoreDisplayComponent);
//	scene->Add(scoreDisplayGo);
//	uiPos.x += 100.f;
//
//	auto liveDisplayGO = std::make_shared<GameObject>();
//	textComp = std::make_shared<TextComponent>(" ", font, color);
//	liveDisplayGO->SetPosition(uiPos);
//	auto liveDisplaycomp = std::make_shared<LivesDisplayComponent>("Lives: ");
//
//	liveDisplayGO->AddComponent<TextComponent>(textComp);
//	liveDisplayGO->AddComponent<LivesDisplayComponent>(liveDisplaycomp);
//	scene->Add(liveDisplayGO);
//
//	uiPos.x += 100.f;
//
//	
//	pepperDisplayGO->SetPosition(uiPos);
//
//
//
//	//for (size_t i = 0; i < posVec.size(); i++)
//	for (size_t i = 0; i < 1; i++)
//
//	{
//		//UI Creation
//	
//
//
//		//UI translate
//		
//		//Player Creation
//		//--------------------------------------------------
//		auto PeterPepper = std::make_shared<GameObject>();
//		auto healthComponent = std::make_shared<HealthComponent>();
//		auto inputComponent = std::make_shared<InputComponent>(static_cast<int>(i));
//		auto spriteComponent = std::make_shared<SpriteComponent>("SpiteSheet.png",15, 11, 0.3f);
//		auto peterPepperComp = std::make_shared<PetterPepperComponent>();
//		auto movementComp = std::make_shared<MovementComponent>(70.f);
//		auto attackComp = std::make_shared<AttackComponent>();
//		attackComp->addObserver(pepperDisplaycomp);
//		healthComponent->addObserver(liveDisplaycomp);
//
//		auto boxCollider = std::make_shared<BoxColliderComponent>("Pepper", 5);
//
//
//		//Anims
//		spriteComponent->AddAnimation("MoveForward", 6, 0, 9, 1);
//		spriteComponent->AddAnimation("Move", 3, 0, 6, 1);
//		spriteComponent->AddAnimation("MoveBackwards", 0, 0, 3, 1);
//		spriteComponent->AddAnimation("Death", 6, 1, 9, 2);
//
//
//		PeterPepper->AddComponent<AttackComponent>(attackComp);
//		PeterPepper->AddComponent<HealthComponent>(healthComponent);
//		PeterPepper->AddComponent<InputComponent>(inputComponent);
//		PeterPepper->AddComponent<SpriteComponent>(spriteComponent);
//		PeterPepper->AddComponent<PetterPepperComponent>(peterPepperComp);
//		PeterPepper->AddComponent<MovementComponent>(movementComp);
//		PeterPepper->AddComponent<BoxColliderComponent>(boxCollider);
//
//
//		glm::vec2 pos = posVec[i];
//		PeterPepper->SetPosition(pos.x, pos.y);
//
//
//		scene->Add(PeterPepper);
//
//		//UI translate
//		uiPos.y += 40.f;
//	}
//
//
//
//}
//static void CreateMrHotDogg() {
//	
//
//	
//	", 15, 11, 0.2f);
//	
//	
//	
//
//
//	
//	
//	
//	
//	
//
//
//
//
//
//	
//	
//	
//	
//
//
//
//
//	
//	
//
//}
void dae::Minigin::LoadGame() const
{
	//Background + SceneLoading
	//-------------------------------------------------------------


	/*auto goChild = std::make_shared<dae::GameObject>();
	texComp = std::make_shared<TextureComponent>("logo.png");
	goChild->SetPosition(glm::vec2{ 216, 180 });
	goChild->AddComponent<TextureComponent>(texComp);*/



	
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
