#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Constants.h"
#include <iostream>
#include <vector>
#include <map>
#include <functional>

class AssetManager;
class Entity;
class Game;
class WipeTransition;

using textfunc = void (*)(std::vector<Entity*>&);
//using stagefunc = void (Game::*)(void);

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update(float deltaTime);
	void render();
	void clean();

	bool running() { return isRunning; }

	void LoadBackGround();
	void LoadMenu();
	void LoadStage0();
	void LoadStage1();

	static SDL_Event event;
	static SDL_Renderer* renderer;
	static TTF_Font* font;
	static AssetManager* assetManager;
	static bool isRunning;
	static std::vector<Entity*>* StopObject;
	static std::vector<Entity*> PushObject;
	static float DeltaSecond;

	//텍스트
	static std::vector<Entity*>& headtexts;
	static std::vector<Entity*>& verbtexts;
	static std::vector<Entity*>& tailtexts;
	static std::map<TextType, textfunc> textfuncmap;

	static std::map<uint32_t, std::function<void(void)>> stagefuncmap;

	static WipeTransition* transtition;

	//현재 게임정보
	static int CurStageIndex;

private:
	SDL_Window* window;
};

