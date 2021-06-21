#include "stdafx.h"
#include "TextureSliceField.h"
#include <iostream>
#include "Input.h"
#include "Tile.h"
TextureSliceField::TextureSliceField()
{
}


TextureSliceField::~TextureSliceField()
{
}

void TextureSliceField::update()
{

	rect.setPosition(Vector2f(center.x*scale.x, center.y*scale.y));
	rect.setSize(Vector2f(size.x*scale.x, size.y*scale.y));
	bool mouseOverBotLeft = rect.getGlobalBounds().contains(Input::MousePosition);
	if (mouseOverBotLeft)
	{
		Vector2f sc = Vector2f(size.x*scale.x / 1024, size.y*scale.y / 1024);
		Vector2f localPos = Vector2f((-center.x + Input::MousePosition.x) / sc.x,
			(-center.y + Input::MousePosition.y) / sc.x);


		if (Input::LastEvent == sf::Event::MouseButtonPressed && pressed == 0)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				pressed = 1;
				bool over = false;
				for (auto i : *spritesBounds)
				{
					over = i->getCoord(Input::MousePosition);
					if (over)
						currentBounds = i;
				}
				if (!over)
				{
					currentBounds = new SpriteOutline(center, localPos, sc);
					spritesBounds->push_back(currentBounds);
					Tile::selectedTile->ConnectedSprite = currentBounds;
				}
			}
		}

		if (Input::LastEvent == sf::Event::MouseMoved)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (currentBounds != nullptr)
				{
					currentBounds->updatePositions(localPos, sc, center);
				}
			}
		}
		if (Input::LastEvent == sf::Event::MouseButtonReleased)
		{
			pressed = 0;
		}
		for (auto i : *spritesBounds)
		{
			i->updateParentPos(sc, Vector2f(center.x*scale.x,
				center.y*scale.y));

		}
		if(Tile::selectedTile!=NULL && currentBounds!=nullptr)
		Tile::selectedTile->setSprite(&editingTexture);
	}
}

void TextureSliceField::render(sf::RenderTarget * target)
{
	target->draw(this->rect);

	for (auto i : *spritesBounds)
	{
		i->draw(target);
	}
}
