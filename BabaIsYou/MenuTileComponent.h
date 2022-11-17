#pragma once
#include "Component.h"
#include "Game.h"
#include "Vector2D.h"
#include "Animation.h"
#include <map>

struct Animation;

class MenuTileComponent :
	public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;
	bool isanimated;
	int maxFrame;
	int animPlaySpeed;
	std::string animName;
	int animIndex;

	std::map<std::string, Animation> animations;

	MenuTileComponent(int srcRectX, int srcRectY, int x, int y, int tileSizeX, int tileSizeY, int tileScale, std::string TextureId,
	bool _isanimated = true, int _maxFrame = 3, int _animPlaySleed = 200);

	~MenuTileComponent() {
		//SDL_DestroyTexture(texture);
	}

	void init() override;
	void update(float deltaTime) override;
	void render() override;

	void play(std::string _animName);
};

