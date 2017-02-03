#include <stdafx.h>

#include "MenuScene.h"

MenuScene::MenuScene()
{
}

void MenuScene::initScene()
{
	//|Compile and link the shader  
	compileAndLinkShader();


	_loadButton = new ModelReader("../models/menuPlane.obj");
	_button = new StaticObject();
	_button->setVertices(_loadButton->GetVertices());
	_button->setNormals(_loadButton->GetNormals());
	_button->setTextures(_loadButton->GetTextureCoordinates());
	_button->VBOobject();

	Bitmap _bmp = Bitmap::bitmapFromFile("../textures/menuRes.bmp");
	_bmp.flipVertically();
	_texButton = new Texture(_bmp);

}

void MenuScene::update()
{
	Bitmap _bmp = Bitmap::bitmapFromFile("../textures/menuLoad.bmp");
	_bmp.flipVertically();
	_texButton = new Texture(_bmp);
	render();
}

void MenuScene::render()
{
	gl::Clear(gl::COLOR_BUFFER_BIT);

	_button->applyTexture(_texButton);	//apply metal texture for robot
	_button->render();	//render robot

}

void MenuScene::resize(int w, int h)
{
	gl::Viewport(0, 0, w, h);
	_width = w;
	_height = h;
}

void MenuScene::compileAndLinkShader()
{
	try {
		_prog.compileShader("../shaders/menuVertShader.vert");
		_prog.compileShader("../shaders/menuFragShader.frag");
		_prog.link();
		_prog.validate();
		_prog.use();
	}
	catch (GLSLProgramException & e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}
