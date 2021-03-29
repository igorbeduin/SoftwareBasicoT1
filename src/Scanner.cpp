#include "../include/Scanner.h"

void Scanner::split_elements(std::string line, int nLine)
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
        if (element[0] == separators[0])
        {  

            elements.push_back(",");
            elementsLine.push_back(nLine);
            elementsClass.push_back("arg_sep");
            element.erase(0, 1);
        }
        elements.push_back(element);
        elementsLine.push_back(nLine);
        if (is_label_sep(element))
        {
            elementsClass.back() = "label";
            elementsClass.push_back("label_sep");
        } else if (is_operation(element))
        {
            elementsClass.push_back("op");
        } else if (is_argument(element))
        {
            elementsClass.push_back("arg");
        } else 
        {
            elementsClass.push_back("");
        }
        
    }
    reset_indexes();
}

void Scanner::obtain_separators(std::string line)
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

void Scanner::reset_indexes()
{
    indexes.clear();
    indexes.push_back(0);
}

std::string Scanner::classify_element(std::string element)
{
    // TODO: classifica o elemento e retorna qual o tipo: label, operation, argument, comment
    return "foo";
}

bool Scanner::is_label_sep(std::string element)
{ // TODO: 
    return false;
}
bool Scanner::is_operation(std::string element)
{ // TODO:
    return false;
}
bool Scanner::is_argument(std::string element)
{ // TODO:
    return false;
}

void Scanner::print_elements()
{
    for (uint i = 0; i < elements.size(); i++)
    {
        std::cout << elements[i] << std::endl;
    }
}