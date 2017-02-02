#include <stdafx.h>

#include "StaticObject.h"

StaticObject::StaticObject()
{

}

glm::mat4 StaticObject::transform(unsigned int object)
{

	_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.5f, 0.0f));	//translate matrix
	_r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
	_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(20.f, 7.f, 20.f));	//scale matrix


	_model = _t1*_r1*_s1;
	return _model;
}

void StaticObject::setMaterial(unsigned int object)
{

	_diffuse = glm::vec3(1.f, 1.f, 1.f);
	_ambient = glm::vec3(.1f, .1f, .1f);
	_specular = glm::vec3(1.0f, 1.0f, 1.0f);


}

glm::mat4 StaticObject::transformTable(unsigned int object)
{
	_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, -10.0f));	//translate matrix
	_r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
	_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix

	_model = _t1*_r1*_s1;
	return _model;
}

glm::mat4 StaticObject::transformSofa(unsigned int object)
{
	_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 0.5f, -7.0f));	//translate matrix
	_r1 = glm::rotate(glm::mat4(1.0f), -1.5708f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
	_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix

	_model = _t1*_r1*_s1;
	return _model;
}

glm::mat4 StaticObject::transformChair(unsigned int object)
{
	switch (object)
	{
	case 0:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.35f, -11.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), -0.0f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	case 1:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.35f, -11.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), -0.0f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	case 2:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.35f, -9.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 3.14f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	case 3:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.35f, -9.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 3.14f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	}
	_model = _t1*_r1*_s1;
	return _model;
}

void StaticObject::setMaterialLeather()
{
	_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	_ambient = glm::vec3(.2f, .2f, 0.2f);
	_specular = glm::vec3(.0f, .0f, .0f);
}

void StaticObject::setMaterialWood()
{
	_diffuse = glm::vec3(.4f, .2f, 0.0f);
	_ambient = glm::vec3(.04f, .01f, .0f);
	_specular = glm::vec3(1.f, 1.f, 1.f);
}

glm::mat4 StaticObject::getModel()
{
	return _model;
}

glm::vec3 StaticObject::getDiffuse()
{
	return _diffuse;
}

glm::vec3 StaticObject::getAmbient()
{
	return _ambient;
}

glm::vec3 StaticObject::getSpecular()
{
	return _specular;
}