#include <iostream>
#include <ctime>
#include "Game.h"


Game::Game(const unsigned char _field[HEIGHT][WIDTH + 1], Settings& settings)
{
	loadMap(_field);

	enemies = new Enemy*[MAX_ENEMY_CAPACITY];
	for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
		enemies[i] = nullptr;

	bullets = new Bullets*[MAX_BULLET_CAPACITY];
	for (size_t i = 0; i < MAX_BULLET_CAPACITY; i++)
		bullets[i] = nullptr;

	if (settings.continueGame == true)
	{
		bool deserialized = deserialize(settings);

		if (deserialized == false)
		{
			reset(_field);
		}
	}
	else
	{
		if (settings.skin == 2)
			player = new Player(player2, Coords(10, 10));
		else if (settings.skin == 3)
			player = new Player(player3, Coords(10, 10));
		else
			player = new Player(player1, Coords(10, 10));
	}
	

	srand((unsigned int)time(0));
}

Game::~Game()
{
	free(field);
}

void Game::draw1stFrame()
{
	setCursorPosition(0, 0);
	for (size_t i = 0; i < HEIGHT; i++)
	{
		std::cout << nextFrame[i];
		if(i != HEIGHT - 1)std::cout << '\n';
	}

	player->draw(nextFrame);
}

void Game::draw()
{
	unsigned lives = 0;
	if (player != nullptr)
		lives = player->getLives();

	for (size_t i = 7; i < 7 + lives; i++)
		nextFrame[0][i] = (unsigned char)221;
	for (size_t i = 7 + lives; i < 14 + lives ; i++)
		nextFrame[0][i] = (unsigned char)255;


	if (player != nullptr)
		player->drawScore(nextFrame);

	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (currFrame[i][j] != nextFrame[i][j])
			{
				setCursorPosition(j, i);
				std::cout << nextFrame[i][j];

				currFrame[i][j] = nextFrame[i][j];
			}
		}
	}
}

void Game::shoot()
{
	if (player->getBeginning().X + player->dimX < WIDTH)
	{
		for (size_t i = 0; i < MAX_BULLET_CAPACITY; i++)
		{
			if (bullets[i] == nullptr)
			{
				bullets[i] = player->shoot();
				break;
			}
		}
	}
}

void Game::loadMap(const unsigned char field[HEIGHT][WIDTH + 1])
{
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j <= WIDTH; j++)
		{
			currFrame[i][j] = field[i][j];
			nextFrame[i][j] = field[i][j];
		}
	}
}

bool Game::movePlayer(Move& move)
{
	player->erase(nextFrame);

	player->move(move);
	Coords coords = player->draw(nextFrame);

	if (coords.Y != 0)
	{
		hitEnemyIfImpact(coords);
		player->getHit();
		if (player->getLives() == 0)
		{
			delete player;
			player = nullptr;
			return false;
		}
	}

	return true;
}

bool Game::hitPlayerIfImpact(const Coords & impact)
{
	if (player == nullptr)
		return true;
	if (impact.Y != 0)
	{
		if (player->collision(impact))
		{
			bool plDead = player->getHit();
			hitEnemyIfImpact(impact);
			if (plDead)
			{
				delete player;
				player = nullptr;
				return true;
			}
		}
	}
	return false;
}

void Game::moveField()
{
	for (size_t i = 0; i < WIDTH; i++)
	{
		 // TO DO...
	}
}

void Game::moveBullets()
{
	for (size_t i = 0; i < MAX_BULLET_CAPACITY; i++)
	{
		if (bullets[i] != nullptr)
		{
			Move bulletDirection = bullets[i]->getDirection();
			bool success = bullets[i]->move(bulletDirection);

			if (success == false)
			{
				deleteBullet(i);
				--i;
			}
		}
	}
}

bool Game::update(Move& move, bool _shoot)
{
	
	try
	{
		randSpawn();
	}
	catch (const std::exception&)
	{
		std::cout << "Something went wrong. The program will shut down\n";
		getchar();
		throw;
	}

	if (move.X == 1)
	{
		eraseAllBullets();
		moveBullets();
	}
	bool plAlive = movePlayer(move);
	if (plAlive == false)
		return false;

	eraseAllEnemies();
	moveEnemies();

	bool plDead = drawAllEnemies();
	if (plDead)
		return false;

	if (move.X != 1)
	{
		eraseAllBullets();
		moveBullets();
	}

	if (_shoot)
		shoot();

	enemiesShoot();

	plDead = drawAllBullets();

	draw();

	return (plAlive && !plDead);
}

void Game::reset(const unsigned char _field[HEIGHT][WIDTH + 1])
{
	delete player;
	player = new Player(player1, Coords(10, 10));

	for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		delete enemies[i];
		enemies[i] = nullptr;
	}

	for (size_t i = 0; i < MAX_BULLET_CAPACITY; i++)
	{
		delete bullets[i];
		bullets[i] = nullptr;
	}

	loadMap(_field);
}

bool Game::serialize(Settings& settings)
{
	std::ofstream out("save.dat", std::ios::binary);
	if (out.is_open() == false)
	{
		setCursorPosition(20, 0);
		std::cout << "Failed to save the current data\n";
		return false;
	}

	settings.serialize(out);

	player->serialize(out);

	unsigned enemiyCount = 0;
	while (enemies[enemiyCount] != nullptr && enemiyCount < MAX_ENEMY_CAPACITY)
		++enemiyCount;

	out.write((const char*)& enemiyCount, sizeof(enemiyCount));

	for (size_t i = 0; i < enemiyCount; i++)
		enemies[i]->serialize(out);

	unsigned bulletsCount = 0;
	while (bullets[bulletsCount] != nullptr && bulletsCount < MAX_BULLET_CAPACITY)
		++bulletsCount;

	out.write((const char*)& bulletsCount, sizeof(bulletsCount));
	for (size_t i = 0; i < bulletsCount; i++)
		bullets[i]->serialize(out);

	if (out.good() == false)
	{
		setCursorPosition(20, 0);
		std::cout << "Failed to save the current data\n";
		out.clear();
		out.close();
		return false;
	}

	out.close();
	return true;
}

bool Game::deserialize(Settings& settings)
{
	std::ifstream in("save.dat", std::ios::binary);
	if (in.is_open() == false)
	{
		setCursorPosition(20, 0);
		std::cout << "Failed to load the data\n";
		return false;
	}

	settings.deserialize(in);

	if (settings.skin == 2)
		player = new Player(player2, in);
	else if (settings.skin == 3)
		player = new Player(player3, in);
	else
		player = new Player(player1, in);

	unsigned enemiyCount = 0;
	in.read((char*)& enemiyCount, sizeof(enemiyCount));

	unsigned enemyLevel;
	for (size_t i = 0; i < enemiyCount; i++)
	{
		in.read((char*)& enemyLevel, sizeof(enemyLevel));
		if(enemyLevel == LEVEL1)
			enemies[i] = new EnemyLevel1(in);
		else if(enemyLevel == LEVEL2)
			enemies[i] = new Enemy2(in);
		else if(enemyLevel == BOSS)
			enemies[i] = new Boss(in);
	}

	unsigned bulletsCount = 0;
	in.read((char*)& bulletsCount, sizeof(bulletsCount));

	for (size_t i = 0; i < bulletsCount; i++)
		bullets[i] = new Bullets(in);

	if (in.good() == false)
	{
		setCursorPosition(20, 0);
		std::cout << "Failed to load the data\n";
		in.clear();
		in.close();
		return false;
	}

	in.close();
	return true;
}

void Game::free(const unsigned char _field[HEIGHT][WIDTH + 1])
{
	delete player;
	player = nullptr;

	for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		delete enemies[i];
		enemies[i] = nullptr;
	}
	delete[] enemies;
	enemies = nullptr;

	for (size_t i = 0; i < MAX_BULLET_CAPACITY; i++)
	{
		delete bullets[i];
		bullets[i] = nullptr;
	}
	delete[] bullets;
	bullets = nullptr;

	loadMap(_field);
}

bool Game::drawAllBullets()
{
	for (size_t i = 0; i < MAX_BULLET_CAPACITY; i++)
	{
		if (bullets[i] != nullptr)
		{
			Coords impact = bullets[i]->draw(nextFrame);
			if (impact.Y != 0)
			{
				if (checkBulletCollision(i, impact))
					return false;

				if (bullets[i]->getDirection().X == 1)
					hitEnemyIfImpact(impact);
				else
					hitPlayerIfImpact(impact);
					
				deleteBullet(i);
			}
		}
	}
	if (player == nullptr)
		return true;
	return false;
}

void Game::eraseAllBullets()
{
	for (size_t i = 0; i < MAX_BULLET_CAPACITY; i++)
		if (bullets[i] != nullptr)
			bullets[i]->erase(nextFrame);
}

void Game::deleteBullet(const unsigned index)
{
	bullets[index]->erase(nextFrame);

	delete bullets[index];
	bullets[index] = nullptr;

	size_t j = index;
	for (; j < MAX_BULLET_CAPACITY - 1; j++)
		bullets[j] = bullets[j + 1];
	bullets[j] = nullptr;
}

bool Game::checkBulletCollision(const unsigned bulletIndex, const Coords& impact)
{
	for (size_t i = 0; i < MAX_BULLET_CAPACITY; i++)
	{
		if (bulletIndex != i && bullets[i] != nullptr)
		{
			if (bullets[i]->collision(impact))
			{
				delete bullets[i];
				bullets[i] = nullptr;

				delete bullets[bulletIndex];
				bullets[bulletIndex] = nullptr;

				return true;
			}
		}
	}
	return false;
}

void Game::moveEnemies()
{
	for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		if (enemies[i] != nullptr)
		{
			bool success = enemies[i]->move();

			if (success == false)
			{
				deleteEnemy(i);
				--i;
			}
		}
	}
}

bool Game::drawAllEnemies()
{
	bool plDead = false;
	Coords impact;
	for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		if (enemies[i] != nullptr)
		{
			impact = enemies[i]->draw(nextFrame);
			plDead = hitPlayerIfImpact(impact);
		}
	}
	return plDead;
}

void Game::eraseAllEnemies()
{
	for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
		if (enemies[i] != nullptr)
			enemies[i]->erase(nextFrame);
}

void Game::deleteEnemy(const unsigned index)
{
	enemies[index]->erase(nextFrame);

	delete enemies[index];
	enemies[index] = nullptr;

	size_t j = index;
	for (; j < MAX_ENEMY_CAPACITY - 1; j++)
		enemies[j] = enemies[j + 1];
	enemies[j] = nullptr;
}

bool Game::hitEnemyIfImpact(const Coords & impact)
{
	for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->collision(impact))
			{
				if (enemies[i]->getHit()) // if the enemy is dead
				{
					player->score(enemies[i]->getLvl());
					deleteEnemy(i);
				}

				return true;
			}
		}
	}
	return false;
}

void Game::enemiesShoot()
{
	bool bossSpawned = false;
	for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
		if (enemies[i] != nullptr && enemies[i]->getLvl() == BOSS)
			bossSpawned = true;

	for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->getBeginning().X > 0)
			{
				for (size_t j = 0; j < MAX_BULLET_CAPACITY; j++)
				{
					if (bullets[j] == nullptr)
					{
						bullets[j] = enemies[i]->shoot();
						if (bossSpawned)
							bullets[j + 1] = enemies[i]->shoot2();
						break;
					}
				}
			}
		}
	}
}

bool Game::randSpawn()
{
	bool bossSpawned = false;
	for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
		if (enemies[i] != nullptr && enemies[i]->getLvl() == BOSS)
			bossSpawned = true;

	if (player->getScore() / 500 >= 1 && player->getScore() % 500 < 200)
	{
		if (bossSpawned == false)
		{
			for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
			{
				if(enemies[i] != nullptr)
					deleteEnemy(i);
			}
			enemies[0] = new Boss();
		}
	}
	else
	{
		bool spawn = rand() % 80;

		if (!spawn)
		{
			for (size_t i = 0; i < MAX_ENEMY_CAPACITY; i++)
			{
				if (enemies[i] == nullptr)
				{
					short enemyType = rand() % 2;
					if(enemyType == 0)
						enemies[i] = new EnemyLevel1();
					else if(enemyType == 1)
						enemies[i] = new Enemy2();
					break;
				}
			}
		}
	}

	return false;
}
