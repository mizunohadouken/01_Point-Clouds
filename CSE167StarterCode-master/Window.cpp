#include "Window.h"

#define DEBUG 0;

const char* window_title = "GLFW Starter Project";
Cube cube(5.0f);

int object_number = 0;

int Window::width;
int Window::height;

std::vector<OBJObject> v_objects;


void Window::initialize_objects()
{
	// TODO parse all objects here, add bunny and dragon
	OBJObject obj_bunny = OBJObject("objs\\bunny.obj");
	OBJObject obj_bear = OBJObject("objs\\bear2.obj");
	OBJObject obj_dragon = OBJObject("objs\\dragon1.obj");

	v_objects.push_back(obj_bunny);
	v_objects.push_back(obj_bear);
	v_objects.push_back(obj_dragon);

#if DEBUG
	int x = v_objects.size();
	std::cout << x;
#endif
}

void Window::clean_up()
{
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size
	glViewport(0, 0, width, height);
	// Set the matrix mode to GL_PROJECTION to determine the proper camera properties
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the perspective of the projection viewing frustum
	gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0);
	// Move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glTranslatef(0, 0, -20);
}

void Window::idle_callback()
{
	// TODO spin object

	// Perform any updates as necessary. Here, we will spin the cube slightly.
//	cube.update();
	if (object_number == 0)
	{
		v_objects[0].update();
	}
	else if (object_number == 1)
	{
		v_objects[1].update();
	}
	else if (object_number == 2)
	{
		v_objects[2].update();
	}
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Set the matrix mode to GL_MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	// Load the identity matrix
	glLoadIdentity();
	

	// TODO  change object to render
	// Render objects
//	cube.draw();
	if (object_number == 0)
	{
		v_objects[0].draw();
#if DEBUG
		std::cout << "Object 1\n";
#endif
	}
	else if (object_number == 1)
	{
		v_objects[1].draw();
#if DEBUG
		std::cout << "Object 2\n";
#endif
	}
	else if (object_number == 2)
	{
		v_objects[2].draw();
#if DEBUG
		std::cout << "Object 3\n";;
#endif
	}
	
	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		
		// TODO add key press actions for F1, F2, & F3 to display/render different OBJs
		else if (key == GLFW_KEY_F1)
		{
			std::cout << "F1\n";
			object_number = 0;
		}
		else if (key == GLFW_KEY_F2)
		{
			object_number = 1;
		}
		else if (key == GLFW_KEY_F3)
		{
			object_number = 2;
		}
		else if (key == GLFW_KEY_X)
		{
			
		}
		else if (key == GLFW_KEY_Y)
		{

		}
		else if (key == GLFW_KEY_Z)
		{

		}
		else if (key == GLFW_KEY_S)
		{

		}
		else if (key == GLFW_KEY_O)
		{

		}
		else if (key == GLFW_KEY_R)
		{

		}

	}
}
