#include "stdafx.h"
#include "Input.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
sf::Vector2i Input::mousePosition = sf::Vector2i(0, 0);
sf::Vector2f Input::MousePosition = sf::Vector2f(0, 0);
sf::Vector2f Input::MouseDelta = sf::Vector2f(0, 0);
 sf::Vector2i  Input::mousePrevPosition = sf::Vector2i(0, 0);
float  Input::mouseWheelScroll = 0;
sf::Event::EventType Input::LastEvent;


int Input::clickCountL=0;
int Input::clickCountR = 0;
int Input::clickCountM = 0;
int Input::pressedTime = 0;
bool Input::MouseLeftClick;
bool Input::MouseRightClick;
bool Input::MouseMiddleClick;
bool Input::MouseDragLeft;
bool Input::MouseDragRight;
bool Input::Scrolled;

void Input::SetMousePosition(sf::Vector2i pos)
{
	mousePosition = pos;
	MousePosition = sf::Vector2f(pos.x, pos.y);
}

void Input::updateEvents(sf::Window &target, sf::Event *e)
{


	std::cout << Scrolled << "\n";

	std::cout << Scrolled << "\n";
	if (e->type == Event::MouseWheelScrolled)
	{

		mouseWheelScroll = e->mouseWheelScroll.delta;
		Scrolled = true;
		std::cout << "evnt"<< e->mouseWheelScroll.delta << "\n";
	}
	else
		Scrolled = false;

	if (e->type == Event::MouseButtonPressed)
	{
		Input::mousePrevPosition = Mouse::getPosition(target);		

		if(Mouse::isButtonPressed(Mouse::Left))
		clickCountL = 1;
		if (Mouse::isButtonPressed(Mouse::Right))
			clickCountR = 1;
		if (Mouse::isButtonPressed(Mouse::Middle))
			clickCountM = 1;
	}
	if (e->type == Event::MouseButtonReleased)
	{
		
		if (clickCountL == 1 && !Mouse::isButtonPressed(Mouse::Left))
		{
			MouseLeftClick = true;
			clickCountL = 0;
		}
		if (clickCountR == 1 && !Mouse::isButtonPressed(Mouse::Right))
		{
			MouseRightClick = true;
			clickCountR = 0;
		}
		if (clickCountM == 1 && !Mouse::isButtonPressed(Mouse::Middle))
		{
			MouseMiddleClick = true;
			clickCountM = 0;
		}
	}
	
	if (e->type == Event::MouseMoved)
	{
		Input::SetMousePosition(Mouse::getPosition(target));
		Vector2i pos = Input::mousePrevPosition - Mouse::getPosition(target);
		Input::MouseDelta = Vector2f(pos.x, pos.y);
	/*	if (pos.y < 0)
			Input::MouseDelta.y = -1;
		else if (pos.y > 0)
			Input::MouseDelta.y = 1;
		else
			Input::MouseDelta.y = 0;*/
		Input::mousePrevPosition = Mouse::getPosition(target);

		if(Mouse::isButtonPressed(Mouse::Right))
			MouseDragRight = true;
	}
}

void Input::clear()
{

	mouseWheelScroll = 0;
	MouseLeftClick = false;
	MouseRightClick = false;
	MouseMiddleClick = false;
	MouseDragRight = false;
	Scrolled = false;
}
