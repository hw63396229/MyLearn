#pragma once

#include <algorithm>
#include <time.h>
#include "Quaternion.h"
#include "glut.h"

class Camera
{
public:
	Camera(void);
	// constructor

	Quaternion clickToSphere(int x, int y);
	// projects a mous click onto the unit sphere

	void setView(void);
	// applies the camera transformation to the OpenGL modelview stack

	void mouse(int button, int state, int x, int y);
	// handles mouse clicks

	void motion(int x, int y);
	// handles mouse drags

	void idle(void);
	// handles camera momentum

	void zoomIn(void);
	// moves viewer toward object

	void zoomOut(void);
	// moves viewer away from object

	Quaternion currentRotation(void) const;
	// returns the rotation corresponding to the current mouse state

	Quaternion pClick;
	// mouse coordinates of current click

	Quaternion pDrag;
	// mouse coordinates of current drag

	Quaternion pLast;
	// mouse coordinates of previous drag

	Quaternion rLast;
	// previous camera rotation

	Quaternion momentum;
	// camera momentum

	int tLast;
	// time of previous drag

	float zoom, vZoom;
	// zoom and zoom velocity
};
