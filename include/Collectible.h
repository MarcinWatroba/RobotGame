#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include <drawable.h>


class Collectible : public Drawable
{
private:
	glm::vec3 _location;	//location of collectible
	glm::vec3 _distance;	//distance from collectible item to player

public:
	Collectible(float x, float y, float z);	//function taking location of collectible as parameter
	bool collected(glm::vec3 robLoc);	//returns true if item has been collected
	glm::vec3 getLocation();	//get collectible location


};

#endif //COLLECTIBLE_H