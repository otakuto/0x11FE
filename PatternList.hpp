#pragma once
#include <iostream>
#include <fstream>
#include <array>
#include <utility>
#include <memory>
#include <string>
#include <list>
#include "Pattern.hpp"

class PatternList
{
	std::shared_ptr<std::list<Pattern>> patternObjects;

public:
    static std::string const LIST_FILENAME;

    PatternList()
    {
    }

    ~PatternList()
    {
    }

    int load();

	std::shared_ptr<std::list<Pattern>> getObjects();
};

