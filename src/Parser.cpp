#include "../include/Parser.h"
#include "../include/TokensTable.h"
#include "../include/StaticSymbols.h"

std::vector<std::string> Parser::outputString;

void Parser::set_elements()
{}
void Parser::set_elements_lines()
{}
void Parser::set_elements_classes()
{}
void Parser::mount_output()
{
    for (uint i = 0; i < TokensTable::elements.size(); i++)
    {   
        int memNumber = -1;
        if (TokensTable::elementsClass[i] == StaticSymbols::operationClass)
        {
            memNumber = DirectTable::directTable[TokensTable::elements[i]]["OP_CODE"];
        } else if (TokensTable::elementsClass[i] == StaticSymbols::symbolClass)
        {
            memNumber = TokensTable::symbTable.get_value(TokensTable::elements[i]);
        }
        if (memNumber != -1)
        {
            std::string out = std::to_string(memNumber);
            outputString.push_back(out);
        }
    }
}

void Parser::verify_syntactic_errors()
{}