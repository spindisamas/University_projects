#ifndef ENEMY_H
#define ENEMY_H
#include "Player.h"

class Enemy :
	public Player
{
public:
	Enemy(const char _graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], const Coords& center, const EnemyLevel level);
	Enemy(const char _graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH], std::ifstream& in);
	virtual ~Enemy();

	virtual bool move();
	virtual Bullets* shoot();

	virtual Bullets* shoot2() = 0;

	EnemyLevel getLvl();

	virtual bool deserialize(std::ifstream& in);
	virtual bool serialize(std::ofstream& out);

protected: 
	void setPatternZigZag();
	unsigned level;
	Move pattern[WIDTH];
	unsigned currMove;
};

#endif // !ENEMY_H
