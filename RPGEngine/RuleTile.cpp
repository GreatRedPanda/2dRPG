#include "stdafx.h"
#include "RuleTile.h"



RuleTile::RuleTile()
{
	rect = sf::RectangleShape(Vector2f(32, 32));
	
		rect.setFillColor(sf::Color::Magenta);

}

RuleTile::~RuleTile()
{
}

rapidjson::Document RuleTile::saveJSON()
{
	rapidjson::Value json_val;
	rapidjson::Document doc;
	auto &alloc = doc.GetAllocator();
	doc.SetObject();


	json_val.SetArray();
	for (auto &rule : rules)
	{
		rapidjson::Value json_valR;
		json_val.PushBack(json_valR.CopyFrom(rule.getRuleJSON(), alloc), alloc);
		
	}

	doc.AddMember("ruleTile",json_val, alloc);
	return doc;
}
RuleTile RuleTile::loadJSON(const rapidjson::Value& doc)
{
	RuleTile rukeTile = RuleTile();
	const  rapidjson::Value& a = doc["ruleTile"];
	assert(a.IsArray());
	for (size_t i = 0; i < a.Size(); i++) // Uses SizeType instead of size_t
	{
		const  rapidjson::Value& ruleObj = a[i];
		Rule r1 = Rule::fromJson(ruleObj);
		rukeTile.rules.push_back(r1);
	}
	return rukeTile;
}

sf::RectangleShape RuleTile::getTile(TM &tilemap, int x, int y)
{
	std::string neighboursStr = "";
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			TB *neighbour = tilemap.getTile(x+j, y+i);
			if (neighbour == nullptr || neighbour != this)
			{
				neighboursStr += "X";
			}
			else if (neighbour == this)
			{
				neighboursStr += "O";
			}
		}
	}

	for (auto &rul: rules)
	{
		if (rul.compareRule(neighboursStr))
			return rul.tile.getTile(tilemap, x, y);
	}

	return rect;
}
