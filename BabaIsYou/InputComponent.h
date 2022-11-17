#pragma once
#include "Game.h"
#include "Component.h"

class TransformComponent;
class SpriteComponent;

//�÷��̾ ������ �� �ִ� ������Ʈ �Դϴ�.
class InputComponent :
	public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override;
	void update(float deltaTime) override;
};

