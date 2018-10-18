#include "stdafx.h"

//#define GLEW_STATIC
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//GLFWwindow* window;
//GLint width, height;
//GLfloat ratio = 1.f;
//GLfloat xpos, ypos;
//GLfloat fScale = 1.0f;	// set inital scale value to 1.0f
//GLfloat rquad = 0.0f;
//
//static void error_callback(int error, const char* description)
//{
//	return;
//}
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	if (action != GLFW_PRESS)
//		return;
//	switch (key)
//	{
//	case GLFW_KEY_ESCAPE:
//		glfwSetWindowShouldClose(window, GL_TRUE);
//		break;
//	default:
//		break;
//	}
//}
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	if (action == GLFW_PRESS) switch (button)
//	{
//	case GLFW_MOUSE_BUTTON_LEFT:
//		std::cout << "Mosue left button clicked!" << std::endl;
//		break;
//	case GLFW_MOUSE_BUTTON_MIDDLE:
//		std::cout << "Mosue middle button clicked!" << std::endl;
//		break;
//	case GLFW_MOUSE_BUTTON_RIGHT:
//		std::cout << "Mosue right button clicked!" << std::endl;
//		break;
//	default:
//		return;
//	}
//	return;
//}
//void cursor_position_callback(GLFWwindow* window, double x, double y)
//{
//	std::cout << "Mouse position move to: " << int(x) << " " << int(y) << std::endl;
//	xpos = float((x - width / 2) / width) * 2;
//	ypos = float(0 - (y - height / 2) / height) * 2;
//	return;
//}
//void scroll_callback(GLFWwindow* window, double x, double y)
//{
//	return;
//}
//void framebuffer_size_callback(GLFWwindow* window, int w, int h)
//{
//	if (height == 0)  									// Prevent A Divide By Zero By
//	{
//		height = 1;										// Making Height Equal One
//	}
//	if (h > 0)
//		ratio = (float)w / (float)h;
//	glViewport(0, 0, w, h); // Setup viewport
//	width = w;
//	height = h;
//	glViewport(0, 0, width, height);						// Reset The Current Viewport
//	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
//	glLoadIdentity();									// Reset The Projection Matrix
//														// Calculate The Aspect Ratio Of The Window
//	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
//	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
//	glLoadIdentity();
//}
//void draw_scene(GLFWwindow* window)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//	glLoadIdentity();
//	glTranslatef(-0.5f, -0.5f, -3.0f);
//	glRotatef(rquad, 1.0f, 1.0f, 1.0f);
//	glBegin(GL_POLYGON);/* f1: front */
//	glColor3f(1.0f, 0.0f, 0.5f);
//	glNormal3f(-1.0f, 0.0f, 0.0f);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glVertex3f(0.0f, 0.0f, 1.0f);
//	glVertex3f(1.0f, 0.0f, 1.0f);
//	glVertex3f(1.0f, 0.0f, 0.0f);
//	glEnd();
//	glBegin(GL_POLYGON);/* f2: bottom */
//	glColor3f(1.0f, 0.5f, 0.0f);
//	glNormal3f(0.0f, 0.0f, -1.0f);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glVertex3f(1.0f, 0.0f, 0.0f);
//	glVertex3f(1.0f, 1.0f, 0.0f);
//	glVertex3f(0.0f, 1.0f, 0.0f);
//	glEnd();
//	glBegin(GL_POLYGON);/* f3:back */
//	glColor3f(0.0f, 0.5f, 1.0f);
//	glNormal3f(1.0f, 0.0f, 0.0f);
//	glVertex3f(1.0f, 1.0f, 0.0f);
//	glVertex3f(1.0f, 1.0f, 1.0f);
//	glVertex3f(0.0f, 1.0f, 1.0f);
//	glVertex3f(0.0f, 1.0f, 0.0f);
//	glEnd();
//	glBegin(GL_POLYGON);/* f4: top */
//	glColor3f(0.5f, 0.0f, 1.0f);
//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glVertex3f(1.0f, 1.0f, 1.0f);
//	glVertex3f(1.0f, 0.0f, 1.0f);
//	glVertex3f(0.0f, 0.0f, 1.0f);
//	glVertex3f(0.0f, 1.0f, 1.0f);
//	glEnd();
//	glBegin(GL_POLYGON);/* f5: left */
//	glColor3f(0.0f, 1.0f, 0.5f);
//	glNormal3f(0.0f, 1.0f, 0.0f);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glVertex3f(0.0f, 1.0f, 0.0f);
//	glVertex3f(0.0f, 1.0f, 1.0f);
//	glVertex3f(0.0f, 0.0f, 1.0f);
//	glEnd();
//	glBegin(GL_POLYGON);/* f6: right */
//	glColor3f(0.5f, 1.0f, 0.0f);
//	glNormal3f(0.0f, -1.0f, 0.0f);
//	glVertex3f(1.0f, 0.0f, 0.0f);
//	glVertex3f(1.0f, 0.0f, 1.0f);
//	glVertex3f(1.0f, 1.0f, 1.0f);
//	glVertex3f(1.0f, 1.0f, 0.0f);
//	glEnd();
//	rquad += 0.8f;
//}
//void init_opengl(void)
//{
//	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
//	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
//	glClearDepth(1.0f);									// Depth Buffer Setup
//	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
//	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
//}
//int main(int argc, char *argv[])
//{
//	glfwSetErrorCallback(error_callback);
//	if (!glfwInit())
//	{
//		exit(EXIT_FAILURE);
//	}
//	window = glfwCreateWindow(640, 480, "opengl tutorial 002-color box", NULL, NULL);
//	if (window == NULL)
//	{
//		glfwTerminate();
//		exit(EXIT_FAILURE);
//	}
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);
//	glfwSetCursorPosCallback(window, cursor_position_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwMakeContextCurrent(window);
//	glfwGetFramebufferSize(window, &width, &height);
//	framebuffer_size_callback(window, width, height);
//	//initialize opengl
//	init_opengl();
//
//	while (!glfwWindowShouldClose(window))
//	{
//		draw_scene(window);
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	glfwTerminate();
//	exit(EXIT_SUCCESS);
//}

//glfwGetCursorPos