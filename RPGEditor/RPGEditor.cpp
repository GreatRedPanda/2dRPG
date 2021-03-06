// RPGEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Button.h"
#include "Application.h"
#include "Scene.h"
#include "GameObject.h"
#include "ScrollView.h"
#include "TextureSliceField.h"
#include <SFML/Main.hpp>
#include "TilesContainer.h"
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


using namespace sf;

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

	Tilemap tm = Tilemap();
	//tm.addTile(&decodedUser, 3, 4);
	//tm.addTile(&decodedUser, 5, 4);
	//tm.addTile(&decodedUser, 6, 4);
	//tm.addTile(&decodedUser, 3, 5);

	tm.addTile(&decodedUser, 3, 3);
	tm.addTile(&decodedUser, 4, 3);
	tm.addTile(&decodedUser, 5, 3);
	tm.addTile(&decodedUser, 3, 4);
	tm.addTile(&decodedUser, 4, 4);
	tm.addTile(&decodedUser, 5, 4);
	tm.addTile(&decodedUser, 6, 4);
	tm.addTile(&decodedUser, 6, 5);
	tm.addTile(&decodedUser, 3, 5);
	tm.addTile(&decodedUser, 4, 5);
	tm.addTile(&decodedUser, 5, 5);
	//tm.addTile(&ttt1,7, 4);
	//tm.addTile(&ttt2, 8, 5);
	//tm.addTile(&ttt1, 8, 4);
	//tm.addTile(&ttt2, 8, 6);
	tm.setActive();
	Application editor = Application(1920, 1024);
	Scene mainScene = Scene();
	Font f = Font();
	f.loadFromFile("C:\\Users\\Office_1\\source\\repos\\RPG\\Resources\\kenvector_future.ttf");


	Button button = Button(Vector2f(10, 580), Vector2f(190, 120), &f, "Add tile" );
	Button button2 = Button(Vector2f(10, 700), Vector2f(190, 120), &f, "Add rule tile");
	Button button3 = Button(Vector2f(110, 700), Vector2f(190, 120), &f, "Delete tile");
	Button button4 = Button(Vector2f(110, 580), Vector2f(190, 120), &f, "Change tileset");
	Button button5 = Button(Vector2f(10, 10), Vector2f(150, 120), &f, "Tiles");
	Button button6 = Button(Vector2f(80, 10), Vector2f(190, 120), &f, "Textures");

	
	TextureSliceField tsf = TextureSliceField(Vector2f(500, 10), Vector2f(1024, 1024),
		"C:\\Users\\Office_1\\source\\repos\\RPG\\Resources\\main.png");

	RenderTexture t1; 
	RenderTexture t2;
	RenderTexture t3;
	RenderTexture t4;
	Shader maskShader;
	ScrollView sv = ScrollView(Vector2f(20, 50), Vector2f(200, 500), 5, &t1, &t2, &maskShader);
	ScrollView svTE = ScrollView(Vector2f(500, 10), Vector2f(1200, 1000), 5, &t3, &t4, &maskShader);
	svTE.addGameObject(&tsf);
	mainScene.addGameObject(&button);
	mainScene.addGameObject(&button2);
	mainScene.addGameObject(&button3);
	mainScene.addGameObject(&button4);
	mainScene.addGameObject(&button5);
	mainScene.addGameObject(&button6);
	mainScene.addGameObject(&sv);
	mainScene.addGameObject(&svTE);
	mainScene.addGameObject(&tm);

	TilesContainer tc = TilesContainer(&sv);

	button.OnPressed.connect(boost::bind(&TilesContainer::handle, &tc));
	button2.OnPressed.connect(boost::bind(&TilesContainer::saveTile, &tc));

	RuleTileEditDrawer rted = RuleTileEditDrawer(Vector2f(500, 10), Vector2f(1200, 1000));
	mainScene.addGameObject(&rted);
	button5.OnPressed.connect(boost::bind(&RuleTileEditDrawer::setActive, &rted));
	button5.OnPressed.connect(boost::bind(&ScrollView::setActive, &svTE));
	button6.OnPressed.connect(boost::bind(&Tilemap::setActive, &tm));

	editor.setActiveScene(&mainScene);
	editor.run();
	
}



//Tile ttt1 = Tile(3, 3, 23, 32, "C:\\Users\\Office_1\\source\\repos\\RPG\\Resources\\main.png");

	//Rule rr1 = Rule();
	//rr1.rule.push_back("XX-");
	//rr1.rule.push_back("XOX");
	//rr1.rule.push_back("---");
	//rr1.tile = ttt1;
	//
	//RuleTile ruleTile1 = RuleTile();
	//ruleTile1.rules.push_back(rr1);
	//rapidjson::Document doc1 = ruleTile1.saveJSON();



	//rapidjson::StringBuffer buffer;
	//// rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	//rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	//doc1.Accept(writer);
	//const std::string& str223 = buffer.GetString();
	//std::cout << "Serialized:" << std::endl;
	//std::cout << str223 << std::endl;

	//string str = "";
	//rapidjson::Document doc2;
	//doc2.Parse(str223.c_str());
	//RuleTile decodedUser = RuleTile::loadJSON(doc2);

