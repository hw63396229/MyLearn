#pragma once
//#include <glad/glad.h> // holds all OpenGL type declarations
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//#include "Shader_s.h"
//#include "ReadObj.h"
//
//class testMesh
//{
//public:
//	testMesh(const std::vector<VFVECTOR3> & vertex, const std::vector<VNVECTOR3UI> & surf) 
//	{
//		triangle.resize(surf.size() * 3);
//		memcpy_s(&triangle.front(), triangle.size() * sizeof(unsigned), &surf.front(), triangle.size() * sizeof(unsigned));
//		SetMesh(vertex);
//	}
//	~testMesh() {}
//
//public:
//	unsigned VAO;
//	void Draw()
//	{
//		//draw mesh
//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, triangle.size(), GL_UNSIGNED_INT, 0);		
//		glBindVertexArray(0);
//	}
//
//private:
//	unsigned VBO, EBO;
//	void SetMesh(const std::vector<VFVECTOR3> & vertex)
//	{
//		// create buffers/arrays
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(1, &VBO);
//		glGenBuffers(1, &EBO);
//
//		glBindVertexArray(VAO);
//		// load data into vertex buffers
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		// A great thing about structs is that their memory layout is sequential for all its items.
//		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
//		// again translates to 3/2 floats which translates to a byte array.
//		glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(VFVECTOR3), &vertex[0], GL_STATIC_DRAW);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangle.size() * sizeof(unsigned), &triangle[0], GL_STATIC_DRAW);
//
//		// set the vertex attribute pointers
//		// vertex Positions
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VFVECTOR3), (void*)0);
//		glBindVertexArray(0);
//	}
//
//private:
//	std::vector<unsigned>    triangle;
//};
