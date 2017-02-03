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

	initTextures();

	_staticModels.push_back(new ModelReader("../models/square2.obj"));
	_staticModels.push_back(new ModelReader("../models/table.obj"));
	_staticModels.push_back(new ModelReader("../models/sofa.obj"));
	_staticModels.push_back(new ModelReader("../models/chair.obj"));
	_staticModels.push_back(new ModelReader("../models/TV3.obj"));
	_staticModels.push_back(new ModelReader("../models/tvCabinet.obj"));
	_staticModels.push_back(new ModelReader("../models/wardrobes.obj"));
	_staticModels.push_back(new ModelReader("../models/door.obj"));
	_staticModels.push_back(new ModelReader("../models/ball.obj"));

	initStaticObjects(_rooms, 0, 0);
	initStaticObjects(_tables, 0, 1);
	initStaticObjects(_sofas, 2, 2);
	initStaticObjects(_chairs, 3, 3);
	initStaticObjects(_tvs, 0, 4);
	initStaticObjects(_TVcabinets, 0, 5);
	initStaticObjects(_wardrobes, 0, 6);
	initStaticObjects(_doors, 0, 7);
	initStaticObjects(_lightbulbs, 0, 8);

	initCollectibles();

	initRobot();

	delete _loadModel;
	_staticModels.clear();

}

void GameScene::initTextures()
{
	Bitmap bmp1 = Bitmap::bitmapFromFile("../textures/gold.jpg");
	bmp1.flipVertically();
	texGold = new Texture(bmp1);

	bmp1 = Bitmap::bitmapFromFile("../textures/squares.bmp");
	bmp1.flipVertically();
	texWall = new Texture(bmp1);

	bmp1 = Bitmap::bitmapFromFile("../textures/leather2.bmp");
	bmp1.flipVertically();
	texLeather = new Texture(bmp1);

	bmp1 = Bitmap::bitmapFromFile("../textures/wood.bmp");
	bmp1.flipVertically();
	texWood = new Texture(bmp1);

	bmp1 = Bitmap::bitmapFromFile("../textures/cleanmetal.png");
	bmp1.flipVertically();
	texMetal = new Texture(bmp1);

	bmp1 = Bitmap::bitmapFromFile("../textures/white.bmp");
	bmp1.flipVertically();
	texWhite = new Texture(bmp1);

	bmp1 = Bitmap::bitmapFromFile("../textures/CoronaWardrobeSet.bmp");
	bmp1.flipVertically();
	texWardrobeWood = new Texture(bmp1);
}

void GameScene::initCollectibles()
{
	_coins.push_back(new Collectible(8.0f, .3f, 9.0f));
	_coins.push_back(new Collectible(-7.0f, .3f, 7.0f));
	_coins.push_back(new Collectible(0.0f, 0.3f, -9.0f));

	for (auto it = _coins.begin(); it != _coins.end(); it++)
	{
		(*it)->setVertices(_staticModels.at(8)->GetVertices());
		(*it)->setNormals(_staticModels.at(8)->GetNormals());
		(*it)->setTextures(_staticModels.at(8)->GetTextureCoordinates());
		(*it)->VBOobject();
	}
}

void GameScene::initStaticObjects(vector<StaticObject*> object, int objIt, int statIt)
{
	for (int i = 0; i < (objIt + 1); i++)
	{
		object.push_back(new StaticObject());
		object.at(i)->setVertices(_staticModels.at(statIt)->GetVertices());
		object.at(i)->setNormals(_staticModels.at(statIt)->GetNormals());
		object.at(i)->setTextures(_staticModels.at(statIt)->GetTextureCoordinates());
		object.at(i)->VBOobject();
	}
	switch (statIt)
	{
	case 0: _rooms = object; break;
	case 1: _tables = object; break;
	case 2: _sofas = object; break;
	case 3: _chairs = object; break;
	case 4: _tvs = object; break;
	case 5: _TVcabinets = object; break;
	case 6: _wardrobes = object; break;
	case 7: _doors = object; break;
	case 8: _lightbulbs = object; break;
	}

}

void GameScene::initRobot()
{
	_loadModel = new ModelReader("../models/square.obj");
	_robot = new Robot();
	_robot->setVertices(_loadModel->GetVertices());
	_robot->setNormals(_loadModel->GetNormals());
	_robot->setTextures(_loadModel->GetTextureCoordinates());
	_robot->VBOobject();
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Update robot position and item collection
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::update(GLFWwindow * window, float t)
{
	if (glfwGetKey(window, GLFW_KEY_D))	//turn right
	{
		_robot->rotate(0, -t * 5.f, 0.0f);

	}
	if (glfwGetKey(window, GLFW_KEY_A))	//turn left
	{
		_robot->rotate(0, t*5.f, 0.0f);

	}
	if (glfwGetKey(window, GLFW_KEY_W))	//go forward
	{

		_robot->forward(0, -t * 5.0f);

	}
	for (auto it = _coins.begin(); it != _coins.end();)	//check if robot collected items
	{
		if ((*it)->collected(_robotLoc) == true)
		{
			_coins.erase(it);
			it = _coins.end();
		}
		else
		{
			it++;
		}

	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set up the lighting variables in the shader
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::setLightParams(QuatCamera camera)
{

	_worldLight = vec3(0.0f, 6.5f, 0.0f);

	_prog.setUniform("La", 1.0f, 1.0f, 1.0f);	//ambient light intensity
	_prog.setUniform("Lp", 1.0f, 1.0f, 1.0f);	//point light intensity

	_prog.setUniform("LightPosition", _worldLight);

	//  prog.setUniform("LightPosition", camera.view() * vec4(worldLight,1.0) );

}

/////////////////////////////////////////////////////////////////////////////////////////////
// Render the scene
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::render(QuatCamera camera)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	//First deal with the plane to represent the ground

	renderCollectible(camera);

	_model = _rooms.at(0)->transform(0);
	_rooms.at(0)->setMaterialGlossyWhite();
	renderStaticObject(camera, _rooms, 0, texWall);

	_model = _tables.at(0)->transformTable(0);
	_tables.at(0)->setMaterialWood();
	renderStaticObject(camera, _tables, 0, texWood);

	for (int i = 0; i < 3; i++)
	{
		_model = _sofas.at(i)->transformSofa(i);
		_sofas.at(i)->setMaterialLeather();
		renderStaticObject(camera, _sofas, i, texLeather);
	}
	_model = _tvs.at(0)->transformTVs(0);
	_tvs.at(0)->setMaterialBlackGlossy();
	renderStaticObject(camera, _tvs, 0, texWhite);

	_model = _TVcabinets.at(0)->transformTVs(1);
	_TVcabinets.at(0)->setMaterialWood();
	renderStaticObject(camera, _TVcabinets, 0, texWood);

	_model = _wardrobes.at(0)->transformWardrobe(0);
	_wardrobes.at(0)->setMaterialWood();
	renderStaticObject(camera, _wardrobes, 0, texWardrobeWood);

	_model = _doors.at(0)->transformDoor(0);
	_doors.at(0)->setMaterialWood();
	renderStaticObject(camera, _doors, 0, texWood);

	_model = _lightbulbs.at(0)->transformLightbulb(0);
	_lightbulbs.at(0)->setMaterialWhite();
	renderStaticObject(camera, _lightbulbs, 0, texWhite);

	for (int i = 0; i < 4; i++)
	{
		_model = _chairs.at(i)->transformChair(i);
		_chairs.at(i)->setMaterialWood();
		renderStaticObject(camera, _chairs, i, texWood);
	}

	renderRobot(camera);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Render collectible objects
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::renderCollectible(QuatCamera camera)
{	
	for (auto it = _coins.begin(); it != _coins.end(); it++)	//for each collectible object
	{

		_t1 = glm::translate(glm::mat4(1.0f), (*it)->getLocation());	//translate matrix
		_r1 = glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
		_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f));	//scale matrix
		_model = _t1*_r1*_s1;	//get model matrix

		setMatrices(camera);	// set matrices

		////////Set the Teapot material properties in the shader and render
		_prog.setUniform("Kd", 1.0f, 0.8f, 0.0f);	//Diffuse reflectancy
		_prog.setUniform("Ka", 0.1f, 0.08f, 0.0f);	//Ambient reflectancy
		_prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);	//Specular reflectancy
		(*it)->applyTexture(texGold);	//apply gold texture to each collectible
		(*it)->render();	//render collectible
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Render static objects
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::renderStaticObject(QuatCamera camera, vector<StaticObject*> objects, unsigned int objIt, Texture* texture)
{

	setMatrices(camera);	//set matrices
		//////Set the Teapot material properties in the shader and render
	_prog.setUniform("Kd", objects.at(objIt)->getDiffuse().x, objects.at(objIt)->getDiffuse().y, objects.at(objIt)->getDiffuse().z);	//Diffuse reflectancy
	_prog.setUniform("Ka", objects.at(objIt)->getAmbient().x, objects.at(objIt)->getAmbient().y, objects.at(objIt)->getAmbient().z);	//Ambient reflectancy
	_prog.setUniform("Ks", objects.at(objIt)->getSpecular().x, objects.at(objIt)->getSpecular().y, objects.at(objIt)->getSpecular().z);	//Specular reflectancy
	objects.at(objIt)->applyTexture(texture);	//apply corresponding textures for each object
	objects.at(objIt)->render();	//render objects

}

/////////////////////////////////////////////////////////////////////////////////////////////
//Render robot object
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::renderRobot(QuatCamera camera)
{

	for (int i = 0; i < 6; i++)	//each body part
	{

		_robot->scalePart(i);	//scale each part
		_robot->setMaterial(i);	//set material reflection for each part

		_s1 = _robot->getScale();	//scale matrix
		_r1 = _robot->view(i);	//rotation matrix
		_t1 = _robot->getTranslation();	//translation matrix

		_model = _t1 * _r1 * _s1;	//get model matrix

		setMatrices(camera);	//set matrices

		//Set the collectible material properties in the shader and render
		_prog.setUniform("Kd", _robot->getDiffuse().x, _robot->getDiffuse().y, _robot->getDiffuse().z);	//Diffuse reflectancy
		_prog.setUniform("Ka", _robot->getAmbient().x, _robot->getAmbient().y, _robot->getAmbient().z);	//Ambient reflectancy
		_prog.setUniform("Ks", _robot->getSpecular().x, _robot->getSpecular().y, _robot->getSpecular().z);	//Specular reflectancy
		_robot->applyTexture(texMetal);	//apply metal texture for robot
		_robot->render();	//render robot
	}
	_robotLoc = glm::vec3(_t1[3][0], _t1[3][1], _t1[3][2]);	//get robot location for collectible items collision detection
}


/////////////////////////////////////////////////////////////////////////////////////////////
//Send the MVP matrices to the GPU
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::setMatrices(QuatCamera camera)
{
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

glm::vec3 GameScene::resetCamera()
{
	return _robot->getZaxis();
}

glm::quat GameScene::resetCameraOrient()
{
	return _robot->getOrientation();
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

