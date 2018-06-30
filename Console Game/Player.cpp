#include <iostream>
#include <ctime>
#include "Player.h"

static unsigned long long timeOfShooting = 0;
//static unsigned long long timePassed = currTime; // time passed from the last shooting


Player::Player(const char _graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], const Coords& center, unsigned short lives) :
	Object(_graphics, center, lives, PLAYER_SPEED),
	framesFromLastShooting(0),
	myScore(0)
{
}

Player::Player(const char _graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], std::ifstream & in):
	Object(_graphics, in)
{
	deserialize(in);
}

Player::~Player()
{
}

bool Player::move(const Move & move)
{
	++framesFromLastShooting;
	return Object::move(move);
}

Bullets * Player::shoot()
{
	if (framesFromLastShooting - (int)(FPS / SHOTS_IN_SEC) >= 0)
	{
		framesFromLastShooting = 0;
		return new Bullets(Coords(beginning.X + dimX, center.Y), Move(1, 0));
	}
	return nullptr;
}

void Player::score(EnemyLevel multiplier)
{
	myScore += (50 * (multiplier + 1));
}

unsigned Player::getScore()
{
	return myScore;
}

void Player::normalState()
{
	speed = PLAYER_SPEED;
}

void Player::bossState()
{
	speed = MAX_SPEED;
}

void Player::drawScore(char field[HEIGHT][WIDTH + 1])
{
	unsigned scoreLen = 0;
	unsigned tempScore = myScore;
	while (tempScore)
	{
		++scoreLen;
		tempScore /= 10;
	}
	tempScore = myScore;

	for (size_t i = WIDTH - 10 + scoreLen; i > WIDTH - 10; i--)
	{
		field[0][i] = tempScore % 10 + '0';
		tempScore /= 10;
	}

}

bool Player::deserialize(std::ifstream & in)
{
	in.read((char*)& framesFromLastShooting, sizeof(framesFromLastShooting));
	in.read((char*)& myScore, sizeof(myScore));

	return in.good();
}

bool Player::serialize(std::ofstream & out)
{
	Object::serialize(out);
	out.write((const char*)& framesFromLastShooting, sizeof(framesFromLastShooting));
	out.write((const char*)& myScore, sizeof(myScore));

	return out.good();
}

