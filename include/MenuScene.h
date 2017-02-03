#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "ModelReader.h"
#include "Texture.h"
#include "StaticObject.h"

class MenuScene
{
private:
	GLSLProgram _prog;

	int _width, _height;

	ModelReader* _loadButton;
	StaticObject* _button;
	Texture *_texButton;

	GLuint vboHandles[3];
	GLuint numOfIndices;
	GLuint vaoHandle;


	void compileAndLinkShader(); //Compile and link the shader
public:
	MenuScene();

	void initScene(); //Initialise the scene

	void update(); //Update the scene

	void render();	//Render the scen

	void resize(int, int); //Resize
};
#endif