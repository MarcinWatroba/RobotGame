#include "stdafx.h"

#include "GameScene.h"

using std::cerr;
using std::endl;

using glm::vec3;

/////////////////////////////////////////////////////////////////////////////////////////////
// Default constructor
/////////////////////////////////////////////////////////////////////////////////////////////
GameScene::GameScene()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////
//Initialise the scene
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::initScene(QuatCamera camera)
{


	//|Compile and link the shader  
	compileAndLinkShader();

	gl::Enable(gl::DEPTH_TEST);

	//Set up the lighting
	setLightParams(camera);

	_robotOrientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	_robotPosition = glm::vec3(0.0f, 4.0f, 0.0f);
	_robotPosition2 = glm::vec3(0.0f, 3.0f, 0.0f);
	_robotMove = 0;
	_xRotation = -1.570796326f;


	_loadModel = new ModelReader("../models/ball.obj");
	_coins.push_back(new Collectible(10.0f, .3f, 0.0f));
	_coins.push_back(new Collectible(-10.0f, .3f, 0.0f));
	_coins.push_back(new Collectible(0.0f, 0.3f, -10.0f));

	Bitmap bmp1 = Bitmap::bitmapFromFile("../textures/gold.jpg");
	texGold = new Texture(bmp1);
	for (auto it = _coins.begin(); it != _coins.end(); it++)
	{
		(*it)->setVertices(_loadModel->GetVertices());
		(*it)->setNormals(_loadModel->GetNormals());
		(*it)->setTextures(_loadModel->GetTextureCoordinates());
		//(*it)->applyTexture(bmp1);
		(*it)->VBOobject();
	}

	_staticModels.push_back(new ModelReader("../models/square2.obj"));
	_staticModels.push_back(new ModelReader("../models/table.obj"));
	_staticModels.push_back(new ModelReader("../models/sofa.obj"));
	_staticModels.push_back(new ModelReader("../models/chair.obj"));
	//_objects.push_back(new StaticObject());
	bmp1 = Bitmap::bitmapFromFile("../textures/squares.bmp");
	bmp1.flipVertically();
	texWall = new Texture(bmp1, gl::LINEAR, gl::CLAMP_TO_EDGE);
	for (int i = 0; i < 4; i++)
	{
		_objects.push_back(new StaticObject());
		_objects.at(i)->setVertices(_staticModels.at(i)->GetVertices());
		_objects.at(i)->setNormals(_staticModels.at(i)->GetNormals());
		_objects.at(i)->setTextures(_staticModels.at(i)->GetTextureCoordinates());
		_objects.at(i)->VBOobject();
	}
	bmp1 = Bitmap::bitmapFromFile("../textures/wood.bmp");
	texWood = new Texture(bmp1);
	for (int i = 0; i < 4; i++)
	{
		_chairs.push_back(new StaticObject());
		_chairs.at(i)->setVertices(_staticModels.at(3)->GetVertices());
		_chairs.at(i)->setNormals(_staticModels.at(3)->GetNormals());
		_chairs.at(i)->setTextures(_staticModels.at(3)->GetTextureCoordinates());
		_chairs.at(i)->VBOobject();
	}


	//_objects.back()->VBOobject();
	bmp1 = Bitmap::bitmapFromFile("../textures/cleanmetal.png");
	texMetal = new Texture(bmp1);
	_loadModel = new ModelReader("../models/square.obj");
	_robot = new Robot();
	_robot->setVertices(_loadModel->GetVertices());
	_robot->setNormals(_loadModel->GetNormals());
	_robot->setTextures(_loadModel->GetTextureCoordinates());

	_robot->VBOobject();



	//gl::ActiveTexture(gl::TEXTURE0);
	//gl::BindTexture(gl::TEXTURE_2D, tex2->object());
	delete _loadModel;
	//delete bmp1;

	//teapot = new VBOTeapot(16, lid);

}

/////////////////////////////////////////////////////////////////////////////////////////////
//Update not used at present
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::update(GLFWwindow * window, float t)
{
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		_robot->rotate(0, -t * 5.f, 0.0f);

	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		_robot->rotate(0, t*5.f, 0.0f);

	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{

		_robot->forward(0, -t * 5.0f);

	}
	for (auto it = _coins.begin(); it != _coins.end(); it++)
	{
		(*it)->collected(_robotLoc);

	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set up the lighting variables in the shader
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::setLightParams(QuatCamera camera)
{

	_worldLight = vec3(0.0f, 6.0f, 0.0f);

	_prog.setUniform("La", 1.0f, 1.0f, 1.0f);	//ambient light intensity
	_prog.setUniform("Lp", 1.0f, 1.0f, 1.0f);	//point light intensity

	_prog.setUniform("LightPosition", _worldLight);

	//  prog.setUniform("LightPosition", camera.view() * vec4(worldLight,1.0) );

}

/////////////////////////////////////////////////////////////////////////////////////////////
// Render the scene
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::render(GLFWwindow * window, QuatCamera camera)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	//First deal with the plane to represent the ground


	for (auto it = _coins.begin(); it != _coins.end(); it++)
	{

		_t1 = glm::translate(glm::mat4(1.0f), (*it)->getLocation());	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f));	//scale matrix
		_model = _t1*_r1*_s1;

		setMatrices(camera);

		////////Set the Teapot material properties in the shader and render
		_prog.setUniform("Kd", 1.0f, 0.8f, 0.0f);	//Diffuse reflectancy
		_prog.setUniform("Ka", 0.1f, 0.08f, 0.0f);	//Ambient reflectancy
		_prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);	//Specular reflectancy
		(*it)->applyTexture(texGold);
		(*it)->render();
	}


	for (int i = 0; i < 4; i++)
	{
		_model = _objects.at(i)->transform(i);
		_objects.at(i)->setMaterial(i);
		setMatrices(camera);

		//////Set the Teapot material properties in the shader and render
		_prog.setUniform("Kd", _objects.at(i)->getDiffuse().x, _objects.at(i)->getDiffuse().y, _objects.at(i)->getDiffuse().z);	//Diffuse reflectancy
		_prog.setUniform("Ka", _objects.at(i)->getAmbient().x, _objects.at(i)->getAmbient().y, _objects.at(i)->getAmbient().z);	//Ambient reflectancy
		_prog.setUniform("Ks", _objects.at(i)->getSpecular().x, _objects.at(i)->getSpecular().y, _objects.at(i)->getSpecular().z);	//Specular reflectancy
		_objects.at(i)->applyTexture(texWall);
		_objects.at(i)->render();
	}
	for (int i = 0; i < 4; i++)
	{
		_model = _chairs.at(i)->transformChair(i);
		_chairs.at(i)->setMaterialWood();
		setMatrices(camera);

		//////Set the Teapot material properties in the shader and render
		_prog.setUniform("Kd", _chairs.at(i)->getDiffuse().x, _chairs.at(i)->getDiffuse().y, _chairs.at(i)->getDiffuse().z);	//Diffuse reflectancy
		_prog.setUniform("Ka", _chairs.at(i)->getAmbient().x, _chairs.at(i)->getAmbient().y, _chairs.at(i)->getAmbient().z);	//Ambient reflectancy
		_prog.setUniform("Ks", _chairs.at(i)->getSpecular().x, _chairs.at(i)->getSpecular().y, _chairs.at(i)->getSpecular().z);	//Specular reflectancy
		_chairs.at(i)->applyTexture(texWood);
		_chairs.at(i)->render();
	}
	//rotate matrix

	_r1 = glm::rotate(glm::mat4(1.0f), -_xRotation, glm::vec3(0.0f, 1.0f, 0.0f));
	for (int i = 0; i < 6; i++)
	{

		_robot->scalePart(i, _robotPosition, _xRotation);
		_robot->setMaterial(i);

		_s1 = _robot->getScale();
		_r1 = _robot->view(i);
		_t1 = _robot->getTranslationM();

		_model = _t1 * _r1 * _s1;

		setMatrices(camera);

		//Set the collectible material properties in the shader and render
		_prog.setUniform("Kd", _robot->getDiffuse().x, _robot->getDiffuse().y, _robot->getDiffuse().z);	//Diffuse reflectancy
		_prog.setUniform("Ka", _robot->getAmbient().x, _robot->getAmbient().y, _robot->getAmbient().z);	//Ambient reflectancy
		_prog.setUniform("Ks", _robot->getSpecular().x, _robot->getSpecular().y, _robot->getSpecular().z);	//Specular reflectancy
		_robot->applyTexture(texMetal);
		_robot->render();
	}
	_robotLoc = glm::vec3(_t1[3][0], _t1[3][1], _t1[3][2]);
}


/////////////////////////////////////////////////////////////////////////////////////////////
//Send the MVP matrices to the GPU
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::setMatrices(QuatCamera camera)
{
	//model = t1*r1*s1;

	mat4 _mv = camera.view() * _model;

	_prog.setUniform("ModelViewMatrix", _mv);
	_prog.setUniform("NormalMatrix",
		mat3(vec3(_mv[0]), vec3(_mv[1]), vec3(_mv[2])));
	_prog.setUniform("MVP", camera.projection() * _mv);
	// the correct matrix to transform the normal is the transpose of the inverse of the M matrix
	mat3 _normMat = glm::transpose(glm::inverse(mat3(_model)));

	_prog.setUniform("M", _model);
	//prog.setUniform("NormalMatrix", normMat);
	_prog.setUniform("V", camera.view());
	_prog.setUniform("P", camera.projection());
}

/////////////////////////////////////////////////////////////////////////////////////////////
// resize the viewport
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::resize(QuatCamera camera, int w, int h)
{
	gl::Viewport(0, 0, w, h);
	_width = w;
	_height = h;
	camera.setAspectRatio((float)w / h);

}

/////////////////////////////////////////////////////////////////////////////////////////////
// Compile and link the shader
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::compileAndLinkShader()
{

	try {
		_prog.compileShader("../shaders/vertexShader.vert");
		_prog.compileShader("../shaders/fragmentShader.frag");
		_prog.link();
		_prog.validate();
		_prog.use();
	}
	catch (GLSLProgramException & e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}