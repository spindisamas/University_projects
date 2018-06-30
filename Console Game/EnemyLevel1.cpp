#include "EnemyLevel1.h"


EnemyLevel1::EnemyLevel1():
	Enemy(enemyType1, Coords(Type1.center.X, rand() % ((HEIGHT - Type1.dimY - 3) - (Type1.dimY + 2) + 1) + (Type1.dimY + 2)), LEVEL1)
{
	speed = 0;
	setPatternZigZag();
}

EnemyLevel1::EnemyLevel1(std::ifstream & in):
	Enemy(enemyType1, in)
{
}

EnemyLevel1::~EnemyLevel1()
{
}

Bullets * EnemyLevel1::shoot2()
{
	return shoot();
}

bool EnemyLevel1::deserialize(std::ifstream & in)
{
	return Enemy::deserialize(in);
}

bool EnemyLevel1::serialize(std::ofstream & out)
{
	return Enemy::serialize(out);
}
