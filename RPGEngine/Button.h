#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "boost/signals2.hpp"


class Button : public GameObject
{
private:
	sf::RectangleShape rect;
	sf::Text text;
	int clickCount = 0;
public:
	// 
	Button(const Button &b):Button(b.center,b.size,nullptr,"")
	{
	
	
	}
	Button(sf::Vector2f center, sf::Vector2f size, sf::Font *font, std::string text)
		:GameObject(center, size)
	{
		
		rect =  sf::RectangleShape(size);
		rect.setPosition(center);
		rect.setFillColor(sf::Color::White);
		this->text = sf::Text(text, *font, 12);
		this->text.setPosition(center);
		this->text.setFillColor(sf::Color::Black);
	}
	~Button();

	void update() override;
	void render(sf::RenderTarget *target) override;

	boost::signals2::signal <void()> OnPressed;


};
