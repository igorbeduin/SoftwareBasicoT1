#include "../include/Simulator.h"
#include "../include/CodeTable.h"
#include "../include/DirectTable.h"


Simulator::Simulator(std::string programPath)
{
    inputProgramPath = programPath;
}

Simulator::~Simulator()
{
}

void Simulator::read_obj_file()
{
    objectFile.open(inputProgramPath);
    outputProgramPath = inputProgramPath.substr(0, inputProgramPath.find(extMark));
    outputProgramPath = outputProgramPath + outputExt;

                                                std::string firstChar;
    objectFile >> firstChar;
    code_len = 0;
    while (!objectFile.eof())
    {    
        code_len++;
        std::string code;
        objectFile >> code;
        memory[code_len - 1] = std::stoi(code);
    }
    objectFile.close();
    if (std::stoi(firstChar) != code_len)
    {
        pc = std::stoi(firstChar);
    }
}

void Simulator::execute()
{
    int code;
    std::cout << "PC <- " << pc << std::endl;
    std::cout << "ACC <- " << acc << std::endl;
    while (!quitRequest)
    {
        std::cout << "-----------------------------" << std::endl;
        jump = false;
        code = memory[pc];
        std::string operation = CodeTable::codeTable[code];
        process_operation(operation);
    }
    outputFile.close();
}

void Simulator::process_operation(std::string operation)
{

    if (operation == "ADD")
    {
        acc = acc + memory[memory[pc + 1]];
    }
    else if (operation == "SUB")
    {
        acc = acc - memory[memory[pc + 1]];
    }
    else if (operation == "MUL")
    {
        acc = acc * memory[memory[pc + 1]];
    }
    else if (operation == "DIV")
    {
        acc = acc / memory[memory[pc + 1]];
    }
    else if (operation == "JMP")
    {
        pc = memory[pc + 1];
        jump = true;
    }
    else if (operation == "JMPN")
    {
        if (acc < 0)
        {
            pc = memory[pc + 1];
            jump = true;
        }
    }
    else if (operation == "JMPP")
    {
        if (acc > 0)
        {
            pc = memory[pc + 1];
            jump = true;
        }
    }
    else if (operation == "JMPZ")
    {
        if (acc == 0)
        {
            pc = memory[pc + 1];
            jump = true;
        }
    }
    else if (operation == "COPY")
    {
        memory[memory[pc + 2]] = memory[memory[pc + 1]];
    }
    else if (operation == "LOAD")
    {
        acc = memory[memory[pc + 1]];
    }
    else if (operation == "STORE")
    {
        memory[memory[pc + 1]] = acc;
    }
    else if (operation == "INPUT")
    {
        std::cout << "Escreva um valor de INPUT: ";
        std::string aux;
        std::cin >> aux;
        memory[memory[pc + 1]] = std::stoi(aux);
    }
    else if (operation == "OUTPUT")
    {
        std::string out = std::to_string(memory[memory[pc + 1]]);
        std::cout << "Valor de OUTPUT: " << out << std::endl;
        print_on_output_file(out);
    }
    else if (operation == "STOP")
    {
        quitRequest = true;
    }
    pc += (jump ? 0 : DirectTable::directTable[operation]["WORDS"]);
    std::cout << "PC <- " << pc << std::endl;
    std::cout << "ACC <- " << acc << std::endl;
}

bool Simulator::get_quit_request()
{
    return quitRequest;
}

void Simulator::print_on_output_file(std::string out)
{
    if (!outputFile.is_open())
    {
        outputFile.open(outputProgramPath);
    }
    outputFile << out << std::endl;
}