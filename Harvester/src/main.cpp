#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Scene.h"
#include "Camera.h"
using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;

GLFWwindow* initialize_window();
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

int main() {
    try {
        GLFWwindow* window = initialize_window();

		Scene scene = Scene();
        
        // main loop
        while (!glfwWindowShouldClose(window)) {
            // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
            glfwPollEvents();

            // Clear the colorbuffer
            glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // TODO (@pochka15): How to update a scene and objects? Use events?

            // Swap the screen buffers
            glfwSwapBuffers(window);
        }
    } catch (exception ex) {
        cout << ex.what() << endl;
    }
    glfwTerminate();

    return 0;
}

GLFWwindow* initialize_window()
{
	if (glfwInit() != GL_TRUE) throw std::exception("GLFW initialization failed");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - Harvester", nullptr, nullptr);
	if (window == nullptr) throw std::exception("GLFW window not created");
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);
	glfwSetScrollCallback(window,scrollCallback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) throw std::exception("GLEW Initialization failed");

	glViewport(0, 0, WIDTH, HEIGHT);

	// glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return window;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    cout << key << endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	std::cout << "TODO mouseCallback()\n";
}
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	std::cout << "TODO scrollCallback()\n";
}
