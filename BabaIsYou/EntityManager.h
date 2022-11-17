#pragma once
#include "Entity.h"
#include <vector>
#include <array>
#include <iostream>
#include <memory>

class EntityManager
{
private:
	//엔티티는 고유한 포인터 타입을 가진다
	std::vector<std::unique_ptr<Entity>> entities;
	//엔티티끼리 레이어로 묶여있습니다.
	std::array<std::vector<Entity*>, MAXLAYERGROUP> layerGroupEntities;

public:
	void update(float deltaTime);
	void render();
	bool HasNoEntities() const;
	void DestroyInactiveEntities();
	void ClearAllEntity();
	std::vector<Entity*> GetEntitiesByLayer(LayerGroup layer) const;
	Entity& addEntity();

	void AddToLayerGroup(Entity* _entity, std::size_t _layerID);
	std::vector<Entity*>& getLayerGroup(std::size_t _layerID);

	void CheckCollisions() const;
};

