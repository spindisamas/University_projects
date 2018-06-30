#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
class Boss :
	public Enemy
{
public:
	Boss();
	Boss(std::ifstream& in);
	virtual ~Boss();

	virtual bool move();
	virtual Bullets* shoot();
	virtual Bullets* shoot2();

	virtual bool deserialize(std::ifstream& in);
	virtual bool serialize(std::ofstream& out);

};

#endif // !BOSS_H
