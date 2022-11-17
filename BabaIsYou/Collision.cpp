#include "Collision.h"
#include "CollisionComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (recA.x + recA.w > recB.x &&//resA오른쪽
		recB.x + recB.w > recA.x &&//resA왼쪽
		recA.y + recA.h > recB.y &&//resA아래
		recB.y + recB.h > recA.y	//resA위
		)
	{
		return true;
	}

	return false;
}

bool Collision::AABB(const CollisionComponent& recA, const CollisionComponent& recB)
{
	if (AABB(recA.collider, recB.collider))
	{
		return true;
	}

	return false;
}
