#include "ResourceManager.h"

using std::string;

ResourceManager& ResourceManager::GetInstance()
{
	// Singleton pattern
	static ResourceManager instance;
	return instance;
}

void ResourceManager::AddTexture(const string& Texture)
{

}

sf::Texture* ResourceManager::GetTexture(const string& Filename)
{
	auto Textureit = mTextureMap.find(Filename);
	if (Textureit != mTextureMap.end())
	{
		return &Textureit->second;
	}
	else
	{
		sf::Texture NewTexture;
		if (NewTexture.loadFromFile(Filename))
		{
			mTextureMap.insert(std::make_pair(Filename, NewTexture));
			return &mTextureMap[Filename];
		}
		else
		{
			std::cout << "Failed to load texture: " << Filename << std::endl;
			return nullptr;
		}
	}
}