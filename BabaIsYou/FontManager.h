#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>

class FontManager
{
public:
	static std::pair<SDL_Rect, SDL_Texture*> LoadFont(std::string text, SDL_Color color = { 0,0,0 });
	static void DrawFont(SDL_Texture* texture, SDL_Rect textRect);
};