#include <GL/glfw.h>
#include <vector>
#include <iostream>
#include <cmath>
#include "Game.hpp"

int main()
{
	glfwInit();
	glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

	glfwSetWindowSizeCallback([](int w, int h)
	{
		glViewport(0, 0, w, h);
		glLoadIdentity();
		gluPerspective(90, static_cast<double>(w) / static_cast<double>(h), 1, 100);
		gluLookAt(0, 0, 64, 0, 0, 0, 0, 1, 0);
	});

	Game game;

	while (glfwGetWindowParam(GLFW_OPENED))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		game.run();
		game.draw();
		glfwSwapBuffers();
	}
	glfwTerminate();
}

