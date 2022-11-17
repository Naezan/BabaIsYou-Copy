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

	//�� ���ҽ�
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

	mapFile.ignore();//�����̽���

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
		mapFile.get(c);//����� ����
		mapFile.ignore();//�����̽���

		//layer, num, (xy, tilextiley)
		//layer, num, (prolayer, xy, tilextiley)
		for (int i = 0; i < atoi(&c); ++i)
		{
			//���̾�
			mapFile.get(c1);
			mapFile.get(c2);
			layerIndex = atoi(&c1) * 10 + atoi(&c2);
			mapFile.ignore();//�޸�

			//����
			mapFile.get(c1);
			mapFile.get(c2);
			num = atoi(&c1) * 10 + atoi(&c2);
			mapFile.ignore();//�޸�
			for (int j = 0; j < num; ++j)
			{
				if (layerIndex == 9)
				{
					//processLayerIndex
					mapFile.get(c1);
					mapFile.get(c2);
					processLayerIndex = static_cast<LayerGroup>(atoi(&c1) * 10 + atoi(&c2));
					mapFile.ignore();//�޸�
				}
				else if (layerIndex == 11)
				{
					//TextType (you, stop, win, push)
					mapFile.get(c1);
					mapFile.get(c2);
					textType = static_cast<TextType>(atoi(&c1) * 10 + atoi(&c2));
					mapFile.ignore();//�޸�
				}

				//������
				mapFile.get(c1);
				mapFile.get(c2);
				int posX = atoi(&c1) * 10 + atoi(&c2);
				mapFile.get(c1);
				mapFile.get(c2);
				int posY = atoi(&c1) * 10 + atoi(&c2);
				mapFile.ignore();//�޸�

				//���ҽ���ġ
				mapFile.get(c1);
				mapFile.get(c2);
				resX = (atoi(&c1) * 10 + atoi(&c2)) * tileSize;//a�� �����ϴ� ��� : a * t + a + 1 -> a(t + 1) + 1
				int deltaX = atoi(&c1) * 10 + atoi(&c2) + 1;
				mapFile.get(c1);
				mapFile.get(c2);
				resY = (atoi(&c1) * 10 + atoi(&c2)) * tileSize;
				int deltaY = atoi(&c1) * 10 + atoi(&c2) + 1;

				mapFile.ignore();//�޸�

				AddTile(resX + deltaX, resY + deltaY, posX * scaledSize + WIDTH_INTERVAL, posY * scaledSize + HEIGHT_INVERVAL,
					true, static_cast<LayerGroup>(layerIndex), processLayerIndex, textType);
			}
		}

		mapFile.ignore();//�����̽���
	}

	mapFile.close();

	//��ֹ� 34 65
	//����������Ʈ 34 35
	//����������Ʈ 34 47
	//�ؽ�Ʈ 14 74 + (18), 14 29, 13 14
	//�÷��̾�� ������Ʈ
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos, bool isAnimate, LayerGroup group, LayerGroup managinglayer, TextType textType)
{
	Entity& tile(manager.addEntity());

	//�ִϸ��̼��� �ִٸ� ��������Ʈ ������Ʈ��
	//�ִϸ��̼��� ���ٸ� Ÿ�� ������Ʈ�� �߰�
	if (isAnimate)
	{
		//���� ��ġ�� �ȼ� ��ġ
		tile.addComponent<TransformComponent>(static_cast<float>(xpos), static_cast<float>(ypos), PIXEL_SIZE, PIXEL_SIZE);
		//��������Ʈ ��ġ
		tile.addComponent<SpriteComponent>(mapID, 3, 200, (srcX - 1) / (tileSize + 1), (srcY - 1) / (tileSize + 1));
		tile.addComponent<CollisionComponent>(ToString(group), xpos, ypos, PIXEL_SIZE, PIXEL_SIZE);
		tile.addLayerGroup(group);
		//���� headtext��� headtext�� ������ ���̾� �߰�?
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
		//Ÿ���� ���̾� �׷쿡 �߰��մϴ�.
		tile.addLayerGroup(group);
	}
}
