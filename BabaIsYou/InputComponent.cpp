#include "InputComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Entity.h"
#include "WipeTransition.h"
#include "EntityManager.h"

void InputComponent::init()
{
	transform = componentOwner->getComponent<TransformComponent>();
	sprite = componentOwner->getComponent<SpriteComponent>();
}

void InputComponent::update(float deltaTime)
{
	//KeyEvent
	//TO DO Add current position to position queue

	//Stop Input When Transition is Doing
	if (Game::transtition != nullptr && !Game::transtition->isTransEnd)
	{
		return;
	}

	static char index = '0';
	static std::string direction = "Down";
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_w:
			transform->velocity.y = -1;
			++index;
			if (index > '3')
				index = '0';
			direction = "Up";
			if (sprite->isPlayable)
				direction.push_back(index);
			if (sprite->hasDirection)
				sprite->play(direction);
			else
				sprite->play("Idle");
			break;
		case SDLK_a:
			transform->velocity.x = -1;
			++index;
			if (index > '3')
				index = '0';
			direction = "Left";
			if (sprite->isPlayable)
				direction.push_back(index);
			if (sprite->hasDirection)
				sprite->play(direction);
			else
				sprite->play("Idle");
			break;
		case SDLK_d:
			transform->velocity.x = 1;
			++index;
			if (index > '3')
				index = '0';
			direction = "Right";
			if (sprite->isPlayable)
				direction.push_back(index);
			if (sprite->hasDirection)
				sprite->play(direction);
			else
				sprite->play("Idle");
			break;
		case SDLK_s:
			transform->velocity.y = 1;
			++index;
			if (index > '3')
				index = '0';
			direction = "Down";
			if (sprite->isPlayable)
				direction.push_back(index);
			if (sprite->hasDirection)
				sprite->play(direction);
			else
				sprite->play("Idle");
			break;
		}
	}

	if (Game::event.type == SDL_KEYUP)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_w:
			transform->velocity.y = 0;
			break;
		case SDLK_a:
			transform->velocity.x = 0;
			break;
		case SDLK_d:
			transform->velocity.x = 0;
			break;
		case SDLK_s:
			transform->velocity.y = 0;
			break;
		case SDLK_z:
			componentOwner->GetEntityManager().DecreaseRecordIndex();
			componentOwner->GetEntityManager().UpdateRecordStack();
			break;
		case SDLK_r:
			if (Game::transtition->transitionOutEvent == nullptr && Game::CurStageIndex != -1)
			{
				Game::transtition->transitionOutEvent = Game::stagefuncmap[Game::CurStageIndex];
				Game::transtition->playTransition(TRANS_TYPE::OUT);
			}
			break;
		case SDLK_ESCAPE:
			//if CurStageIndex != -1 -> Return To Menu
			if (Game::CurStageIndex != -1)
			{
				if (Game::transtition->transitionOutEvent == nullptr)
				{
					Game::transtition->transitionOutEvent = Game::stagefuncmap[99];
					Game::transtition->playTransition(TRANS_TYPE::OUT);
				}
			}
			else
				Game::isRunning = false;
		}
	}
}
