#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include <drawable.h>


class StaticObject : public Drawable
{
private:
	glm::mat4 _t1;
	glm::mat4 _r1;
	glm::mat4 _s1;
	glm::mat4 _model;

	glm::vec3 _diffuse;
	glm::vec3 _ambient;
	glm::vec3 _specular;
public:
	StaticObject();
	glm::mat4 transform(unsigned int object);
	glm::mat4 transformChair(unsigned int object);
	void setMaterial(unsigned int object);
	void setMaterialWood();
	glm::mat4 getModel();
	glm::vec3 getDiffuse();
	glm::vec3 getAmbient();
	glm::vec3 getSpecular();


};

#endif //STATICOBJECT_H