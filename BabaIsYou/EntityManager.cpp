#include "EntityManager.h"
#include "CollisionComponent.h"
#include "Collision.h"
#include "TransformComponent.h"
#include "Vector2D.h"

void EntityManager::update(float deltaTime)
{
	for (auto& entity : entities)
	{
		entity->update(deltaTime);
	}
	DestroyInactiveEntities();
}

void EntityManager::render()
{
	for (int layeridex = 0; layeridex < MAXLAYERGROUP; ++layeridex)
	{
		for (auto& entity : GetEntitiesByLayer(static_cast<LayerGroup>(layeridex)))
		{
			entity->render();
		}
	}
}

bool EntityManager::HasNoEntities() const
{
	return entities.size() == 0;
}

void EntityManager::DestroyInactiveEntities()
{
	//remove_if는 조건에 맞게 제거하고 새로운 end iterator를 반환합니다. 
	//이때의 end itorator는 마지막배열의 다음주솟값을 가리킵니다.
	//새로운 end부터 낡은end까지의 값을 제거합니다.
	//최종적으로 활성화되지 않은 녀석들을 제거해줍니다.
	for (unsigned int i(0u); i < MAXLAYERGROUP; ++i)
	{
		auto& layer(layerGroupEntities[i]);
		//레이어에서 활성화되지 않았거나
		//현재 엔티티가 레이어그룹을 소유하고 있지 않은오브젝트들을 제거합니다.
		layer.erase(std::remove_if(
			std::begin(layer), std::end(layer),
			[i](Entity* _entity)
			{
				if (!_entity->isActive() || !_entity->hasLayerGroup(i))
				{
					_entity->destroyComponents();
					return true;
				}
				else
					return false;
			}),
			std::end(layer));
	}

	entities.erase(std::remove_if(
		std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity>& entity)
		{
			//entities의 요소를 체크합니다
			if (!entity->isActive())
			{
				entity->destroyComponents();
				return true;
			}
			else
			{
				return false;
			}
		}),
		std::end(entities));
}

void EntityManager::ClearAllEntity()
{
	for (auto& en : entities)
	{
		en->destroy();
	}
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerGroup layer) const
{
	std::vector<Entity*> layeredEntities;
	for (auto& entity : entities)
	{
		if (entity->hasLayerGroup(layer))
		{
			layeredEntities.emplace_back(entity.get());
		}
	}

	return layeredEntities;
}

Entity& EntityManager::addEntity()
{
	Entity* entity = new Entity(*this);
	std::unique_ptr<Entity> uentity{ entity };
	entities.emplace_back(std::move(uentity));
	return *entity;
}

void EntityManager::AddToLayerGroup(Entity* _entity, std::size_t _layerID)
{
	layerGroupEntities[_layerID].emplace_back(_entity);
}

std::vector<Entity*>& EntityManager::getLayerGroup(std::size_t _layerID)
{
	return layerGroupEntities[_layerID];
}

void EntityManager::CheckCollisions() const
{
	for (int i = 0; i < entities.size() - 1; ++i)
	{
		auto& triggerEntity = entities[i];
		if (triggerEntity->hasComponent<CollisionComponent>())
		{
			CollisionComponent* triggerCollider = triggerEntity->getComponent<CollisionComponent>();
			for (int j = i + 1; j < entities.size(); ++j)
			{
				auto& triggeredEntity = entities[j];
				if (triggerEntity != triggeredEntity && triggeredEntity->hasComponent<CollisionComponent>())
				{
					CollisionComponent* triggeredCollider = triggeredEntity->getComponent<CollisionComponent>();
					if (Collision::AABB(*triggerCollider, *triggeredCollider))
					{
						if (triggerCollider->colType == CollisionType::Overlap && triggeredCollider->colType == CollisionType::Overlap)
						{
							if (!triggerCollider->CheckCollision(triggeredCollider))
							{
								//둘다 overlap이라면 overlap충돌을 처리한다
								triggerCollider->CurColState = CollisionState::BeginOverlap;
								triggeredCollider->CurColState = CollisionState::BeginOverlap;
								//서로에게 충돌했다는 정보를 넘겨준다
								triggerCollider->CollisionList.push_back(triggeredCollider);
								triggeredCollider->CollisionList.push_back(triggerCollider);

								//triggerEntity->collisionEvent();
								//triggeredEntity->collisionEvent();
								//std::cout << triggerCollider->tag << " BeginOverlap " << triggeredCollider->tag << std::endl;
								//std::cout << "BeginOverlap" << std::endl;
							}
							else
							{
								triggerCollider->CurColState = CollisionState::Overlapping;
								triggeredCollider->CurColState = CollisionState::Overlapping;
								triggerEntity->collisionEvent();
								triggeredEntity->collisionEvent();
								//std::cout << "Overlapping" << std::endl;
							}
						}
					}
					else if (triggerCollider->CheckCollision(triggeredCollider))
					{
						triggerCollider->CurColState = CollisionState::EndOverlap;
						triggeredCollider->CurColState = CollisionState::EndOverlap;
						triggerCollider->EraseCollision(triggeredCollider);
						triggeredCollider->EraseCollision(triggerCollider);
						//std::cout << triggerCollider->tag << " EndOverlap " << triggeredCollider->tag << std::endl;
						//std::cout << "EndOverlap" << std::endl;
					}
				}
			}
		}
	}

	//Ignore
}
