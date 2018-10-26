#include "stdafx.h"
#include "DrawToothNormal.h"

float deltaTime = 0.f, lastFrame = 0.f;
float lastX = (float)SCR_WIDTH / 2.0f, lastY = (float)SCR_HEIGHT / 2.0f;
bool firstMouse = true;
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
Camera camera;
int m_button = -1, m_mode = -1, m_action = -1;
Quaternion r = 1.f;

void DrawToothNormal::DrawNormal(std::string path)
{
	m_read.ReadMeshData(path, data);
	surface.resize(data.face.size() * 3);
	memcpy_s(&surface.front(), surface.size() * sizeof(unsigned), &data.face.front(), surface.size() * sizeof(unsigned));

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tooth", nullptr, nullptr);
	assert(window != nullptr);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	if (!gladLoadGL())
	{
		//gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		std::cout << "glfw init failed!" << std::endl;
		system("pause");
	}

	glEnable(GL_DEPTH_TEST);
	Shader  shader("tooth.vert", "tooth.frag");

	unsigned VAO, VBO[2];
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(VFVector3), &data.vertices.front(), GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VFVector3), nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, data.normals.size() * sizeof(VFVector3), &data.normals.front(), GL_STATIC_DRAW);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VFVector3), nullptr);
	glEnableVertexAttribArray(1);

	shader.use();

	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		shader.setVec3("objectColor", .8f, 0.5f, 0.31f);
		shader.setVec3("lightColor", 1.f, 1.f, 1.f);
		
		
		glm::mat4 model;
		shader.setMat4("model", model);
		
		r = (camera.pDrag * camera.pClick.conj()) * camera.rLast;
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
		glm::mat4 rot = {
			M[0], M[1], M[2], M[3],
			M[4], M[5], M[6], M[7],
			M[8], M[9], M[10], M[11], 
			M[12], M[13], M[14], M[15]
		};

		glm::vec3 eye = glm::vec3(0.f, 0.f, 100.f * camera.zoom);
		glm::vec3 center = glm::vec3(camera.xslide, camera.yslide, 0.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 view = calculate_lookAt_matrix(eye, center, up) * rot;

		glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, .1f, 300.f);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);
		
		glDrawElements(GL_TRIANGLES, surface.size(), GL_UNSIGNED_INT, &surface.front());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(2, VBO);

	glfwTerminate();
}

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

	if(m_button == GLFW_MOUSE_BUTTON_LEFT && m_action == GLFW_PRESS)
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
