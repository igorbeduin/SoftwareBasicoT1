#include "../include/Scanner.h"
#include "../include/StaticSymbols.h"

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
        if (element[0] == (StaticSymbols::spaceSeparator)[0])
        {
            element.erase(0, 1);
        }
        if (element[0] == (StaticSymbols::argumentSeparator)[0])
        {
            TokensTable::insert_token(StaticSymbols::argumentSeparator, nLine, StaticSymbols::dummyClass);
            element.erase(0, 1);
        }
        if (element[0] == (StaticSymbols::labelSeparator)[0])
        {
            TokensTable::insert_token(StaticSymbols::labelSeparator, nLine, StaticSymbols::dummyClass);
            element.erase(0, 1);
        }
        TokensTable::insert_token(element, nLine, StaticSymbols::dummyClass);
        
    }
    reset_indexes();
}

void Scanner::obtain_separators(std::string line)
{
    for (uint i = 0; i < line.length(); i++)
    {
        bool sepFound;
        sepFound = std::find(StaticSymbols::separators.begin(), StaticSymbols::separators.end(), line[i]) != StaticSymbols::separators.end();

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

void Scanner::classify_elements()
{
    TokensTable::search_for_sections();
    TokensTable::classify_tokens();
    if (!ControlVariables::quitRequest)
    {
        TokensTable::find_first_pass_errors();
    }
    if (!ControlVariables::quitRequest)
    {
        TokensTable::fill_symb_table();
    }
}

void Scanner::print_elements()
{
    TokensTable::print_elements();
}
