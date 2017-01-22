#include <stdafx.h>

#include "StaticObject.h"

StaticObject::StaticObject()
{

}

glm::mat4 StaticObject::transform(unsigned int object)
{
	switch (object)
	{
	case 0:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 7.4f, 0.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(50.f, 15.f, 50.f));	//scale matrix
		break;
	case 1:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 1.f, 0.5f));	//scale matrix
		break;
	case 2:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, -15.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	case 3:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.5f, -15.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	}


	_model = _t1*_r1*_s1;
	return _model;
}

void StaticObject::setMaterial(unsigned int object)
{
	switch (object)
	{
	case 0:
		_diffuse = glm::vec3(1.f, 1.f, 1.f);
		_ambient = glm::vec3(.8f, .8f, .8f);
		_specular = glm::vec3(.0f, .0f, .0f);
		break;
	case 1:
		_diffuse = glm::vec3(.4f, .4f, .4f);
		_ambient = glm::vec3(.04f, .04f, .04f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 2:
		_diffuse = glm::vec3(.4f, .2f, .0f);
		_ambient = glm::vec3(.04f, .02f, .0f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 3:
		_diffuse = glm::vec3(.2f, .2f, .2f);
		_ambient = glm::vec3(.02f, .02f, .02f);
		_specular = glm::vec3(0.f, 0.f, 0.f);
		break;
	case 4:
		_diffuse = glm::vec3(.2f, .2f, .2f);
		_ambient = glm::vec3(.01f, .01f, .01f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 5:
		_diffuse = glm::vec3(.2f, .2f, .2f);
		_ambient = glm::vec3(.01f, .01f, .01f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	}
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