#include "pch.h"
#include <iostream>
#include "Button.h"
#include "Application.h"
#include "Scene.h"
#include "GameObject.h"
#include "ScrollView.h"
#include "TextureSliceField.h"
#include <SFML/Main.hpp>

#include "boost/bind.hpp"
#include "boost/signals2.hpp"
#include "RuleTileEditDrawer.h"

#include "rapidjson.h"
#include "Document.h"
#include "StringBuffer.h"
#include "PrettyWriter.h"
#include <iostream>
#include <fstream>
#include "Rule.h"

#include "CAGenerator.h"
using namespace sf;

void setTiles(Tilemap &tm, int**map, int width, int height, TB *tile);
int main()
{
	std::string jsonLine;
	std::string line;
	std::ifstream in("ruleTile.tile"); // окрываем файл для чтения
	if (in.is_open())
	{
		while (getline(in, line))
		{
			jsonLine += line;
		}
	}
	in.close();
	rapidjson::Document doc2;
	doc2.Parse(jsonLine.c_str());
	RuleTile decodedUser = RuleTile::loadJSON(doc2);



	Tile ttt1 = Tile(3, 3, 23, 32, "C:\\Users\\Office_1\\source\\repos\\RPG\\Resources\\main.png");
	Tile ttt2 = Tile(3, 3, 23, 32, "C:\\Users\\Office_1\\source\\repos\\RPG\\Resources\\main.png");
	Tile ttt3 = Tile(3, 3, 23, 32, "C:\\Users\\Office_1\\source\\repos\\RPG\\Resources\\main.png");

	Tilemap tm = Tilemap(Vector2i(20,20),Vector2f(1, 1), Vector2f(1800, 1800));
	RenderTexture rt;
	RenderTexture rt2;
	Shader sh;
	ScrollView view = ScrollView(Vector2f(0, 0), Vector2f(1800, 1800), 5 , &rt, &rt2, &sh);
	view.addGameObject(&tm);
	int **map = CAGenerator::generate(40, 40, 4445334);
	setTiles(tm, map, 40, 40, &decodedUser);
	Application editor = Application(1920, 1024);
	Scene mainScene = Scene();
	mainScene.addGameObject(&view);

	editor.setActiveScene(&mainScene);
	editor.run();


}

void setTiles(Tilemap &tm, int**map ,int width, int height, TB *tile)
{
	for (int i = 0; i < width * 2; i++)
	{
		tm.addTile(tile, i, -2);
		tm.addTile(tile, i, -1);
		tm.addTile(tile, i, height*2);
		tm.addTile(tile, i, height * 2+1);

	}
	for (int i = 0; i < height * 2; i++)
	{
		tm.addTile(tile, -2, i);
		tm.addTile(tile, -1, i);
		tm.addTile(tile, width*2, i);
		tm.addTile(tile, width * 2+1, i);
	}
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{



			if (map[i][j] == 1)
			{
				for (int x = i * 2; x <= i * 2 + 1; x++)
				{
					for (int y = j * 2; y <= j * 2 + 1; y++)
					{
						tm.addTile(tile, x,y);
						
					}
				}
			}

		}

	}
}