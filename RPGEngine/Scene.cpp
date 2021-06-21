#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	this->sceneObjects =  list<GameObject *>();
}


Scene::~Scene()
{
	//delete &sceneObjects;
}

void Scene::update()
{
	for (GameObject *go : sceneObjects)
	{
		if(go->IsActive)
		go->update();
	}
}

void Scene::render(sf::RenderTarget* target)
{
	for (list<GameObject *>::const_iterator iter =sceneObjects.begin(),
		endIter = sceneObjects.end();
		iter != endIter;
		++iter)
	{
		GameObject *object = *iter;
		if (object->IsActive)
		object->render(target);
	}
}
void Scene::addGameObject(GameObject *gameObject)
{
	sceneObjects.push_back(gameObject);

}

void Scene::deleteGameObject(GameObject *gameObject)
{
	sceneObjects.remove(gameObject);
	gameObject->~GameObject();
}

void Scene::resize(sf::Vector2f oldSize, sf::Vector2f newSize)
{
	for (auto &i : sceneObjects)
	{
		i->resize( oldSize,  newSize);
	}
}
