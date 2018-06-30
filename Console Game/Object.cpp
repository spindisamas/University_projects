#include <iostream>
#include <fstream>
#include <ctime>
#include "Object.h"

Object::Object(const char _graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], const Coords& _center):
	graphics(_graphics),
	dimX(1),
	dimY(1),
	center(_center),
	beginning(_center),
	lives(1),
	speed(MAX_SPEED),
	secondsStopped(0)
{
	srand((unsigned int)time(0));
}

Object::Object(const char _graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], const Coords& _center, unsigned _lives, const unsigned _speed) :
	graphics(_graphics),
	dimX(graphics.dimX),
	dimY(graphics.dimY),
	center(_center),
	beginning((_center.X - ((dimX / 2) - (dimX % 2 == 0))) , (_center.Y - ((dimY / 2) - (dimY % 2 == 0)))),
	lives(_lives),
	speed(_speed),
	secondsStopped(0)
{
	srand((unsigned int)time(0));
}

Object::Object(const char _graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], std::ifstream& in):
	graphics(_graphics),
	dimX(graphics.dimX),
	dimY(graphics.dimY)
{
	deserialize(in);
}

Object::~Object()
{
}

bool Object::move(const Move & _move)
{
	bool everythingIsStillOK = true;

	if (secondsStopped >= delay - speed)
	{
		secondsStopped = 0;

		if (_move.X == 0 && _move.Y == 0)
			return everythingIsStillOK;

		if ((beginning.X != 0 && _move.X < 0) || (beginning.X != WIDTH - dimX && _move.X > 0))
		{
			beginning.X += _move.X;
			center.X += _move.X;
		}
		else if(_move.X != 0)
			everythingIsStillOK = false;

		if ((beginning.Y != 2 && _move.Y > 0) || (beginning.Y != HEIGHT - dimY && _move.Y < 0))
		{
			beginning.Y -= _move.Y;
			center.Y -= _move.Y;
		}
		else if(_move.Y != 0)
			everythingIsStillOK = false;
	}
	else
		++secondsStopped;

	return everythingIsStillOK;
}

Coords Object::draw(char field[HEIGHT][WIDTH + 1])
{
	Coords collision(0, 0);
	for (size_t i = 0; i < dimY; i++)
	{
		for (size_t j = 0; graphics.graphics[i][j] != '\0'; j++)
		{
			if (graphics.graphics[i][j] != ' ')
			{
				if (graphics.graphics[i][j] != field[beginning.Y + i][beginning.X + j] && field[beginning.Y + i][beginning.X + j] != ' ')
				{
					collision.X = beginning.X + (unsigned short)j;
					collision.Y = beginning.Y + (unsigned short)i;
				}
				field[beginning.Y + i][beginning.X + j] = graphics.graphics[i][j];
			}
		}
	}
	return collision;
}

void Object::erase(char field[HEIGHT][WIDTH + 1])
{
	for (size_t i = 0; i < dimY; i++)
	{
		for (size_t j = 0; graphics.graphics[i][j] != '\0'; j++)
		{
			if(graphics.graphics[i][j] != ' ')
				field[beginning.Y + i][beginning.X + j] = ' ';
		}
	}
}

bool Object::collision(const Coords & coordsOfCollision)
{
	if (coordsOfCollision.Y >= beginning.Y && coordsOfCollision.Y < beginning.Y + dimY)
	{
		if (coordsOfCollision.X >= beginning.X && coordsOfCollision.X < beginning.X + dimX)
		{
			Coords coordsOnTheGraphics(coordsOfCollision.X - beginning.X, coordsOfCollision.Y - beginning.Y);

			if (graphics.graphics[coordsOnTheGraphics.Y][coordsOnTheGraphics.X] != ' ')
			{
				return true;
			}
		}
	}
	return false;
}

Coords Object::getCenter()
{
	return center;
}

Coords Object::getBeginning()
{
	return beginning;
}

bool Object::getHit()
{
	// returns true if the object is left with 0 lives
	--lives;
	return lives == 0 ? true : false;
}

unsigned short Object::getLives()
{
	return lives;
}

bool Object::deserialize(std::ifstream& in)
{
	in.read((char*)& center, sizeof(center));
	beginning.X = (center.X - ((dimX / 2) - (dimX % 2 == 0)));
	beginning.Y = (center.Y - ((dimY / 2) - (dimY % 2 == 0)));

	in.read((char*)& lives, sizeof(lives));
	in.read((char*)& speed, sizeof(speed));
	in.read((char*)& secondsStopped, sizeof(secondsStopped));

	return in.good();
}

bool Object::serialize(std::ofstream & out)
{
	out.write((const char*)& center, sizeof(center));
	out.write((const char*)& lives, sizeof(lives));
	out.write((const char*)& speed, sizeof(speed));
	out.write((const char*)& secondsStopped, sizeof(secondsStopped));

	return out.good();
}
