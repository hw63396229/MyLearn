#include "stdafx.h"
//#include "Depend.h"
//#include "CallBack.h"
//#include "Model.h"
//
//int LNgeometryshaderexploding()
//{
//	// glfw: initialize and configure
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// glfw window creation
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	if (!gladLoadGL())//(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// configure global opengl state
//	glEnable(GL_DEPTH_TEST);
//
//	// build and compile shaders
//	Shader shader("9.2.geometry_shader.vert", "9.2.geometry_shader.frag", "9.2.geometry_shader.gs");
//
//	// load models
//	Model nanosuit("../model/nanosuit.obj");
//
//	// render loop
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		processInput(window);
//
//		// render
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// configure transformation matrices
//		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();;
//		glm::mat4 model;
//		shader.use();
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", view);
//		shader.setMat4("model", model);
//
//		// add time component to geometry shader in the form of a uniform
//		shader.setFloat("time", glfwGetTime());
//
//		// draw model
//		nanosuit.Draw(shader);
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}