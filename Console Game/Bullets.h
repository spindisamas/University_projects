#ifndef BULLET_H
#define BULLET_H

#include "Object.h"
class Bullets :
	public Object
{
public:
	Bullets(const Coords& center, const Move& direction);
	Bullets(std::ifstream& in);

	virtual ~Bullets();

	Move getDirection();

	virtual bool deserialize(std::ifstream& in);
	virtual bool serialize(std::ofstream& out);

protected:
	Move direction;

};

#endif // !BULLET_H
