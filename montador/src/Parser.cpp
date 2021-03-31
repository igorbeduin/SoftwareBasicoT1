#include "../include/Parser.h"
#include "../include/TokensTable.h"
#include "../include/StaticSymbols.h"

std::vector<std::string> Parser::outputStringVector;

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
        if ((int)i == TokensTable::dataSection["end"])
        {
            outputStringVector.insert(outputStringVector.begin(), std::to_string(outputStringVector.size()));
        }

        int memNumber = -1;
        if (TokensTable::elementsClass[i] == StaticSymbols::operationClass)
        {
            if (TokensTable::elements[i] == "CONST") 
            {
                memNumber = (TokensTable::elementsClass[i + 1] == StaticSymbols::argumentClass)? std::stoi(TokensTable::elements[i+1]):0;
            } else
            {
                memNumber = DirectTable::directTable[TokensTable::elements[i]]["OP_CODE"];
            }
        } else if (TokensTable::elementsClass[i] == StaticSymbols::symbolClass)
        {   
            memNumber = TokensTable::symbTable.get_value(TokensTable::elements[i]);
        }
        if (memNumber != -1)
        {
            std::string out = std::to_string(memNumber);
            outputStringVector.push_back(out);
        }
    }
}

void Parser::verify_syntactic_errors()
{
    for (uint i = 0; i < TokensTable::elements.size(); i++)
    {
        if (TokensTable::elementsClass[i] == StaticSymbols::operationClass)
        {
            if (TokensTable::elements[i] == "COPY")
            {
                if ((TokensTable::elementsClass[i + 1] != StaticSymbols::symbolClass)
                    || (TokensTable::elementsClass[i + 2] != StaticSymbols::argumentSeparatorClass)
                    || (TokensTable::elementsClass[i + 3] != StaticSymbols::symbolClass))
                    {
                        std::cout << std::endl << std::endl << ">>>> ERRO SINTATICO NA LINHA " << TokensTable::elementsLine[i] << " <<<<" << std::endl;
                        std::cout << "Abortando o programa..." << std::endl << std::endl;
                        TokensTable::set_quit_request(true);
                        break;
                    }
            }
        }
    }
}