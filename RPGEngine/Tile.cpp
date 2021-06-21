#include "stdafx.h"
#include "Tile.h"
#include "Input.h"

Tile *Tile::selectedTile = NULL;
vector <Tile*> Tile::allLoadedTilesCollection;
void Tile::addTileToCollection(Tile * tile)
{
	allLoadedTilesCollection.push_back(tile);
}

Tile* Tile::tileExists(string texturePath, Vector2i botCoords, Vector2i topCoords)
{

	//find tile
	return nullptr;
}

Tile::Tile()
{
	selectedTile = this;
}

void Tile::update()
{


	bool mouseOver = rect.getGlobalBounds().contains(Input::MousePosition);
	if (mouseOver)
	{
		rect.setFillColor(sf::Color::Green);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) )
		{
		
		}
	}


}
void Tile::setSprite(sf::Texture *texture)
{
	rect.setTexture(texture);
	rect.setTextureRect(sf::IntRect((int)ConnectedSprite->botLeft->x, 
		(int)ConnectedSprite->botLeft->y,
		abs((int)ConnectedSprite->botLeft->x- (int)ConnectedSprite->topRight->x),
		abs((int)ConnectedSprite->botLeft->y - (int)ConnectedSprite->topRight->y)
	));
}
void Tile::render(sf::RenderTarget * target)
{

	target->draw(rect);
}

sf::RectangleShape Tile::getTile(TM &tilemap, int x, int y)
{
	return rect;
}
rapidjson::Document Tile::saveJSON()
{
	rapidjson::Value json_val;
	rapidjson::Document doc;
	auto &alloc = doc.GetAllocator();
	doc.SetObject();

	json_val.SetInt(botLX);
	doc.AddMember("botLeftX", json_val, alloc);
	json_val.SetInt(botLY);
	doc.AddMember("botLeftY", json_val, alloc);
	json_val.SetInt(topRX);
	doc.AddMember("topRightX", json_val, alloc);
	json_val.SetInt(topRY);
	doc.AddMember("topRightY", json_val, alloc);
	json_val.SetString(texturePath.c_str(), alloc);
	doc.AddMember("texture", json_val, alloc);

	return doc;
}

Tile Tile::loadJSON(const rapidjson::Value & doc)
{

	uint64_t botLeftX = doc["botLeftX"].GetUint64();
	uint64_t botLeftY = doc["botLeftY"].GetUint64();
	uint64_t topRightX = doc["topRightX"].GetUint64();
	uint64_t topRightY = doc["topRightY"].GetUint64();
	std::string texturePath = doc["texture"].GetString();

	Tile *tile = Tile::tileExists(texturePath, sf::Vector2i(botLeftX, botLeftY), sf::Vector2i(topRightX, topRightY));
	if (tile!=nullptr)
	{
		return *tile;
	}
	else
	{
		Tile t = Tile(botLeftX, botLeftY, topRightX, topRightY, texturePath);
		Tile::addTileToCollection(&t);
		return t;
	}
	
}
