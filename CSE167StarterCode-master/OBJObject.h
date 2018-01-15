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
	glm::mat4 toWorld, m_translate, m_rotate, m_scale, m_orbit;
	float angle;


public:
	OBJObject(const char* filepath);

	// methods

	void parse(const char* filepath);
	void draw();
	void update();
	void spin(float);
	void translation(glm::vec3 v_translate);
	void scale(float scale_factor);
	void rotation(float rotation_angle_deg, glm::vec3 rotation_axis);
	void orbit(float rotation_angle_deg, glm::vec3 rotation_axis);
	void reset_position();
	void reset_orientation_scale();
};

#endif