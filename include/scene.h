#ifndef SCENE_H
#define SCENE_H

#include "QuatCamera.h"


class Scene
{
public:
	Scene() : m_animate(true) { }
	
    /*
      Initialize the scene.
      */
    virtual void initScene(QuatCamera camera) = 0;

    /*
      This is called prior to every frame.
      */
   virtual void update(GLFWwindow * window, float t ) = 0;

    /*
      Draw scene.
      */
    virtual void render(GLFWwindow * window, QuatCamera camera) = 0;

    /*
      Called when screen is resized.
      */
    virtual void resize(QuatCamera camera,int, int) = 0;

	virtual glm::vec3 resetCamera() = 0;
	virtual glm::quat resetCameraOrient() = 0;
    
    void animate( bool value ) { m_animate = value; }
    bool animating() { return m_animate; }
    
protected:
	bool m_animate;
};



#endif // SCENE_H
