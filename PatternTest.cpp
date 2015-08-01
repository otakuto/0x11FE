#include <iostream>
#include "PatternTest.hpp"
#include "PatternObject.hpp"
#include "Pattern.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "PatternTest" << std::endl << std::endl;
    std::cout << "loading " << Pattern::LIST_FILENAME << std::endl;
    Pattern pattern;
    if (pattern.load())
        return -1;
    std::cout << "loaded pattern:" << std::endl;
    std::list<PatternObject> * list = pattern.getObjects();
    for (auto const & e : *list)
    {
        std::cout << e.getName() << std::endl;
        e.putDebug(0, 0, 0, 0);
    }
    std::cout << "end" << std::endl;
}
