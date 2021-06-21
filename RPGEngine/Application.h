#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Scene.h"
using namespace sf;
using namespace std;

class Application
{
public:
	Application();
	Application(size_t width, size_t height);
	~Application();
	void update();
	void run();
	void render();
	void updateEvents();
	void setActiveScene(Scene *scene);
	RenderWindow* getWindow();
private:
	sf::RenderWindow *gameWindow;
	sf::Event gameInputEvent;
	list<Scene *> scenes;
	Scene *activeScene;
	sf::Vector2f targetSize;
};

