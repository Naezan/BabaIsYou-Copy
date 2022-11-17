#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2D.h"
#include <functional>

enum class TRANS_TYPE
{
	OUT, IN
};

class WipeTransition
{
private:
	Vector2D centerPos;

	int height;
	int width;
	int scale;
	int speed;

	SDL_Rect dest;
	SDL_Texture* textureMask;

public:
	WipeTransition(int _speed);
	~WipeTransition();

	void playTransition(TRANS_TYPE type);
	void updateTransition(float deltaTime);
	void render();
	void setTransition(TRANS_TYPE type);

	bool isTransEnd = false;
	std::function<void(void)> transitionInEvent;
	std::function<void(void)> transitionOutEvent;
};

