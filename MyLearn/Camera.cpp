#include"Camera.h"

Camera::Camera(void)
	:pClick(1.f), 
	 pDrag(1.f),
	 pLast(1.f),
	 rLast(1.f),
	 momentum(1.f),
	 zoom(1.f) 
    { }

Quaternion Camera::clickToSphere(int x, int y)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	int w = viewport[2];
	int h = viewport[3];

	Quaternion p(0.f, 2.f * static_cast<float>(x) / static_cast<float>(w) - 1,
		         2.f * static_cast<float>(y) / static_cast<float>(h) - 1, 0.f);
	
	if (p.norm2() > 1.f)
	{
		p.normalize();
		p.im().z = 0.f;
	}
	else
	{
		p.im().z = sqrtf(1.f - p.norm2());
	}

	return p;
}

void Camera::setView(void) const
{
	Quaternion r = (pDrag * pClick.conj()) * rLast;

	float w = r[0];
	float x = r[1];
	float y = r[2];
	float z = r[3];

	GLfloat M[16] = {
		1.f - 2.f*y*y - 2.f*z*z, 2.f*x*y + 2.f*w*z, 2.f*x*z - 2.f*w*y, 0.f,
		2.f*x*y - 2.f*w*z, 1.f - 2.f*x*x - 2.f*z*z, 2.f*y*z + 2.f*w*x, 0.f,
		2.f*x*z + 2.f*w*y, 2.f*y*z - 2.f*w*x, 1.f - 2.f*x*x - 2.f*y*y, 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(M);
}

void Camera::mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		pClick = pDrag = pLast = clickToSphere(x, y);
		momentum = 1.f;
	}
	if (state == GLUT_UP)
	{
		float timeSinceDrag = (clock() - tLast) / static_cast<float>(CLOCKS_PER_SEC);

		if (timeSinceDrag < .1f)
		{
			momentum = pDrag * pLast.conj();
			momentum = (.03f * momentum + .97f).unit();
		}
		else
			momentum = 1.f;

		rLast = pDrag * pClick.conj() * rLast;
		pClick = pDrag = 1.f;
	}
}

void Camera::motion(int x, int y)
{
	tLast = clock();
	pLast = pDrag;
	pDrag = clickToSphere(x, y);
}

void Camera::idle(void)
{
	// get time since last idle event
	static int t0 = clock();
	int t1 = clock();
	float dt = (t1 - t0) / static_cast<float>(CLOCKS_PER_SEC);

	rLast = momentum * rLast;
	momentum = ((1.f - .5f * dt) * momentum + .5f * dt).unit();

	zoom += vZoom * dt;
	vZoom *= std::max(0.f, 1.f - .5f * dt);

	t0 = t1;
}

void Camera::zoomIn(void)
{
	vZoom -= .5f;
}

void Camera::zoomOut(void)
{
	vZoom += .5f;
}

Quaternion Camera::currentRotation(void) const
{
	return (pDrag * pClick.conj()) * rLast;
}
