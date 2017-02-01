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
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.5f, 0.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(20.f, 7.f, 20.f));	//scale matrix
		break;
	case 1:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, -10.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	case 2:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(14.0f, 0.5f, -10.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), -1.5708f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	case 3:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.35f, -11.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), -0.0f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	case 4:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.35f, -11.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), -0.0f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	case 5:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.35f, -9.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 3.14f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	case 6:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.35f, -9.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 3.14f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.f, 1.0f));	//scale matrix
		break;
	case 7:
		_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.5f, -11.0f));	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), -0.0f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
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
		_ambient = glm::vec3(.1f, .1f, .1f);
		_specular = glm::vec3(1.0f, 1.0f, 1.0f);
		break;
	case 1:
		_diffuse = glm::vec3(.4f, .2f, .0f);
		_ambient = glm::vec3(.04f, .02f, .0f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 2:
		_diffuse = glm::vec3(.2f, .2f, .2f);
		_ambient = glm::vec3(.02f, .02f, .02f);
		_specular = glm::vec3(0.f, 0.f, 0.f);
		break;
	case 3:
		_diffuse = glm::vec3(.4f, .2f, 0.f);
		_ambient = glm::vec3(.04f, .02f, .0f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 4:
		_diffuse = glm::vec3(.4f, .2f, 0.0f);
		_ambient = glm::vec3(.04f, .01f, .0f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 5:
		_diffuse = glm::vec3(.4f, .2f, 0.0f);
		_ambient = glm::vec3(.04f, .01f, .0f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 6:
		_diffuse = glm::vec3(.4f, .2f, 0.0f);
		_ambient = glm::vec3(.04f, .01f, .0f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 7:
		_diffuse = glm::vec3(.4f, .2f, 0.0f);
		_ambient = glm::vec3(.04f, .01f, .0f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	}
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