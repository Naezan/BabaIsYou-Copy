#pragma once
#include "Component.h"
#include "Game.h"
#include "TextureManager.h"
#include <map>

class TransformComponent;
struct Animation;

class SpriteComponent :
	public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	//dest는 left,top으로 그림을 시작할 위치
	//source는 스프라이트 리소스의 이미지 위치
	SDL_Rect SourceRect, DestRect;
	bool isanimated;//애니메이션 여부
	int maxFrame;//최대 프레임
	int animPlaySpeed;
	std::string animName;//애니메이션 재생용

	int spriteIndexY;

public:
	int animIndex;//현재 프레임
	bool hasDirection = false;
	bool isPlayable = false;
	std::map<std::string, Animation> animations;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent(std::string _textureID);
	SpriteComponent(std::string _textureID, int _maxFrame, int _animPlaySpeed, int spriteX, int spriteY, bool hasDir = false, bool isPlayer = false);

	void init() override;
	void update(float deltaTime) override;
	void render() override;

	void setTexture(std::string _textureID);
	void play(std::string _animName);
};

