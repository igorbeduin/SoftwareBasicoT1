#include "../include/TokensTable.h"
#include "../include/StaticSymbols.h"

void TokensTable::insert_token(std::string element, int elementLine, std::string elementClass)
{
    elements.push_back(element);
    elementsLine.push_back(elementLine);
    elementsClass.push_back(elementClass);
}

void TokensTable::print_elements()
{
    for (uint i = 0; i < elements.size(); i++)
    {
        std::cout << elements[i] << std::endl;
    }
}

void TokensTable::classify_tokens()
{
    for (uint i = 0; i < elements.size(); i++)
    {
        if (is_label_sep(elements[i]))
        {
            elementsClass[i-1] = StaticSymbols::labelClass;
            elementsClass[i] = StaticSymbols::labelSeparatorClass;
        } else if (is_argument_sep(elements[i]))
        {
            elementsClass[i] = StaticSymbols::argumentSeparatorClass;
        }
    }
}

bool TokensTable::is_label_sep(std::string element)
{ 
    return (element == StaticSymbols::labelSeparator? true : false);
}

bool TokensTable::is_argument_sep(std::string element)
{
    return (element == StaticSymbols::argumentSeparator? true : false);
}

bool TokensTable::is_operation(std::string element)
{
    return false;
}

bool TokensTable::is_argument(std::string element)
{ // TODO:
    return false;
}