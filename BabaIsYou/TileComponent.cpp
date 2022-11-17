#include "TileComponent.h"
#include "Animation.h"

void TileComponent::update(float deltaTime)
{
	destRect.x = static_cast<int>(position.x/* - Game::camera.x*/);
	destRect.y = static_cast<int>(position.y/* - Game::camera.y*/);
}

void TileComponent::render()
{
	TextureManager::DrawTexture(texture, srcRect, destRect, SDL_FLIP_NONE);
}
