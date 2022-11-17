#pragma once
#include <SDL.h>

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* filepath, int r = 84, int g = 165, int b = 75, SDL_BlendMode mode = SDL_BLENDMODE_BLEND);
	static void DrawTexture(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};

