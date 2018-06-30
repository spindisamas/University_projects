#ifndef OBJECT_H_
#define OBJECT_H_
#include <fstream>
#include "SideFuncs.h"

class Object
{
public:
	Object(const char graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], const Coords& center);
	Object(const char graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], const Coords& center, unsigned lives, const unsigned speed);
	Object(const char graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], std::ifstream& in);

	virtual ~Object();

	bool move(const Move& _move);

	Coords draw(char field[HEIGHT][WIDTH + 1]);
	void erase(char field[HEIGHT][WIDTH + 1]);

	bool collision(const Coords& coordsOfCollision);

	Coords getCenter();
	Coords getBeginning();
	bool getHit();

	unsigned short getLives();

	virtual bool deserialize(std::ifstream& in);
	virtual bool serialize(std::ofstream& out);

	const Graphics graphics;

	const unsigned dimX;
	const unsigned dimY;

protected:
	Coords center;
	Coords beginning;

	short lives;
	unsigned speed;
	unsigned secondsStopped;
};

#endif // !OBJECT_H_
