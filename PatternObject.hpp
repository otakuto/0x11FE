#pragma once
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <fstream>
#include <list>

class PatternObject
{
    std::string filename;
    int width;
    int height;
	std::shared_ptr<std::list<std::list<unsigned char>>> pattern;

public:
    static const std::string BASEDIR;

    PatternObject(std::string filename)
	:
	filename(BASEDIR + filename)
    {
    }

    ~PatternObject()
    {
    }

    int load();

    std::string getName() const;

    std::string setName(std::string n);

	std::shared_ptr<std::list<std::list<unsigned char>>> getPattern();

    int putDebug(int x, int y, int maxx, int maxy) const;
};

