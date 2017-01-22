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

	////Create the plane to represent the ground
	//plane = new VBOPlane(100.0, 100.0, 100, 100);
	////controlTower2
	_building = new ModelReader("../models/ball.obj");
	_coin = new Collectible;
	_coin->setVertices(_building->GetVertices());
	_coin->setNormals(_building->GetNormals());
	_coin->VBOobject();

	_lightBulb = new ModelReader("../models/ball.obj");
	_lightBulb->VBOobject();
	_loadRobot = new ModelReader("../models/square.obj");

	_robot = new Robot();
	_robot->setVertices(_loadRobot->GetVertices());
	_robot->setNormals(_loadRobot->GetNormals());
	_robot->VBOobject();


	glm::mat4 _lid = glm::mat4(1.0);

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
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set up the lighting variables in the shader
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::setLightParams(QuatCamera camera)
{

	_worldLight = vec3(10.0f, 16.0f, 0.0f);

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

	_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));	//translate matrix
	_r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
	_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));	//scale matrix
	_model = _t1*_r1*_s1;
	//Set the matrices for the plane although it is only the model matrix that changes so could be made more efficient	
	setMatrices(camera);

	//Set the plane's material properties in the shader and render
	_prog.setUniform("Kd", 0.7f, 1.0f, 0.7f);	//Diffuse reflectancy
	_prog.setUniform("Ka", 0.07f, 0.1f, 0.07f);	//Ambient reflectancy
	_prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);	//Specular reflectancy
	//plane->render();


	//Now set up the teapot 


	_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 10.0f, 0.0f));	//translate matrix
	_r1 = glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
	_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));	//scale matrix
	_model = _t1*_r1*_s1;

	setMatrices(camera);

	//Set the Teapot material properties in the shader and render
	_prog.setUniform("Kd", 0.9f, 0.5f, 0.3f);	//Diffuse reflectancy
	_prog.setUniform("Ka", 0.09f, 0.05f, 0.03f);	//Ambient reflectancy
	_prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);	//Specular reflectancy
	//teapot->render();

	_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 0.0f, 0.0f));	//translate matrix
	_r1 = glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
	_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));	//scale matrix
	_model = _t1*_r1*_s1;

	setMatrices(camera);

	////////Set the Teapot material properties in the shader and render
	_prog.setUniform("Kd", 0.9f, 0.5f, 0.3f);	//Diffuse reflectancy
	_prog.setUniform("Ka", 0.09f, 0.05f, 0.03f);	//Ambient reflectancy
	_prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);	//Specular reflectancy
	_coin->render();

	_t1 = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 16.0f, 0.0f));	//translate matrix
	_r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
	_s1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, .25f, .25f));	//scale matrix
	_model = _t1*_r1*_s1;

	setMatrices(camera);

	//////Set the Teapot material properties in the shader and render
	_prog.setUniform("Kd", .0f, .0f, .0f);	//Diffuse reflectancy
	_prog.setUniform("Ka", 1.0f, 1.0f, 1.0f);	//Ambient reflectancy
	_prog.setUniform("Ks", .0f, .0f, .0f);	//Specular reflectancy
	_lightBulb->render();

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
		//Set the Teapot material properties in the shader and render
		_prog.setUniform("Kd", _robot->getDiffuse().x, _robot->getDiffuse().y, _robot->getDiffuse().z);	//Diffuse reflectancy
		_prog.setUniform("Ka", _robot->getAmbient().x, _robot->getAmbient().y, _robot->getAmbient().z);	//Ambient reflectancy
		_prog.setUniform("Ks", _robot->getSpecular().x, _robot->getSpecular().y, _robot->getSpecular().z);	//Specular reflectancy
		_robot->render();
	}

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
		_prog.compileShader("../shaders/diffuse.vert");
		_prog.compileShader("../shaders/diffuse.frag");
		_prog.link();
		_prog.validate();
		_prog.use();
	}
	catch (GLSLProgramException & e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}