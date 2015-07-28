#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>
#include <cmath>
#include "Game.hpp"
#include "PatternList.hpp"
#include "Pattern.hpp"
#include "Cursor.hpp"

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
	//GLFWwindow * window = glfwCreateWindow(mode->width, mode->height, "0x11FE", monitor, nullptr);
	GLFWwindow * window = glfwCreateWindow(mode->width, mode->height, "0x11FE", nullptr, nullptr);
    glfwMakeContextCurrent(window);

	Game game(window);

	PatternList patternList;
	patternList.load();
	static Cursor cursor(window, patternList.getObjects());

	int x = 512;
	int y = 384;
	int z = 512;

	static int wheel = 0;
	glfwSetScrollCallback(window, [](auto window, double x, double y)
	{
		wheel = y;
	});

	glfwSetCursorEnterCallback(window, [](auto window, int enter)
	{
		cursor.isVisible = enter;
	});

    while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glLoadIdentity();
		gluPerspective(90, static_cast<double>(width) / static_cast<double>(height), 1, 2048);
		gluLookAt(x, y, z, x, 0, z, 0, 0, -1);

		if (glfwGetKey(window, GLFW_KEY_Q))
		{
			static double cursorPos[2];
			static double old[2];
			glfwGetCursorPos(window, &cursorPos[0], &cursorPos[1]);
			cursor.x = cursorPos[0];
			cursor.y = cursorPos[1];
		}

		int move = 10;

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		{
			move = 1;
		}
		else
		{
			move = 10;
		}

		if (glfwGetKey(window, GLFW_KEY_UP))
		{
			y -= move;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN))
		{
			y += move;
		}

		if (glfwGetKey(window, GLFW_KEY_D))
		{
			x += move;
		}
		if (glfwGetKey(window, GLFW_KEY_A))
		{
			x -= move;
		}
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			z -= move;
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			z += move;
		}

		if (wheel)
		{
			y -= wheel * move * 5;
			wheel = 0;
		}

		game.run();
		cursor.run();
		game.draw();
		cursor.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

