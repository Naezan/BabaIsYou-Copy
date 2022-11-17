#include "CollisionComponent.h"
#include "TransformComponent.h"
#include "EntityManager.h"
#include "TextureManager.h"

void CollisionComponent::init()
{
	if (!componentOwner->hasComponent<TransformComponent>())
	{
		componentOwner->addComponent<TransformComponent>();
	}

	if (componentOwner->hasComponent<TransformComponent>())
	{
		transform = componentOwner->getComponent<TransformComponent>();

		texture = TextureManager::LoadTexture("assets/ColTex.png", 255, 255, 255);
		sourceRect = { 0, 0, PIXEL_SIZE, PIXEL_SIZE };
		//sourceRect = { 0, 0, transform->width, transform->height };
		destRect = { collider.x, collider.y, collider.w, collider.h };
	}
}

void CollisionComponent::update(float deltaTime)
{
	//TO DO Ignore MapTile
	
	collider.x = static_cast<int>(transform->position.x + extraSize);
	collider.y = static_cast<int>(transform->position.y + extraSize);
	collider.w = sourceRect.w * transform->scale;
	collider.h = sourceRect.h * transform->scale;
	destRect.x = collider.x;
	destRect.y = collider.y;
}

void CollisionComponent::render()
{
	//TO DO
	//TextureManager::DrawTexture(texture, sourceRect, destRect, SDL_FLIP_NONE);
}


bool CollisionComponent::CheckCollision(CollisionComponent* targetCol)
{
	for (std::list<CollisionComponent*>::iterator iter = CollisionList.begin(); iter != CollisionList.end(); ++iter)
	{
		if (*iter == targetCol)
		{
			return true;
		}
	}

	return false;
}

void CollisionComponent::EraseCollision(CollisionComponent* targetCol)
{
	for (std::list<CollisionComponent*>::iterator iter = CollisionList.begin(); iter != CollisionList.end(); ++iter)
	{
		if (*iter == targetCol)
		{
			CollisionList.erase(iter);
			return;
		}
	}
}