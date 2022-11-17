#include "Menu.h"
#include "Game.h"
#include "EntityManager.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "MenuTileComponent.h"
#include "FontManager.h"
#include <fstream>

extern EntityManager manager;

Menu::Menu(std::string _mapID, int _mapScale, int _mapTileX, int _mapTileY, int _tileScale, int _tilePixelSize)
	: mapID(_mapID), mapScale(_mapScale), mapTileSizeX(_mapTileX), mapTileSizeY(_mapTileY), tileScale(_tileScale), tileSize(_tilePixelSize)
{

}

Menu::~Menu()
{
	for (std::pair<SDL_Rect, SDL_Texture*> tex : textTextures)
	{
		SDL_DestroyTexture(tex.second);
	}
	textTextures.clear();
}

void Menu::LoadMenu()
{
	Entity& bg1(manager.addEntity());

	bg1.addComponent<MenuTileComponent>(912, 24, WIDTH_INTERVAL, HEIGHT_INVERVAL,
		mapTileSizeX, mapTileSizeY, mapScale, mapID);
	bg1.addLayerGroup(LayerMap);

	Entity& bg2(manager.addEntity());
	bg2.addComponent<MenuTileComponent>(1729, 24, WIDTH_INTERVAL, HEIGHT_INVERVAL,
		mapTileSizeX, mapTileSizeY, mapScale, mapID);
	bg2.addLayerGroup(LayerMap);
}

void Menu::LoadMenuObject(std::string path, int mapX, int mapY)
{
	char c, c1, c2;
	std::fstream mapFile;
	mapFile.open(path);

	static std::vector<std::string> mapIDs = { "obstacle","staticobject" };

	int resX, resY, layerIndex, num, stageIndex;
	for (std::string id : mapIDs)
	{
		mapID = id;
		mapFile.get(c);//출력할 개수
		mapFile.ignore();//스페이스바


		for (int i = 0; i < atoi(&c); ++i)
		{
			//레이어
			mapFile.get(c1);
			mapFile.get(c2);
			layerIndex = atoi(&c1) * 10 + atoi(&c2);
			mapFile.ignore();//콤마

			//개수
			mapFile.get(c1);
			mapFile.get(c2);
			num = atoi(&c1) * 10 + atoi(&c2);
			mapFile.ignore();//콤마
			for (int j = 0; j < num; ++j)
			{
				stageIndex = -1;
				//스테이지타일이라면
				if (id == "staticobject")
				{
					mapFile.get(c1);
					mapFile.get(c2);
					stageIndex = atoi(&c1) * 10 + atoi(&c2);
					mapFile.ignore();//콤마
				}

				//포지션
				mapFile.get(c1);
				mapFile.get(c2);
				int posX = atoi(&c1) * 10 + atoi(&c2);
				mapFile.get(c1);
				mapFile.get(c2);
				int posY = atoi(&c1) * 10 + atoi(&c2);
				mapFile.ignore();//콤마

				//리소스위치
				mapFile.get(c1);
				mapFile.get(c2);
				resX = (atoi(&c1) * 10 + atoi(&c2)) * tileSize;//a를 추출하는 방법 : a * t + a + 1 -> a(t + 1) + 1
				int deltaX = atoi(&c1) * 10 + atoi(&c2) + 1;
				mapFile.get(c1);
				mapFile.get(c2);
				resY = (atoi(&c1) * 10 + atoi(&c2)) * tileSize;
				int deltaY = atoi(&c1) * 10 + atoi(&c2) + 1;

				mapFile.ignore();//콤마

				AddTile(resX + deltaX, resY + deltaY, posX * tileScale * tileSize + WIDTH_INTERVAL, posY * tileScale * tileSize + HEIGHT_INVERVAL,
					true, static_cast<LayerGroup>(layerIndex), stageIndex);
			}
		}

		mapFile.ignore();//스페이스바
	}

	mapFile.close();
}

void Menu::LoadCollisionMap(std::string path, int mapX, int mapY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				Entity& tcol(manager.addEntity());
				tcol.addComponent<TransformComponent>(static_cast<float>(x * PIXEL_SIZE + WIDTH_INTERVAL), static_cast<float>(y * PIXEL_SIZE + HEIGHT_INVERVAL), PIXEL_SIZE, PIXEL_SIZE);
				tcol.addComponent<CollisionComponent>("menuCollider", x * PIXEL_SIZE + WIDTH_INTERVAL, y * PIXEL_SIZE + HEIGHT_INVERVAL, PIXEL_SIZE, PIXEL_SIZE);
				tcol.getComponent<CollisionComponent>()->colType = CollisionType::Block;
				tcol.addLayerGroup(LayerCollider);
			}
			mapFile.ignore();
		}
		mapFile.ignore();
	}

	mapFile.close();

	Game::StopObject = &manager.getLayerGroup(LayerCollider);
}

void Menu::AddTile(int srcX, int srcY, int xpos, int ypos, bool isAnimate, LayerGroup group, int stageIndex)
{
	Entity& tile(manager.addEntity());

	if (isAnimate)
	{
		tile.addComponent<TransformComponent>(static_cast<float>(xpos), static_cast<float>(ypos), PIXEL_SIZE, PIXEL_SIZE);
		tile.addComponent<SpriteComponent>(mapID, 3, 200, (srcX - 1) / (tileSize + 1), (srcY - 1) / (tileSize + 1));
		tile.addComponent<CollisionComponent>(ToString(group), xpos, ypos, PIXEL_SIZE, PIXEL_SIZE);
		tile.addLayerGroup(group);

		if (stageIndex != -1)
		{
			tile.setStageIndex(stageIndex);
			std::string stagetext;
			if (stageIndex < 10)
			{
				stagetext.push_back('0');
			}
			stagetext.append(std::to_string(stageIndex));
			std::pair<SDL_Rect, SDL_Texture*> fontinfo = FontManager::LoadFont(stagetext);
			SDL_Texture* texture = fontinfo.second;
			SDL_Rect textRect = fontinfo.first;
			textRect.x = xpos + 4;
			textRect.y = ypos + 1;

			textTextures.push_back(std::make_pair(textRect, texture));
		}
	}
}

void Menu::DrawStageText()
{
	for (std::pair<SDL_Rect, SDL_Texture*> p : textTextures)
	{
		FontManager::DrawFont(p.second, p.first);
	}
}