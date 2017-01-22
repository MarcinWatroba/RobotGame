#include <stdafx.h>
#include <Collectible.h>

Collectible::Collectible(float x, float y, float z)
{
	_location.x = x;
	_location.y = y;
	_location.z = z;
	std::cout << x << " " << y << " " << z << std::endl;
}

void Collectible::collected(glm::vec3 robLoc)
{
	if (robLoc.x < _location.x + 2.f && robLoc.x > _location.x - 2.f)
	{
		if (robLoc.z < _location.z + 2.f && robLoc.z > _location.z - 2.f)
		{
			std::cout << "scored!" << std::endl;
			delete this;
		}
	}

}

glm::vec3 Collectible::getLocation()
{
	return _location;
}