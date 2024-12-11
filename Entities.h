
#pragma once
#include<SFML/Graphics.hpp>

class Entities
{
public:
	//constructor
	Entities() = default;
	virtual ~Entities() = default;

	void virtual Update(float DeltaTime) = 0;
	void virtual Render(sf::RenderWindow& window) = 0;
	void virtual Clean() = 0;
};
