#include "../include/Parser.h"
#include "../include/TokensTable.h"
#include "../include/StaticSymbols.h"

std::vector<bool> Parser::relAdresses;
std::vector<std::string> Parser::outputStringVector;
std::vector<int> Parser::relativeIdxData;

void Parser::set_elements()
{}
void Parser::set_elements_lines()
{}
void Parser::set_elements_classes()
{}
void Parser::mount_output()
{
    for (int i = TokensTable::textSection["begin"]; i < TokensTable::textSection["end"] + 1; i++)
    {   
        int memNumber = std::numeric_limits<int>::min();
        bool is_relative = false;

        if (TokensTable::elementsClass[i] == StaticSymbols::operationClass)
        {
            if (TokensTable::elements[i] == "CONST") 
            {
                if (TokensTable::elementsClass[i + 1] == StaticSymbols::argumentClass)
                {
                    if (TokensTable::elements[i+1][0] == '-'){
                        std::string number = TokensTable::elements[i + 1].substr(1);
                        memNumber = (-1) * std::stoi(number);
                    }
                    else
                    {
                        memNumber = std::stoi(TokensTable::elements[i + 1]);
                    }
                }

            } else
            {
                memNumber = DirectTable::directTable[TokensTable::elements[i]]["OP_CODE"];
            }
        } else 
        {
            if (TokensTable::elementsClass[i] == StaticSymbols::symbolClass)
            {   
                if (!TokensTable::symbTable.get_is_extern(TokensTable::elements[i]))
                {
                    memNumber = TokensTable::symbTable.get_value(TokensTable::elements[i]);
                    relativeIdxData.push_back(outputStringVector.size());
                } else
                {
                    memNumber = 0;
                    TokensTable::usageTable.insert_usage(outputStringVector.size(), TokensTable::elements[i]);
                }
            }
            is_relative = true;
        }

        if (memNumber != std::numeric_limits<int>::min())
        {
            std::string out = std::to_string(memNumber);
            outputStringVector.push_back(out);
            relAdresses.push_back(is_relative);
        }
    }

    int data_section_offset = outputStringVector.size();

    for (int i = TokensTable::dataSection["begin"]; i < TokensTable::dataSection["end"] + 1; i++)
    {
        int memNumber = std::numeric_limits<int>::min();
        bool is_relative = false;

        if (TokensTable::elementsClass[i] == StaticSymbols::operationClass)
        {
            if (TokensTable::elements[i] == "CONST")
            {
                if (TokensTable::elementsClass[i + 1] == StaticSymbols::argumentClass)
                {
                    if (TokensTable::elements[i + 1][0] == '-')
                    {
                        std::string number = TokensTable::elements[i + 1].substr(1);
                        memNumber = (-1) * std::stoi(number);
                    }
                    else
                    {
                        memNumber = std::stoi(TokensTable::elements[i + 1]);
                    }
                }
            }
            else
            {
                memNumber = DirectTable::directTable[TokensTable::elements[i]]["OP_CODE"];
            }
        }
        else 
        {
            if (TokensTable::elementsClass[i] == StaticSymbols::symbolClass)
            {
                memNumber = TokensTable::symbTable.get_value(TokensTable::elements[i]);
            }
            is_relative = true;
        }
        if (memNumber != std::numeric_limits<int>::min())
        {
            std::string out = std::to_string(memNumber);
            outputStringVector.push_back(out);
            relAdresses.push_back(is_relative);
        }
    }

    int label_offset = outputStringVector.size() - data_section_offset;

    TokensTable::set_offset_to_labels(label_offset);
    TokensTable::set_offset_to_data_labels(data_section_offset);

    for (uint i = 0; i < relativeIdxData.size(); i++)
    {
        int new_value = 0;
        int output_idx = relativeIdxData[i];
        int value = std::stoi(outputStringVector[output_idx]);
        if (value < label_offset)
        {
            new_value = value + data_section_offset;
        } else
        {
            new_value =  value - label_offset;
        }
        outputStringVector[output_idx] = std::to_string(new_value);
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
                    || (TokensTable::elementsClass[i + 3] != StaticSymbols::symbolClass)
                    || (TokensTable::elementsLine[i + 4] == TokensTable::elementsLine[i]))
                    {
                        std::cout << std::endl << std::endl << ">>>> ERRO SINTATICO NA L" << TokensTable::elementsLine[i] << " <<<<" << std::endl;
                        std::cout << "Abortando o programa..." << std::endl << std::endl;
                        ControlVariables::set_quitRequest(true);
                        break;
                    }
            }
            else if ((TokensTable::elements[i] == "ADD") || (TokensTable::elements[i] == "SUB") ||
                     (TokensTable::elements[i] == "MUL") || (TokensTable::elements[i] == "DIV") ||
                     (TokensTable::elements[i] == "LOAD") || (TokensTable::elements[i] == "STORE") ||
                     (TokensTable::elements[i] == "INPUT") || (TokensTable::elements[i] == "OUTPUT"))
            {
                if ((TokensTable::elementsClass[i + 1] != StaticSymbols::symbolClass) ||
                    (TokensTable::elementsLine[i + 2] == TokensTable::elementsLine[i]))
                    {
                        std::cout << std::endl << std::endl << ">>>> ERRO SINTATICO NA L" << TokensTable::elementsLine[i] << " <<<<" << std::endl;
                        std::cout << "Abortando o programa..." << std::endl << std::endl;
                        ControlVariables::set_quitRequest(true);
                        break;
                    }
            }
            else if ((TokensTable::elements[i] == "JMP") || (TokensTable::elements[i] == "JMPN") ||
                     (TokensTable::elements[i] == "JMPP") || (TokensTable::elements[i] == "JMPZ"))
            {
                if ((TokensTable::elementsClass[i + 1] != StaticSymbols::symbolClass) ||
                    (TokensTable::elementsLine[i + 2] == TokensTable::elementsLine[i]))
                {
                    std::cout << std::endl << std::endl << ">>>> ERRO SINTATICO NA L" << TokensTable::elementsLine[i] << " <<<<" << std::endl;
                    std::cout << "Abortando o programa..." << std::endl << std::endl;
                    ControlVariables::set_quitRequest(true);
                    break;
                }
            }
            else if (TokensTable::elements[i] == "CONST")
            {
                if ((TokensTable::elementsClass[i + 1] != StaticSymbols::argumentClass) ||
                    (TokensTable::elementsLine[i + 2] == TokensTable::elementsLine[i]))
                {
                    std::cout << std::endl << std::endl << ">>>> ERRO SINTATICO NA L" << TokensTable::elementsLine[i] << " <<<<" << std::endl;
                    std::cout << "Abortando o programa..." << std::endl << std::endl;
                    ControlVariables::set_quitRequest(true);
                    break; 
                }
            }
        }
    }
}

void Parser::reset_class()
{
    relativeIdxData.clear();
    outputStringVector.clear();
    relAdresses.clear();
}

ObjectCode Parser::get_objectCode()
{
    ObjectCode objArray;
    objArray.set_objCodeArray(outputStringVector);
    objArray.set_relAdresses(relAdresses);
    return objArray;
}