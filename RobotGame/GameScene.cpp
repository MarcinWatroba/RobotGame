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

	robotOrientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	robotPosition = glm::vec3(0.0f, 4.0f, 0.0f);
	robotPosition2 = glm::vec3(0.0f, 3.0f, 0.0f);
	robotMove = 0;
	xRotation = -1.570796326f;

	////Create the plane to represent the ground
	//plane = new VBOPlane(100.0, 100.0, 100, 100);
	////controlTower2
	//m_building = new ModelReader("models\\ball.obj");
	//m_building->VBOobject();
	//m_lightBulb = new ModelReader("models\\ball.obj");
	//m_lightBulb->VBOobject();
	//m_loadRobot = new ModelReader("models\\square.obj");

	//_robot = new Robot();
	//_robot->setVertices(m_loadRobot->GetVertices());
	//_robot->setNormals(m_loadRobot->GetNormals());
	//_robot->VBOobject();


	glm::mat4 lid = glm::mat4(1.0);

	//teapot = new VBOTeapot(16, lid);

}

/////////////////////////////////////////////////////////////////////////////////////////////
//Update not used at present
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::update(GLFWwindow * window, float t)
{
	//if (glfwGetKey(window, GLFW_KEY_D))
	//{
	//	_robot->rotate(0, -t * 5.f, 0.0f);

	//}
	//if (glfwGetKey(window, GLFW_KEY_A))
	//{
	//	_robot->rotate(0, t*5.f, 0.0f);

	//}
	//if (glfwGetKey(window, GLFW_KEY_W))
	//{

	//	_robot->forward(0, -t * 5.0f);

	//}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set up the lighting variables in the shader
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::setLightParams(QuatCamera camera)
{

	worldLight = vec3(10.0f, 16.0f, 0.0f);

	prog.setUniform("La", 1.0f, 1.0f, 1.0f);	//ambient light intensity
	prog.setUniform("Lp", 1.0f, 1.0f, 1.0f);	//point light intensity

	prog.setUniform("LightPosition", worldLight);

	//  prog.setUniform("LightPosition", camera.view() * vec4(worldLight,1.0) );

}

/////////////////////////////////////////////////////////////////////////////////////////////
// Render the scene
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::render(GLFWwindow * window, QuatCamera camera)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	//First deal with the plane to represent the ground

	t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));	//translate matrix
	r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));	//rotate matrix
	s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));	//scale matrix
	model = t1*r1*s1;
	//Set the matrices for the plane although it is only the model matrix that changes so could be made more efficient	
	setMatrices(camera);

	//Set the plane's material properties in the shader and render
	prog.setUniform("Kd", 0.7f, 1.0f, 0.7f);	//Diffuse reflectancy
	prog.setUniform("Ka", 0.07f, 0.1f, 0.07f);	//Ambient reflectancy
	prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);	//Specular reflectancy
	//plane->render();


	//Now set up the teapot 


	t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 10.0f, 0.0f));	//translate matrix
	r1 = glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
	s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));	//scale matrix
	model = t1*r1*s1;

	setMatrices(camera);

	//Set the Teapot material properties in the shader and render
	prog.setUniform("Kd", 0.9f, 0.5f, 0.3f);	//Diffuse reflectancy
	prog.setUniform("Ka", 0.09f, 0.05f, 0.03f);	//Ambient reflectancy
	prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);	//Specular reflectancy
	//teapot->render();

	t1 = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 0.0f, 0.0f));	//translate matrix
	r1 = glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
	s1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));	//scale matrix
	model = t1*r1*s1;

	setMatrices(camera);

	////////Set the Teapot material properties in the shader and render
	prog.setUniform("Kd", 0.9f, 0.5f, 0.3f);	//Diffuse reflectancy
	prog.setUniform("Ka", 0.09f, 0.05f, 0.03f);	//Ambient reflectancy
	prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);	//Specular reflectancy
	//m_building->render();

	t1 = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 16.0f, 0.0f));	//translate matrix
	r1 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));	//rotate matrix
	s1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, .25f, .25f));	//scale matrix
	model = t1*r1*s1;

	setMatrices(camera);

	//////Set the Teapot material properties in the shader and render
	prog.setUniform("Kd", .0f, .0f, .0f);	//Diffuse reflectancy
	prog.setUniform("Ka", 1.0f, 1.0f, 1.0f);	//Ambient reflectancy
	prog.setUniform("Ks", .0f, .0f, .0f);	//Specular reflectancy
	//m_lightBulb->render();

	//rotate matrix
	r1 = glm::rotate(glm::mat4(1.0f), -xRotation, glm::vec3(0.0f, 1.0f, 0.0f));
	for (int i = 0; i < 6; i++)
	{

		//_robot->scalePart(i, robotPosition, xRotation);
		//_robot->setMaterial(i);

		//s1 = _robot->getScale();
		//r1 = _robot->view(i);
		//t1 = _robot->getTranslationM();

		//model = t1 * r1 * s1;

		//setMatrices(camera);
		////////Set the Teapot material properties in the shader and render
		//prog.setUniform("Kd", _robot->getDiffuse().x, _robot->getDiffuse().y, _robot->getDiffuse().z);	//Diffuse reflectancy
		//prog.setUniform("Ka", _robot->getAmbient().x, _robot->getAmbient().y, _robot->getAmbient().z);	//Ambient reflectancy
		//prog.setUniform("Ks", _robot->getSpecular().x, _robot->getSpecular().y, _robot->getSpecular().z);	//Specular reflectancy
		//_robot->render();
	}

}


/////////////////////////////////////////////////////////////////////////////////////////////
//Send the MVP matrices to the GPU
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::setMatrices(QuatCamera camera)
{
	//model = t1*r1*s1;

	mat4 mv = camera.view() * model;

	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix",
		mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	prog.setUniform("MVP", camera.projection() * mv);
	// the correct matrix to transform the normal is the transpose of the inverse of the M matrix
	mat3 normMat = glm::transpose(glm::inverse(mat3(model)));

	prog.setUniform("M", model);
	//prog.setUniform("NormalMatrix", normMat);
	prog.setUniform("V", camera.view());
	prog.setUniform("P", camera.projection());
}

/////////////////////////////////////////////////////////////////////////////////////////////
// resize the viewport
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::resize(QuatCamera camera, int w, int h)
{
	gl::Viewport(0, 0, w, h);
	width = w;
	height = h;
	camera.setAspectRatio((float)w / h);

}

/////////////////////////////////////////////////////////////////////////////////////////////
// Compile and link the shader
/////////////////////////////////////////////////////////////////////////////////////////////
void GameScene::compileAndLinkShader()
{

	try {
		prog.compileShader("Shaders/diffuse.vert");
		prog.compileShader("Shaders/diffuse.frag");
		prog.link();
		prog.validate();
		prog.use();
	}
	catch (GLSLProgramException & e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}