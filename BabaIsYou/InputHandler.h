#pragma once
#include "Game.h"

class InputHandler
{
public:
	InputHandler() {}
	~InputHandler() {}

	KeyEvent handleupdate();
	KeyEvent handleQuit();

private:
	const Uint8* KeyState = SDL_GetKeyboardState(NULL);
};

