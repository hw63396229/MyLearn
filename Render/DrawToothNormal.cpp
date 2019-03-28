#include "stdafx.h"
#include "DrawToothNormal.h"

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
		//shader.setVec3("objectColor", .8f, 0.5f, 0.31f); 
		shader.setVec3("objectColor", .9f, 0.9f, 0.9f);
		shader.setVec3("lightColor", 1.f, 1.f, 1.f);
		shader.setVec3("lightPos", lightPos);
		
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
		shader.setVec3("viewPos", eye);
		
		glDrawElements(GL_TRIANGLES, surface.size(), GL_UNSIGNED_INT, &surface.front());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(2, VBO);

	glfwTerminate();
}