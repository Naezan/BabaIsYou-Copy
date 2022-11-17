#pragma once
#include "Game.h"
#include "Component.h"
#include "TextureManager.h"
#include "AssetManager.h"
#include "Vector2D.h"

class TileComponent :
    public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;
	bool isanimated;

	TileComponent(int srcRectX, int srcRectY, int x, int y, int tileSize, int tileScale, std::string TextureId)
	{
		texture = Game::assetManager->GetTexture(TextureId);

		srcRect.x = srcRectX;
		srcRect.y = srcRectY;
		srcRect.w = srcRect.h = tileSize;

		destRect.x = x;//TO DO ??
		destRect.y = y;
		destRect.w = destRect.h = tileSize * tileScale;

		position.x = static_cast<float>(x);
		position.y = static_cast<float>(y);
	}

	~TileComponent() {
		//SDL_DestroyTexture(texture);
	}

	void update(float deltaTime) override;
	void render() override;
};

