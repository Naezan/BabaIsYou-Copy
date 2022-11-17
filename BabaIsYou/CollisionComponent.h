#pragma once
#include"Component.h"
#include "Game.h"
#include <list>

class TransformComponent;

class CollisionComponent :
	public Component
{
public:
	SDL_Rect collider;
	std::string tag;
	CollisionType colType = CollisionType::Ignore;
	CollisionState CurColState = CollisionState::NotOverlapping;

	SDL_Texture* texture;//for rendering
	SDL_Rect sourceRect, destRect;

	TransformComponent* transform;

	std::list<CollisionComponent*> CollisionList;
	int extraSize;

	CollisionComponent(std::string _tag)
	{
		tag = _tag;
		collider.w = PIXEL_SIZE;
		collider.h = PIXEL_SIZE;
	}

	CollisionComponent(std::string _tag, int _w, int _h, int extrasize = 0)
	{
		tag = _tag;
		collider.w = _w;
		collider.h = _h;
		extraSize = extrasize;
	}

	CollisionComponent(std::string _tag, int _x, int _y, int _w, int _h)
	{
		tag = _tag;
		collider = { _x, _y, _w, _h };
		extraSize = 0;
	}

	void init() override;
	void update(float deltaTime) override;
	void render() override;

	bool CheckCollision(CollisionComponent* targetCol);
	void EraseCollision(CollisionComponent* targetCol);
};

