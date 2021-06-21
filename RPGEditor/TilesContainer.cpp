#include "pch.h"
#include "TilesContainer.h"




TilesContainer::TilesContainer(ScrollView * scrollView)
{
	this->scrollView = scrollView;
}

TilesContainer::~TilesContainer()
{
}

void TilesContainer::handle()
{
	
	Tile  *t =new   Tile(scrollView->center, Vector2f(32,32));
	scrollView->addGameObject(t);
	tiles->push_back(t);
}


