#include "stdafx.h"
#include "Depend.h"

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//
//// settings
//const unsigned int SCR_WIDTH = 320;
//const unsigned int SCR_HEIGHT = 240;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//double deltaTime = 0.0f;
//double lastFrame = 0.0f;
//
////lighting
//glm::vec3 lightPos(1.2f, 1.f, 2.f);
//
//int main()
//{
//	// glfw: initialize and configure
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// glfw window creation
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LNGL", NULL, NULL);
//	assert(window != NULL);
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// configure global opengl state
//	glEnable(GL_DEPTH_TEST);
//
//	// build and compile our shader zprogram
//	Shader  lightingShader("3.1.materials.vert", "3.1.materials.frag");
//	Shader  lampShader("3.1.lamp.vert", "3.1.lamp.frag");
//
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//	float vertices[] = {
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//	};
//
//	// first, configure the cube's VAO (and VBO)
//	unsigned cubeVAO, VBO;
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &VBO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBindVertexArray(cubeVAO);
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
//	glEnableVertexAttribArray(0);
//	// normal attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
//	unsigned lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
//	glEnableVertexAttribArray(0);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		double currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		processInput(window);
//
//		//render
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// be sure to activate shader when setting uniforms/drawing objects
//		lightingShader.use();
//		lightingShader.setVec3("light.position", lightPos);
//		lightingShader.setVec3("viewPos", camera.Position);
//		//light properties
//		glm::vec3  lightColor;
//		lightColor.x = sinf(static_cast<float>(glfwGetTime()) * 2.f);
//		lightColor.y = sinf(static_cast<float>(glfwGetTime()) * .7f);
//		lightColor.z = sinf(static_cast<float>(glfwGetTime()) * 1.3f);
//		glm::vec3  diffuseColor = lightColor * glm::vec3(.5f);             //decrease the influence
//		glm::vec3  ambientColor = diffuseColor * glm::vec3(.2f);           //low influence
//		lightingShader.setVec3("light.ambient", ambientColor);
//		lightingShader.setVec3("light.diffuse", diffuseColor);
//		lightingShader.setVec3("light.specular", 1.f, 1.f, 1.f);
//
//		// material properties
//		lightingShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//		lightingShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
//		lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
//		lightingShader.setFloat("material.shininess", 32.0f);
//
//		// view/projection transformations
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, .1f, 100.f);
//		glm::mat4 view = camera.GetViewMatrix();
//		lightingShader.setMat4("projection", projection);
//		lightingShader.setMat4("view", view);
//		// world transformation
//		glm::mat4 model;
//		lightingShader.setMat4("model", model);
//
//		//render the cube
//		glBindVertexArray(cubeVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		// also draw the lamp object
//		lampShader.use();
//		lampShader.setMat4("projection", projection);
//		lampShader.setMat4("view", view);
//		model = glm::mat4();
//		model = glm::translate(model, lightPos);
//		model = glm::scale(model, glm::vec3(.2f));     //a smaller cube
//		lampShader.setMat4("model", model);
//
//		glBindVertexArray(lightVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	glDeleteBuffers(1, &cubeVAO);
//	glDeleteBuffers(1, &lightVAO);
//	glDeleteBuffers(1, &VBO);
//
//	glfwTerminate();
//	return 0;
//}
//
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
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
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
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}