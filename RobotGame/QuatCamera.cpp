#include "stdafx.h"

#include "QuatCamera.h"





//World coordinate System Axes
const glm::vec3 WORLDX = glm::vec3(1,0,0);
const glm::vec3 WORLDY = glm::vec3(0,1,0);
const glm::vec3 WORLDZ = glm::vec3(0,0,1);


/////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////////////////////
	QuatCamera::QuatCamera() 
	{
		reset();
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Get the position
/////////////////////////////////////////////////////////////////////////////////////////////
	const glm::vec3& QuatCamera::position() const
	{
		return _position;
	}

	const glm::quat& QuatCamera::orientation() const
	{
		return _orientation;
	}


/////////////////////////////////////////////////////////////////////////////////////////////
// Set the position
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::setPosition(const glm::vec3& position)
	{
		_position = position;
	}


/////////////////////////////////////////////////////////////////////////////////////////////
// Get the fieldOfView
/////////////////////////////////////////////////////////////////////////////////////////////
	float QuatCamera::fieldOfView() const
	{
		return _fieldOfView;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set the fieldOfView
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::setFieldOfView(float fieldOfView)
	{
		assert(fieldOfView>0.0f && fieldOfView <180.0f);
		_fieldOfView = fieldOfView;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Get the aspectRatio
/////////////////////////////////////////////////////////////////////////////////////////////
	float QuatCamera::aspectRatio() const
	{
		return _aspectRatio;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set the aspectRatio
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::setAspectRatio(float aspectRatio)
	{
		assert(aspectRatio >0.0f);
		_aspectRatio = aspectRatio;
	}


/////////////////////////////////////////////////////////////////////////////////////////////
// Get the nearPlane
/////////////////////////////////////////////////////////////////////////////////////////////
	float QuatCamera::nearPlane() const
	{
		return _nearPlane;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Get the far Plane
/////////////////////////////////////////////////////////////////////////////////////////////
	float QuatCamera::farPlane() const
	{
		return _farPlane;
	}

	
/////////////////////////////////////////////////////////////////////////////////////////////
// Set the nearPlane and the farPlane
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::setNearAndFarPlanes(float nearPlane, float farPlane)
	{
		assert(nearPlane > 0.0f);
		assert(farPlane > nearPlane);
		_nearPlane = nearPlane;
		_farPlane = farPlane;
	}

///////////////////////////////////////////////////////////////////////////////////////////
// Generate a quaternion from axis and rotation angle in radians
//This is to construct the rotation quaternion
////////////////////////////////////////////////////////////////////////////////////////////

	glm::quat fromAxisAngle(glm::vec3 axis, float angle)
	{
		glm::quat rotation;

		rotation.x = sin(angle / 2) * axis.x;
		rotation.y = sin(angle / 2) * axis.y;
		rotation.z = sin(angle / 2) * axis.z;
		rotation.w = cos(angle / 2);

		//return quaternion used to change the camera orientation
		return rotation;

	}

/////////////////////////////////////////////////////////////////////////////////////////////
//Rotate the camera
//Orient according to required pitch and yaw
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::rotate(const float yaw, const float pitch)
	{
		_position -= _zaxis * 5.0f;
		xRotation = fromAxisAngle(WORLDX, pitch);
		yRotation = fromAxisAngle(WORLDY, yaw);

		//updating camera orientation, the order is: x rotation first, y rotation second
		_orientation = xRotation * _orientation * yRotation;

		//need to normalize
		glm::normalize(_orientation);

		//update the camera view
		updateView();
		_position += _zaxis * 5.0f;
	}

	void QuatCamera::freeRotate(const float yaw, const float pitch)
	{
		xRotation = fromAxisAngle(WORLDX, pitch);
		yRotation = fromAxisAngle(WORLDY, yaw);

		//updating camera orientation, the order is: x rotation first, y rotation second
		_orientation = xRotation * _orientation * yRotation;

		//need to normalize
		glm::normalize(_orientation);

		//update the camera view
		updateView();
	}

	
/////////////////////////////////////////////////////////////////////////////////////////////
// Pan the camera
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::pan(const float x, const float y)
	{
		
		_position += _xaxis * x;
		_position += _yaxis * -y;
		
		//Now call update()
		updateView();
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Zoom the camera
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::zoom(const float z)
	{

		_position += _zaxis * z;
			
		//Now call updateView()
		updateView();

	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Update the camera view
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::updateView()
	{
		//Construct the view matrix from orientation quaternion and position vector
		
		//First get the matrix from the 'orientation' Quaternion
		//This deals with the rotation and scale part of the view matrix
		_view = glm::mat4_cast(_orientation); // Rotation and Scale

		//Extract the camera coordinate axes from this matrix
		_xaxis = glm::vec3(_view[0][0],_view[1][0],_view[2][0]);
		_yaxis = glm::vec3(_view[0][1],_view[1][1],_view[2][1]);
		_zaxis = glm::vec3(_view[0][2],_view[1][2],_view[2][2]);

		//And use this and current camera position to set the translate part of the view matrix
		_view[3][0] = -glm::dot(_xaxis,_position); //Translation x
		_view[3][1] = -glm::dot(_yaxis,_position); //Translation y
		_view[3][2] = -glm::dot(_zaxis,_position); //Translation z

	}

	/////////////////////////////////////////////////////////////////////////////////////////////
// Reset the Up
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::roll(const float z)
	{
		//obtaining rotation quaternion for roll
		zRotation = fromAxisAngle(WORLDZ, z);

		//updating orientation
		_orientation = _orientation * zRotation;

		//need to normalize
		glm::normalize(_orientation);

		//update the camera view
		updateView();
	}


/////////////////////////////////////////////////////////////////////////////////////////////
// Reset the camera
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::reset(void)
	{
		//Initialise camera axes
		_xaxis = WORLDX;
		_yaxis = WORLDY;
		_zaxis = WORLDZ;

		//Initialise camera position 
		_position= glm::vec3(0.0f,2.0f,5.0f);

		//Initialise the orientation
		_orientation = glm::quat(1.0,0.0,0.0,0.0);

		//Initialise camera perspective parameters
		_fieldOfView = glm::radians(50.0f);
		_nearPlane = 0.01f;
		_farPlane = 100.0f;
		_aspectRatio = 4.0f/3.0f;

		_projection = glm::perspective(_fieldOfView,_aspectRatio,_nearPlane,_farPlane);

		updateView();
	}

	void QuatCamera::setCamPosition(glm::vec3 position)
	{

		_camPosition = position;
		//std::cout << _camPosition.x << " : " << _camPosition.z << std::endl;
	}

	void QuatCamera::resetPosition(glm::quat orientation, ::vec3 position)
	{
		std::cout << "Camera: " << _orientation.x << " " << _orientation.y << std::endl;
		_orientation = orientation;
		_orientation.y = -orientation.y;
		std::cout << "Camera: " << _orientation.x << " " << _orientation.y << std::endl;
		_position.x = -position.x;
		_position.y = 2.0f;
		_position.z = position.z;

		std::cout << position.x << " : " << position.z << std::endl;
		updateView();
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Return the camera View matrix
/////////////////////////////////////////////////////////////////////////////////////////////
	glm::mat4 QuatCamera::view() 
	{

		this->updateView();
		return _view;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Return the camera Projection matrix
/////////////////////////////////////////////////////////////////////////////////////////////
	glm::mat4 QuatCamera::projection() 
	{

		return _projection;
		
	}

	