#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Game.h"

#include "AssetManager.h"
#include "EntityManager.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "CollisionComponent.h"

#include "Map.h"
#include "Menu.h"
#include "Functions.h"

#include "WipeTransition.h"

#include <string>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

Map* bg1;
Map* bg2;
Menu* menu;
Map* stage1;
EntityManager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
TTF_Font* Game::font;
AssetManager* Game::assetManager = new AssetManager(&manager);
bool Game::isRunning = false;
std::vector<Entity*>* Game::StopObject = nullptr;
std::vector<Entity*> Game::PushObject = {};
float Game::DeltaSecond = 0;

//�ؽ�Ʈ �Լ� ����
std::map<TextType, textfunc> Game::textfuncmap;
std::map<uint32_t, std::function<void(void)>> Game::stagefuncmap;

WipeTransition* Game::transtition = nullptr;

int Game::CurStageIndex = -1;

//���̾�� ����� �迭��
std::vector<Entity*>& players(manager.getLayerGroup(LayerBaba));
//���� �ؽ�Ʈ ������
std::vector<Entity*>& Game::headtexts(manager.getLayerGroup(LayerHeadText));
std::vector<Entity*>& Game::verbtexts(manager.getLayerGroup(LayerVerbText));
std::vector<Entity*>& Game::tailtexts(manager.getLayerGroup(LayerTailText));

Game::Game()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(193);

	textfuncmap.emplace(TextType::You, isYou);
	textfuncmap.emplace(TextType::Stop, isStop);
	textfuncmap.emplace(TextType::Push, isPush);
	textfuncmap.emplace(TextType::Win, isWin);
	textfuncmap.emplace(TextType::Death, isDeath);
	textfuncmap.emplace(TextType::Shut, isShut);
	textfuncmap.emplace(TextType::Open, isOpen);
	textfuncmap.emplace(TextType::Hot, isHot);
	textfuncmap.emplace(TextType::Melt, isMelt);
	textfuncmap.emplace(TextType::Sink, isSink);
	textfuncmap.emplace(TextType::Move, isMove);

	stagefuncmap.emplace(99, std::bind(&Game::LoadMenu, this));
	stagefuncmap.emplace(0, std::bind(&Game::LoadStage0, this));
	stagefuncmap.emplace(1, std::bind(&Game::LoadStage1, this));
}

Game::~Game()
{
	textfuncmap.clear();
	stagefuncmap.clear();
	//TO DO SDL_Texture* is Leaking
	_CrtDumpMemoryLeaks();
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Successfully Init!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Successfully Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			//SDL_SetRenderDrawColor(renderer, 21, 24, 31, SDL_ALPHA_OPAQUE);
			SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			std::cout << "Renderer Successfully Created!" << std::endl;
		}

		if (TTF_Init() == -1)
			std::cout << TTF_GetError() << std::endl;
		else
			std::cout << "ttf is Successfully Created!" << std::endl;

		isRunning = true;
	}
	else
	{
		std::cout << SDL_GetError() << std::endl;
		isRunning = false;
	}

	//initAsset
	assetManager->AddTexture("bg", "assets/bg.png");
	assetManager->AddTexture("terrain", "assets/terrain.png");
	assetManager->AddTexture("obstacle", "assets/obstacle.png");
	assetManager->AddTexture("playable", "assets/playable.png");
	assetManager->AddTexture("dynamicobject", "assets/dynamicobject.png");
	assetManager->AddTexture("staticobject", "assets/staticobject.png");
	assetManager->AddTexture("text", "assets/text.png");
	assetManager->AddTexture("menumap", "assets/menumap.png");

	//Transition
	transtition = new WipeTransition(20);

	//font
	font = TTF_OpenFont("assets/VT323-Regular.ttf", 18);

	LoadMenu();
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Game::update(float deltaTime)
{
	DeltaSecond = deltaTime;
	manager.update(deltaTime);
	manager.CheckCollisions();//���� ������� �ʽ��ϴ�.
	transtition->updateTransition(deltaTime);
}

void Game::render()
{
	SDL_RenderClear(renderer);

	if (manager.HasNoEntities())
	{
		return;
	}

	manager.render();
	if (menu != nullptr)
		menu->DrawStageText();
	transtition->render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(font);
	SDL_Quit();
	if (assetManager != nullptr)
	{
		delete assetManager;
		assetManager = nullptr;
	}
	if (transtition != nullptr)
	{
		delete transtition;
		transtition = nullptr;
	}

	manager.ClearAllEntity();
	manager.DestroyInactiveEntities();

	if (bg1 != nullptr)
	{
		delete bg1;
		bg1 = nullptr;
	}
	if (bg2 != nullptr)
	{
		delete bg2;
		bg2 = nullptr;
	}
	if (menu != nullptr)
	{
		delete menu;
		menu = nullptr;
	}
	if (stage1 != nullptr)
	{
		delete stage1;
		stage1 = nullptr;
	}

	std::cout << "Game Successfully Quited!" << std::endl;
}

void Game::LoadBackGround()
{
	bg1 = new Map("bg", 1, 854);
	bg1->LoadBG();
	bg2 = new Map("terrain", 1, 24);//��Ÿ���� ������, ��Ÿ���� �ȼ���
	bg2->LoadMap("assets/map.map", 33, 18);//������ Ÿ��
}

void Game::LoadMenu()
{
	manager.ClearAllEntity();
	manager.DestroyInactiveEntities();

	CurStageIndex = -1;
	StopObject = nullptr;
	PushObject.clear();

	if (bg1 != nullptr)
	{
		delete bg1;
		bg1 = nullptr;
	}
	if (bg2 != nullptr)
	{
		delete bg2;
		bg2 = nullptr;
	}
	if (menu != nullptr)
	{
		delete menu;
		menu = nullptr;
	}
	if (stage1 != nullptr)
	{
		delete stage1;
		stage1 = nullptr;
	}

	LoadBackGround();

	//Loadmenu 793 432
	menu = new Menu("menumap", 1, WINDOW_WIDTH - WIDTH_INTERVAL * 2, WINDOW_HEIGHT - HEIGHT_INVERVAL * 2); //���Ÿ�Ͻ�����, ���x, ���y, �޴�������Ʈ ������, �޴�������Ʈ�ȼ���
	menu->LoadMenu();
	menu->LoadMenuObject("assets/menu.map", 33, 18); //Ŀ��, ����, ������, ttf
	menu->LoadCollisionMap("assets/menucol.map", 33, 18);

	//���̾ �̺�Ʈ ���ε�
	auto menufunc = isMenu;
	(*menufunc)(manager.getLayerGroup(LayerMenu));

	Entity& player(manager.addEntity());

	player.addComponent<TransformComponent>(static_cast<float>(WIDTH_INTERVAL) + 9 * PIXEL_SIZE - 5, static_cast<float>(HEIGHT_INVERVAL) + 15 * PIXEL_SIZE - 5, LARGE_PIXEL_SIZE, LARGE_PIXEL_SIZE);
	player.addComponent<SpriteComponent>("staticobject", 3, 200, 15, 34);
	player.addComponent<CollisionComponent>("Baba", PIXEL_SIZE, PIXEL_SIZE, 5);
	player.addLayerGroup(LayerBaba);
	(*textfuncmap[TextType::You])(players);

	transtition->playTransition(TRANS_TYPE::IN);
}

void Game::LoadStage0()
{
	manager.ClearAllEntity();
	manager.DestroyInactiveEntities();

	CurStageIndex = 0;
	StopObject = nullptr;
	PushObject.clear();

	if (bg1 != nullptr)
	{
		delete bg1;
		bg1 = nullptr;
	}
	if (bg2 != nullptr)
	{
		delete bg2;
		bg2 = nullptr;
	}
	if (menu != nullptr)
	{
		delete menu;
		menu = nullptr;
	}
	if (stage1 != nullptr)
	{
		delete stage1;
		stage1 = nullptr;
	}

	LoadBackGround();

	stage1 = new Map("stage1", 1, 24);
	stage1->LoadObject("assets/stage1.map", 33, 18);

	//�ʹݿ� �ؽ�Ʈ���� ������踦 �����մϴ�.
	std::vector<std::pair<Vector2D, LayerGroup>> textgroupvec;
	for (Entity*& text : headtexts)
	{
		Vector2D nextRightPos = Vector2D(text->getComponent<TransformComponent>()->position.x + PIXEL_SIZE, text->getComponent<TransformComponent>()->position.y);
		Vector2D nextBottomPos = Vector2D(text->getComponent<TransformComponent>()->position.x, text->getComponent<TransformComponent>()->position.y + PIXEL_SIZE);
		for (Entity*& verb : verbtexts)
		{
			//���� ������ ��ġ�� �����ϰ��ִ� �׷��� ������ �־��ݴϴ�.
			Vector2D verbPos = Vector2D(verb->getComponent<TransformComponent>()->position.x, verb->getComponent<TransformComponent>()->position.y);
			if (verbPos == nextRightPos)
			{
				verbPos.x += PIXEL_SIZE;
				textgroupvec.emplace_back(verbPos, text->getManagingLayer());
				verbPos.x -= PIXEL_SIZE;
			}
			if (verbPos == nextBottomPos)
			{
				verbPos.y += PIXEL_SIZE;
				textgroupvec.emplace_back(verbPos, text->getManagingLayer());
				verbPos.y -= PIXEL_SIZE;
			}
		}
	}

	for (Entity*& tailtext : tailtexts)
	{
		Vector2D tailTextPos = tailtext->getComponent<TransformComponent>()->position;
		for (std::pair<Vector2D, LayerGroup>& textgroup : textgroupvec)
		{
			if (tailTextPos == textgroup.first)
			{
				//�� ������ id�� ���εǾ��ִ� �Լ��� �������� �� �Լ��� �Ű������� layeredobj�� �־��ָ� �ȴ�.
				std::vector<Entity*>& layeredobj = manager.getLayerGroup(textgroup.second);
				textfunc func = textfuncmap[tailtext->getTextType()];
				(*func)(layeredobj);
			}
		}
	}

	textfunc func = textfuncmap[TextType::Push];
	(*func)(headtexts);
	(*func)(verbtexts);
	(*func)(tailtexts);

	Entity& player(manager.addEntity());

	player.addComponent<TransformComponent>(static_cast<float>(WIDTH_INTERVAL) + 12 * PIXEL_SIZE, static_cast<float>(HEIGHT_INVERVAL) + 10 * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE);
	player.addComponent<SpriteComponent>("playable", 3, 150, 23, 0, true, true);
	player.addComponent<CollisionComponent>("Baba", PIXEL_SIZE, PIXEL_SIZE);
	player.addLayerGroup(LayerBaba);

	(*textfuncmap[TextType::You])(players);

	transtition->playTransition(TRANS_TYPE::IN);
}

void Game::LoadStage1()
{
	//TO DO������ ��� ������Ʈ ����
	manager.ClearAllEntity();
	manager.DestroyInactiveEntities();

	CurStageIndex = 1;
	StopObject = nullptr;
	PushObject.clear();

	LoadBackGround();

	transtition->playTransition(TRANS_TYPE::IN);
}