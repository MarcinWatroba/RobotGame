#include <stdafx.h>
#include <Collectible.h>

Collectible::Collectible(float x, float y, float z)
{
	_location.x = x;
	_location.y = y;
	_location.z = z;
	std::cout << x << " " << y << " " << z << std::endl;




}

bool Collectible::collected(glm::vec3 robLoc)
{
	if (robLoc.x < _location.x + 1.f && robLoc.x > _location.x - 1.f)
	{
		if (robLoc.z < _location.z + 1.f && robLoc.z > _location.z - 1.f)
		{
			std::cout << "scored!" << std::endl;
			return true;
		}
		else
		{
			return false;
		}
	}

}

glm::vec3 Collectible::getLocation()
{
	return _location;
}

