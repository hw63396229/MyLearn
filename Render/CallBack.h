#pragma once
#include <iostream>
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Custom implementation of the LookAt function
glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);

// settings
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

// camera
extern Camera camera;
extern float lastX;
extern float lastY;
extern bool firstMouse;

// timing
extern float deltaTime;
extern float lastFrame;

extern glm::vec3  lightPos;
extern int m_button, m_mode, m_action;
extern Quaternion r;