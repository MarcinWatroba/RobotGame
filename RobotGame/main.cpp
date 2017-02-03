// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "QuatCamera.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define MOVE_VELOCITY 0.01f
#define ROTATE_VELOCITY 0.001f

//The GLFW Window
GLFWwindow *window;
MenuScene *menuscene;
GameScene *scene;

//The camera
QuatCamera camera;

//To keep track of cursor location
double lastCursorPositionX, lastCursorPositionY, cursorPositionX, cursorPositionY;
float currentFrame;
float deltaTime;
float lastFrame;
bool freeCamera;
bool playing = false;

/////////////////////////////////////////////////////////////////////////////////////////////
//Callback function for keypress use to toggle animate (not used at the moment)
// and to check for R to reset camera
/////////////////////////////////////////////////////////////////////////////////////////////
static void key_callback(GLFWwindow* window, int key, int cancode, int action, int mods)
{
	if (playing)
	{
		if (key == 'R' && action == GLFW_RELEASE)
		{
			freeCamera = false;
			camera.resetPosition(scene->resetCameraOrient(), scene->resetCamera());
		}
	}
	else
	{
		if (key == 257 && action == GLFW_RELEASE)
		{
			menuscene->update();
			glfwSwapBuffers(window);
			glfwPollEvents();
			scene->initScene(camera);
			playing = true;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Callback function when mouse wheel is scrolled
/////////////////////////////////////////////////////////////////////////////////////////////
void scroll_callback(GLFWwindow *window, double x, double y)
{
	if (playing)
	{
		freeCamera = true;
		camera.zoom((float)y*0.5f);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Initialise 
/////////////////////////////////////////////////////////////////////////////////////////////
void initializeGL() {


	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	lastCursorPositionX = 0.0;
	lastCursorPositionY = 0.0;
	cursorPositionX = 0.0;
	cursorPositionY = 0.0;
	currentFrame = 0.0;
	deltaTime = 0.0;
	lastFrame = 0.0;

	// Create the scene class and initialise it for the camera
	menuscene = new MenuScene();
	scene = new GameScene();

	//scene->initScene(camera);
	menuscene->initScene();


}

/////////////////////////////////////////////////////////////////////////////////////////////
// Update
/////////////////////////////////////////////////////////////////////////////////////////////
void update(float t)
{
	//Get the current cursor position
	glfwGetCursorPos(window, &cursorPositionX, &cursorPositionY);
	//currentFrame = (float)glfwGetTime();
	//See how much the cursor has moved
	float deltaX = (float)(lastCursorPositionX - cursorPositionX);
	float deltaY = (float)(lastCursorPositionY - cursorPositionY);

	//Rotates camera right around the robot
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		if (!freeCamera)
		{
			camera.rotate(t * 5, 0.0f);
		}
	}

	//Rotates camera left around the robot
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		if (!freeCamera)
		{
			camera.rotate(-t * 5, 0.0f);
		}
	}

	//moves camera forward
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		if (!freeCamera)
		{
			camera.zoom(-t * 5);
		}
	}

	//Using a different way (i.e. instead of callback) to check for RIGHT mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		freeCamera = true;
		camera.pan(deltaX*MOVE_VELOCITY, deltaY*MOVE_VELOCITY);

	}
	//To adjust Roll with MIDDLE mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{
		freeCamera = true;
		camera.roll(deltaX*ROTATE_VELOCITY);

	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		//Rotate the camera. The 0.001f is a velocity mofifier to make the speed sensible
		freeCamera = true;
		camera.freeRotate(deltaX*ROTATE_VELOCITY, deltaY*ROTATE_VELOCITY);
	}

	//Store the current cursor position
	lastCursorPositionX = cursorPositionX;
	lastCursorPositionY = cursorPositionY;

}


/////////////////////////////////////////////////////////////////////////////////////////////
// Main loop updates scene and renders until we quit
/////////////////////////////////////////////////////////////////////////////////////////////
void mainLoop() {
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		currentFrame = (float)glfwGetTime();
		deltaTime = (float)currentFrame - lastFrame;
		lastFrame = (float)currentFrame;
		//GLUtils::checkForOpenGLError(__FILE__,__LINE__);
		if (playing)
		{
			update(deltaTime);
			scene->update(window, deltaTime);
			scene->render(camera);
		}
		else
		{
			menuscene->render();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
		//glfwSetTime(0.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// resize
/////////////////////////////////////////////////////////////////////////////////////////////
void resizeGL(QuatCamera camera, int w, int h) {
	menuscene->resize(w, h);
	scene->resize(camera, w, h);
}

int _tmain(int argc, _TCHAR* argv[])
{

	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);

	// Open the window
	string title = "Robot game";
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	//Key callback
	glfwSetKeyCallback(window, key_callback);

	//Mouse callback, not used at the moment
	//glfwSetMouseButtonCallback(window,mouse_callback);

	//Scroll callback
	glfwSetScrollCallback(window, scroll_callback);//Set callback

												   // Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

	if (!didLoad) {

		glfwTerminate();
		exit(EXIT_FAILURE);
	}



	// Initialization
	initializeGL();

	resizeGL(camera, WIN_WIDTH, WIN_HEIGHT);


	// Enter the main loop
	mainLoop();

	// Close window and terminate GLFW
	glfwTerminate();

	delete menuscene;
	delete scene;

	// Exit program
	exit(EXIT_SUCCESS);
}
