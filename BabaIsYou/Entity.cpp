#include "Entity.h"
#include "EntityManager.h"
#include "Game.h"
#include "TransformComponent.h"

Entity::Entity(EntityManager& _manager) : manager(_manager)
{
	componentVector.resize(MAXCOMPONENTS);
}

Entity::~Entity()
{
}

void Entity::update(float deltaTime)
{
	for (auto& component : components)
	{
		component->update(deltaTime);
	}
}

void Entity::render()
{
	for (auto& component : components)
	{
		component->render();
	}
}

void Entity::destroy()
{
	active = false;
}

void Entity::initComponent()
{
	for (auto comp : components)
	{
		comp->init();
	}
}

void Entity::destroyComponents()
{
	for (auto comp : components)
	{
		if (comp != nullptr)
		{
			delete comp;
		}
	}
	components.clear();
	componentVector.clear();
}

void Entity::addLayerGroup(std::size_t _layerID)
{
	layerGroupBitSet[_layerID] = true;
	//Add To LayerGroup
	manager.AddToLayerGroup(this, _layerID);
}

void Entity::setManagingLayer(LayerGroup group)
{
	managinglayer = group;
}

void Entity::setTextType(TextType type)
{
	textType = type;
}

void Entity::setStageIndex(int index)
{
	stageIndex = index;
}


std::vector<Entity*> Entity::FindNextPushObject(Vector2D position, Vector2D velocity, int& index)
{
	std::vector<Entity*> objlist;
	//int index = 1;
	bool isreset = false;

	if (Game::PushObject.empty())
	{
		return objlist;
	}
	
	Vector2D pos = position + (velocity * PIXEL_SIZE * index);
	std::vector<Entity*>::iterator iter = Game::PushObject.begin();
	for (iter; iter != Game::PushObject.end(); ++iter)
	{
		//초기값 탐색조건
		if (isreset)
		{
			--iter;
			isreset = false;
		}

		//만약에 다음에 오는 오브젝트를 찾았다면 그 오브젝트를 벡터에 추가해주고 그 다음블록이 될 오브젝트를 찾습니다.
		if ((*iter)->getComponent<TransformComponent>()->position == pos)
		{
			objlist.push_back(*iter);
			++index;
			pos = position + (velocity * PIXEL_SIZE * index);
			iter = Game::PushObject.begin();
			isreset = true;
			continue;
		}
		//하나라도 중간에 오는 오브젝트를 찾지 못하면 for문을 빠져나갑니다.
	}

	return objlist;
}