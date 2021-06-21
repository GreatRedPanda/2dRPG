#include "stdafx.h"
#include "Button.h"
#include "Input.h"
#include <iostream>


//Button::Button()
//{
//	
//}


//Button::Button(const Button &)
//{
//}

Button::~Button()
{
}

void Button::update()
{
	rect.setPosition(Vector2f(center.x*scale.x, center.y*scale.y));
	rect.setSize(Vector2f(size.x*scale.x, size.y*scale.y));
	this->text.setPosition(Vector2f(center.x*scale.x, center.y*scale.y));
	this->text.setScale(Vector2f(scale.x, scale.y));

	bool mouseOver =rect.getGlobalBounds().contains(Input::MousePosition);
	if (mouseOver)
	{
		rect.setFillColor(sf::Color::Green);

		if (Input::MouseLeftClick)
		{
			OnPressed();
		}
		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCount == 0)
		{
			clickCount = 1;

			OnPressed();

		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCount ==1)
		{
			clickCount = 0;
		}*/
	}
	else
		rect.setFillColor(sf::Color::White);
}

void Button::render(sf::RenderTarget *target)
{

	target->draw(this->rect);
	target->draw(this->text);

}
