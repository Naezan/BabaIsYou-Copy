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
	//dest�� left,top���� �׸��� ������ ��ġ
	//source�� ��������Ʈ ���ҽ��� �̹��� ��ġ
	SDL_Rect SourceRect, DestRect;
	bool isanimated;//�ִϸ��̼� ����
	int maxFrame;//�ִ� ������
	int animPlaySpeed;
	std::string animName;//�ִϸ��̼� �����

	int spriteIndexY;

public:
	int animIndex;//���� ������
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

