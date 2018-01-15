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
	v_objects[object_number].update();

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
	v_objects[object_number].draw();
	
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
		
		// press F1, F2, & F3 to display/render different OBJs
		else if (key == GLFW_KEY_F1){object_number = 0;}
		else if (key == GLFW_KEY_F2){object_number = 1;}
		else if (key == GLFW_KEY_F3){object_number = 2;}

		// translate along x axis
		else if (key == GLFW_KEY_X)
		{
			if (mods == GLFW_MOD_SHIFT){v_objects[object_number].translation(glm::vec3(.5f, 0.f, 0.f));}
			else{v_objects[object_number].translation(glm::vec3(-.5f, 0.f, 0.f));}
		}

		// translate along y axis
		if (key == GLFW_KEY_Y)
		{
			if (mods == GLFW_MOD_SHIFT) { v_objects[object_number].translation(glm::vec3(0.f, 0.5f, 0.f));}
			else { v_objects[object_number].translation(glm::vec3(0.f, -.5f, 0.f));}
		}

		// translate along z axis
		else if (key == GLFW_KEY_Z)
		{
			if (mods == GLFW_MOD_SHIFT){v_objects[object_number].translation(glm::vec3(0.f, 0.f, -1.f));}
			else{v_objects[object_number].translation(glm::vec3(0.f, 0.f, 1.f));}
		}

		// scale object
		else if (key == GLFW_KEY_S)
		{
			if (mods == GLFW_MOD_SHIFT){v_objects[object_number].scale(1.5f);}
			else{v_objects[object_number].scale(.5f);}
		}

		// orbit object about the z axis
		else if (key == GLFW_KEY_O)
		{
			if (mods == GLFW_MOD_SHIFT) { v_objects[object_number].orbit(10.f, glm::vec3(0.f, 0.f, 1.f)); }
			else { v_objects[object_number].orbit(10.f, glm::vec3(0.f, 0.f, -1.f)); }
		}

		// reset position or orientation/scale
		else if (key == GLFW_KEY_R)
		{
			// upper case R resets scale and orientation
			if (mods == GLFW_MOD_SHIFT) { v_objects[object_number].reset_orientation_scale(); }
			// lower case r resets position
			else { v_objects[object_number].reset_position(); }
		}

	}
}
