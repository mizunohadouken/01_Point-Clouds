#include "OBJObject.h"

OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);
	m_translate = glm::mat4(1.0f);
	m_rotate = glm::mat4(1.0f);
	m_scale = glm::mat4(1.0f);
	m_orbit = glm::mat4(1.0f);
	point_size = 1.f;
	parse(filepath);
	this->angle = 0.f;

}

void OBJObject::parse(const char *filepath) 
{
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data
	std::cout << "parsing: " << filepath << "\n";

	FILE* fp;
	float x, y, z;
	float r, g, b;
	int char1, char2;
	glm::vec3 temp_vec, temp_normal;


	// open file to read and error out if not available
	fp = fopen(filepath, "rb");
	if (fp == NULL) { std::cerr << "error loading file" << std::endl; exit(-1); }

	char1 = fgetc(fp);
	char2 = fgetc(fp);

	while (char1 != EOF)
	{
		if ((char1 == 'v') && (char2 == ' '))
		{
			fscanf(fp, "%f %f %f %f %f %f ", &temp_vec.x, &temp_vec.y, &temp_vec.z, &r, &g, &b);
			vertices.push_back(temp_vec);
		}
		else if ((char1 == 'v') && (char2 == 'n'))
		{
			fscanf(fp, "%f %f %f", &temp_vec.x, &temp_vec.y, &temp_vec.z);
			normals.push_back(temp_vec);
		}
		else if (char1 == '#')
		{
			std::cout << "it's a comment" << std::endl;
		}
		char1 = fgetc(fp);
		char2 = fgetc(fp);
	}


	printf("Vertices: %lu\nNormals: %lu\n\n", vertices.size(), normals.size());

	fclose(fp);
}

void OBJObject::draw() 
{
	glMatrixMode(GL_MODELVIEW);

	// Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(&(toWorld[0][0]));

	glBegin(GL_POINTS);
	// Loop through all the vertices of this OBJ Object and render them
	for (unsigned int i = 0; i < vertices.size(); ++i) 
	{
		glColor3f(normals[i].x, normals[i].y, normals[i].z);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();

	// Pop the save state off the matrix stack
	// This will undo the multiply we did earlier
	glPopMatrix();
}

void OBJObject::rasterize_object(glm::mat4 m_DPV)
{

}

void OBJObject::update()
{
	//spin(1.f);
}

void OBJObject::spin(float deg)
{
	this->toWorld = toWorld * glm::rotate(glm::mat4(1.0f), deg / 180.0f * glm::pi<float>(), glm::vec3(0.f,1.f,0.f));
}

void OBJObject::translation(glm::vec3 v_translate)
{
	glm::mat4 m_translation = glm::translate(glm::mat4(1.f), v_translate);
	this->toWorld = m_translation * this->toWorld;	
}

void OBJObject::scale(float scale_factor)
{
	toWorld = toWorld * glm::scale(glm::mat4(1.f), glm::vec3(scale_factor));
}

void OBJObject::rotation(float rotation_angle_deg, glm::vec3 rotation_axis)
{
	toWorld = toWorld * glm::rotate(glm::mat4(1.0f), rotation_angle_deg / 180.0f * glm::pi<float>(), rotation_axis);
}

void OBJObject::orbit(float rotation_angle_deg, glm::vec3 rotation_axis)
{
	toWorld = glm::rotate(glm::mat4(1.0f), rotation_angle_deg / 180.0f * glm::pi<float>(), rotation_axis) * toWorld;
}

void OBJObject::reset_position()
{
	toWorld[3][0] = 0.f;
	toWorld[3][1] = 0.f;
	toWorld[3][2] = 0.f;
}

void OBJObject::reset_orientation_scale()
{
	glm::vec3 stored_translation = glm::vec3(toWorld[3][0], toWorld[3][1], toWorld[3][2]);
	toWorld = glm::mat4(1.f);
	translation(stored_translation);
}

void OBJObject::change_point_size(float point_size_change)
{
	point_size = point_size * point_size_change;
	glPointSize(point_size);
}

glm::mat4 OBJObject::get_world_mat()
{
	return toWorld;
}

std::vector<glm::vec3> OBJObject::get_vertices_vec()
{
	return vertices;
}

std::vector<glm::vec3> OBJObject::get_normals_vec()
{
	return normals;
}
