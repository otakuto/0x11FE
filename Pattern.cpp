#include "Pattern.hpp"

const std::string Pattern::BASEDIR = "pattern/";

int Pattern::load()
{
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
        {
            maxcolumns = columns;
        }
        if (!lines)
        {
            pattern = std::make_shared<std::list<std::list<unsigned char>>>();
        }
        std::list<unsigned char> line = std::list<unsigned char>();
        for (int c = 0; c < columns; ++c)
        {
            if (str[c] == '0')
                line.push_back(false);
            else if (str[c] == '1')
                line.push_back(true);
            else
            {
                std::cerr << "pattern parser error:" << filename << std::endl;
                return -1;
            }
        }
        pattern->push_back(line);
        ++lines;
    }
    height = lines;
    width = maxcolumns;
    ifs.close();
    return 0;
}

std::string Pattern::getName() const
{
    return filename;
}

std::string Pattern::setName(std::string n)
{
    return filename = n;
}

int adjustPosition(int num, int min, int max)
{
    if (num < min)
        num = min;
    if (num > max)
        num = max;
    return num;
}

std::shared_ptr<std::list<std::list<unsigned char>>> Pattern::getPattern()
{
	return pattern;
}

int Pattern::putDebug(int x, int y, int maxx, int maxy) const
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

    for (auto const & e : *pattern)
    {
        for (auto const & row : e)
        {
            std::cout << static_cast<int>(row);
        }
        std::cout << std::endl;
    }

    return 0;
}
