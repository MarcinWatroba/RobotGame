#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include <drawable.h>


class Collectible : public Drawable
{
private:
	glm::vec3 _location;
	glm::vec3 _distance;

public:
	Collectible(float x, float y, float z);
	bool collected(glm::vec3 robLoc);
	glm::vec3 getLocation();


};

#endif //COLLECTIBLE_H