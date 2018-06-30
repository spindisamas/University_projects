#ifndef ENEMY2_H
#define ENEMY2_H

#include "Enemy.h"
class Enemy2 :
	public Enemy
{
public:
	Enemy2();
	Enemy2(std::ifstream& in);
	virtual ~Enemy2();

	virtual Bullets* shoot2();

	virtual bool deserialize(std::ifstream& in);
	virtual bool serialize(std::ofstream& out);

};

#endif // !ENEMY2_H
