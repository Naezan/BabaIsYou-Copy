#pragma once
#include "Game.h"
#include "WipeTransition.h"
#include <functional>

//언리얼의 콜리전채널처럼 특정오브젝트는 block하고 특정오브젝트는 overlap, ignore하는 식의 유형별로 나눠야한다
//텍스트는 기본이 block
//람다 함수를 채워주자

void isYou(std::vector<Entity*>& vec)
{
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;
		//TO DO 나와 충돌했을때 내가할것
		v->addComponent<InputComponent>();
		v->collisionEvent = []()
		{
			//TO DO 호출될 일이 없음
			//std::cout << "You!!" << std::endl;
		};
	}
}

void isStop(std::vector<Entity*>& vec)
{
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Block;
		v->collisionEvent = []()
		{
			//TO DO 기본적으로 호출될일이 없음
			//std::cout << "Stop" << std::endl;
		};
	}
	Game::StopObject = &vec;//임시 TO DO
}

void isPush(std::vector<Entity*>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		vec[i]->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;

		vec[i]->collisionEvent = []()
		{
			//Nothing 필요할때 사용됩니다.
		};

		Game::PushObject.push_back(vec[i]);
	}
}

void isWin(std::vector<Entity*>& vec)
{
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;
		v->collisionEvent = [&v]()
		{
			//만약 플레이어라면 성공후 메뉴로 이동
			if (Game::transtition->transitionOutEvent == nullptr)
			{
				for (CollisionComponent*& obj : v->getComponent<CollisionComponent>()->CollisionList)
				{
					if (obj->tag == "Baba")
					{
						//TO DO 클리어 글자 띄우기
						Game::transtition->transitionOutEvent = Game::stagefuncmap[99];
						Game::transtition->playTransition(TRANS_TYPE::OUT);
						break;
					}
				}
			}
		};
	}
}

void isDeath(std::vector<Entity*>& vec)
{
	//collision.overlap
	//overlap이벤트 닿은 오브젝트의 태그가 플레이어라면 ... 플레이어 Destroy 충돌함수 바인딩
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;
		v->collisionEvent = []()
		{
			//TO DO
			std::cout << "Death" << std::endl;
		};
	}
}

void isShut(std::vector<Entity*>& vec)
{
	//collision.overlap
	//overlap이벤트 닿은 오브젝트의 태그가 Open이라면 ... 본인 삭제 충돌함수 바인딩
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;
		v->collisionEvent = []()
		{
			//TO DO
			std::cout << "Shut" << std::endl;
		};
	}
}

void isOpen(std::vector<Entity*>& vec)
{
	//collision.overlap
	//overlap이벤트 닿은 오브젝트의 태그가 Shut이라면 ... 본인 삭제 충돌함수 바인딩
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;
		v->collisionEvent = []()
		{
			//TO DO
			std::cout << "Open" << std::endl;
		};
	}
}

void isHot(std::vector<Entity*>& vec)
{
	//collision.overlap
	//overlap이벤트 닿은 오브젝트의 태그가 Melt이라면 ... 아무것도X
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;
		v->collisionEvent = []()
		{
			//TO DO
			std::cout << "Hot" << std::endl;
		};
	}
}

void isMelt(std::vector<Entity*>& vec)
{
	//collision.overlap
	//overlap이벤트 닿은 오브젝트의 태그가 Hot이라면 ... 본인 삭제 충돌함수 바인딩
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;
		v->collisionEvent = []()
		{
			//TO DO
			std::cout << "Melt" << std::endl;
		};
	}
}

void isSink(std::vector<Entity*>& vec)
{
	//collision.overlap
	//overlap이벤트 어떤 태그건 닿는 오브젝트 둘 다 소멸 충돌함수 바인딩
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;
		v->collisionEvent = []()
		{
			//TO DO
			std::cout << "Sink" << std::endl;
		};
	}
}

void isMove(std::vector<Entity*>& vec)
{
	//collision.overlap
	//그냥 특정방향으로 계속 이동
	//만약 벽을 만났다면 속도 * -1 충돌함수 바인딩
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;
		v->collisionEvent = []()
		{
			//TO DO
			std::cout << "Move" << std::endl;
		};
	}
}

void isMenu(std::vector<Entity*>& vec)
{
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;
		v->collisionEvent = [&v]()
		{
			if (Game::event.type == SDL_KEYDOWN)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_SPACE:
					if (Game::transtition != nullptr && Game::transtition->transitionOutEvent == nullptr)
					{
						Game::transtition->transitionOutEvent = Game::stagefuncmap[v->getStageIndex()];
						Game::transtition->playTransition(TRANS_TYPE::OUT);
					}
					break;
				}
			}
		};
	}
}