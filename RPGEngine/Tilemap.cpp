#include "stdafx.h"
#include "Tilemap.h"


Tilemap::Tilemap()
{
	this->center = Vector2f(300, 0);

}

Tilemap::Tilemap( sf::Vector2i mapSize, sf::Vector2f scale, sf::Vector2f size)
{
	this->scale = scale;
	this->size = size;
	this->originalSize = Vector2f(1800*3,1800*3);
	this->mapSize = mapSize;
}
Tilemap::~Tilemap()
{
}

void Tilemap::update()
{
}

void Tilemap::render(sf::RenderTarget * target)
{

	Vector2f sc = Vector2f(size.x/ originalSize.x, size.y/ originalSize.y);
	for (auto &i: tilesMap)
	{
		int x = i.first;
		for (auto &j : i.second)
		{
			int y = j.first;

		RectangleShape s=tilesMap[x][y]->getTile(*this, x, y);
		s.setScale(sc);
		s.setPosition(Vector2f(center.x + x * 32*sc.x, center.y+y * 32 * sc.y));
		target->draw(s);
		}

	}
}

void Tilemap::addTile(TB * tile, int x, int y)
{




	if (tilesMap.find(x) !=tilesMap.end())
	{
		// если ряд был

		unordered_map<int, TB*> row = tilesMap[x];

		//такой элемент уже может быть. Если есть, тогда replace
		if (tilesMap[x].find(y) != tilesMap[x].end())
		{
			//tilesMap[x].
			//replace
		}
		else
		{
			tilesMap[x].insert(std::pair<int, TB*>(y, tile));
		}
	}
	else
	{

		//еслм ряда не было
		unordered_map<int, TB*> row;
		row.insert(std::pair<int, TB*>(y,tile));
		tilesMap.insert(std::pair<int, unordered_map<int, TB*>>(x, row));
	}
}

TB * Tilemap::getTile(int x, int y)
{
	
	TB *tb = nullptr;
	
	if (tilesMap.find(x) != tilesMap.end())
	{
		if (tilesMap[x].find(y) != tilesMap[x].end())
		{
			tb = tilesMap[x][y];
		}
		
	}
	
	return tb;
}
