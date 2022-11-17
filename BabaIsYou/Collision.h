#pragma once
#include <SDL.h>

class CollisionComponent;

//�̹����� �浹�� �浹ü�� �浹�� �����մϴ�
class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const CollisionComponent& recA, const CollisionComponent& recB);
};

