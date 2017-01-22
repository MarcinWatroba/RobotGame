#ifndef ROBOT_H
#define ROBOT_H

#include "drawable.h"

class Robot : public Drawable
{
private:

	int _width, _height;

	float _time;

	glm::mat4 _s1;
	mat4 _model;
	mat4 _model2;

	glm::vec3 _diffuse;
	glm::vec3 _ambient;
	glm::vec3 _specular;


	float _limbAngle;

	bool _walking;

	//vector<float> _vertices;	
	//vector<float> _normals;

	//unsigned int _vaoHandle;

	glm::vec3 _xaxis;
	glm::vec3 _yaxis;
	glm::vec3 _zaxis;
	glm::vec3 _sceneAxis;
	//Camera position vector and Quaternoin to represent camera orientation
	glm::vec3 _position;
	glm::quat _orientation;
	glm::quat q_rotation[2];
	glm::quat q_limbRotation[2];


	glm::vec3 _lHandPosition;
	glm::vec3 _rHandPosition;
	glm::vec3 _bodyPosition;
	glm::vec3 _headPosition;
	glm::vec3 _lLegPosition;
	glm::vec3 _rLegPosition;


	glm::quat _xRotation;
	glm::quat _yRotation;
	glm::quat _zRotation;
	
	glm::quat _xRotation2;


	glm::mat4 _view;
	glm::mat4 _projection;
	glm::mat4 _translate;
	glm::quat _translateQuat;
	glm::mat4 _rotation;
	glm::mat4 _limbRotation;

public:
	Robot();

	void scalePart(unsigned int part, glm::vec3 position, float rotation);
	void setMaterial(unsigned int part);


	glm::mat4 getScale();

	glm::vec3 getDiffuse();
	glm::vec3 getAmbient();
	glm::vec3 getSpecular();


	glm::mat4 getTranslationM();


	void rotate(unsigned int part, const float yaw, const float pitch); //Rotate camera
	void animate(unsigned int part);
	void forward(unsigned int part, const float z);


	void updateView(unsigned int part);  //Update the camera
	glm::mat4 view(unsigned int i);

	//void setVertices(vector<float>& vertices);
	//void setNormals(vector<float>& normals);
	//void VBOobject();
	//void render() const;
	//vector<float>& setTextureCoordinates();
};

#endif