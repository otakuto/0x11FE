#pragma once
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <fstream>
#include <list>

class Pattern
{
    std::string filename;
    int width;
    int height;
	std::shared_ptr<std::list<std::list<unsigned char>>> pattern;

public:
    static const std::string BASEDIR;

    Pattern(std::string filename)
	:
	filename(BASEDIR + filename)
    {
    }

    ~Pattern()
    {
    }

    int load();

    std::string getName() const;

    std::string setName(std::string n);

	int getWidth() const;
	int getHeight() const;

	std::shared_ptr<std::list<std::list<unsigned char>>> getPattern() const;

    int putDebug(int x, int y, int maxx, int maxy) const;
};

