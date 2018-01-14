#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class OBJObject
{
private:


	//variables
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4 toWorld;
	float angle;


public:
	OBJObject(const char* filepath);

	// methods
	bool readvals(std::stringstream & s, const int numvals, float * values);
	void parse(const char* filepath);
	void draw();
	void update();
	void spin(float);
};

#endif