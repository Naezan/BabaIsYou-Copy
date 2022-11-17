#include "TextureManager.h"
#include "Game.h"

SDL_Texture* TextureManager::LoadTexture(const char* filepath, int r, int g, int b, SDL_BlendMode mode)
{
	SDL_Surface* surface = IMG_Load(filepath);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, r, g, b));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_SetTextureBlendMode(texture, mode);
	SDL_FreeSurface(surface);

	return texture;
}

void TextureManager::DrawTexture(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	//SDL_RenderCopy(Game::renderer, texture, &src, &dest);
	SDL_RenderCopyEx(Game::renderer, texture, &src, &dest, NULL, NULL, flip);
}
