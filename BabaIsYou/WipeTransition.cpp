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
		//Ʈ������Out�̺�Ʈ
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
		//Ʈ������In�̺�Ʈ
		return;
	}

	scale += static_cast<int>(deltaTime * speed);//������ ����
	dest.x = static_cast<int>(centerPos.x - (scale / 2));//�Ǽ� �׸��� ������ ��ġ
	dest.y = static_cast<int>(centerPos.y - (scale / 2));//�Ǽ� �׸��� ������ ��ġ
	dest.h = scale;//���� �׸��� ����
	dest.w = scale;//���� �׸��� �ʺ�

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