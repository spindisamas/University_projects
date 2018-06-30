#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "Object.h"
#include "Bullets.h"
#include "SideFuncs.h"

class Player:
	public Object
{
public:
	Player(const char _graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], const Coords& center, unsigned short lives = 3);
	Player(const char _graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], std::ifstream& in);
	virtual ~Player();
	virtual bool move(const Move& move);
	virtual Bullets* shoot();

	void score(EnemyLevel multiplier);
	unsigned getScore();

	void normalState();
	void bossState();

	void drawScore(char field[HEIGHT][WIDTH + 1]);

	virtual bool deserialize(std::ifstream& in);
	virtual bool serialize(std::ofstream& out);

private:
	int framesFromLastShooting;
	unsigned myScore;
};

#endif // !__PLAYER_H_INCLUDED__
