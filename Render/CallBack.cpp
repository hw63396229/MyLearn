#include "stdafx.h"
#include "CallBack.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera   camera;

float deltaTime = 0.f;
float lastFrame = 0.f;
float lastX = (float)SCR_WIDTH / 2.0f;
float lastY = (float)SCR_HEIGHT / 2.0f;
bool firstMouse = true;
glm::vec3 lightPos(1.2f, 1.0f, 200.0f);
int m_button = -1, m_mode = -1, m_action = -1;
Quaternion r = 1.f;

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
		return;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	default:
		break;
	}
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	if (m_button == GLFW_MOUSE_BUTTON_LEFT && m_action == GLFW_PRESS)
		camera.motion((int)xpos, (int)ypos);
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	if (yoffset == -1)
		camera.zoom -= 0.01f;
	else    //yoffset == 1
		camera.zoom += 0.01f;
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.yslide -= 0.5f;
		r = 0.f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.yslide += 0.5f;
		r = 0.f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.xslide += 0.5f;
		r = 0.f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.xslide -= 0.5f;
		r = 0.f;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.zoom -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.zoom += 0.005f;
}

void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	m_button = button;
	m_mode = mods;
	m_action = action;

	camera.mouse(button, !action, (int)lastX, (int)lastY);  //GLFW_PRESS与GLUT_DOWN值相反

	//if (action == GLFW_PRESS) switch (button)
	//{
	//    case GLFW_MOUSE_BUTTON_LEFT:
	//    	//Mouse left button clicked!"
	//    	//camera.mouse(button, !action, (int)lastX, (int)lastY);
	//    	break;
	//    case GLFW_MOUSE_BUTTON_MIDDLE:
	//    	//"Mouse middle button clicked!"
	//    	break;
	//    case GLFW_MOUSE_BUTTON_RIGHT:
	//    	//"Mouse right button clicked!"
	//    	std::cout << "Mouse Right Button Pressed! " << std::endl;
	//    	break;
	//    default:
	//    	return;
	//}
	//if(action == GLFW_RELEASE) switch (button)
	//{
	//case GLFW_MOUSE_BUTTON_LEFT:
	//	//std::cout << "Released!" << std::endl;
	//	break;
	//default:
	//	return;
	//}

	return;
}

glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	// 1. Position = known
	// 2. Calculate cameraDirection
	glm::vec3 zaxis = glm::normalize(position - target);
	// 3. Get positive right axis vector
	glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
	// 4. Calculate camera up vector
	glm::vec3 yaxis = glm::cross(zaxis, xaxis);

	// Create translation and rotation matrix
	// In glm we access elements as mat[col][row] due to column-major layout
	glm::mat4 translation; // Identity matrix by default
	translation[3][0] = -position.x; // Third column, first row
	translation[3][1] = -position.y;
	translation[3][2] = -position.z;
	glm::mat4 rotation;
	rotation[0][0] = xaxis.x; // First column, first row
	rotation[1][0] = xaxis.y;
	rotation[2][0] = xaxis.z;
	rotation[0][1] = yaxis.x; // First column, second row
	rotation[1][1] = yaxis.y;
	rotation[2][1] = yaxis.z;
	rotation[0][2] = zaxis.x; // First column, third row
	rotation[1][2] = zaxis.y;
	rotation[2][2] = zaxis.z;

	// Return lookAt matrix as combination of translation and rotation matrix
	return rotation * translation; // Remember to read from right to left (first translation then rotation)
}

// Don't forget to replace glm::lookAt with your own version
// view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//view = calculate_lookAt_matrix(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));