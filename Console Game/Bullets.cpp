#include "Bullets.h"

Bullets::Bullets(const Coords& center, const Move& _direction):
	Object(bullet, center),
	direction(_direction)
{
}

Bullets::Bullets(std::ifstream & in):
	Object(bullet, in)
{
	deserialize(in);
}

Bullets::~Bullets()
{
}

Move Bullets::getDirection()
{
	return direction;
}

bool Bullets::deserialize(std::ifstream & in)
{
	in.read((char*)& direction, sizeof(direction));
	return in.good();
}

bool Bullets::serialize(std::ofstream & out)
{
	Object::serialize(out);
	out.write((const char*)& direction, sizeof(direction));
	return out.good();
}
