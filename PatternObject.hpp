#pragma once
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <fstream>
#include <list>

class PatternObject
{
    std::string name;
    int width;
    int height;
    std::list<std::list<bool>> * pattern;

public:
    static const std::string BASEDIR;

    PatternObject(std::string filename)
	:
	name(filename)
    {
    }

    int load();

    std::string getName() const;

    std::string setName(std::string n);

    int putDebug(int x, int y, int maxx, int maxy) const;

    ~PatternObject()
    {
    }

};
