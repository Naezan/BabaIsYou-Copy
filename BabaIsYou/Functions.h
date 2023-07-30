#pragma once
#include "Game.h"
#include "WipeTransition.h"
#include <functional>

//�𸮾��� �ݸ���ä��ó�� Ư��������Ʈ�� block�ϰ� Ư��������Ʈ�� overlap, ignore�ϴ� ���� �������� �������Ѵ�
//�ؽ�Ʈ�� �⺻�� block
//���� �Լ��� ä������

void isYou(std::vector<Entity*>& vec)
{
	for (auto& v : vec)
	{
		v->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;
		//TO DO ���� �浹������ �����Ұ�
		v->addComponent<InputComponent>();
		v->collisionEvent = []()
		{
			//TO DO ȣ��� ���� ����
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
			//TO DO �⺻������ ȣ������� ����
			//std::cout << "Stop" << std::endl;
		};
	}
	Game::StopObject = &vec;//�ӽ� TO DO
}

void isPush(std::vector<Entity*>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		vec[i]->getComponent<CollisionComponent>()->colType = CollisionType::Overlap;

		vec[i]->collisionEvent = []()
		{
			//Nothing �ʿ��Ҷ� ���˴ϴ�.
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
			//���� �÷��̾��� ������ �޴��� �̵�
			if (Game::transtition->transitionOutEvent == nullptr)
			{
				for (CollisionComponent*& obj : v->getComponent<CollisionComponent>()->CollisionList)
				{
					if (obj->tag == "Baba")
					{
						//TO DO Ŭ���� ���� ����
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
	//overlap�̺�Ʈ ���� ������Ʈ�� �±װ� �÷��̾��� ... �÷��̾� Destroy �浹�Լ� ���ε�
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
	//overlap�̺�Ʈ ���� ������Ʈ�� �±װ� Open�̶�� ... ���� ���� �浹�Լ� ���ε�
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
	//overlap�̺�Ʈ ���� ������Ʈ�� �±װ� Shut�̶�� ... ���� ���� �浹�Լ� ���ε�
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
	//overlap�̺�Ʈ ���� ������Ʈ�� �±װ� Melt�̶�� ... �ƹ��͵�X
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
	//overlap�̺�Ʈ ���� ������Ʈ�� �±װ� Hot�̶�� ... ���� ���� �浹�Լ� ���ε�
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
	//overlap�̺�Ʈ � �±װ� ��� ������Ʈ �� �� �Ҹ� �浹�Լ� ���ε�
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
	//�׳� Ư���������� ��� �̵�
	//���� ���� �����ٸ� �ӵ� * -1 �浹�Լ� ���ε�
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