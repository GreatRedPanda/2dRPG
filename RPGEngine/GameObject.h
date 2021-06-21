#pragma once
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;
using namespace std;
class GameObject
{
protected:

	sf::Vector2f scale;
	list<GameObject *> sceneObjects = list<GameObject *>();
public:
	GameObject(sf::Vector2f center, sf::Vector2f size);
	GameObject();
	~GameObject();
	virtual void update();
	virtual	void render(sf::RenderTarget *target);
	virtual void resize(sf::Vector2f oldSize, sf::Vector2f newSize);
	sf::Vector2f center;
	sf::Vector2f size;
	GameObject *parent;
	void addGameObject(GameObject *gameObject);
	void setActive();
	bool IsActive=true;
};

