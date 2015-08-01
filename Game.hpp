#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <utility>

class Game
{
	static constexpr int CELL_LENGTH_0 = 1000;
	static constexpr int CELL_LENGTH_1 = 1000;
	std::array<std::vector<std::vector<unsigned char>>, 2> swap;
	std::vector<std::vector<unsigned char>> * cell;
	std::vector<std::vector<unsigned char>> * next;

public:
	Game()
	:
	swap(),
	cell(&swap[0]),
	next(&swap[1])
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
			(*cell)[256][256 + i] = true;
		}
		for (int i = 0; i < 512; ++i)
		{
			(*cell)[i][512] = true;
		}
	}

	void run()
	{
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

				if (sum == 2)
				{
					(*next)[x][y] = (*cell)[x][y];
				}
				else if (sum == 3)
				{
					(*next)[x][y] = true;
				}
				else
				{
					(*next)[x][y] = false;
				}
			}
		}

		std::swap(cell, next);
	}

	void draw() const
	{
		static GLdouble const vertex[][3] =
		{
			{0, 0, 0},
			{1, 0, 0},
			{1, 0, 1},
			{0, 0, 1}
		};
		static GLubyte const color[3] = {0x00, 0xFF, 0x00};

		for (int x = 0; x < CELL_LENGTH_0; ++x)
		{
			for (int y = 0; y < CELL_LENGTH_1; ++y)
			{
				if ((*cell)[x][y])
				{
					glPushMatrix();
					glTranslated(x, 0, y);
					glColor3ubv(color);
					glBegin(GL_QUADS);
					for (auto && e : vertex)
					{
						glVertex3dv(e);
					}
					glEnd();
					glPopMatrix();
				}
			}
		}
	}
};

