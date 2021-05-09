#include "../include/TokensTable.h"
#include "../include/StaticSymbols.h"

std::vector<std::string> TokensTable::elements;
std::vector<int> TokensTable::elementsLine;
std::vector<std::string> TokensTable::elementsClass;

std::map<std::string, int> TokensTable::dataSection;
std::map<std::string, int> TokensTable::textSection;

SymbTable TokensTable::symbTable;
DefTable TokensTable::defTable;
UsageTable TokensTable::usageTable;

int TokensTable::max_length = 50;

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
    std::cout << "L1: ";
    for (uint i = 0; i < elements.size(); i++)
    {   
        if (i > 0 && elementsLine[i] != elementsLine[i-1])
        {
            std::cout << std::endl << "L" << elementsLine[i] << ": ";
        }
        std::cout << elements[i] << " ";
        
        // INICIA LOOP
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
                    ControlVariables::set_quitRequest(true);
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
                raise_semantic_error(i);
                break;
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
        } else if (i != 0)
        {
            if (elementsClass[i - 1] == StaticSymbols::operationClass && elements[i - 1] != "SPACE")
            {
                if (elementsClass[i] != StaticSymbols::ignoreClass)
                {
                    elementsClass[i] = StaticSymbols::symbolCandidateClass;
                }
                if (lexical_error(i))
                {
                    ControlVariables::set_quitRequest(true);
                    break;
                }
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
    std::cout << std::endl;
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

    if ((element[0]) == '-')
    {
        element.erase(0, 1);
    }
    
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
    else if (*(elements.end() - 1) == StaticSymbols::endMark && *(elementsClass.end() - 1) == StaticSymbols::ignoreClass)
    {
        textSection["end"] = ((elements.end() - 1) - elements.begin());
    }

    if (textSection["begin"] > dataSection["begin"])
    {
        dataSection["end"] = textSection["begin"] - 1;
    }
    else
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

void TokensTable::fill_tables()
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
                if (elements[i] != StaticSymbols::externMark)
                {
                    if (elements[i] != StaticSymbols::publicMark)
                    {
                        lineCounter += DirectTable::directTable[elements[i]]["WORDS"];
                    }
                }
                else
                {
                    symbTable.set_as_extern(elements[i - 2], true);
                }
            } 
        }
    }
    //ACHA PUBLICS
    for (uint i = 0; i < elements.size(); i++)
    {
        if (elementsClass[i] == StaticSymbols::operationClass && elements[i] == StaticSymbols::publicMark)
        {
            if (elementsClass[i+1] == StaticSymbols::symbolClass)
            {
                std::string symbol = elements[i + 1];
                defTable.insert_value(symbol, symbTable.get_value(symbol));
            }
        }
    }
}

void TokensTable::find_first_pass_errors()
{   
    for (uint i = 0; i < elements.size(); i++)
    {
        if (elementsClass[i] == StaticSymbols::symbolCandidateClass)
        {
            raise_semantic_error(i);
            break;
        }
        if (elementsClass[i] == StaticSymbols::dummyClass)
        {
            raise_syntactic_error(i);
            break;
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
        std::cout << std::endl << std::endl << ">>>> ERRO LEXICO NA L" << elementsLine[index] << " <<<<" << std::endl;
        std::cout << "Abortando o programa..." << std::endl << std::endl;
    }
    return found;
}

void TokensTable::raise_semantic_error(int index)
{
        std::cout << std::endl << std::endl << ">>>> ERRO SEMANTICO NA L" << elementsLine[index] << " <<<<" << std::endl;
        std::cout << "Abortando o programa..." << std::endl << std::endl;
        ControlVariables::set_quitRequest(true);
}

void TokensTable::raise_syntactic_error(int index)
{
        std::cout << std::endl << std::endl << ">>>> ERRO SINTATICO NA L" << elementsLine[index] << " <<<<" << std::endl;
        std::cout << "Abortando o programa..." << std::endl << std::endl;
        ControlVariables::set_quitRequest(true);
}

void TokensTable::reset_class()
{
    elements.clear();
    elementsLine.clear();
    elementsClass.clear();
    dataSection.clear();
    textSection.clear();
    symbTable.reset_class();
    defTable.reset_class();
    usageTable.reset_class();
}

bool TokensTable::found_modTags(bool isModule)
{
    // TODO: ver se o begin precisa mesmo de label + : antes
    if (isModule)
    {
        if (elements[2] != StaticSymbols::beginMark)
        {
            std::cout << "ERROR: no 'BEGIN' found!" << std::endl;
            return false;
        } 
        if (*(elements.end() - 1) != StaticSymbols::endMark)
        {
            std::cout << "ERROR: no 'END' found!" << std::endl;
            return false;
        }
        elementsClass[2] = StaticSymbols::ignoreClass;
        *(elementsClass.end() - 1) = StaticSymbols::ignoreClass;
        return true;
    }
    else if (elements[2] == StaticSymbols::beginMark)
    {
        std::cout << "ERROR: 'BEGIN' found!" << std::endl;
    } else 
    {
        return false;
    }
    if (*(elements.end() - 1) == StaticSymbols::endMark)
    {
        std::cout << "ERROR: 'END' found!" << std::endl;
    } else 
    {
        return false;
    }
    return true;
}

void TokensTable::remove_label_spaces()
{
    for (uint i = 0; i < elements.size(); i++)
    {
        if (elements[i] == StaticSymbols::dummyClass)
        {
            if (elements[i - 1] == StaticSymbols::labelSeparator)
            {
                elements.erase(elements.begin() + i, elements.begin() + i + 1);
                elementsLine.erase(elementsLine.begin() + i, elementsLine.begin() + i + 1);
                elementsClass.erase(elementsClass.begin() + i, elementsClass.begin() + i + 1);
            }
        }
    }
}

SymbTable TokensTable::get_symbTable()
{
    return symbTable;
}

DefTable TokensTable::get_defTable()
{
    return defTable;
}

UsageTable TokensTable::get_usageTable()
{
    return usageTable;
}