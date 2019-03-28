#pragma once
#include <iostream>
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);
unsigned int loadCubemap(const std::vector<std::string> &faces);

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

//light
extern glm::vec3 lightPos;