#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "ModelReader.h"
#include "Robot.h"
#include "Collectible.h"
#include "StaticObject.h"
#include "Texture.h"

class GameScene : public Scene
{
private:
	GLSLProgram _prog;

	int _width, _height;

	vec3 _worldLight;

	ModelReader* _loadModel;
	vector<ModelReader*> _staticModels;
	Robot* _robot;
	vector<Collectible*> _coins;
	vector<StaticObject*> _objects;
	vector<StaticObject*> _rooms;
	vector<StaticObject*> _sofas;
	vector<StaticObject*> _chairs;
	vector<StaticObject*> _tables;
	Texture *texMetal;
	Texture *texGold;
	Texture *texLeather;
	Texture *texWood;
	Texture *texWall;
	//Texture *tex2;

	mat4 _model; //Model matrix

	vec3 _robotLoc;

	glm::mat4 _t1;
	glm::mat4 _r1;
	glm::mat4 _s1;
	glm::vec3 _xaxis;
	float _xa;
	float _za;


	void setMatrices(QuatCamera camera); //Set the camera matrices

	void compileAndLinkShader(); //Compile and link the shader

public:
	GameScene();

	void setLightParams(QuatCamera camera); //Setup the lighting

	void initScene(QuatCamera camera); //Initialise the scene

	void initTextures();

	void initCollectibles();

	void initStaticObjects(vector<StaticObject*> object, int objIt, int statIt);

	void initRobot();

	void update(GLFWwindow * window, float t); //Update the scene

	void render(GLFWwindow * window, QuatCamera camera);	//Render the scene

	void renderCollectible(QuatCamera camera);

	void renderStaticObject(QuatCamera camera, vector<StaticObject*> objects, unsigned int objIt, Texture* texture);

	void renderRobot(QuatCamera camera);

	void resize(QuatCamera camera, int, int); //Resize

};

#endif //GAMESCENE_H