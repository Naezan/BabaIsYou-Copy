#include "SpriteComponent.h"
#include "Animation.h"
#include "TransformComponent.h"
#include "AssetManager.h"
#include "Entity.h"

SpriteComponent::SpriteComponent(std::string _textureID)
{
	isanimated = false;
	setTexture(_textureID);
}

SpriteComponent::SpriteComponent(std::string _textureID, int _maxFrame, int _animPlaySpeed, int spriteX, int spriteY, bool hasDir, bool isPlayer)
{
	isanimated = true;
	maxFrame = _maxFrame;
	animPlaySpeed = _animPlaySpeed;
	hasDirection = hasDir;
	isPlayable = isPlayer;

	//애니메이션 추가
	if (hasDir)//플레이어, 움직임이 있는 오브젝트
	{
		//플레이어의 경우 각방향마다 right1, right2, right3, right4 4가지의 애니메이션이 존재하고
		//애니메이션마다 3가지의 스프라이트가 있다.
		//플레이어가 아닌 방향이 있는 오브젝트는 방향마다 1가지씩의 애니메이션이 존재하고
		//애니메이션마다 3가지의 스프라이트가 있다.
		if (isPlayer)
		{
			//spriteX, spriteY가 좌표가 되고 그곳을기준으로 인덱스를 정함
			Animation downAnimation1 = Animation(spriteX + 12, _maxFrame, _animPlaySpeed);
			Animation downAnimation2 = Animation(spriteX + 1 + 12, _maxFrame, _animPlaySpeed);
			Animation downAnimation3 = Animation(spriteX + 2 + 12, _maxFrame, _animPlaySpeed);
			Animation downAnimation4 = Animation(spriteX + 3 + 12, _maxFrame, _animPlaySpeed);
			Animation rightAnimation1 = Animation(spriteX, _maxFrame, _animPlaySpeed);
			Animation rightAnimation2 = Animation(spriteX + 1, _maxFrame, _animPlaySpeed);
			Animation rightAnimation3 = Animation(spriteX + 2, _maxFrame, _animPlaySpeed);
			Animation rightAnimation4 = Animation(spriteX + 3, _maxFrame, _animPlaySpeed);
			Animation leftAnimation1 = Animation(spriteX + 8, _maxFrame, _animPlaySpeed);
			Animation leftAnimation2 = Animation(spriteX + 1 + 8, _maxFrame, _animPlaySpeed);
			Animation leftAnimation3 = Animation(spriteX + 2+ 8, _maxFrame, _animPlaySpeed);
			Animation leftAnimation4 = Animation(spriteX + 3+ 8, _maxFrame, _animPlaySpeed);
			Animation upAnimation1 = Animation(spriteX + 4, _maxFrame, _animPlaySpeed);
			Animation upAnimation2 = Animation(spriteX + 1 + 4, _maxFrame, _animPlaySpeed);
			Animation upAnimation3 = Animation(spriteX + 2 + 4, _maxFrame, _animPlaySpeed);
			Animation upAnimation4 = Animation(spriteX + 3 + 4, _maxFrame, _animPlaySpeed);
			animations.emplace("Down0", downAnimation1);
			animations.emplace("Down1", downAnimation2);
			animations.emplace("Down2", downAnimation3);
			animations.emplace("Down3", downAnimation4);
			animations.emplace("Right0", rightAnimation1);
			animations.emplace("Right1", rightAnimation2);
			animations.emplace("Right2", rightAnimation3);
			animations.emplace("Right3", rightAnimation4);
			animations.emplace("Left0", leftAnimation1);
			animations.emplace("Left1", leftAnimation2);
			animations.emplace("Left2", leftAnimation3);
			animations.emplace("Left3", leftAnimation4);
			animations.emplace("Up0", upAnimation1);
			animations.emplace("Up1", upAnimation2);
			animations.emplace("Up2", upAnimation3);
			animations.emplace("Up3", upAnimation4);
			animIndex = 0;
			animName = "Down0";
		}
		else
		{
			Animation downAnimation = Animation(spriteX + 3, _maxFrame, _animPlaySpeed);
			Animation rightAnimation = Animation(spriteX, _maxFrame, _animPlaySpeed);
			Animation leftAnimation = Animation(spriteX + 2, _maxFrame, _animPlaySpeed);
			Animation upAnimation = Animation(spriteX + 1, _maxFrame, _animPlaySpeed);
			animations.emplace("Down", downAnimation);
			animations.emplace("Right", rightAnimation);
			animations.emplace("Left", leftAnimation);
			animations.emplace("Up", upAnimation);
			animIndex = 0;
			animName = "Down";
		}
	}
	else//idle애니메이션만 있는 오브젝트
	{
		Animation idleAnimation = Animation(spriteX, _maxFrame, _animPlaySpeed);
		animations.emplace("Idle", idleAnimation);
		animIndex = 0;
		animName = "Idle";
	}

	spriteIndexY = spriteY;//TO DO

	play(animName);

	setTexture(_textureID);
}

void SpriteComponent::init()
{
	transform = componentOwner->getComponent<TransformComponent>();
	SourceRect.x = SourceRect.y = 0;
	SourceRect.w = transform->width;
	SourceRect.h = transform->height;
}

void SpriteComponent::update(float deltaTime)
{
	if (isanimated)
	{
		//y값 1칸 내리기 애니메이션 스프라이트 변경
		SourceRect.y = (SourceRect.h + 1) * static_cast<int>((SDL_GetTicks() / animPlaySpeed) % maxFrame) + 1 + spriteIndexY * (PIXEL_SIZE + 1);
		//x값 1칸 밀기
		SourceRect.x = animIndex * (PIXEL_SIZE + 1) + 1;
	}

	DestRect.x = static_cast<int>(transform->position.x);
	DestRect.y = static_cast<int>(transform->position.y);
	DestRect.w = transform->width * transform->scale;
	DestRect.h = transform->height * transform->scale;
}

void SpriteComponent::render()
{
	TextureManager::DrawTexture(texture, SourceRect, DestRect, spriteFlip);
}

void SpriteComponent::setTexture(std::string _textureID)
{
	texture = Game::assetManager->GetTexture(_textureID);
}

void SpriteComponent::play(std::string _animName)
{
	maxFrame = animations[_animName].maxframe;
	animIndex = animations[_animName].index;
	animPlaySpeed = animations[_animName].playspeed;
	animName = _animName;//플레이할때 사용?
}

void SpriteComponent::play()
{
	maxFrame = animations[animName].maxframe;
	animIndex = animations[animName].index;
	animPlaySpeed = animations[animName].playspeed;
}

void SpriteComponent::SetAnimName(std::string _animName)
{
	animName = _animName;
}

std::string SpriteComponent::GetCurrentAnimName()
{
	return animName;
}
