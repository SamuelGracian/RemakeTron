#pragma once
//includes std
#include<string>
#include <iostream>
#include <map>

//includes sfml
#include<SFML/Graphics.hpp>

using std::string;

class ResourceManager
{
public:

	/// <summary>
	/// Create a new instance of the ResourceManager, using the Singleton pattern
	/// </summary>
	/// <returns></returns>
	static ResourceManager& GetInstance();

	void AddTexture(const string& TextureName);

	sf::Texture* GetTexture(const string& FileName);

private:
	ResourceManager() = default;

	//~ResourceManager();

	std::map<string, sf::Texture> mTextureMap;
};
