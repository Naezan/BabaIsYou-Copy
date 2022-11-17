#pragma once
#include <string>
#include "Constants.h"

class Map
{
public:
	Map(std::string _mapID, int _mapscale, int _tilesize);
	~Map();

	void LoadBG();
	void LoadMap(std::string path, int mapX, int mapY);
	void LoadObject(std::string path, int mapX, int mapY);
	void AddTile(int srcX, int srcY, int xpos, int ypos, bool isAnimate = false, 
	LayerGroup group = LayerMap, LayerGroup managinglayer = LayerEnd, TextType textType = TextType::Default);

private:
	std::string mapID;
	int mapScale;
	int tileSize;
	int scaledSize;
};

