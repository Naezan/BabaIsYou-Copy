#include "InputHandler.h"

KeyEvent InputHandler::handleupdate()
{
	if (KeyState[SDL_SCANCODE_W]) {
		return KEY_UP;
	}
	else if (KeyState[SDL_SCANCODE_S]) {
		return KEY_DOWN;
	}
	else if (KeyState[SDL_SCANCODE_A]) {
		return KEY_LEFT;
	}
	else if (KeyState[SDL_SCANCODE_D]) {
		return KEY_RIGHT;
	}
	else if (KeyState[SDL_SCANCODE_Z]) {
		return KEY_UNDO;
	}
	else if (KeyState[SDL_SCANCODE_R]) {
		return KEY_RESTART;
	}
	else if (KeyState[SDL_SCANCODE_ESCAPE]) {
		return KEY_QUIT;
	}

	return KEY_END;
}

KeyEvent InputHandler::handleQuit()
{
	SDL_PollEvent(&Game::event);
	switch (Game::event.type)
	{
	case SDL_QUIT://X로 창을 닫았을때
		return KEY_QUIT;
		break;
	}

	return KEY_END;
}
