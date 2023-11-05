#include "Game.h"

const int FPS = 60;
const int TicksPerFrame = 1000 / FPS;//1프레임당 16ms로 만들고 싶다

Game* game = nullptr;

int main( int argc, char* argv[])
{
	Uint64 start;
	Uint64 end;
	//int deltaTime;

	game = new Game();

	game->init("BaBaIsYou",
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
	,WINDOW_WIDTH, WINDOW_HEIGHT,
	false);

	while (game->running())
	{
		start = SDL_GetTicks64();//ms단위

		//handle any user input
		game->handleEvents();
		//update all object eg. positions, etc..
		game->update(1);
		//render changes to the display
		game->render();

		end = SDL_GetTicks64();

		//1프레임당 몇 ms인지
		int deltaframe = static_cast<int>(end - start);
		//델타타임 구하기
		/*dt = deltaframe * 100.f;
		dt = (deltaframe > 1.f) ? 1.f : deltaframe;*/

		//너무 빠르면 특정60프레임을 맞추기 위해서 특정ms시간만큼 딜레이한다
		//특정 ms만큼 대기함으로써 1프레임당 16ms를 맞춰 거의 60프레임에 맞는 ms를 갖출 수 있다.
		if (deltaframe < TicksPerFrame)
		{
			SDL_Delay(TicksPerFrame - deltaframe);
		}
	}

	game->clean();

	if (game != nullptr)
	{
		delete game;
	}

	return 0;
}