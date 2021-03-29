#include "../include/Parser.h"

void Parser::split_elements(std::string line)
{   
    obtain_separators(line);
    for (uint i = 0; i < indexes.size(); i++)
    {   
        std::string element;
        if (indexes[i] != indexes[indexes.size() - 1])
        {   
            int elementLength = indexes[i + 1] - indexes[i];
            int correctFactor = (indexes[i] != 0? 1:0);
            element = line.substr(indexes[i] + correctFactor, elementLength);
        } else 
        {
            element = line.substr(indexes[i]);
        }
        elements.push_back(element);
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