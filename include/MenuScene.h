#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "ModelReader.h"
#include "Texture.h"
#include "StaticObject.h"

class MenuScene
{
private:
	GLSLProgram _prog;	//used for shaders

	int _width, _height;

	ModelReader* _menuModel;	//load menu plane
	StaticObject* _menu;	//menu object
	Texture *_menuTex;	//menu texture

	void compileAndLinkShader(); //Compile and link the shader
public:
	MenuScene();

	void initScene(); //Initialise the scene

	void update(); //Update the scene

	void render();	//Render the scen

	void resize(int, int); //Resize
};
#endif