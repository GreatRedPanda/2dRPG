#pragma once
#include <random>
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>    // std::find
#include <math.h>    // std::find
using namespace std;
class CAGenerator
{


	class Room
	{

	public:
		 int MaxX;
		 int MaxY;

		 int MinX;
		 int MinY;

		 std::vector< sf::Vector2i> positions;
		 std::vector< sf::Vector2i> edgePositions;
		 std::list< Room> connectedRooms;
		 float Distance(Room other)
		 {
			 sf::Vector2i pos1 = positions[0];
			 sf::Vector2i pos2 = other.positions[0];
			 float r = std::pow((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y), 0.5f);
			 return r;
		 }

		 bool isConnected(Room other)
		 {		
			 for (auto &i : connectedRooms)
			 {
				 if (&i == &other)
				 {
					 return true;
				 }

			 }
			 for (auto &i : other.connectedRooms)
			 {
				 if (&i == this)
				 {
					 return true;
				 }

			 }
			 return false;
		 }
	
		 std::vector< sf::Vector2i> ConnectRooms(Room other)
		 {

		
			 sf::Vector2i coordR1 = sf::Vector2i(edgePositions[0]);
			 sf::Vector2i coordR2 = sf::Vector2i(other.edgePositions[0]);
			 sf::Vector2i bestCoordThis = coordR1;
			 sf::Vector2i bestCoordOther = coordR2;
			 float bestDistance = std::pow((coordR1.x - coordR2.x)*(coordR1.x - coordR2.x) +
				 (coordR1.y - coordR2.y)*(coordR1.y - coordR2.y), 0.5f);
			 for(auto  &coord : edgePositions)
			 {
				 for (auto &otherCoord : other.edgePositions)
				 {

					 coordR1 = coord;
					 coordR2 = otherCoord;
					 float distance = std::pow((coordR1.x - coordR2.x)*(coordR1.x - coordR2.x) +
						 (coordR1.y - coordR2.y)*(coordR1.y - coordR2.y), 0.5f);
					 if (distance < bestDistance)
					 {
						 bestDistance = distance;
						 bestCoordThis = sf::Vector2i(coord);
						 bestCoordOther = sf::Vector2i(otherCoord);
					 }
				 }
			 }
			 std::vector< sf::Vector2i> result = std::vector< sf::Vector2i>();
			 result.push_back(bestCoordThis);
			 result.push_back(bestCoordOther);
			 return result;
		 }

	
	
	};
public:

static	int ** generate(int width, int height, int seed)
	{
				
		srand(seed);

		int** map ;
		map = new int*[width];
		for (int i = 0; i < width; i++)
			map[i] = new int[height];

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{


				if (rand()%100/100.0 > 0.45)
					map[i][ j] = 1;
			}

		}


		for (int i = 0; i < 1; i++)
		{
			map = doSimulationStep(map, 3, 4, width, height);
		}

		std::vector< sf::Vector2i> takenPositions = std::vector< sf::Vector2i>();

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{


				if (map[i][ j] !=1)
				{
					takenPositions.push_back(sf::Vector2i(i, j));
				}
			}
		}

		std::list<Room> rooms = std::list<Room>();
		CreateRooms(rooms, map, takenPositions, width, height);
		map=connectNearestRooms(rooms,0, map);

		return map;
	}

static	int ** doSimulationStep(int **baseMap, int deathLimit, int birthLimit, int _width, int _height)
	{
		 int **newMap;
		 newMap =new  int *[_width];
		 for (int i = 0; i < _width; i++)
			 newMap[i] = new int[_height];


		for (int i = 0; i < _width; i++)
		{
			for (int j = 0; j < _height; j++)
			{
				int aliveNeighbours = countAliveNeighbours(baseMap, i, j, _width, _height);

				if (baseMap[i][j] == 1)
				{
					if (aliveNeighbours > deathLimit)
					{
						newMap[i][ j] = 1;
					}
				}
				else
				{
					if (aliveNeighbours > birthLimit)
					{
				
						newMap[i][ j] = 1;
					}
				}
			}
		}
		return newMap;
	}

static	 int countAliveNeighbours(int **map, int x, int y, int _width, int _height)
	{

		int count = 0;


		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{

				if (i == 0 && j == 0)
					continue;
				int n_x = x + i;
				int n_y = j + y;

				if (n_x < 0 || n_y < 0 || n_x >= _width || n_y >= _height)
				{
					count++;
					continue;
				}
				if (map[n_x][n_y] == 1)
				{

					count++;
				}


			}
		}
		return count;

	}



static void CreateRooms(std::list<Room> &rooms, int **map, std::vector< sf::Vector2i> &positions, int _width, int _height)
{
	while (positions.size() != 0)
	{
		Room r =  Room();
		sf::Vector2i currentPos = positions[0];
		std::vector< sf::Vector2i> result = std::vector< sf::Vector2i>();
		result.push_back(currentPos);
		positions.erase(positions.begin());
		std::vector< sf::Vector2i> neighbours = std::vector< sf::Vector2i>();
		neighbours.push_back(currentPos);
		do
		{
			neighbours.erase(neighbours.begin());
			std::vector< sf::Vector2i> n = getFilledNeighbours(map, currentPos, _width, _height);
			for(auto  &nn : n)
			{

				std::vector<sf::Vector2i>::iterator	itn = std::find(neighbours.begin(), neighbours.end(), nn);
				std::vector<sf::Vector2i>::iterator	itr= std::find(result.begin(), result.end(), nn);

				if (itn==neighbours.end() && itr == result.end())
				{
					neighbours.push_back(nn);
				}
			}
			if (neighbours.size() == 0)
				break;
			currentPos = neighbours[0];
			result.push_back(currentPos);
			std::vector<sf::Vector2i>::iterator	it = std::find(positions.begin(), positions.end(), currentPos);
			if (it != positions.end())
			 positions.erase(it);
		} while (neighbours.size() != 0);


		if (result.size() > 2)
		{
			r.positions = result;
			getRoomEdgeCoords(r, map, _width, _height);
			rooms.push_back(r);

		}
	}



}





static void getRoomEdgeCoords(Room &r, int** map, int width, int height)
{
	for(auto &c : r.positions)
	{
		std::vector< sf::Vector2i>  neighbours = std::vector< sf::Vector2i>();

		neighbours.push_back(c + sf::Vector2i(0,1));
		neighbours.push_back(c - sf::Vector2i(0, 1));
		neighbours.push_back(c + sf::Vector2i(1, 0));
		neighbours.push_back(c - sf::Vector2i(1, 0));


		for(auto &n : neighbours)
		{


			if (n.y < 0 || n.x < 0 || n.y >= height || n.x >= width)
			{
				std::vector<sf::Vector2i>::iterator	itn = std::find(r.edgePositions.begin(), r.edgePositions.end(), c);
				if(itn==r.edgePositions.end())
				r.edgePositions.push_back(c);
				continue;
			}
			if (map[n.x][n.y] == 1)
			{
				std::vector<sf::Vector2i>::iterator	itn = std::find(r.edgePositions.begin(), r.edgePositions.end(), c);
				if (itn == r.edgePositions.end())
					r.edgePositions.push_back(c);
			}

		}

	}

}
static std::vector< sf::Vector2i> getFilledNeighbours(int** map, sf::Vector2i start,int width, int height)
{
	std::vector< sf::Vector2i> neighbours = std::vector< sf::Vector2i>();
	std::vector< sf::Vector2i> result =  std::vector< sf::Vector2i>();
	neighbours.push_back(start + sf::Vector2i(0, 1));
	neighbours.push_back(start - sf::Vector2i(0, 1));
	neighbours.push_back(start + sf::Vector2i(1, 0));
	neighbours.push_back(start - sf::Vector2i(1, 0));




	for (auto &n : neighbours)
	{


		if (n.y < 0 || n.x < 0 || n.y >= width || n.x >= height)
			continue;

		if (map[n.x][ n.y] !=1)
			result.push_back(n);

	}

	return result;

}

static int** connectNearestRooms(std::list<Room> &rooms,float threshold, int** map)
{
	for(auto &r : rooms)
	{

		Room connectionRoom;

		float distance = 200000000;
		for (auto &r2 : rooms)
		{


			if (&r == &r2 || r.isConnected(r2))
				continue;
			float newDistance = r.Distance(r2);
			if (distance > newDistance)
			{

				connectionRoom = r2;
				distance = newDistance;
			}

		}


		r.connectedRooms.push_back(connectionRoom);

		map=carvePassage(r, connectionRoom, map);
	}
	return map;
}

static int** carvePassage(Room r1, Room r2, int** map)
{
	std::vector< sf::Vector2i> tiles = r1.ConnectRooms(r2);
	
	int dx = (int)abs(tiles[1].x - tiles[0].x);
	int stepX = (tiles[0].x < tiles[1].x) ? 1 : -1;
	int dy = (int)abs(tiles[1].y - tiles[0].y);
	int stepY = (tiles[0].y < tiles[1].y) ? 1 : -1;

	int error = (dx > dy ? dx : -dy) / 2;
	int moreMove = 0;
	while (true)
	{
		map[tiles[0].x][tiles[0].y] = 0;
		if (moreMove == 1)
			break;
		if (tiles[0].x == tiles[1].x && tiles[0].y == tiles[1].y)
		{
			moreMove = 1;
		}
		int e2 = error;
		if (e2 < dy)
		{

			error += dx;
			tiles[0].y += stepY;
		}

		if (e2 > -dx)
		{
			error -= dy;
			tiles[0].x += stepX;

		}
	}
	return map;
}

};

