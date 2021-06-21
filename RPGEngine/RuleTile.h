#pragma once
#include "GameObject.h"
#include "SFML/GpuPreference.hpp"
#include <list>
#include "TileBase.h"
#include "Rule.h"
#include "Tilemap.h"
class RuleTile: public TileBase
{
	sf::RectangleShape rect;
public:
	RuleTile();
	~RuleTile();
	list<Rule> rules;// = list<Rule*>();
	
	rapidjson::Document saveJSON() override;
	sf::RectangleShape getTile(TM &tilemap, int x, int y) override;

   static RuleTile loadJSON(const rapidjson::Value & doc);
	
};

