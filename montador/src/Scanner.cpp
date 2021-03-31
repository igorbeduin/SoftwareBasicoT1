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
    TokensTable::fill_symb_table();
}

void Scanner::print_elements()
{
    TokensTable::print_elements();
}

bool Scanner::verify_lexical_errors()
{
    for (uint i = 0; i < TokensTable::elements.size();i++)
    {
        if (i > 0 && TokensTable::elementsLine[i] != TokensTable::elementsLine[i - 1])
        {
            std::cout << std::endl;
        }
            std::cout << TokensTable::elements[i];
        if (lexical_error((int)i))
        {
            std::cout << std::endl << "ERRO LEXICO NA LINHA " << std::to_string(TokensTable::elementsLine[i]) << std::endl;
            return true;
        }
        else
        {
            std::cout << " ";

        }
    }
    return false;
}

bool Scanner::lexical_error(int index)
{
    bool found = false;
    if ((TokensTable::elementsClass[index] == StaticSymbols::labelClass)
        || (TokensTable::elementsClass[index] == StaticSymbols::symbolClass))
    {
        std::cout << TokensTable::elements[index].length() << std::endl;
        if (TokensTable::elements[index].length() > 50)
        {
            found = true;
        } else if (std::find(numbers.begin(), numbers.end(), TokensTable::elements[index][0]) != numbers.end())
        {
            found = true;
        } else
        {
            for (int i = 0; i < (int)TokensTable::elements[index].length(); i++)
            {
                if ((std::find(numbers.begin(), numbers.end(), TokensTable::elements[index][i]) == numbers.end()) &&
                    (std::find(letters.begin(), letters.end(), TokensTable::elements[index][i]) == letters.end()))
                    {
                        found = true;
                    }
            }
        }
    }

    return found;
}