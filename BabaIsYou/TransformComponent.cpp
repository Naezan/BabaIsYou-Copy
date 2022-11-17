#include "TransformComponent.h"
#include "Game.h"
#include"Entity.h"
#include "SpriteComponent.h"
#include "EntityManager.h"
#include "CollisionComponent.h"
#include "InputComponent.h"

void TransformComponent::init()
{
	velocity.Zero();
}

void TransformComponent::update(float deltaTime)
{
	static float deltaX = 0;
	static float deltaY = 0;

	//���࿡ ���� �����ߴٸ� �����ӿ���X
	if (velocity.x == -1 && roundf(position.x) <= WIDTH_INTERVAL)
		return;
	else if (velocity.x == 1 && roundf(position.x) >= WINDOW_WIDTH - WIDTH_INTERVAL - PIXEL_SIZE)
		return;
	if (velocity.y == -1 && roundf(position.y) <= HEIGHT_INVERVAL)
		return;
	else if (velocity.y == 1 && roundf(position.y) >= WINDOW_HEIGHT - HEIGHT_INVERVAL - PIXEL_SIZE)
		return;

	/*if (componentOwner->getComponent<CollisionComponent>()->tag)
	{
		//TO DO
	}*/

	Direction dir = DIREND;
	if (velocity.x == 1) dir = RIGHT;
	else if (velocity.x == -1) dir = LEFT;
	else if (velocity.y == 1) dir = DOWN;
	else if (velocity.y == -1) dir = UP;

	//�������� ������ ����X
	if (dir == DIREND)
		return;

	//������ �浹ó��
	if (Game::StopObject != nullptr)
	{
		for (auto& obj : *Game::StopObject)
		{
			Vector2D tmpVec = position + componentOwner->getComponent<CollisionComponent>()->extraSize;
			if (tmpVec + (velocity * PIXEL_SIZE) == obj->getComponent<TransformComponent>()->position)
			{
				return;
			}
		}
	}

	std::vector<Entity*> objs;
	//���¹����� �տ��ִ��� üũ�������
	for (int i = 0; i < PIXEL_SIZE * 2; ++i)
	{
		switch (dir)
		{
		case UP:
		{
			deltaY += velocity.y * deltaTime / 2.f;
		}
		break;
		case DOWN:
		{
			deltaY += velocity.y * deltaTime / 2.f;
		}
		break;
		case LEFT:
		{
			deltaX += velocity.x * deltaTime / 2.f;
		}
		break;
		case RIGHT:
		{
			deltaX += velocity.x * deltaTime / 2.f;
		}
		break;
		}

		int index = 1;
		//������ �����ʿ� isPush ������Ʈ�� �ִ��� üũ�ϰ� ������Ʈ ����Ʈ�� �߰����ݴϴ�.
		objs = componentOwner->FindNextPushObject(position, velocity, index);

		//index�� ��ġ�� ���̳� ������ �κ����ִٸ� objlist�� ����ش�
		Vector2D checkPos = position + (velocity * PIXEL_SIZE * index);
		if (Game::StopObject != nullptr)
		{
			for (auto& obj : *Game::StopObject)
			{
				if (obj->getComponent<TransformComponent>()->position == checkPos)
				{
					objs.clear();
					break;
				}
			}
		}

		//��ã�ų� checkpos�� ���� ����ٸ�
		if (index != 1 && objs.empty() || 
		(checkPos.x <= WIDTH_INTERVAL - PIXEL_SIZE || checkPos.x >= WINDOW_WIDTH - WIDTH_INTERVAL ||
		checkPos.y <= HEIGHT_INVERVAL - PIXEL_SIZE || checkPos.y >= WINDOW_HEIGHT - HEIGHT_INVERVAL))
		{
			return;
		}

		position += velocity * (deltaTime / 2.f);

		//��ó��
		for (Entity*& obj : objs)
		{
			obj->getComponent<TransformComponent>()->position += velocity * (deltaTime / 2.f);
			obj->getComponent<CollisionComponent>()->update(deltaTime);
			obj->getComponent<SpriteComponent>()->update(deltaTime);
		}

		//�浹ü�� int���̱⶧���� �ѹ� ������Ʈ�Ѱɷ� �浹ü�� �������� �ʴ´�
		componentOwner->getComponent<CollisionComponent>()->update(deltaTime);

		//TO DO �ʹ� ���� ������
		SDL_RenderClear(Game::renderer);
		componentOwner->getComponent<SpriteComponent>()->update(deltaTime);
		componentOwner->GetEntityManager().render();
		SDL_RenderPresent(Game::renderer);
	}

	if (deltaX >= PIXEL_SIZE || deltaX <= -PIXEL_SIZE || deltaY >= PIXEL_SIZE || deltaY <= -PIXEL_SIZE)
	{
		position.x = roundf(position.x);
		position.y = roundf(position.y);
		deltaX = 0;
		velocity.x = 0;//�߿���!
		deltaY = 0;
		velocity.y = 0;//�߿���!
	}

	for (Entity*& obj : objs)
	{
		obj->getComponent<TransformComponent>()->position.RoundVectorf();
	}

	//TO DO ��������Ȯ�� �Լ� �߰�
	std::vector<std::pair<Vector2D, LayerGroup>> textgroupvec;
	for (Entity*& text : Game::headtexts)
	{
		int connectionCount = 0;
		Vector2D nextRightPos = Vector2D(text->getComponent<TransformComponent>()->position.x + PIXEL_SIZE, text->getComponent<TransformComponent>()->position.y);
		Vector2D nextBottomPos = Vector2D(text->getComponent<TransformComponent>()->position.x, text->getComponent<TransformComponent>()->position.y + PIXEL_SIZE);
		for (Entity*& verb : Game::verbtexts)
		{
			Vector2D verbPos = Vector2D(verb->getComponent<TransformComponent>()->position.x, verb->getComponent<TransformComponent>()->position.y);
			if (verbPos == nextRightPos)
			{
				verbPos.x += PIXEL_SIZE;
				textgroupvec.emplace_back(verbPos, text->getManagingLayer());
				verbPos.x -= PIXEL_SIZE;
				++connectionCount;
			}
			if (verbPos == nextBottomPos)
			{
				verbPos.y += PIXEL_SIZE;
				textgroupvec.emplace_back(verbPos, text->getManagingLayer());
				verbPos.y -= PIXEL_SIZE;
				++connectionCount;
			}
		}
		if (connectionCount == 0)
		{
			//��ǲ ������Ʈ ����
			std::vector<Entity*>& Etts = componentOwner->GetEntityManager().getLayerGroup(text->getManagingLayer());
			for (Entity*& Ett : Etts)
			{
				Ett->removeComponent<InputComponent>();
				if (Ett->hasComponent<CollisionComponent>())
				{
					Ett->getComponent<CollisionComponent>()->colType = CollisionType::Ignore;
				}

				if (Ett->getTextType() == TextType::Stop)
				{
					Game::StopObject = nullptr;
					Ett->setTextType(TextType::Default);
				}
			}
			Game::PushObject.clear();
			(*Game::textfuncmap[TextType::Push])(Game::headtexts);
			(*Game::textfuncmap[TextType::Push])(Game::verbtexts);
			(*Game::textfuncmap[TextType::Push])(Game::tailtexts);
		}
	}

	if (!textgroupvec.empty())
	{
		for (std::pair<Vector2D, LayerGroup>& textgroup : textgroupvec)
		{
			int connectionCount = 0;
			for (Entity*& tailtext : Game::tailtexts)
			{
				if (tailtext->getComponent<TransformComponent>()->position == textgroup.first)
				{
					std::vector<Entity*>& layeredobj = componentOwner->GetEntityManager().getLayerGroup(textgroup.second);
					for (Entity*& Ett : layeredobj)
					{
						Ett->removeComponent<InputComponent>();
						Ett->setTextType(tailtext->getTextType());//�ص��� �ؽ�Ʈ Ÿ���� ������ �ؽ�ƮŸ������ ����
					}
					textfunc func = Game::textfuncmap[tailtext->getTextType()];
					(*func)(layeredobj);
					++connectionCount;
				}
			}

			if (connectionCount == 0)
			{
				//��ǲ ������Ʈ ����
				std::vector<Entity*>& Etts = componentOwner->GetEntityManager().getLayerGroup(textgroup.second);
				for (Entity*& Ett : Etts)
				{
					Ett->removeComponent<InputComponent>();
					if (Ett->hasComponent<CollisionComponent>())
					{
						Ett->getComponent<CollisionComponent>()->colType = CollisionType::Ignore;
					}

					if (Ett->getTextType() == TextType::Stop)
					{
						Game::StopObject = nullptr;
						Ett->setTextType(TextType::Default);
					}
				}
				Game::PushObject.clear();
				(*Game::textfuncmap[TextType::Push])(Game::headtexts);
				(*Game::textfuncmap[TextType::Push])(Game::verbtexts);
				(*Game::textfuncmap[TextType::Push])(Game::tailtexts);
			}
		}
	}
}
