#include "Enemy2.h"



Enemy2::Enemy2():
	Enemy(enemyType2, Coords(Type2.center.X, rand() % ((HEIGHT - Type2.dimY - 3) - (Type2.dimY + 2) + 1) + (Type2.dimY + 2)), LEVEL2)
{
	lives = 2;
	speed = MAX_SPEED / 3;
	setPatternZigZag();
}

Enemy2::Enemy2(std::ifstream & in) :
	Enemy(enemyType2, in)
{
}


Enemy2::~Enemy2()
{
}

Bullets * Enemy2::shoot2()
{
	return shoot();
}

bool Enemy2::deserialize(std::ifstream & in)
{
	return Enemy::deserialize(in);
}

bool Enemy2::serialize(std::ofstream & out)
{
	return Enemy::serialize(out);
}
