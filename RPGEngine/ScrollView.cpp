#include "stdafx.h"
#include "ScrollView.h"
#include <iostream>
#include "Input.h"
ScrollView::ScrollView()
{
}


ScrollView::~ScrollView()
{
}

void ScrollView::update()
{

	bool mouseOver = elementsContainer.getGlobalBounds().contains(Input::MousePosition);
	if (mouseOver)
	{
		for (auto &i : this->sceneObjects)
		{
			if(Input::Scrolled)
				//if (Input::LastEvent == sf::Event::MouseWheelScrolled)
			  i->size = Vector2f(i->size.x + 2, i->size.y +2);
	

			if(Input::MouseDragRight)
				i->center += Vector2f(Input::MouseDelta.x*2, Input::MouseDelta.y*2);
			i->update();
		}
	}
}

void ScrollView::render(sf::RenderTarget * target)
{

	Vector2f pos = Vector2f(center.x*scale.x, center.y*scale.y);
	Vector2f pos2 = pos+Vector2f(size.x / 2 * scale.x, size.y / 2 * scale.y);
	this->containerTexture->clear();
	this->containerTexture->setView(View(pos2, Vector2f(size.x*scale.x, size.y*scale.x)));
	this->containerTexture->draw(elementsContainer);
	this->containerTexture->display();
	const sf::Texture& t1 = this->containerTexture->getTexture();
	sf::Sprite sprite1(t1);
	sprite1.setPosition(pos);
	target->draw(sprite1);

	this->texture->clear();	
	this->texture->setView(View(pos2, Vector2f(size.x*scale.x, size.y*scale.x)));
	this->texture->draw(elementsContainer);
	for (auto &i: this->sceneObjects)
	{		
	// if (elementsContainer.getGlobalBounds().intersects(sf::FloatRect(i->center, i->size)))
		{
			i->render(this->texture);
		}
	}
	this->texture->display();
	const sf::Texture& t = this->texture->getTexture();	
	sf::Sprite sprite(t);
	sprite.setPosition(pos);
	maskShader->setUniform("_mainText", t);
    maskShader->setUniform("_maskText", t1);
	target->draw(sprite);

}

void ScrollView::resize(sf::Vector2f oldSize, sf::Vector2f newSize)
{

	
	float ratioX = newSize.x / oldSize.x;
	float ratioY = newSize.y / oldSize.y;

	float percent = (ratioX < ratioY) ? ratioY : ratioX;
	
	scale.x = percent;
	scale.y = percent;
	elementsContainer.setPosition(Vector2f(center.x*scale.x, center.y*scale.y));
	elementsContainer.setSize(Vector2f(size.x*scale.x, size.y*scale.y));
	for (auto &i : this->sceneObjects)
	{
		
			i->resize(oldSize, newSize);
		
	}
	containerTexture->create(size.x*scale.x, size.y*scale.y);
	
	texture->create(size.x*scale.x, size.y*scale.y);
	//cout << "percent " << size.x*scale.x<<"   "<<size.y*scale.y;
}

