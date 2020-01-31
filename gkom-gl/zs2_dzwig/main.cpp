#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include "Scene.h"

const GLuint WIDTH = 800, HEIGHT = 600;

GLFWwindow* Initialize();
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, int button, int action, int mods);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

Scene* scene = nullptr;

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	try
	{
		GLFWwindow* window = Initialize();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		
		scene = new Scene(window, projection);

		clock_t previousTime = clock();

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();

			glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			clock_t time = clock();
			GLfloat dt = (GLfloat)(time - previousTime) / CLOCKS_PER_SEC;

			scene->Update(dt);
			scene->Render(dt);

			previousTime = time;

			glfwSwapBuffers(window);
		}
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

	glfwTerminate();

	return 0;
}

GLFWwindow* Initialize()
{
	if (glfwInit() != GL_TRUE) throw std::exception("GLFW initialization failed");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - harvester", nullptr, nullptr);
	if (window == nullptr) throw std::exception("GLFW window not created");
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) throw std::exception("GLEW Initialization failed");

	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return window;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{	
	if (scene != nullptr)
	{
		scene->KeyCallback(key, scancode, action, mode);
	}
}

void MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (scene != nullptr)
	{
		scene->MouseCallback(button, action, mods);
	}
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	if (scene != nullptr)
	{
		scene->ScrollCallback(xOffset, yOffset);
	}
}