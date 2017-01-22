#ifndef GAMESCENE_H
#define GAMESCENE_H

using glm::mat4;

class GameScene : public Scene
{
private:
	GLSLProgram prog;

	int width, height;

	vec3 worldLight;

	//ModelReader* _building;
	//ModelReader* _lightBulb;
	//ModelReader* _loadRobot;
	//Robot* _robot;
	float xRotation;
	mat4 model; //Model matrix

	glm::mat4 t1;
	glm::mat4 r1;
	glm::mat4 s1;
	glm::vec3 _xaxis;
	float xa;
	float za;

	float robotMove;
	glm::vec3 robotPosition;
	glm::vec3 robotPosition2;
	glm::quat robotOrientation;

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