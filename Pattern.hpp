#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <iostream>
#include <fstream>
#include <array>
#include <utility>
#include <string>
#include <list>
#include "PatternObject.hpp"

class Pattern
{
    std::list<PatternObject> * patternObjects;

    int loadList();
    int loadObject();
public:
    static const std::string LIST_FILENAME;

    Pattern()
    {
    }

    ~Pattern()
    {
    }

    int load();

    std::list<PatternObject> * getObjects();
};

#endif
