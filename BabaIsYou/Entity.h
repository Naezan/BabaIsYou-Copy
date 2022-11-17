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

//호출될때마다 1씩 증가시켜준다
inline std::size_t GetNewComponentID()
{
	//unsinged int의 최솟값 static으로 선언해서 이후에는 건너뛴다
	static std::size_t typeID = 0u;
	return typeID++;
}

//noexcept 이 키워드는 예외를 발생시키지 않는다고 컴파일러에게 명시해준다
template <typename T>
inline std::size_t GetComponentID() noexcept
{
	//T의 기본 클래스가 Component클래스인지 아닌지 판단합니다.
	static_assert (std::is_base_of<Component, T>::value, "");
	//T마다 최초 1번 초기화 되며 GetNewComponentID에는 Add할때 지정된 값을 가지고있다.
	//GetNewComponentID는 2번호출되지 않는다.
	static std::size_t type = GetNewComponentID();
	return type;
}

//constexpr지정자는 상수타입임과 동시에 컴파일단계에서 무조건 초기화해줘야한다
//constexpr std::size_t MAXCOMPONENTS = 256;
//constexpr std::size_t MAXLAYERGROUP = 32;

//하나의 엔티티가 가지고 있는 컴포넌트들의 비트값?을 뜻합니다
//비트로 비교해서 컴포넌트가 있는지 없는지 체크할 수 있습니다
using ComponentBitSet = std::bitset<MAXCOMPONENTS>;
//렌더링할 레이어를 구분해줍니다.
using LayerGroupBitSet = std::bitset<MAXLAYERGROUP>;
//컴포넌트를 가져올때 사용합니다.
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

	//텍스트가 사용합니다? 택스트용 클래스를 따로 만들어야 할지도
	LayerGroup managinglayer = LayerEnd;
	TextType textType = Default;

	//스테이지용 타일에서 사용합니다.
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
		//컴포넌트ID를 추가합니다
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
		//여기서 auto는 컴포넌트배열의 특정 컴포넌트 포인터 타입을 가지고 있습니다.
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

