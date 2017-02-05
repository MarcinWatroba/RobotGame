#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include <drawable.h>


class StaticObject : public Drawable
{
private:
	//transformation matrices
	glm::mat4 _t1;
	glm::mat4 _r1;
	glm::mat4 _s1;
	glm::mat4 _model;	//model matrix

	//material reflections
	glm::vec3 _diffuse;
	glm::vec3 _ambient;
	glm::vec3 _specular;
public:
	StaticObject();

	//functions transforming each object
	glm::mat4 transform(unsigned int object);
	glm::mat4 transformSofa(unsigned int object);
	glm::mat4 transformChair(unsigned int object);
	glm::mat4 transformTable(unsigned int object);
	glm::mat4 transformTVs(unsigned int object);
	glm::mat4 transformWardrobe(unsigned int object);
	glm::mat4 transformDoor(unsigned int object);
	glm::mat4 transformLightbulb(unsigned int object);

	//set each static object materials
	void setMaterialGlossyWhite();
	void setMaterialWhite();
	void setMaterialLeather();
	void setMaterialWood();
	void setMaterialBlackGlossy();

	glm::mat4 getModel();
	glm::vec3 getDiffuse();
	glm::vec3 getAmbient();
	glm::vec3 getSpecular();


};

#endif //STATICOBJECT_H