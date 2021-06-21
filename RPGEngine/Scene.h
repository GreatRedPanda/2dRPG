#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "GameObject.h"

using namespace sf;
using namespace std;

class Scene
{
private:

	list<GameObject *> sceneObjects;
public:
	Scene();
	~Scene();
	void update();
	void render(sf::RenderTarget *target);
	void addGameObject(GameObject *gameObject);
	void deleteGameObject(GameObject *gameObject);
	virtual void resize(sf::Vector2f oldSize, sf::Vector2f newSize);
};

