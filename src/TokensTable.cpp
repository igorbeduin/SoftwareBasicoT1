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
        if (is_operation(elements[i]))
        {
            elementsClass[i] = StaticSymbols::operationClass;
        } else if (is_label_sep(elements[i]))
        {
            elementsClass[i-1] = StaticSymbols::labelClass;
            if (!symbTable.exist(elements[i-1]))
            {
                symbTable.insert_symbol(elements[i - 1]);
            } else 
            {
                // TODO: Implementar erro de quando a label ja existe na primeira passada
            }
            elementsClass[i] = StaticSymbols::labelSeparatorClass;
        } else if (is_argument_sep(elements[i]))
        {
            elementsClass[i] = StaticSymbols::argumentSeparatorClass;
        } else if (is_argument(elements[i]))
        {
            elementsClass[i] = StaticSymbols::argumentClass;
        } else if (is_symbol(elements[i]))
        {
            
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
    std::map<std::string, std::map<std::string, int>>::iterator found = DirectTable::directTable.find(element);
    if (found != DirectTable::directTable.end())
    {
        return true;
    }
    return false;
}

bool TokensTable::is_argument(std::string element)
{
    try
    {
        std::stoi(element);
        return true;
    }
    catch(const std::exception& e)
    {
        return false;
    }
}

void TokensTable::search_for_sections()
{
    std::vector<std::string>::iterator dataFound = std::find(elements.begin(), elements.end(), StaticSymbols::dataSectionMark);
    if (dataFound != elements.end() && *(dataFound-1) == StaticSymbols::sectionMark)
    {
        dataSection["begin"] = dataFound - elements.begin() + 1;
    }
    std::vector<std::string>::iterator textFound = std::find(elements.begin(), elements.end(), StaticSymbols::textSectionMark);
    std::vector<std::string>::iterator stopFound = std::find(elements.begin(), elements.end(), StaticSymbols::stopSectionMark);
    if (textFound != elements.end() && *(dataFound - 1) == StaticSymbols::sectionMark)
    {
        textSection["begin"] = textFound - elements.begin() + 1;
    }
    if (stopFound != elements.end())
    {
        textSection["end"] = (stopFound - elements.begin());
    }

    if (textSection["begin"] > dataSection["begin"])
    {
        dataSection["end"] = textSection["begin"] - 1;
    } else
    {
        dataSection["end"] = elements.size() - 1;
    }
}