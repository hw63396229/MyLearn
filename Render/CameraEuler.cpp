#include "stdafx.h"
#include "CameraEuler.h"

CameraEuler::CameraEuler(const VFVECTOR3 & pos, const VFVECTOR3 & target, const VFVECTOR3 & up)
{
	m_pos = pos;
	m_target = target;
	m_up = up;
	n = VFVECTOR3(pos.x - target.x, pos.y - target.y, pos.z - target.z);
	u = VFVECTOR3(up.Cross(n).x, up.Cross(n).y, up.Cross(n).z);
	v = VFVECTOR3(n.Cross(u).x, n.Cross(u).y, n.Cross(u).z);

	n.Normalize();
	u.Normalize();
	v.Normalize();

	zoom = 1.f;
	setModelViewMatrix();
}

void CameraEuler::setCamera(float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ)
{
	/* 构造向量 */
	m_pos.x = eyeX, m_pos.y = eyeY, m_pos.z = eyeZ;
	m_target.x = lookX, m_target.y = lookY, m_target.z = lookZ;
	m_up.x = upX, m_up.y = upY, m_up.z = upZ;
	VFVECTOR3 upvec(m_up.x - m_pos.x, m_up.y - m_pos.y, m_up.z - m_pos.z);

	/* 计算n、u、v并归一化*/
	n = m_pos - m_target;
	u = upvec.Cross(n);
	v = n.Cross(u);

	u.Normalize();
	v.Normalize();
	n.Normalize();
	setModelViewMatrix();
}

/* 计算变换后的视点矩阵*/
void CameraEuler::setModelViewMatrix()
{
	float m[16];
	m[0] = u.x; m[4] = u.y; m[8] = u.z; m[12] = -m_pos.Dot(u);
	m[1] = v.x; m[5] = v.y; m[9] = v.z; m[13] = -m_pos.Dot(v);
	m[2] = n.x; m[6] = n.y; m[10] = n.z; m[14] = -m_pos.Dot(n);
	m[3] = 0;  m[7] = 0;  m[11] = 0;  m[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);     //用M矩阵替换原视点矩阵 
}

/* 摄像机初始化*/
void CameraEuler::setShape(float viewAngle, float aspect, float Near, float Far)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                                   //设置当前矩阵模式为投影矩阵并归一化  
	gluPerspective(viewAngle, aspect, Near, Far);        //对投影矩阵进行透视变换 
}

/* 摄像机绕三个轴平移的计算函数*/
void CameraEuler::slide(float du, float dv, float dn)
{
	m_pos[0] = m_pos[0] + du*u.x + dv*v.x + dn*n.x;
	m_pos[1] = m_pos[1] + du*u.y + dv*v.y + dn*n.y;
	m_pos[2] = m_pos[2] + du*u.z + dv*v.z + dn*n.z;
	m_target[0] = m_target[0] + du*u.x + dv*v.x + dn*n.x;
	m_target[1] = m_target[0] + du*u.y + dv*v.y + dn*n.y;
	m_target[2] = m_target[0] + du*u.z + dv*v.z + dn*n.z;
	setModelViewMatrix();
}

/* 摄像机绕n、v、u轴旋转的计算函数*/
void CameraEuler::roll(float angle)
{
	float cs = cos(angle*3.14159265f / 180.f);
	float sn = sin(angle*3.14159265f / 180.f);
	VFVECTOR3 t(u);
	VFVECTOR3 s(v);
	u.x = cs*t.x - sn*s.x;
	u.y = cs*t.y - sn*s.y;
	u.z = cs*t.z - sn*s.z;

	v.x = sn*t.x + cs*s.x;
	v.y = sn*t.y + cs*s.y;
	v.z = sn*t.z + cs*s.z;

	setModelViewMatrix();          //每次计算完坐标轴变化后调用此函数更新视点矩阵  
}

void CameraEuler::yaw(float angle)
{
	float cs = cos(angle*3.14159265f / 180.f);
	float sn = sin(angle*3.14159265f / 180.f);
	VFVECTOR3 t(n);
	VFVECTOR3 s(u);

	n.x = cs*t.x - sn*s.x;
	n.y = cs*t.y - sn*s.y;
	n.z = cs*t.z - sn*s.z;

	u.x = sn*t.x + cs*s.x;
	u.y = sn*t.y + cs*s.y;
	u.z = sn*t.z + cs*s.z;

	setModelViewMatrix();
}

void CameraEuler::pitch(float angle)
{
	float cs = cos(angle*3.14159265f / 180.f);
	float sn = sin(angle*3.14159265f / 180.f);
	VFVECTOR3 t(v);
	VFVECTOR3 s(n);

	v.x = cs*t.x - sn*s.x;
	v.y = cs*t.y - sn*s.y;
	v.z = cs*t.z - sn*s.z;

	n.x = sn*t.x + cs*s.x;
	n.y = sn*t.y + cs*s.y;
	n.z = sn*t.z + cs*s.z;

	setModelViewMatrix();
}

/* 获取eye到坐标原点的距离 */
float CameraEuler::getDist()
{
	float dist = pow(m_pos.x, 2) + pow(m_pos.y, 2) + pow(m_pos.z, 2);
	return pow(dist, 0.5f);
}

void CameraEuler::zoomIn(void)
{
	vZoom -= .5f;
}

void CameraEuler::zoomOut(void)
{
	vZoom += .5f;
}
