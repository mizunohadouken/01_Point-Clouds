#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>

#ifdef __APPLE__
// If modern OpenGL replace gl.h with gl3.h
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include "Cube.h"

#include "OBJObject.h"
#include <vector>

class Window
{
public:
	//variables
	static int width;
	static int height;
	static float* pixels;
	static bool b_rasterize;

	// methods
	static void initialize_objects();
	static void clean_up();
	static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback();
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void clearBuffer();
	static void drawPoint(int x, int y, float r, float g, float b);

	static void rasterize();


private:

	
};

#endif

