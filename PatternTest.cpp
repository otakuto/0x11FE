#include "PatternTest.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "PatternTest" << std::endl << std::endl;
    std::cout << "loading " << Pattern::LIST_FILENAME << std::endl;
    Pattern pattern = Pattern();
    if (pattern.load())
        return -1;
    std::cout << "loaded pattern:" << std::endl;
    std::list<PatternObject> * list = pattern.getObjects();
    std::list<PatternObject>::iterator it = list->begin();
    while (it != list->end())
    {
        std::cout << it->getName() << std::endl;
        it->putDebug(0, 0, 0, 0);
        it++;
    }
    std::cout << "end" << std::endl;
    return 0;
}
