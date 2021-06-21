#pragma once
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include <list>
#include "Rule.h"
#include "Tile.h"
#include "ScrollView.h"
#include "RuleTile.h"
#include "Button.h"
using namespace sf;
class RuleTileEditDrawer: public GameObject
{

	RectangleShape *rect;

	list<list <Button >> *rects ;
public:
	RuleTileEditDrawer(sf::Vector2f center, sf::Vector2f size) :GameObject(center, size)
	{
		this->rects = new list<list <Button>>();
		for (size_t n1 = 0; n1 < 3; n1++)
		{
			list <Button> rectsN =  list <Button>();
			for (size_t i = 0; i < 3; i++)
			{
				for (size_t j = 0; j < 3; j++)
				{
 					Button *b =new Button( Vector2f(0+ i * 60+center.x, 180 * n1+ j * 60+center.y),
						Vector2f(50, 50), nullptr, "buttin");

					rectsN.push_back(*b);
				}
			}
			
			this->rects->push_back(rectsN);
		}
	}
	~RuleTileEditDrawer();

	RuleTile *selectedRuleTile;
	void render(RenderTarget *target) override;
};

