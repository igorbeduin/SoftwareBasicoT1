#include "../include/Parser.h"

void Parser::split_elements(std::string line)
{   
    obtain_separators(line);
    for (int i = 0; i < indexes.size() - 1; i++)
    {

    }

}

void Parser::obtain_separators(std::string line)
{
    for (uint i = 0; i < line.length(); i++)
    {
        std::cout << i << std::endl;
        bool sepFound;
        sepFound = std::find(separators.begin(), separators.end(), line[i]) != separators.end();

        if (sepFound)
        {
            indexes.push_back(i);
        }
    }
}

void Parser::reset_elements()
{}