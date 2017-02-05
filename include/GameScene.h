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
	GLSLProgram _prog;	//used for shaders

	int _width, _height;
	unsigned int _score;

	vec3 _worldLight;

	//3d model objects
	vector<ModelReader*> _staticModels;
	Robot* _robot;

	//vector of collectibles
	vector<Collectible*> _coins;

	//vector of static objects
	vector<StaticObject*> _lightbulbs;
	vector<StaticObject*> _rooms;
	vector<StaticObject*> _sofas;
	vector<StaticObject*> _chairs;
	vector<StaticObject*> _tables;
	vector<StaticObject*> _tvs;
	vector<StaticObject*> _TVcabinets;
	vector<StaticObject*> _wardrobes;
	vector<StaticObject*> _doors;

	//textures
	Texture *texMetal;
	Texture *texGold;
	Texture *texLeather;
	Texture *texWood;
	Texture *texWall;
	Texture *texWhite;
	Texture *texWardrobeWood;
	//Texture *tex2;

	mat4 _model; //Model matrix

	vec3 _robotLoc;

	glm::mat4 _t1;	//translation matrix
	glm::mat4 _r1;	//rotation matrix
	glm::mat4 _s1;	//scale matrix

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

	void render(QuatCamera camera);	//Render the scene

	void renderCollectible(QuatCamera camera);

	void renderStaticObject(QuatCamera camera, vector<StaticObject*> objects, unsigned int objIt, Texture* texture);

	void renderRobot(QuatCamera);

	void resize(QuatCamera camera, int, int); //Resize

	glm::vec3 resetCamera();
	glm::quat resetCameraOrient();
};

#endif //GAMESCENE_H