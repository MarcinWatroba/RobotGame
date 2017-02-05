#include <stdafx.h>
#include <Collectible.h>

Collectible::Collectible(float x, float y, float z)	//sets location of the item
{
	_location.x = x;
	_location.y = y;
	_location.z = z;
}

bool Collectible::collected(glm::vec3 robLoc)	//checks if item was collected
{
	if (robLoc.x < _location.x + 1.f && robLoc.x > _location.x - 1.f)
	{
		if (robLoc.z < _location.z + 1.f && robLoc.z > _location.z - 1.f)
		{
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

