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
		//�ʱⰪ Ž������
		if (isreset)
		{
			--iter;
			isreset = false;
		}

		//���࿡ ������ ���� ������Ʈ�� ã�Ҵٸ� �� ������Ʈ�� ���Ϳ� �߰����ְ� �� ��������� �� ������Ʈ�� ã���ϴ�.
		if ((*iter)->getComponent<TransformComponent>()->position == pos)
		{
			objlist.push_back(*iter);
			++index;
			pos = position + (velocity * PIXEL_SIZE * index);
			iter = Game::PushObject.begin();
			isreset = true;
			continue;
		}
		//�ϳ��� �߰��� ���� ������Ʈ�� ã�� ���ϸ� for���� ���������ϴ�.
	}

	return objlist;
}