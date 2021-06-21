#pragma once
#include "Button.h"
#include "Input.h"
#include <iostream>
#include "ScrollView.h"
#include "Tile.h"
#include <stdio.h>

#include "list"
//using namespace System;
//[event_receiver(native)]
class TilesContainer
{
	ScrollView *scrollView;
	list<Tile *> *tiles = new list<Tile *>();
public:
	TilesContainer(ScrollView *scrollView);
	~TilesContainer();
	
	void handle();


	void saveTile() 
	{
		for (auto &i : *tiles)
		{
			i->save();
		}

	}
};

