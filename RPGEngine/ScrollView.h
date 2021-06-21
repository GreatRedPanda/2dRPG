#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

class ScrollView : public GameObject
{

	sf::RenderTexture *texture;
	sf::RenderTexture *containerTexture;
	sf::RectangleShape elementsContainer;
	sf::RectangleShape scrollBar;

	sf::Shader *maskShader;

	sf::Vector2f scale = sf::Vector2f(1, 1);
public:
	ScrollView();
	~ScrollView();
	ScrollView(sf::Vector2f center, sf::Vector2f size, float scrollBarWidth, sf::RenderTexture *t, sf::RenderTexture *t2,	sf::Shader *maskSh )
		:GameObject(center, size)
	{

		elementsContainer = sf::RectangleShape(size);
		elementsContainer.setPosition(center);
		elementsContainer.setFillColor(sf::Color::White);
	
		t->create(size.x	, size.y );
		this->texture = t;	
		t2->create(size.x , size.y );
		this->containerTexture = t2;	
		maskSh->loadFromFile("C:\\Users\\Office_1\\source\\repos\\RPG\\RPGEngine\\Mix.frag", sf::Shader::Fragment);
		this->maskShader = maskSh;
		
	}

	void update() override;
	void render(sf::RenderTarget *target) override;
	void resize(sf::Vector2f oldSize, sf::Vector2f newSize) override;


};

