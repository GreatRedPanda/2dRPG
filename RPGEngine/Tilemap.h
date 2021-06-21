#pragma once
#ifndef  TILEMAP_H
#define TILEMAP_H


#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "TileBase.h"
#include <vector>
//#include <map>
#include <unordered_map>
typedef class TileBase TB;
class Tilemap: public GameObject
{
	unordered_map<int, unordered_map<int, TB*>> tilesMap;
	vector<vector<TB *>> *tiles;

	sf::Vector2i mapSize;
	sf::Vector2f originalSize;
public:
	Tilemap();
	Tilemap(sf::Vector2i mapSize, sf::Vector2f scale, sf::Vector2f size);
	~Tilemap();
	void update() override;
	void render(sf::RenderTarget *target) override;
	void addTile(TB *tile, int x, int y);
	TB* getTile( int x, int y);
};

#endif // ! TILEMAP_H