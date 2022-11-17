#include "Map.h"
#include "Game.h"
#include "EntityManager.h"
#include "TileComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include <fstream>

//
extern EntityManager manager;

Map::Map(std::string _mapID, int _mapscale, int _tilesize)
	: mapID(_mapID), mapScale(_mapscale), tileSize(_tilesize)
{
	scaledSize = _mapscale * _tilesize;
}

Map::~Map()
{
}

void Map::LoadBG()
{
	AddTile(0, 0, 0, 0, false, LayerMap);
}

void Map::LoadMap(std::string path, int mapX, int mapY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	//맵 리소스
	int resX, resY;
	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			mapFile.get(c);
			resY = atoi(&c) * tileSize;
			mapFile.get(c);
			resX = atoi(&c) * tileSize;
			AddTile(resX, resY, x * scaledSize + WIDTH_INTERVAL, y * scaledSize + HEIGHT_INVERVAL, false, LayerMap);
			mapFile.ignore();
		}
	}

	mapFile.ignore();//스페이스바

	mapFile.close();
}

void Map::LoadObject(std::string path, int mapX, int mapY)
{
	char c, c1, c2;
	std::fstream mapFile;
	mapFile.open(path);

	static std::vector<std::string> mapIDs = { "obstacle","staticobject","dynamicobject","text","playable" };

	int resX, resY, layerIndex, num;
	LayerGroup processLayerIndex = LayerEnd;
	TextType textType = TextType::Default;
	for (std::string id : mapIDs)
	{
		mapID = id;
		mapFile.get(c);//출력할 개수
		mapFile.ignore();//스페이스바

		//layer, num, (xy, tilextiley)
		//layer, num, (prolayer, xy, tilextiley)
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
				if (layerIndex == 9)
				{
					//processLayerIndex
					mapFile.get(c1);
					mapFile.get(c2);
					processLayerIndex = static_cast<LayerGroup>(atoi(&c1) * 10 + atoi(&c2));
					mapFile.ignore();//콤마
				}
				else if (layerIndex == 11)
				{
					//TextType (you, stop, win, push)
					mapFile.get(c1);
					mapFile.get(c2);
					textType = static_cast<TextType>(atoi(&c1) * 10 + atoi(&c2));
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

				AddTile(resX + deltaX, resY + deltaY, posX * scaledSize + WIDTH_INTERVAL, posY * scaledSize + HEIGHT_INVERVAL,
					true, static_cast<LayerGroup>(layerIndex), processLayerIndex, textType);
			}
		}

		mapFile.ignore();//스페이스바
	}

	mapFile.close();

	//장애물 34 65
	//정적오브젝트 34 35
	//동적오브젝트 34 47
	//텍스트 14 74 + (18), 14 29, 13 14
	//플레이어블 오브젝트
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos, bool isAnimate, LayerGroup group, LayerGroup managinglayer, TextType textType)
{
	Entity& tile(manager.addEntity());

	//애니메이션이 있다면 스프라이트 컴포넌트를
	//애니메이션이 없다면 타일 컴포넌트를 추가
	if (isAnimate)
	{
		//실제 배치할 픽셀 위치
		tile.addComponent<TransformComponent>(static_cast<float>(xpos), static_cast<float>(ypos), PIXEL_SIZE, PIXEL_SIZE);
		//스프라이트 위치
		tile.addComponent<SpriteComponent>(mapID, 3, 200, (srcX - 1) / (tileSize + 1), (srcY - 1) / (tileSize + 1));
		tile.addComponent<CollisionComponent>(ToString(group), xpos, ypos, PIXEL_SIZE, PIXEL_SIZE);
		tile.addLayerGroup(group);
		//만약 headtext라면 headtext가 관리할 레이어 추가?
		if (managinglayer != LayerEnd)
		{
			tile.setManagingLayer(managinglayer);
		}
		if (textType != Default)
		{
			tile.setTextType(textType);
		}
	}
	else
	{
		tile.addComponent<TileComponent>(srcX, srcY,
			xpos, ypos,
			tileSize, mapScale,
			mapID);
		//타일을 레이어 그룹에 추가합니다.
		tile.addLayerGroup(group);
	}
}
