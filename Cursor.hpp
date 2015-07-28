#pragma once
#include <iterator>
#include <memory>
#include "Game.hpp"
#include "Pattern.hpp"

class Cursor
{
	GLFWwindow * const window;
	std::shared_ptr<Game> game;
	std::shared_ptr<std::list<Pattern>> patternObjects;
	std::list<Pattern>::iterator select;
public:
	int x;
	int y;
	bool isVisible;

public:
	Cursor(GLFWwindow * const window, std::shared_ptr<Game> game, std::shared_ptr<std::list<Pattern>> patternObjects)
	:
	window(window),
	game(game),
	patternObjects(patternObjects),
	select(patternObjects->begin()),
	x(),
	y(),
	isVisible(true)
	{
	}

	void run()
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT))
		{
			if (select == patternObjects->begin())
			{
				select = std::prev(patternObjects->end());
			} else
			{
				--select;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT))
		{
			if (select == std::prev(patternObjects->end()))
			{
				select = patternObjects->begin();
			}
			else
			{
				++select;
			}
		}
		{
			static bool key = true;
			if (glfwGetKey(window, GLFW_KEY_ENTER))
			{
				if (key)
				{
					game->pastePattern(x, y, false, *select);
					key = false;
				}
			}
			else
			{
				key = true;
			}
		}
	}

	void draw() const
	{
		if (!isVisible)
		{
			return;
		}

		constexpr GLdouble vertex[][3] =
		{
			{0, 0, 0},
			{1, 0, 0},
			{1, 0, 1},
			{0, 0, 1}
		};
		constexpr GLubyte color[3] = {0x00, 0xFF, 0x00};

		auto const pattern = select->getPattern();

		int i = 0;
		for (auto const & row : *pattern)
		{
			int j = 0;
			for (auto const e : row)
			{
				if (e)
				{
					glPushMatrix();
					glTranslated(x + j, 0, y + i);
					glColor3ubv(color);
					glBegin(GL_QUADS);
					for (auto & v : vertex)
					{
						glVertex3dv(v);
					}
					glEnd();
					glPopMatrix();
				}
				++j;
			}
			++i;
		}

	}
};
