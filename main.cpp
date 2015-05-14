#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>
#include <cmath>
#include "Game.hpp"

int main()
{
	glfwInit();

	int count;
	GLFWmonitor ** monitors = glfwGetMonitors(&count);
	GLFWmonitor * monitor = monitors[0];
	//GLFWmonitor * monitor = glfwGetPrimaryMonitor();
	GLFWvidmode const * mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	GLFWwindow * window = glfwCreateWindow(mode->width, mode->height, "0x11FE", monitor, nullptr);
    glfwMakeContextCurrent(window);

	Game game;

    while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glLoadIdentity();
		gluPerspective(90, static_cast<double>(width) / static_cast<double>(height), 1, 1024);
		gluLookAt(0, 100, 64, 0, 0, 0, 0, 1, 0);

		game.run();
		game.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

