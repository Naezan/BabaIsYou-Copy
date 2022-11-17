#pragma once
#include "SDL.h"
#include "Constants.h"
#include <string>
#include <vector>

class Menu
{
public:
	Menu(std::string _mapID, int _mapScale = 1, int _mapTileX = 793, int _mapTileY = 432, int _tileScale = 1, int _tilePixelSize = 24);
	~Menu();

	void LoadMenu();
	void LoadMenuObject(std::string path, int mapX, int mapY);
	void LoadCollisionMap(std::string path, int mapX, int mapY);
	void AddTile(int srcX, int srcY, int xpos, int ypos, bool isAnimate = false,
		LayerGroup group = LayerMap, int stageIndex = -1);
	void DrawStageText();

	std::vector<std::pair<SDL_Rect, SDL_Texture*>> textTextures;

private:
	std::string mapID;
	int mapScale;
	int mapTileSizeX;
	int mapTileSizeY;
	int tileSize;
	int tileScale;
};

