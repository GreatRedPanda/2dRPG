#pragma once
#include <SFML/Graphics.hpp>
class Input
{

private:
	static sf::Vector2i  mousePosition;

	static int clickCountL;
	static int clickCountR;
	static int clickCountM;
	static int pressedTime;
public:
	static sf::Vector2i  mousePrevPosition;
	static float  mouseWheelScroll;
	static sf::Vector2f MousePosition;
	static sf::Vector2f MouseDelta;
	static void SetMousePosition(sf::Vector2i pos);
	static sf::Event::EventType LastEvent;

	static void updateEvents(sf::Window &target, sf::Event *e);
	static void clear();

	static bool MouseLeftClick;
	static bool MouseRightClick;
	static bool MouseDragLeft;
	static bool MouseDragRight;
	static bool MouseMiddleClick;

	static bool Scrolled;
};

