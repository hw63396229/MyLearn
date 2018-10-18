#include "stdafx.h"
#include "ReadObj.h"

bool ReadObj::ReadMeshData(std::string & path, MeshData & data)
{
	std::ifstream in(path.c_str());

	std::string line;
	while (std::getline(in, line))
	{
		std::stringstream  ss(line);
		std::string token;
		ss >> token;

		if (token == "v") { readPosition(ss, data); continue; } //vertex
		if (token == "vt") { readTexCoord(ss, data); continue; } //texture coordinate
		if (token == "vn") { readNormal(ss, data); continue; }   //vertex normal
		if (token == "f") { readFace(ss, data); continue; }     //face
		if (token[0] == '#') continue;  //comment
		if (token == "o") continue;     //object name
		if (token == "g") continue;     //group name
		if (token == "s") continue;     //smoothing group
		if (token == "mtllib") continue;//material library
		if (token == "usemtl") continue;//material
		if (token == "") continue;      //empty string

		std::cerr << "Error: does not appear to be a valid Wavefront OBJ file !	" << std::endl;
		std::cerr << "Offending line: " << line << ")" << std::endl;
		return false;
	}
	return true;
}

void ReadObj::readPosition(std::stringstream & ss, MeshData & data)
{
	float x, y, z;
	ss >> x >> y >> z;
	data.vertices.push_back(VFVector3(x, y, z));
}

void ReadObj::readTexCoord(std::stringstream & ss, MeshData & data)
{
	float u, v;
	ss >> u >> v;
	data.texcoords.push_back(VFVector3(u, v, 0.f));
}

void ReadObj::readNormal(std::stringstream & ss, MeshData & data)
{
	float x, y, z;
	ss >> x >> y >> z;
	data.normals.push_back(VFVector3(x, y, z));
}

void ReadObj::readFace(std::stringstream & ss, MeshData & data)
{
	//std::vector<Index> faceIndices;
	std::string token;
	VNVECTOR3UI   temp;
	unsigned i = 0;
	while (ss >> token)
	{
		//faceIndices.push_back(parseFaceIndex(token));
		temp[i] = parseFaceIndex(token).position;
		i ++;
	}
	//data.indices.push_back(faceIndices);
	data.face.push_back(temp);
}

Index ReadObj::parseFaceIndex(const std::string & token)
{
	std::stringstream  in(token);
	std::string indexstring;
	int indices[3] = { -1, -1, -1 };
	int i = 0;

	while (std::getline(in, indexstring, '/'))
	{
		std::stringstream  ss(indexstring);
		ss >> indices[i++];
	}

	// decrement since indices in OBJ files are 1-based
	return Index(indices[0] - 1, indices[1] - 1, indices[2] - 1);
}
