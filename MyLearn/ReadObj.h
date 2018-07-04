#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vmath/vfvector3.h>
#include <vmath/vnvector.h>

class Index
{
public:
	Index(void)
	{}

	Index(int p, int t, int n)
		: position(p), texcoord(t), normal(n)
	{}

	bool operator<(const Index& i) const
	{
		if (position < i.position) return true;
		if (position > i.position) return false;
		if (texcoord < i.texcoord) return true;
		if (texcoord > i.texcoord) return false;
		if (normal < i.normal) return true;
		if (normal > i.normal) return false;
		return false;
	}

	int position;
	int texcoord;
	int normal;
};

class  MeshData
{
public:
	std::vector<VFVector3>    vertices;
	std::vector<VNVECTOR3UI>   face;
	std::vector<VFVector3> texcoords;
	std::vector<VFVector3> normals;	
	//std::vector< std::vector< Index > > indices;
};

class ReadObj
{
public:
	ReadObj() {}
	~ReadObj() {}

	bool  ReadMeshData(std::string & path, MeshData& data);

private:
	void  readPosition(std::stringstream& ss, MeshData& data);
	void  readTexCoord(std::stringstream& ss, MeshData& data);
	void  readNormal(std::stringstream& ss, MeshData& data);
	void  readFace(std::stringstream& ss, MeshData& data);
	Index parseFaceIndex(const std::string& token);
};