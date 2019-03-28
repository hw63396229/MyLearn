#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "CallBack.h"
#include "Mesh.h"
#include "Shader_s.h"
#include <ReadObj.h>

class DrawToothNormal
{
public:
	DrawToothNormal() {}
	~DrawToothNormal() {}

	void DrawNormal(std::string path);

private:
	MeshData  data;
	ReadObj   m_read;
	std::vector<unsigned>  surface;
};

