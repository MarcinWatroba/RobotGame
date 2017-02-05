
#include "stdafx.h"

#include "Robot.h"



const glm::vec3 WORLDX = glm::vec3(1, 0, 0);
const glm::vec3 WORLDY = glm::vec3(0, 1, 0);
const glm::vec3 WORLDZ = glm::vec3(0, 0, 1);

glm::quat fromAxis(glm::vec3 axis, float angle)
{
	glm::quat rotation;

	rotation.x = sin(angle / 2) * axis.x;
	rotation.y = sin(angle / 2) * axis.y;
	rotation.z = sin(angle / 2) * axis.z;
	rotation.w = cos(angle / 2);

	//return quaternion used to change the orientation
	return rotation;

}

Robot::Robot()
{
	_translate = glm::mat4(1.0f);
	_xaxis = WORLDX;
	_yaxis = WORLDY;
	_zaxis = WORLDZ;
	_walking = false;

	_lHandPosition = glm::vec3(0.3f, 1.22f, -0.f);
	_rHandPosition = glm::vec3(-0.3f, 1.22f, -0.f);
	_bodyPosition = glm::vec3(0.f, 1.22f, -0.f);
	_headPosition = glm::vec3(0.f, 1.77f, -0.f);
	_lLegPosition = glm::vec3(0.1f, 0.40f, -0.f);
	_rLegPosition = glm::vec3(-0.1f, 0.40f, -0.f);

	_limbAngle = 0.0;
	//Initialise the orientation
	_orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	q_rotation[0] = glm::quat(1.0, 0.0, 0.0, 0.0);
	q_limbRotation[0] = glm::quat(1.0, 0.0, 0.0, 0.0);
	q_rotation[1] = glm::quat(1.0, 0.0, 0.0, 0.0);
	q_limbRotation[1] = glm::quat(1.0, 0.0, 0.0, 0.0);


}

void Robot::scalePart(unsigned int part)
{

	switch (part)
	{
	case 0 : 
			 _s1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.15f, .8f, 0.15f));
		break;
	case 1 : 
			 _s1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.15f, .8f, 0.15f));
		break;
	case 2 :
			 _s1 = glm::scale(glm::mat4(1.0f), glm::vec3(.4f, .8f, .18f));
		break;
	case 3:
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(.4f, .2f, .18f));
		break;
	case 4:
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.15f, .8f, 0.15f));
		break;
	case 5:
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.15f, .8f, 0.15f));
		break;
	}
 

}

void Robot::setMaterial(unsigned int part)
{
	switch (part)
	{
	case 0 :
		_diffuse = glm::vec3(1.f, 1.f, 0.f);
		_ambient = glm::vec3(.1f, .1f, .0f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 1 :
		_diffuse = glm::vec3(1.f, 1.f, 0.f);
		_ambient = glm::vec3(.1f, .1f, .0f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 2 :
		_diffuse = glm::vec3(.2f, .2f, .2f);
		_ambient = glm::vec3(.01f, .01f, .01f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 3 :
		_diffuse = glm::vec3(1.f, 1.f, .0f);
		_ambient = glm::vec3(.1f, .1f, .0f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 4 :
		_diffuse = glm::vec3(.2f, .2f, .2f);
		_ambient = glm::vec3(.01f, .01f, .01f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	case 5 :
		_diffuse = glm::vec3(.2f, .2f, .2f);
		_ambient = glm::vec3(.01f, .01f, .01f);
		_specular = glm::vec3(1.f, 1.f, 1.f);
		break;
	}
}

glm::mat4 Robot::getScale()
{
	return _s1;
}

glm::vec3 Robot::getDiffuse()
{
	return _diffuse;
}
glm::vec3 Robot::getAmbient()
{
	return _ambient;
}
glm::vec3 Robot::getSpecular()
{
	return _specular;
}



//Rotate the robot
void Robot::rotate(unsigned int part, float yaw, const float pitch)
{

	//make sure it is rotated at the origin of the robot
	_lHandPosition -= _sceneAxis * .4f;
	_rHandPosition += _sceneAxis * .4f;
	_lLegPosition += _sceneAxis * .4f;
	_rLegPosition -= _sceneAxis * .4f;
	_lHandPosition -= _xaxis * 0.3f;
	_rHandPosition -= _xaxis * -0.3f;
	_lLegPosition -= _xaxis * 0.1f;
	_rLegPosition -= _xaxis * -0.1f;


	_yRotation = fromAxis(WORLDY, yaw);

	//calculate robot orientation and rotation of different body parts
	_orientation = _orientation * _yRotation;

	for (int i = 0; i < 2 ; i++)
	{
		q_limbRotation[i] = _yRotation * q_limbRotation[i];
		q_rotation[i] = q_rotation[i] * _yRotation;
	}

	updateRobot(part);

	_lHandPosition += _sceneAxis * .4f;
	_rHandPosition -= _sceneAxis * .4f;
	_lLegPosition -= _sceneAxis * .4f;
	_rLegPosition += _sceneAxis * .4f;
	_lHandPosition += _xaxis * 0.3f;
	_rHandPosition += _xaxis * -0.3f;
	_lLegPosition += _xaxis * 0.1f;
	_rLegPosition += _xaxis * -0.1f;


}

void Robot::forward(unsigned int part, const float z)
{
	//make sure that body parts are rotated and moved at the robot origin
	_time = z;
	_lHandPosition -= _sceneAxis * .4f;
	_rHandPosition += _sceneAxis * .4f;
	_lLegPosition += _sceneAxis * .4f;
	_rLegPosition -= _sceneAxis * .4f;

	//limb angle variable makes sure limbs do not rotate over a certain angle and walking boolean tells program if limb should be animated and rotated forward or backward
	if (_limbAngle >= 0.70f)
	{
		_walking = true;
	}
	else if (_limbAngle <= -0.70f)
	{
		_walking = false;
	}

	if (_walking == false)
	{
		_limbAngle -= _time;
	}
	else
	{
		_limbAngle += _time;
	}

	//animate limbs
	q_rotation[1] = _xRotation2 * q_rotation[1];
	q_limbRotation[1] = q_limbRotation[1] * _xRotation2;

	q_rotation[0] = _xRotation * q_rotation[0];
	q_limbRotation[0] = q_limbRotation[0] * _xRotation;

	//move robot forward
	_lHandPosition += _zaxis * z;
	_rHandPosition += _zaxis * z;
	_bodyPosition += _zaxis * z;
	_headPosition += _zaxis * z;
	_lLegPosition += _zaxis * z;
	_rLegPosition += _zaxis * z;

	updateRobot(part);

	_lHandPosition += _sceneAxis * .4f;
	_rHandPosition -= _sceneAxis * .4f;
	_lLegPosition -= _sceneAxis * .4f;
	_rLegPosition += _sceneAxis * .4f;



}

void Robot::animate(unsigned int part)
{
	//deals with the rotation of limbs, makes sure these are rotated in correct direction
	if (part == 0 || part == 4)
	{
		if (_walking == true)
		{
			_xRotation = fromAxis(WORLDX, -_time);
		}
		else if (_walking == false)
		{
			_xRotation = fromAxis(WORLDX, +_time);
		}
	}
	else if (part == 1 || part == 5)
	{
		if (_walking == true)
		{
			_xRotation2 = fromAxis(WORLDX, +_time);
		}
		else if (_walking == false)
		{
			_xRotation2 = fromAxis(WORLDX, -_time);
		}
	}
	else
	{
		_xRotation = fromAxis(WORLDX, 0.0f);
		_xRotation2 = fromAxis(WORLDX, 0.0f);
	}
}


// Update the robot position and orientation
void Robot::updateRobot(unsigned int part)
{

	animate(part);

	//set the location of each robot part
	switch (part)
	{
	case 0: 	
		_translate[3][0] = -_lHandPosition.x;
		_translate[3][1] = _lHandPosition.y;
		_translate[3][2] = _lHandPosition.z; 
		break;
	case 1: 	
		_translate[3][0] = -_rHandPosition.x;
		_translate[3][1] = _rHandPosition.y;
		_translate[3][2] = _rHandPosition.z;
		break;
	case 2:
		_translate[3][0] = -_bodyPosition.x;
		_translate[3][1] = _bodyPosition.y;
		_translate[3][2] = _bodyPosition.z;
		break;
	case 3:

		_translate[3][0] = -_headPosition.x;
		_translate[3][1] = _headPosition.y;
		_translate[3][2] = _headPosition.z;
		break;
	case 4:
		_translate[3][0] = -_lLegPosition.x;
		_translate[3][1] = _lLegPosition.y;
		_translate[3][2] = _lLegPosition.z;
		break;
	case 5:
		_translate[3][0] = -_rLegPosition.x;
		_translate[3][1] = _rLegPosition.y;
		_translate[3][2] = _rLegPosition.z;
		break;
	}

	//This deals with the body rotation of the robot
	_bodyRotation = glm::mat4_cast(_orientation); 

	//this deals with each limb rotation
	if (part == 1 || part == 4)
	{
		_limbRotation = glm::mat4_cast(q_limbRotation[0]);
		_rotation = glm::mat4_cast(q_rotation[0]);
	}
	if (part == 0 || part == 5)
	{
		_limbRotation = glm::mat4_cast(q_limbRotation[1]);
		_rotation = glm::mat4_cast(q_rotation[1]);
	}

	//Extract the robot coordinate axes from this matrix
	_xaxis = glm::vec3(_bodyRotation[0][0], _bodyRotation[1][0], _bodyRotation[2][0]);
	_yaxis = glm::vec3(_limbRotation[0][1], _bodyRotation[1][1], _limbRotation[2][1]);
	_zaxis = glm::vec3(_bodyRotation[0][2], _bodyRotation[1][2], _bodyRotation[2][2]);

	//extract the robot's z axis without the limb rotation affecting it
	_sceneAxis = glm::vec3(_rotation[0][1], _bodyRotation[1][1], _rotation[2][1]);


}
//get rotation of each body part
glm::mat4 Robot::getRotation(unsigned int i)
{

	this->updateRobot(i);
	switch (i)
	{
	case 0:
		return _limbRotation;
		break;
	case 1:
		return _limbRotation;
		break;
	case 2:
		return _bodyRotation;
		break;
	case 3:
		return _bodyRotation;
		break;
	case 4:
		return _limbRotation;
		break;
	case 5:
		return _limbRotation;
		break;
	default:
		return _bodyRotation;
		break;
	}
}


glm::mat4 Robot::getTranslation()
{
	return _translate;
}

//used for resetting camera when R button is pressed
glm::vec3 Robot::getZaxis()
{
	_camPosition = _bodyPosition + _zaxis * 5.0f;
	return _camPosition;
}

glm::quat Robot::getOrientation()
{
	return _orientation;
}

