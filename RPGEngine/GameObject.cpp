#include "stdafx.h"
#include "GameObject.h"
#include <iostream>

GameObject::GameObject(sf::Vector2f center, sf::Vector2f size)
{
	this->center = center;
	this->size = size;
	scale = Vector2f(1, 1);
}

GameObject::GameObject()
{

	this->center = Vector2f(0, 0);
	this->size = Vector2f(1, 1);
}


GameObject::~GameObject()
{
}

void GameObject::update()
{
}

void GameObject::render(sf::RenderTarget * target)
{
}

void GameObject::resize(sf::Vector2f oldSize, sf::Vector2f newSize)
{

	float ratioX = newSize.x / oldSize.x;
	float ratioY = newSize.y / oldSize.y;

	float percent = (ratioX < ratioY) ? ratioY : ratioX;
	cout << "percent " << percent;
	scale.x = percent;
	scale.y = percent;
}
void GameObject::addGameObject(GameObject * gameObject)
{
	sceneObjects.push_back(gameObject);
}

void GameObject::setActive()
{
	IsActive = !IsActive;
}


