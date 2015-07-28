#include "PatternList.hpp"

const std::string PatternList::LIST_FILENAME = "pattern/list";

int PatternList::load()
{
    std::ifstream ifs(LIST_FILENAME);
    std::string buffer;
    if (!ifs || ifs.fail())
    {
        std::cerr << "unable to open pattern list file " << LIST_FILENAME << std::endl;
        return -1;
    }

    patternObjects = std::make_shared<std::list<Pattern>>();
    while (getline(ifs, buffer))
    {
        if (!buffer.find("#"))
        {
            continue;
        }
        Pattern pattern(buffer);
        if (pattern.load())
        {
            return -1;
        }
        patternObjects->push_back(pattern);
    }
    return 0;
}

std::shared_ptr<std::list<Pattern>> PatternList::getObjects()
{
    return patternObjects;
}
