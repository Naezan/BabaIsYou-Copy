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
class Vector2D;

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

	void ClearStage(int stageIndex = -1);
	void ClearStageMap();
	void LoadBackGround();
	void LoadMenu();
	void CreateMenu();

	//�������� �Լ� ���ε� ���ϼ��� ���� �Ű������� ������ �ʽ��ϴ�.
	void LoadStage0();
	void LoadStage1();


	void SetInitialSentence(std::vector<std::pair<Vector2D, LayerGroup>>& textgroup);
	void SetLastSentence(std::vector<std::pair<Vector2D, LayerGroup>>& textgroup);

	void SetPushTextObject();
	void SetPlayer(float posX, float posY, int meshHeight, int meshWidth,
		const char* spriteName, int frameCount, int animSpeed, int spriteX, int spriteY, bool hasDir, bool isPlayer,
		const char* collisionName, int extraCollisionSize, size_t layerID);

	static SDL_Event event;
	static SDL_Renderer* renderer;
	static TTF_Font* font;
	static AssetManager* assetManager;
	static bool isRunning;
	static std::vector<Entity*>* StopObject;
	static std::vector<Entity*> PushObject;
	static float DeltaSecond;

	//�ؽ�Ʈ
	static std::vector<Entity*>& headtexts;
	static std::vector<Entity*>& verbtexts;
	static std::vector<Entity*>& tailtexts;
	static std::map<TextType, textfunc> textfuncmap;

	static std::map<uint32_t, std::function<void(void)>> stagefuncmap;

	static WipeTransition* transtition;

	//���� ��������
	static int CurStageIndex;

private:
	SDL_Window* window;
};

