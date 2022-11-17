#include "WipeTransition.h"
#include "Game.h"
#include "TextureManager.h"

WipeTransition::WipeTransition(int _speed)
{
	speed = _speed;
	centerPos.x = WINDOW_WIDTH / 2;
	centerPos.y = WINDOW_HEIGHT / 2;
}
WipeTransition::~WipeTransition()
{

}

void WipeTransition::playTransition(TRANS_TYPE type)
{
	setTransition(type);

	dest.x = static_cast<int>(centerPos.x - (scale / 2));
	dest.y = static_cast<int>(centerPos.y - (scale / 2));
	dest.h = scale;
	dest.w = scale;
	textureMask = TextureManager::LoadTexture("assets/CloudMask.png", 255, 255, 255);
}

void WipeTransition::updateTransition(float deltaTime)
{
	if (isTransEnd)
	{
		return;
	}

	if (scale <= 0)
	{
		scale = 0;
		isTransEnd = true;
		if (transitionOutEvent != nullptr)
		{
			transitionOutEvent();
			transitionOutEvent = nullptr;
		}
		//트랜지션Out이벤트
		return;
	}
	if (scale >= 1700)
	{
		scale = 1700;
		isTransEnd = true;
		if (transitionInEvent != nullptr)
		{
			transitionInEvent();
			transitionInEvent = nullptr;
		}
		//트랜지션In이벤트
		return;
	}

	scale += static_cast<int>(deltaTime * speed);//무조건 정수
	dest.x = static_cast<int>(centerPos.x - (scale / 2));//실수 그리기 시작할 위치
	dest.y = static_cast<int>(centerPos.y - (scale / 2));//실수 그리기 시작할 위치
	dest.h = scale;//정수 그리는 높이
	dest.w = scale;//정수 그리는 너비

	SDL_RenderSetClipRect(Game::renderer, &dest);
}

void WipeTransition::render()
{
	SDL_RenderCopy(Game::renderer, textureMask, NULL, &dest);
}

void WipeTransition::setTransition(TRANS_TYPE type)
{
	switch (type)
	{
	case TRANS_TYPE::OUT:
		isTransEnd = false;
		scale = 1699;
		speed = speed > 0 ? speed *= -1 : speed;
		break;
	case TRANS_TYPE::IN:
		isTransEnd = false;
		scale = 1;
		speed = speed < 0 ? speed *= -1 : speed;
		break;
	}
}