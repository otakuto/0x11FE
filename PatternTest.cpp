#include <iostream>
#include "PatternTest.hpp"
#include "Pattern.hpp"
#include "PatternList.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "PatternTest" << std::endl << std::endl;
    std::cout << "loading " << PatternList::LIST_FILENAME << std::endl;
    PatternList patternList;
    if (patternList.load())
        return -1;
    std::cout << "loaded pattern:" << std::endl;
	std::shared_ptr<std::list<Pattern>> list = patternList.getObjects();
    for (auto const & e : *list)
    {
        std::cout << e.getName() << std::endl;
        e.putDebug(0, 0, 0, 0);
    }
    std::cout << "end" << std::endl;
}
