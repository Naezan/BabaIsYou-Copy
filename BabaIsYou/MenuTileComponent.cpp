#include "MenuTileComponent.h"
#include "TextureManager.h"
#include "AssetManager.h"

MenuTileComponent::MenuTileComponent(int srcRectX, int srcRectY, int x, int y, int tileSizeX, int tileSizeY, int tileScale, std::string TextureId,
	bool _isanimated, int _maxFrame, int _animPlaySleed)
{
		texture = Game::assetManager->GetTexture(TextureId);
		isanimated = _isanimated;
		maxFrame = _maxFrame;
		animPlaySpeed = _animPlaySleed;

		srcRect.x = srcRectX;
		srcRect.y = srcRectY;
		srcRect.w = tileSizeX;
		srcRect.h = tileSizeY;

		destRect.x = x;//TO DO ??
		destRect.y = y;
		destRect.w = tileSizeX * tileScale;
		destRect.h = tileSizeY * tileScale;

		position.x = static_cast<float>(x);
		position.y = static_cast<float>(y);
}

void MenuTileComponent::init()
{
	if (isanimated)
	{
		Animation idleAnimation = Animation(0, maxFrame, animPlaySpeed);
		animations.emplace("Idle", idleAnimation);
		animName = "Idle";

		play(animName);
	}
}

void MenuTileComponent::update(float deltaTime)
{
	if (isanimated)
	{
		srcRect.y = (24 + srcRect.h) * static_cast<int>((SDL_GetTicks() / animPlaySpeed) % maxFrame) + 24;
	}

	destRect.x = static_cast<int>(position.x);
	destRect.y = static_cast<int>(position.y);
}

void MenuTileComponent::render()
{
	TextureManager::DrawTexture(texture, srcRect, destRect, SDL_FLIP_NONE);
}

void MenuTileComponent::play(std::string _animName)
{
	maxFrame = animations[_animName].maxframe;
	animIndex = animations[_animName].index;
	animPlaySpeed = animations[_animName].playspeed;
	animName = _animName;
}