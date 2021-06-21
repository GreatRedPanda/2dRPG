#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "SpriteOutline.h"
#include "rapidjson.h"
#include "Document.h"
#include "StringBuffer.h"
#include "PrettyWriter.h"
#include <iostream>
#include <fstream>
#include "TileBase.h"
class Tile: public GameObject, public TileBase
{
private:
	string texturePath;
	int botLX;
	int botLY;
	int topRX;
	int topRY;
	sf::RectangleShape rect;
	Texture *texture;
public:
	Tile();
	Tile(int bLX, int bLY, int tRX, int tRY, string texturePath)
	{
		botLX = bLX; botLY = bLY;
		topRY = tRX; topRY = tRY;
		this->texturePath = texturePath;
		loadTexture();
		rect = sf::RectangleShape(Vector2f(32,32));
		if (this->texture == nullptr)
		{
			rect.setFillColor(sf::Color::Magenta);
		}
		else
		{
			rect.setTexture(this->texture);
			rect.setTextureRect(sf::IntRect(botLX, botLY, 32, 32));
		}
	}
	void loadTexture()
	{
		texture = new Texture();
		texture->loadFromFile(this->texturePath);
	}
	Tile(sf::Vector2f center, sf::Vector2f size)
		:GameObject(center, size)
	{
		selectedTile = this;
		rect = sf::RectangleShape(size);
		rect.setPosition(center);
		rect.setFillColor(sf::Color::Magenta);
	}
	~Tile() {
	
	
	}

	static  Tile *selectedTile;
	
	SpriteOutline *ConnectedSprite=NULL;

	void setSprite(sf::Texture *texture);
	void update() override;
	rapidjson::Document saveJSON() override;
	static Tile loadJSON(const rapidjson::Value & doc);
	static vector <Tile*> allLoadedTilesCollection;
	static void addTileToCollection(Tile *tile);
	static Tile* tileExists(string texturePath, Vector2i botCoords, Vector2i topCoords);
	sf::RectangleShape getTile(TM &tilemap, int x, int y) override;

	void render(sf::RenderTarget *target)override;
	void save()
	{
		rapidjson::Value json_val;
		rapidjson::Document doc;
		auto &alloc = doc.GetAllocator();
		doc.SetObject();

		json_val.SetInt(ConnectedSprite->botLeft->x);
		doc.AddMember("botLeftX", json_val, alloc);
		json_val.SetInt(ConnectedSprite->botLeft->y);
		doc.AddMember("botLeftY", json_val, alloc);
		json_val.SetInt(ConnectedSprite->topRight->x);
		doc.AddMember("topRightX", json_val, alloc);
		json_val.SetInt(ConnectedSprite->topRight->y);
		doc.AddMember("topRightY", json_val, alloc);
		json_val.SetString(texturePath.c_str(), alloc);
		doc.AddMember("texture", json_val, alloc);

		//rapidjson::StringBuffer buffer;
		//
		//rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		//doc.Accept(writer);

		//const std::string& str = buffer.GetString();
		//cout << str;
		//std::ofstream saveFile("tile1.tile");
		//saveFile.write((char *)&str, sizeof(str));

	}
};

