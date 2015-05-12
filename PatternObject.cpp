#include "PatternObject.hpp"

const std::string PatternObject::BASEDIR = "pattern/";

int PatternObject::load()
{
    std::string filename = BASEDIR + name.c_str();
    std::ifstream ifs(filename);
    if (!ifs || ifs.fail())
    {
        std::cerr << "unable to open pattern file : " << filename << std::endl;
        return -1;
    }
    else
    {
        std::cout << "loading " << filename << std::endl;
    }

    int lines = 0;
    int maxcolumns = 0;
    std::string str;
    while (getline(ifs, str))
    {
        int columns = str.length();
        if (maxcolumns < columns)
            maxcolumns = columns;
        if (!lines)
            pattern = new std::list<std::list<bool>>(0);
        std::list<bool> line = std::list<bool>(0);
        for (int c = 0; c < columns; ++c)
        {
            if (str[c] == '0')
                line.push_back(false);
            else if (str[c] == '1')
                line.push_back(true);
            else
            {
                std::cerr << "pattern parser error:" << name << std::endl;
                return -1;
            }
        }
        pattern->push_back(line);
        lines++;
    }
    height = lines;
    width = maxcolumns;
    ifs.close();
    return 0;
}

std::string PatternObject::getName()
{
    return name;
}

std::string PatternObject::setName(std::string n)
{
    return name = n;
}

int adjustPosition(int num, int min, int max)
{
    if (num < min)
        num = min;
    if (num > max)
        num = max;
    return num;
}

int PatternObject::putDebug(int x, int y, int maxx, int maxy)
{
    if (!pattern)
    {
        std::cerr << "oops" << std::endl;
        return -1;
    }
    int startx = adjustPosition(x - width / 2, 0, maxx);
    int starty = adjustPosition(y - height / 2, 0, maxy);;
    std::cout << "startx:";
    std::cout << startx;
    std::cout << ", starty:";
    std::cout << starty;
    std::cout << std::endl;

    std::list<std::list<bool>>::iterator ity = pattern->begin();
    while (ity != pattern->end())
    {
        std::list<bool>::iterator itx = ity->begin();
        while (itx != ity->end())
        {
            std::cout << (int)(*itx);
            itx++;
        }
        std::cout << std::endl;
        ity++;
    }
    return 0;
}
