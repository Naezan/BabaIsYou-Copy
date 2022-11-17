#include "FontManager.h"
#include "Game.h"

std::pair<SDL_Rect, SDL_Texture*> FontManager::LoadFont(std::string text, SDL_Color color)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(Game::font, text.c_str(), color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_Rect textRect = { 0,0,textSurface->w,textSurface->h };
	SDL_FreeSurface(textSurface);

	return std::make_pair(textRect, textTexture);
}

void FontManager::DrawFont(SDL_Texture* texture, SDL_Rect textRect)
{
	SDL_RenderCopy(Game::renderer, texture, NULL, &textRect);
}