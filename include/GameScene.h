#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "ModelReader.h"
#include "Robot.h"
#include "Collectible.h"

using glm::mat4;

class GameScene : public Scene
{
private:
	GLSLProgram _prog;

	int _width, _height;

	vec3 _worldLight;

	ModelReader* _lightBulb;
	ModelReader* _loadModel;
	Robot* _robot;
	vector<Collectible*> _coins;

	float _xRotation;
	mat4 _model; //Model matrix

	vec3 _robotLoc;

	glm::mat4 _t1;
	glm::mat4 _r1;
	glm::mat4 _s1;
	glm::vec3 _xaxis;
	float _xa;
	float _za;

	float _robotMove;
	glm::vec3 _robotPosition;
	glm::vec3 _robotPosition2;
	glm::quat _robotOrientation;

	void setMatrices(QuatCamera camera); //Set the camera matrices

	void compileAndLinkShader(); //Compile and link the shader

public:
	GameScene();

	void setLightParams(QuatCamera camera); //Setup the lighting

	void initScene(QuatCamera camera); //Initialise the scene

	void update(GLFWwindow * window, float t); //Update the scene

	void render(GLFWwindow * window, QuatCamera camera);	//Render the scene

	void resize(QuatCamera camera, int, int); //Resize

};

#endif //GAMESCENE_H