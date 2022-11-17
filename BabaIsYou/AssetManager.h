#pragma once
#include "Game.h"
#include <string>
#include <map>

class EntityManager;

class AssetManager
{
public:
	AssetManager(EntityManager* _manager);
	~AssetManager();

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
private:
	std::map<std::string, SDL_Texture*> textures;
	EntityManager* manager;

	//TO DO Add font
};

