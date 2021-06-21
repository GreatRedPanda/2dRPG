#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Scene.h"
#include "GameObject.h"
using namespace sf;
using namespace std;
class SpriteOutline
{

	CircleShape *topLeftSign= new CircleShape(4);
	CircleShape *botLeftSign = new  CircleShape(4);
	CircleShape *topRSign = new  CircleShape(4);
	CircleShape *botRSign = new  CircleShape(4);

	Vector2f *currentAnchor;
public:
	SpriteOutline();
	SpriteOutline(Vector2f parentPos, Vector2f botL, Vector2f topR);
	~SpriteOutline();
	void draw(RenderTarget *target);
	Vector2f pivot;
	Vector2f *botLeft;
	Vector2f *topRight;

	void updatePositions(Vector2f localPos, Vector2f localPosScale, Vector2f parentPos);
	void updateParentPos(Vector2f localPosScale, Vector2f parentOriginPos);
	bool getCoord(Vector2f pointerPos);

	
};

