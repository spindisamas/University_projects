#ifndef ENEMY_LEVEL_1_
#define ENEMY_LEVEL_1_
#include "SideFuncs.h"

#include "Enemy.h"
class EnemyLevel1 :
	public Enemy
{
public:
	EnemyLevel1();
	EnemyLevel1(std::ifstream& in);
	virtual ~EnemyLevel1();

	virtual Bullets* shoot2();

	virtual bool deserialize(std::ifstream& in);
	virtual bool serialize(std::ofstream& out);

private:
};

#endif // !ENEMY_LEVEL_1_
