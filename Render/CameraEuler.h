#pragma once
#include <glut.h>
#include <vfvector3.h>

class CameraEuler
{
public:
	CameraEuler() : zoom(1.f) {}
	CameraEuler(const VFVECTOR3& pos, const VFVECTOR3& target, const VFVECTOR3& up);
	~CameraEuler() {}

	/* 设置摄像机的位置, 观察点和向上向量 */
	void setCamera(float eyeX, float eyeY, float eyeZ,
		           float lookX, float lookY, float lookZ,
		           float upX, float upY, float upZ);
	void  setModelViewMatrix();
	void  setShape(float viewAngle, float aspect, float Near, float Far);
	void  slide(float du, float dv, float dn);
	void  roll(float angle);
	void  yaw(float angle);
	void  pitch(float angle);
	float getDist();
	void  zoomIn(void);     // moves viewer toward object
	void  zoomOut(void);    // moves viewer away from object

	float zoom, vZoom;     // zoom and zoom velocity
private:
	VFVECTOR3 m_pos;
	VFVECTOR3 m_target;
	VFVECTOR3 m_up;
	VFVECTOR3 u, v, n;
};
