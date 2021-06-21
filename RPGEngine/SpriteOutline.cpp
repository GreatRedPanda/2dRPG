#include "stdafx.h"
#include "SpriteOutline.h"
#include <iostream>

SpriteOutline::SpriteOutline()
{
}

SpriteOutline::SpriteOutline(Vector2f parentPos, Vector2f botL, Vector2f topR)
{
	botLeft = new Vector2f(botL.x, botL.y);
	topRight = new Vector2f(botL.x, botL.y);
	//botRight = new Vector2f(topR.x, topR.y);

	topLeftSign->setFillColor(Color::Blue);
	botLeftSign->setFillColor(Color::Red);
	topRSign->setFillColor(Color::Green);
	botRSign->setFillColor(Color::Cyan);

	currentAnchor = topRight;
	updatePositions(botL, topR, parentPos);
}


SpriteOutline::~SpriteOutline()
{
}

void SpriteOutline::draw(RenderTarget * target)
{
	target->draw(*botRSign);
	target->draw(*botLeftSign);
	target->draw(*topLeftSign);
	target->draw(*topRSign);
}

void SpriteOutline::updatePositions( Vector2f localPos, Vector2f localPosScale, Vector2f parentPos)
{
	currentAnchor->x = localPos.x;
	currentAnchor->y = localPos.y;
	updateParentPos(localPosScale, parentPos);

}

void SpriteOutline::updateParentPos(Vector2f localPosScale, Vector2f parentOriginPos)
{
	Vector2f tR = Vector2f(topRight->x * localPosScale.x,
		topRight->y * localPosScale.y);
	Vector2f bL = Vector2f(botLeft->x * localPosScale.x,
		botLeft->y * localPosScale.y);
	cout << topRight->y << "  " <<
		topRight->x << "\n";
	topRSign->setPosition(tR + parentOriginPos);
	botLeftSign->setPosition(bL + parentOriginPos);
	botRSign->setPosition(bL + Vector2f(tR.x - bL.x, 0) + parentOriginPos);
	topLeftSign->setPosition(bL + Vector2f(0, tR.y - bL.y) + parentOriginPos);
}

bool SpriteOutline::getCoord(Vector2f pointerPos)
{
	bool mouseOverBotLeft = botLeftSign->getGlobalBounds().contains(pointerPos);
	if (mouseOverBotLeft)
	{
		currentAnchor = botLeft;
		return true;
	}
	bool mouseOverTopRight = topRSign->getGlobalBounds().contains(pointerPos);
	if (mouseOverTopRight)
	{
		currentAnchor = topRight;
		return true;
	}

	return false;
}
