#include "Enemy.h"

Enemy::Enemy(const char graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], const Coords& center, const EnemyLevel _level):
	Player(graphics, center, 1),
	level(_level),
	currMove(0)
{
	speed = 0;

	for (size_t i = 0; i < WIDTH; i++)
		pattern[i] = Move();
}

Enemy::Enemy(const char _graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], std::ifstream & in):
	Player(_graphics, in)
{
	deserialize(in);
}


Enemy::~Enemy()
{
}

bool Enemy::move()
{
	if (currMove == WIDTH)
		currMove = 0;

	bool success = this->Object::move(pattern[currMove]);
	if (secondsStopped == 0)
		++currMove;

	return success;
}

Bullets * Enemy::shoot()
{
	unsigned shootChance = rand() % 75;
	if(!shootChance)
		return new Bullets(Coords(beginning.X - 1, center.Y), Move(-1, 0));

	return nullptr;
}

EnemyLevel Enemy::getLvl()
{
	return (EnemyLevel)level;
}

bool Enemy::deserialize(std::ifstream & in)
{
	in.read((char*)& level, sizeof(level));
	for (size_t i = 0; i < WIDTH; i++)
	{
		in.read((char*)& pattern[i], sizeof(pattern[i]));
	}
	in.read((char*)& currMove, sizeof(currMove));
	
	return in.good();
}

bool Enemy::serialize(std::ofstream & out)
{
	out.write((const char*)& level, sizeof(level));
	Player::serialize(out);

	out.write((const char*)& level, sizeof(level));
	for (size_t i = 0; i < WIDTH; i++)
	{
		out.write((const char*)& pattern[i], sizeof(pattern[i]));
	}
	out.write((const char*)& currMove, sizeof(currMove));

	return out.good();
}

void Enemy::setPatternZigZag()
{
	for (size_t i = 0; i < WIDTH; i += 3)
	{
		for (size_t j = i; j < i + 3 && j < WIDTH; j++)
			pattern[j] = Move(-1, 1);

		i += 3;

		for (size_t j = i; j < i + 3 && j < WIDTH; j++)
			pattern[j] = Move(-1, -1);
	}
}
