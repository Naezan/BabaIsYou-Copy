#pragma once
#include <SDL.h>

class CollisionComponent;

//이미지의 충돌과 충돌체의 충돌을 관리합니다
class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const CollisionComponent& recA, const CollisionComponent& recB);
};

