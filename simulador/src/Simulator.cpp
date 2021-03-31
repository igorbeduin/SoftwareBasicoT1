#include "../include/Simulator.h"
#include "../include/CodeTable.h"
#include "../include/DirectTable.h"

int Simulator::defaultValue = std::numeric_limits<int>::min();

    Simulator::Simulator(std::string programPath)
{
    inputProgramPath = programPath;
    std::fill_n(memory, 500, Simulator::defaultValue);
}

Simulator::~Simulator()
{
}

void Simulator::read_obj_file()
{
    objectFile.open(inputProgramPath);
    while (!objectFile.eof())
    {
        std::string code;
        objectFile >> code;
        codeArray.push_back(code);
    }
    objectFile.close();
}

void Simulator::execute()
{
    int arguments;
    for (uint i = 0; i < codeArray.size(); i++)
    {
        int code;
        code = std::stoi(codeArray[i]);
        std::string op = CodeTable::codeTable[code];
        arguments = DirectTable::directTable[op]["WORDS"] - 1;
        process_operation(op, arguments, i);
        i += arguments; 
    }
}

void Simulator::process_operation(std::string op, int waitValues, int index)
{

    if (op == "ADD")
    {
    }
    else if (op == "SUB")
    {
    }
    else if (op == "MUL")
    {
    }
    else if (op == "DIV")
    {
    }
    else if (op == "JMP")
    {
    }
    else if (op == "JMPN")
    {
    }
    else if (op == "JMPP")
    {
    }
    else if (op == "JMPZ")
    {
    }
    else if (op == "COPY")
    {
    }
    else if (op == "LOAD")
    {
    }
    else if (op == "STORE")
    {
    }
    else if (op == "INPUT")
    {
        std::string aux;
        std::cin >> aux;
        memory[std::stoi(codeArray[index + 1])] = std::stoi(aux);
    }
    else if (op == "OUTPUT")
    {
    }
    else if (op == "STOP")
    {
    }
}