#ifndef __Game_H_INCLUDED__
#define __Game_H_INCLUDED__

#include "Player.h"
#include "EnemyLevel1.h"
#include "Enemy2.h"
#include "Boss.h"
#include "SideFuncs.h"
#include "Bullets.h"

class Game
{
public:
	Game(const unsigned char field[HEIGHT][WIDTH + 1], Settings& settings);
	~Game();
	
	void draw1stFrame();
	void draw();

	void shoot();

	bool update(Move& move, bool shoot);
	void reset(const unsigned char field[HEIGHT][WIDTH + 1]);

	bool serialize(Settings& settings);
	bool deserialize(Settings& settings);

	void free(const unsigned char field[HEIGHT][WIDTH + 1]);

private:
	void loadMap(const unsigned char field[HEIGHT][WIDTH + 1]);

	bool movePlayer(Move& move);
	bool hitPlayerIfImpact(const Coords& impact);

	void moveField();

	void moveBullets();
	bool drawAllBullets();
	void eraseAllBullets();
	void deleteBullet(const unsigned index);
	bool checkBulletCollision(const unsigned bulletIndex, const Coords& impact);

	void moveEnemies();
	bool drawAllEnemies();
	void eraseAllEnemies();
	void deleteEnemy(const unsigned index);
	bool hitEnemyIfImpact(const Coords& impact);
	void enemiesShoot();

	bool randSpawn();

private:
	Player* player;
	Enemy** enemies;
	Bullets** bullets;

	char currFrame[HEIGHT][WIDTH + 1]; // CF
	char nextFrame[HEIGHT][WIDTH + 1]; // NF
};


#endif // !__Game_H_INCLUDED__


