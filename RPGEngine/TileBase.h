#pragma once
#include "GameObject.h"
#include "SFML/GpuPreference.hpp"
#include <list>
#include "rapidjson.h"
#include "Document.h"
#include "Tilemap.h"
#include <vector>
typedef class Tilemap TM;
class TileBase
{
public:
	/*TileBase();
	~TileBase();*/
	virtual rapidjson::Document saveJSON()=0;
	virtual sf::RectangleShape getTile(TM &tilemap, int x, int y) = 0;

	
};

