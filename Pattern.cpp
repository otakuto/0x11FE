#include "Pattern.hpp"
#include "PatternObject.hpp"

const std::string Pattern::LIST_FILENAME = PatternObject::BASEDIR + "list";

int Pattern::load()
{
    std::ifstream ifs(LIST_FILENAME);
    std::string buffer;
    if (!ifs || ifs.fail())
    {
        std::cerr << "unable to open pattern list file " << LIST_FILENAME << std::endl;
        return -1;
    }

    patternObjects = new std::list<PatternObject>(0);
    while (getline(ifs, buffer))
    {
        if (!buffer.find("#"))
            continue;
        PatternObject po = PatternObject(buffer);
        if (po.load())
            return -1;
        patternObjects->push_back(po);
    }
    return 0;
}

std::list<PatternObject> * Pattern::getObjects()
{
    return patternObjects;
}
