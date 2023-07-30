#pragma once

#include <vector>
#include <bitset>
#include <list>
#include <functional>
#include "Component.h"
#include "Constants.h"

class Component;
class EntityManager;
class Vector2D;

inline std::size_t GetNewComponentID()
{
	//�ּ� ȣ�� ���Ŀ��� �ǳʶڴ�
	static std::size_t typeID = 0;
	return typeID++;
}

template <typename T>
inline std::size_t GetComponentID()
{
	//T�� �⺻ Ŭ������ ComponentŬ�������� �ƴ��� �Ǵ��մϴ�.
	static_assert (std::is_base_of<Component, T>::value, "type error");
	//T(������Ʈ Ÿ��)���� ���� 1�� ȣ��˴ϴ�.
	static std::size_t type = GetNewComponentID();
	return type;
}

//constexpr�����ڴ� ���Ÿ���Ӱ� ���ÿ� �����ϴܰ迡�� ������ �ʱ�ȭ������Ѵ�
//constexpr std::size_t MAXCOMPONENTS = 256;
//constexpr std::size_t MAXLAYERGROUP = 32;

//�ϳ��� ��ƼƼ�� ������ �ִ� ������Ʈ���� ��Ʈ��?�� ���մϴ�
//��Ʈ�� ���ؼ� ������Ʈ�� �ִ��� ������ üũ�� �� �ֽ��ϴ�
using ComponentBitSet = std::bitset<MAXCOMPONENTS>;
//�������� ���̾ �������ݴϴ�.
using LayerGroupBitSet = std::bitset<MAXLAYERGROUP>;
//������Ʈ�� �����ö� ����մϴ�.
using ComponentVector = std::vector<Component*>;

class Entity
{
private:
	EntityManager& manager;
	bool active = true;
	std::vector<Component*> components;

	ComponentVector componentVector;
	ComponentBitSet componentBitSet;
	LayerGroupBitSet layerGroupBitSet;

	//�ؽ�Ʈ�� ����մϴ�? �ý�Ʈ�� Ŭ������ ���� ������ ������
	LayerGroup managinglayer = LayerEnd;
	TextType textType = Default;

	//���������� Ÿ�Ͽ��� ����մϴ�.
	int stageIndex = -1;

public:
	Entity(EntityManager& _manager);// : manager(_manager)
	~Entity();

	void init();
	void update(float deltaTime);
	void render();
	bool isActive() const { return active; }
	void destroy();

	EntityManager& GetEntityManager() { return manager; }

	void initComponent();

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... args)
	{
		T* component(new T(std::forward<TArgs>(args)...));
		component->componentOwner = this;
		components.emplace_back(component);
		//������ƮID�� �߰��մϴ�
		componentVector[GetComponentID<T>()] = component;
		componentBitSet[GetComponentID<T>()] = true;

		component->init();
		return *component;
	}

	template<typename T>
	void removeComponent()
	{
		if (hasComponent<T>())
		{
			std::vector<Component*>::iterator iter = components.begin();
			for (iter; iter != components.end(); ++iter)
			{
				if (*iter == getComponent<T>())
				{
					components.erase(iter);
					break;
				}
			}
			componentVector[GetComponentID<T>()] = nullptr;
			componentBitSet[GetComponentID<T>()] = false;
		}
	}

	template<typename T>
	T* getComponent() const
	{
		//���⼭ auto�� ������Ʈ�迭�� Ư�� ������Ʈ ������ Ÿ���� ������ �ֽ��ϴ�.
		auto ptr(componentVector[GetComponentID<T>()]);
		return static_cast<T*>(ptr);
	}

	template<typename T> bool hasComponent() const
	{
		return componentBitSet[GetComponentID<T>()];
	}

	void destroyComponents();

	bool hasLayerGroup(std::size_t _layerID) { return layerGroupBitSet[_layerID]; }

	void addLayerGroup(std::size_t _layerID);
	void deleteLayerGroup(std::size_t _layerID) { layerGroupBitSet[_layerID] = false; }
	void setManagingLayer(LayerGroup group);
	LayerGroup getManagingLayer() { return managinglayer; }
	void setTextType(TextType type);
	TextType getTextType() { return textType; }
	void setStageIndex(int index);
	int getStageIndex() { return stageIndex; }

	std::vector<Entity*> FindNextPushObject(Vector2D position, Vector2D velocity, int& index);

	std::function<void()> collisionEvent;
};

