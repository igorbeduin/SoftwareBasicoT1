#include "../include/TokensTable.h"
#include "../include/StaticSymbols.h"

std::vector<std::string> TokensTable::elements;
std::vector<int> TokensTable::elementsLine;
std::vector<std::string> TokensTable::elementsClass;
std::map<std::string, int> TokensTable::dataSection;
std::map<std::string, int> TokensTable::textSection;
SymbTable TokensTable::symbTable;
int TokensTable::max_length = 50;
bool TokensTable::quitRequest = false;
std::vector<char> TokensTable::numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
std::vector<char> TokensTable::letters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                             'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                             'V', 'W', 'X', 'Y', 'Z', '_'};

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
        if (i > 0 && elementsLine[i] != elementsLine[i-1])
        {
            std::cout << std::endl;
        }
        std::cout << elements[i] << " ";
        if (is_operation(elements[i]))
        {
            elementsClass[i] = StaticSymbols::operationClass;
        } else if (is_label_sep(elements[i]))
        {
            if (elementsClass[i-1]==StaticSymbols::dummyClass)
            {
                elementsClass[i-1] = StaticSymbols::labelClass;
                if (lexical_error(i - 1))
                {
                    quitRequest = true;
                    break;
                }
            }
            elementsClass[i] = StaticSymbols::labelSeparatorClass;
            if (!symbTable.exist(elements[i - 1]))
            {
                symbTable.insert_symbol(elements[i - 1]);
            }
            else
            {
                // TODO: Implementar erro de quando a label ja existe na primeira passada
            }

        } else if (is_argument_sep(elements[i]))
        {
            elementsClass[i] = StaticSymbols::argumentSeparatorClass;
        } else if (is_argument(elements[i]))
        {
            elementsClass[i] = StaticSymbols::argumentClass;
        } else if (is_section_mark(elements[i]) && is_section_mark(elements[i+1]))
        {
            elementsClass[i] = StaticSymbols::ignoreClass;
            elementsClass[i + 1] = StaticSymbols::ignoreClass;
        } else if (elementsClass[i - 1] == StaticSymbols::operationClass && elements[i - 1] != "SPACE")
        {
            elementsClass[i] = StaticSymbols::symbolCandidateClass;
            if (lexical_error(i))
            {
                quitRequest = true;
                break;
            }
        }
    }
    for (uint i = 0; i < elements.size(); i++)
    {
        if ((elementsClass[i] == StaticSymbols::symbolCandidateClass)
            || (elementsClass[i] == StaticSymbols::dummyClass))
            {
                if (is_symbol(elements[i]))
                {
                    elementsClass[i] = StaticSymbols::symbolClass;
                }
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
    for (uint i = 0; i < element.length(); i++)
    {
        char character = element[i];
        int int_character = character - '0';
        if (int_character < 0 || int_character > 9)
        {
            return false;
        }
    }
    return true;
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

bool TokensTable::is_symbol(std::string element)
{
    return symbTable.exist(element);
}

bool TokensTable::is_section_mark(std::string element)
{
    return (element == StaticSymbols::sectionMark ||
            element == StaticSymbols::dataSectionMark ||
            element == StaticSymbols::textSectionMark ||
            element == StaticSymbols::stopSectionMark);
        
}

bool TokensTable::is_in_text_section(int index)
{
    return (index >= textSection["begin"] && index <= textSection["end"]);
}

void TokensTable::fill_symb_table()
{
    int lineCounter = 0;
    for (uint i = 0; i < elements.size(); i++)
    {
        if (elementsClass[i] != StaticSymbols::ignoreClass)
        {
            if (elementsClass[i] == StaticSymbols::labelClass)
            {
                symbTable.insert_value(elements[i], lineCounter);
            }
            if (elementsClass[i] == StaticSymbols::operationClass)
            {
                lineCounter += DirectTable::directTable[elements[i]]["WORDS"];
            }
        }
    }
}

bool TokensTable::lexical_error(int index)
{
    bool found = false;
    if ((TokensTable::elementsClass[index] == StaticSymbols::labelClass)
        || (TokensTable::elementsClass[index] == StaticSymbols::symbolClass)
        || (TokensTable::elementsClass[index] == StaticSymbols::symbolCandidateClass))
    {
        if ((int)TokensTable::elements[index].length() > max_length)
        {
            found =  true;
        } else if (std::find(numbers.begin(), numbers.end(), TokensTable::elements[index][0]) != numbers.end())
        {
            found =  true;
        } else
        {
            for (int i = 0; i < (int)TokensTable::elements[index].length(); i++)
            {
                if ((std::find(numbers.begin(), numbers.end(), TokensTable::elements[index][i]) == numbers.end()) &&
                    (std::find(letters.begin(), letters.end(), TokensTable::elements[index][i]) == letters.end()))
                    {
                        found =  true;
                    }
            }
        }
    }
    if (found)
    {
        std::cout << std::endl << "ERRO LEXICO NA LINHA " << elementsLine[index] << std::endl;
    }
    return found;
}

bool TokensTable::get_quit_request()
{
    return quitRequest;
}