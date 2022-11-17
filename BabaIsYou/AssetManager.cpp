#include "AssetManager.h"
#include "TextureManager.h"

AssetManager::AssetManager(EntityManager* _manager)
	: manager(_manager)
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}
