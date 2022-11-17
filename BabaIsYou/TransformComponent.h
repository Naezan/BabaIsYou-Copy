#pragma once

#include "Component.h"
#include "Vector2D.h"

class TransformComponent :
	public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int height = 24;
	int width = 24;
	int scale = 1;

	Vector2D beginPos;

	TransformComponent()
	{
		position.Zero();
		height = 0;
		width = 0;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
		height = 0;
		width = 0;
		scale = 1;
	}
	TransformComponent(float x, float y, int h, int w, int s = 1)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}

	void init() override;
	void update(float deltaTime) override;
};

