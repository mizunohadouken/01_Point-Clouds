#include "OBJObject.h"

OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);
	parse(filepath);
}

bool OBJObject::readvals(std::stringstream &s, const int numvals, float* values)
{
	for (int i = 0; i < numvals; i++)
	{
		s >> values[i];
		if (s.fail())
		{
			std::cout << "Failed reading value " << i << " will skip\n";
			return false;
		}
	}
	return true;
}

void OBJObject::parse(const char *filepath) 
{
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data
	std::cout << "parsing: " << filepath << "\n";

	int char1, char2;
	glm::vec3 temp_vec, temp_normal;

	// open file to read and error out if not available
	FILE* fp = fopen(filepath, "rb");
	if (fp == NULL) { std::cerr << "error loading file" << std::endl; exit(-1); }

	do
	{
		char1 = fgetc(fp);
		char2 = fgetc(fp);

		if ((char1 == 'v') && (char2 == ' '))
		{
			fscanf(fp, "%f %f %f", &temp_vec.x, &temp_vec.y, &temp_vec.z);
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
	}
	while (char1 != EOF);

	printf("Vertices: %lu\nNormals: %lu\n\n", vertices.size(), normals.size());

	fclose(fp);


//	std::cout << "Parsed normals: " << normals.size() << "\n\n";

	/*
	std::string str, cmd;
	std::ifstream in;

	in.open(filepath);
	std::cout << "parsing: " << filepath << "\n";

	if (in.is_open())
	{

	getline(in, str);
	while (in)
	{
	if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#'))
	{
	std::stringstream s(str);
	s >> cmd;
	float values[10];
	bool valid_input;

	if (cmd == "v111")
	{
	valid_input = readvals(s, 3, values);
	if (valid_input)
	{
	vertices.push_back(glm::vec3(values[0], values[1], values[2]));
	}
	}
	else if (cmd == "vn111")
	{
	valid_input = readvals(s, 3, values);
	if (valid_input)
	{
	glm::vec3 temp_vec = glm::vec3(values[0], values[1], values[2]);
	normals.push_back(temp_vec);
	}

	}
	else
	{
	std::cerr << "Unknown Command: " << cmd << " Skipping \n";
	}

	}
	}
	}
	else
	{
	std::cerr << "Unable to Open Input Data File " << filepath << "\n";
	throw 2;
	}
	*/
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

void OBJObject::update()
{
	spin(1.f);
}

void OBJObject::spin(float deg)
{
	this->angle += deg;
	if (this->angle > 360.f || this->angle < -360.f) this->angle = 0.0f;

	this->toWorld = glm::rotate(glm::mat4(1.f), this->angle / 180.f * glm::pi<float>(), glm::vec3(0.f, 1.f, 0.f));
}
