#include "stdafx.h"
//#include "Depend.h"
//#include "ReadObj.h"
//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 100.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//// lighting
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//
//int main()
//{
//	MeshData  data;
//	ReadObj   m_read;
//	std::string path("D:\\down.obj");
//	m_read.ReadMeshData(path, data);
//	std::vector<unsigned>   surface;
//	surface.resize(data.face.size() * 3);
//	memcpy_s(&surface.front(), surface.size() * sizeof(unsigned), &data.face.front(), surface.size() * sizeof(unsigned));
//
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tooth", nullptr, nullptr);
//	assert(window != nullptr);
//
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	
//	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	if (!gladLoadGL())
//	{
//		//gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
//		std::cout << "glfw init failed!" << std::endl;
//		system("pause");
//	}
//
//	glEnable(GL_DEPTH_TEST);
//	Shader  shader("tooth.vert", "tooth.frag");
//
//	unsigned VAO, VBO[2];
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(2, VBO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
//	glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(VFVector3), &data.vertices.front(), GL_STATIC_DRAW);
//
//	glBindVertexArray(VAO);
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VFVector3), nullptr);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//	glBufferData(GL_ARRAY_BUFFER, data.normals.size() * sizeof(VFVector3), &data.normals.front(), GL_STATIC_DRAW);
//	// normal attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VFVector3), nullptr);
//	glEnableVertexAttribArray(1);
//
//	shader.use();
//
//	while (!glfwWindowShouldClose(window))
//	{
//		double currentTime = glfwGetTime();
//		deltaTime = currentTime - lastFrame;
//		lastFrame = currentTime;
//
//		processInput(window);
//
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		shader.use();
//		shader.setVec3("objectColor", .8f, 0.5f, 0.31f);
//		shader.setVec3("lightColor", 1.f, 1.f, 1.f);
//
//		glm::mat4 model;
//		shader.setMat4("model", model);
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, .1f, 300.f);
//		shader.setMat4("view", view);
//		shader.setMat4("projection", projection);
//
//		glDrawElements(GL_TRIANGLES, surface.size(), GL_UNSIGNED_INT, &surface.front());
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(2, VBO);
//
//	glfwTerminate();
//	return 0;
//}
//
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyBoard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyBoard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyBoard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyBoard(RIGHT, deltaTime);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	if (action == GLFW_PRESS) switch (button)
//	{
//	case GLFW_MOUSE_BUTTON_LEFT:
//		//Mosue left button clicked!"
//		break;
//	case GLFW_MOUSE_BUTTON_MIDDLE:
//		//"Mosue middle button clicked!"
//		break;
//	case GLFW_MOUSE_BUTTON_RIGHT:
//		//"Mosue right button clicked!"
//		break;
//	default:
//		return;
//	}
//	return;
//}

////根据屏幕坐标得到视点空间坐标
//void Get3Dpos(int x, int y, fVector3* pp) {
//	GLint viewport[4];
//	GLdouble modelview[16];
//	GLdouble projection[16];
//	GLfloat winX, winY, winZ;
//	GLdouble object_x, object_y, object_z;
//	int mouse_x = x;
//	int mouse_y = y;
//	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
//	glGetDoublev(GL_PROJECTION_MATRIX, projection);
//	glGetIntegerv(GL_VIEWPORT, viewport);
//
//	winX = (float)mouse_x;
//	winY = (float)viewport[3] - (float)mouse_y - 1.0f;
//	glReadBuffer(GL_BACK);
//	glReadPixels(mouse_x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
//	gluUnProject((GLdouble)winX, (GLdouble)winY, (GLdouble)winZ, modelview, projection, viewport, &object_x, &object_y, &object_z);
//	*pp.x = object_x;
//	*pp.y = object_y;
//	*pp.z = object_z;
//}
//
////根据视点空间坐标得到世界空间坐标
//GetWorldPos(int x, int y) {
//	//得到观察空间的坐标
//	fVector3 pp;
//	Pick(x, y, &pp);
//
//	//求视点的UVN系统
//	fVector3 U, V, N;                   //fVector3为自定义向量类
//	fVector3 up = { 0.0,1.0,0.0 };
//	fVector3 eye, direction;            //视点坐标与观察点坐标
//
//	N = eye - direction                 //矢量减法
//		U = N.cross(up);                    //矢量叉乘
//	V = N.cross(U);
//
//	N.normalize();                      //矢量归一化
//	U.normalize();
//	V.normalize();
//
//	//求世界坐标
//	fVector3 worldpos = { 0.0f，0.0f，0.0f };
//	worldpos.x = U.x * pp.x + V.x * pp.y + N.x * pp.z + eye.x;
//	worldpos.x = U.y * pp.x + V.y * pp.y + N.y * pp.z + eye.y;
//	worldpos.z = U.z * pp.x + V.z * pp.y + N.z * pp.z + eye.z;
//}