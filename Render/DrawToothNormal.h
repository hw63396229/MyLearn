#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Shader_s.h"
#include "Camera.h"
#include <ReadObj.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

extern float deltaTime, lastFrame;
extern float lastX, lastY;
extern bool firstMouse;
extern glm::vec3  lightPos;
extern int m_button, m_mode, m_action;
extern Quaternion r;

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

// Custom implementation of the LookAt function
glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
//{
//	// 1. Position = known
//	// 2. Calculate cameraDirection
//	glm::vec3 zaxis = glm::normalize(position - target);
//	// 3. Get positive right axis vector
//	glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
//	// 4. Calculate camera up vector
//	glm::vec3 yaxis = glm::cross(zaxis, xaxis);
//
//	// Create translation and rotation matrix
//	// In glm we access elements as mat[col][row] due to column-major layout
//	glm::mat4 translation; // Identity matrix by default
//	translation[3][0] = -position.x; // Third column, first row
//	translation[3][1] = -position.y;
//	translation[3][2] = -position.z;
//	glm::mat4 rotation;
//	rotation[0][0] = xaxis.x; // First column, first row
//	rotation[1][0] = xaxis.y;
//	rotation[2][0] = xaxis.z;
//	rotation[0][1] = yaxis.x; // First column, second row
//	rotation[1][1] = yaxis.y;
//	rotation[2][1] = yaxis.z;
//	rotation[0][2] = zaxis.x; // First column, third row
//	rotation[1][2] = zaxis.y;
//	rotation[2][2] = zaxis.z;
//
//	// Return lookAt matrix as combination of translation and rotation matrix
//	return rotation * translation; // Remember to read from right to left (first translation then rotation)
//}

// Don't forget to replace glm::lookAt with your own version
// view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//view = calculate_lookAt_matrix(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));