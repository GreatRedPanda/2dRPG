#include "stdafx.h"
#include "Application.h"
#include "Input.h"
#include <iostream>

Application::Application()
{
}

Application::Application(size_t width, size_t height)
{
	this->gameWindow = new  RenderWindow(VideoMode(width, height), "Name");
	targetSize = Vector2f(width, height);
}


Application::~Application()
{
}
void Application::update()
{

	this->activeScene->update();
}

void Application::run()
{

	while (this->gameWindow->isOpen())
	{
		this->updateEvents();
		this->update();

		this->render();
	}
}

void Application::render()
{

	this->gameWindow->clear();

	this->activeScene->render(gameWindow);
	this->gameWindow->display();
}

void Application::updateEvents()
{
	//Input::mouseWheelScroll = 0;
	Input::clear();
	while (this->gameWindow->pollEvent(this->gameInputEvent))
	{
		Input::LastEvent = this->gameInputEvent.type;
		if (this->gameInputEvent.type == Event::Closed)
		{
			this->gameWindow->close();
		}
		
		if (this->gameInputEvent.type == Event::Resized)
		{
			Vector2u size = this->gameWindow->getSize();
			Vector2f	viewSize = Vector2f(size.x, size.y);
			View view(Vector2f(size.x / 2, size.y / 2), viewSize);
			this->gameWindow->setView(view);
			this->activeScene->resize(targetSize, viewSize);
		}
		Input::updateEvents(*gameWindow, &gameInputEvent);
	}

	

}

void Application::setActiveScene(Scene *scene)
{
	activeScene = scene;
}

RenderWindow* Application::getWindow()
{

	RenderWindow *w = this->gameWindow;

	return w;
}