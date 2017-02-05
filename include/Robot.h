#ifndef ROBOT_H
#define ROBOT_H

#include "drawable.h"

class Robot : public Drawable
{
private:

	int _width, _height;

	float _time;	//delta time used for animation

	glm::mat4 _s1;

	glm::vec3 _diffuse;
	glm::vec3 _ambient;
	glm::vec3 _specular;


	float _limbAngle;	//angle of limb rotation

	bool _walking;	//boolean checks if limbs should rotate forward or backward

	glm::vec3 _xaxis;
	glm::vec3 _yaxis;
	glm::vec3 _zaxis;
	glm::vec3 _sceneAxis;
	//Camera position vector and Quaternoin to represent camera orientation
	glm::vec3 _position;
	glm::quat _orientation;
	glm::quat q_rotation[2];	//quaternion for rotation of the robot
	glm::quat q_limbRotation[2]; //quaternion for rotation of legs and arms


	glm::vec3 _lHandPosition;
	glm::vec3 _rHandPosition;
	glm::vec3 _bodyPosition;
	glm::vec3 _headPosition;
	glm::vec3 _lLegPosition;
	glm::vec3 _rLegPosition;

	//used to position camera behind robot
	glm::vec3 _camPosition;

	// quaternions used for body rotation on each axis
	glm::quat _xRotation;
	glm::quat _yRotation;
	glm::quat _zRotation;
	
	//quaternion used for limb rotation
	glm::quat _xRotation2;


	glm::mat4 _bodyRotation;
	glm::mat4 _translate;
	glm::mat4 _rotation;
	glm::mat4 _limbRotation;

public:
	Robot();

	//scale and set material for each part of a robot
	void scalePart(unsigned int part);
	void setMaterial(unsigned int part);


	glm::mat4 getScale();

	glm::vec3 getDiffuse();
	glm::vec3 getAmbient();
	glm::vec3 getSpecular();

	//needed for resetting camera and orientation of camera to behind the robot
	glm::vec3 getZaxis();
	glm::quat getOrientation();

	glm::mat4 getTranslation();	//used for moving robot
	glm::mat4 getRotation(unsigned int i); //get robot body and limb rotation

	void rotate(unsigned int part, const float yaw, const float pitch); //Rotate camera
	void animate(unsigned int part);	//animate robot limbs
	void forward(unsigned int part, const float z);	//used for moving robot forward


	void updateRobot(unsigned int part);  //Update the camera


};

#endif