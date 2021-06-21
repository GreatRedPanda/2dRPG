#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "SpriteOutline.h"
#include <list>
class TextureSliceField : public GameObject
{
	Vector2f *currnt;
	sf::RectangleShape rect;
	sf::Texture editingTexture;
	list<SpriteOutline *> *spritesBounds=new  list<SpriteOutline *>();
	SpriteOutline *currentBounds;
	int pressed = 0;
public:
	TextureSliceField();
	TextureSliceField(sf::Vector2f center, sf::Vector2f size, std::string textureLoad)
		:GameObject(center, size)
	{
		rect = sf::RectangleShape(size);
		rect.setPosition(center);

		editingTexture.loadFromFile(textureLoad);
		rect.setTexture(&editingTexture);
	}
	~TextureSliceField();
	void update() override;
	void render(sf::RenderTarget *target) override;
};

