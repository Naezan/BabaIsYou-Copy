#pragma once
#include "Game.h"
#include <string>
#include <map>

class EntityManager;

class AssetManager
{
public:
	static AssetManager& GetInstance(EntityManager* _manager = nullptr) {
		if (instance == nullptr) {
			instance = new AssetManager(_manager);
		}

		return *instance;
	}

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:
	AssetManager(EntityManager* _manager);
	static AssetManager* instance;

private:
	std::map<std::string, SDL_Texture*> textures;
	EntityManager* manager;

	//TO DO Add font
};

