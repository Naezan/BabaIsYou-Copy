#include "Game.h"

const int FPS = 60;
const int TicksPerFrame = 1000 / FPS;//1�����Ӵ� 16ms�� ����� �ʹ�

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
		start = SDL_GetTicks64();//ms����

		//handle any user input
		game->handleEvents();
		//update all object eg. positions, etc..
		game->update(1);
		//render changes to the display
		game->render();

		end = SDL_GetTicks64();

		//1�����Ӵ� �� ms����
		int deltaframe = static_cast<int>(end - start);
		//��ŸŸ�� ���ϱ�
		/*dt = deltaframe * 100.f;
		dt = (deltaframe > 1.f) ? 1.f : deltaframe;*/

		//�ʹ� ������ Ư��60�������� ���߱� ���ؼ� Ư��ms�ð���ŭ �������Ѵ�
		//Ư�� ms��ŭ ��������ν� 1�����Ӵ� 16ms�� ���� ���� 60�����ӿ� �´� ms�� ���� �� �ִ�.
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