#pragma once
#include "Game.h"
#include "Component.h"

class TransformComponent;
class SpriteComponent;

//플레이어만 소유할 수 있는 컴포넌트 입니다.
class InputComponent :
	public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override;
	void update(float deltaTime) override;
};

