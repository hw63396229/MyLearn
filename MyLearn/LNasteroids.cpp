#include "stdafx.h"
//#include "Depend.h"
//#include "CallBack.h"
//#include "Model.h"
////LNasteroids
//int main()
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
//	if(!gladLoadGL())// (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// configure global opengl state
//	glEnable(GL_DEPTH_TEST);
//
//	// build and compile shaders
//	Shader shader("10.2.instancing.vert", "10.2.instancing.frag");
//
//	// load models
//	Model rock("../model/rock/rock.obj");
//	Model planet("../model/planet/planet.obj");
//
//	// generate a large list of semi-random model transformation matrices
//	unsigned int amount = 1000;
//	glm::mat4* modelMatrices;
//	modelMatrices = new glm::mat4[amount];
//	srand(glfwGetTime()); // initialize random seed	
//	float radius = 50.0;
//	float offset = 2.5f;
//	for (unsigned int i = 0; i < amount; i++)
//	{
//		glm::mat4 model;
//		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
//		float angle = (float)i / (float)amount * 360.0f;
//		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float x = sin(angle) * radius + displacement;
//		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
//		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float z = cos(angle) * radius + displacement;
//		model = glm::translate(model, glm::vec3(x, y, z));
//
//		// 2. scale: Scale between 0.05 and 0.25f
//		float scale = (rand() % 20) / 100.0f + 0.05;
//		model = glm::scale(model, glm::vec3(scale));
//
//		// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
//		float rotAngle = (rand() % 360);
//		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
//
//		// 4. now add to list of matrices
//		modelMatrices[i] = model;
//	}
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
//		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
//		glm::mat4 view = camera.GetViewMatrix();;
//		shader.use();
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", view);
//
//		// draw planet
//		glm::mat4 model;
//		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
//		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
//		shader.setMat4("model", model);
//		planet.Draw(shader);
//
//		// draw meteorites
//		for (unsigned int i = 0; i < amount; i++)
//		{
//			shader.setMat4("model", modelMatrices[i]);
//			rock.Draw(shader);
//		}
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}