#include "Boss.h"



Boss::Boss():
	Enemy(boss1, Coords(WIDTH - 9, HEIGHT / 2 + 6), BOSS)
{
	lives = 20;
	speed = MAX_SPEED - 3;
	for (size_t i = 0; i < WIDTH; i += 11)
	{
		for (size_t j = i; j < i + 11 && j < WIDTH; j++)
			pattern[j] = Move(0, 1);

		i += 11;

		for (size_t j = i; j < i + 11 && j < WIDTH; j++)
			pattern[j] = Move(0, -1);
	}
}

Boss::Boss(std::ifstream & in):
	Enemy(boss1, in)
{
}


Boss::~Boss()
{
}

bool Boss::move()
{
	if (currMove == WIDTH - 5 - 11)
		currMove = 0;

	bool success = this->Object::move(pattern[currMove]);
	if (secondsStopped == 0)
		++currMove;

	return success;
}

Bullets * Boss::shoot()
{
	return new Bullets(Coords(beginning.X - 1, beginning.Y), Move(-1, 0));
}

Bullets * Boss::shoot2()
{
	return new Bullets(Coords(beginning.X - 1, beginning.Y + dimY - 1), Move(-1, 0));
}

bool Boss::deserialize(std::ifstream & in)
{
	return Enemy::deserialize(in);
}

bool Boss::serialize(std::ofstream & out)
{
	return Enemy::serialize(out);
}
