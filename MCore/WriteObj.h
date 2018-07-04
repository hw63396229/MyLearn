#pragma once
#include <iostream>
#include <fstream>
#include <vmath/vfvector3.h>
#include <vmath/vnvector.h>

class WriteObj
{
public:
	WriteObj():path("out.obj") {}
	~WriteObj() {}

	void Write(const unsigned & vLen,  const VFVECTOR3* pVertices, const unsigned & sLen, const VNVECTOR3UI* pSurfaces)
	{
		std::ofstream fp(path);
		for (unsigned i = 0; i < vLen; i++)
		{
			fp << "v " << pVertices[i].x << " " << pVertices[i].y << " " << pVertices[i].z << std::endl;
		}
		for (unsigned i = 0; i < sLen; i++)
		{
			fp << "f " << pSurfaces[i].x + 1 << " " << pSurfaces[i].y + 1 << " " << pSurfaces[i].z + 1 << std::endl;
		}
		fp.close();
	}

	void SetPath(const std::string & str) { path = str; }

private:
	std::string  path;
};