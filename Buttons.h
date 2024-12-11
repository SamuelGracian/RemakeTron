#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Entities.h"

class Buttons : public Entities
{
public:
	//Inherit from Entitie

	/// <summary>
	/// Constructor for the Buttons class
	/// </summary>
	/// <param name="Size"></param>
	/// <param name="Position"></param>
	/// <param name="color">fill color</param>
	/// <param name="color">outline color</param>
	/// <param name="Text"></param>
	Buttons(const sf::Vector2f& Size, sf::Vector2f Position, sf::Color color, const std::string& Text)
		:mfSize(Size), mfPosition(Position), mShapeColor(color)
	{
		mButton.setSize(mfSize);
		mButton.setPosition(mfPosition);
		mButton.setFillColor(mShapeColor);
	};

	void Render(sf::RenderWindow& window) override
	{
		window.draw(mButton);
	}
	void Update(float DeltaTime) override;
	void Clean() override;

	void (*OnCommand)();

private:
	sf::Vector2f mfSize;
	sf::Vector2f mfPosition;
	sf::Color mShapeColor;
	sf::RectangleShape mButton;
};
