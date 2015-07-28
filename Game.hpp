#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include "Pattern.hpp"

class Game
{
	static constexpr int CELL_LENGTH_0 = 1024;
	static constexpr int CELL_LENGTH_1 = 1024;

	GLFWwindow * const window;
	std::array<std::vector<std::vector<unsigned char>>, 2> swap;
	std::vector<std::vector<unsigned char>> * cell;
	std::vector<std::vector<unsigned char>> * next;

	bool isStop;

public:
	Game(GLFWwindow * const window)
	:
	window(window),
	swap(),
	cell(&swap[0]),
	next(&swap[1]),
	isStop(false)
	{
		for (int i = 0; i < 2; ++i)
		{
			swap[i].resize(CELL_LENGTH_0);
			for (int j = 0; j < CELL_LENGTH_0; ++j)
			{
				swap[i][j].resize(CELL_LENGTH_1);
			}
		}

		for (int i = 0; i < 512; ++i)
		{
			(*cell)[512][256 + i] = true;
		}
		for (int i = 0; i < 512; ++i)
		{
			(*cell)[256 + i][512] = true;
		}
	}

	void run()
	{
		{
			static bool key = true;
			if (glfwGetKey(window, GLFW_KEY_SPACE))
			{
				if (key)
				{
					isStop = !isStop;
					key = false;
				}
			}
			else
			{
				key = true;
			}
		}

		if (isStop)
		{
			return;
		}
		/*
		static int time = 0;
		if (time >= 10)
		{
			time = 0;
		}
		else
		{
			++time;
			return;
		}
		*/

		for (int x = 1; x < CELL_LENGTH_0 - 1; ++x)
		{
			for (int y = 1; y < CELL_LENGTH_1 - 1; ++y)
			{
				int sum = 0;
				for (int i = -1; i <= 1; ++i)
				{
					for (int j = -1; j <= 1; ++j)
					{
						if (i == 0 && j == 0)
						{
						}
						else if ((*cell)[x + i][y + j])
						{
							++sum;
						}
					}
				}

				switch (sum)
				{
					case 2:
					(*next)[x][y] = (*cell)[x][y];
					break;

					case 3:
					(*next)[x][y] = true;
					break;

					default:
					(*next)[x][y] = false;
					break;
				}
			}
		}

		std::swap(cell, next);
	}

	void draw() const
	{
		constexpr GLdouble vertex[][3] =
		{
			{0, 0, 0},
			{1, 0, 0},
			{1, 0, 1},
			{0, 0, 1}
		};
		constexpr GLubyte color[3] = {0x00, 0xFF, 0x00};

		for (int y = 0; y < CELL_LENGTH_1; ++y)
		{
			for (int x = 0; x < CELL_LENGTH_0; ++x)
			{
				if ((*cell)[y][x])
				{
					glPushMatrix();
					glTranslated(x, 0, y);
					glColor3ubv(color);
					glBegin(GL_QUADS);
					for (auto v : vertex)
					{
						glVertex3dv(v);
					}
					glEnd();
					glPopMatrix();
				}
			}
		}
	}

	void pastePattern(int x, int y, bool isReverse, Pattern const & pattern)
	{
		if ((0 <= x) && ((x + pattern.getWidth()) < CELL_LENGTH_1) && (0 <= y) && ((y + pattern.getHeight()) < CELL_LENGTH_0))
		{
			int i = 0;
			for (auto const & row : *pattern.getPattern())
			{
				int j = 0;
				for (auto const e : row)
				{
					if (isReverse)
					{
						(*cell)[y + j][x + i] = !e;
					}
					else
					{
						(*cell)[y + j][x + i] = e;
					}
					++j;
				}
				++i;
			}
		}
	}
};

