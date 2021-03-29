#include "../include/Parser.h"

void Parser::split_elements(std::string line, int nLine)
{   
    obtain_separators(line);
    for (uint i = 0; i < indexes.size(); i++)
    {   
        std::string element;
        if (indexes[i] != indexes[indexes.size() - 1])
        {   
            int elementLength = indexes[i + 1] - indexes[i];
            element = line.substr(indexes[i], elementLength);
        } else 
        {
            element = line.substr(indexes[i]);
        }
        if (element[0] == separators[1])
        {
            element.erase(0, 1);
        }
        elements.push_back(element);
        std::map<int, std::string> elementInfo;
        elementInfo[nLine]=classify_element(element);
        elementInfoTable.push_back(elementInfo);
    }
    reset_indexes();
}

void Parser::obtain_separators(std::string line)
{
    for (uint i = 0; i < line.length(); i++)
    {
        bool sepFound;
        sepFound = std::find(separators.begin(), separators.end(), line[i]) != separators.end();

        if (sepFound)
        {
            indexes.push_back(i);
        }
    }
    std::sort(indexes.begin(), indexes.end());
}

void Parser::reset_indexes()
{
    indexes.clear();
    indexes.push_back(0);
}

std::string Parser::classify_element(std::string element)
{
    // TODO: classifica o elemento e retorna qual o tipo: label, operation, argument, comment
    return "foo";
}