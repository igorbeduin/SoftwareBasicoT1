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
    int arguments = 0;
    for (uint i = 0; i < codeArray.size(); i++)
    {
        int code;
        code = std::stoi(codeArray[i]);
        if (arguments == 0)
        {
            std::string op = CodeTable::codeTable[code];
            arguments = DirectTable::directTable[op]["WORDS"] - 1;
            process_operation(op, arguments, i);
            i += arguments;
        } 
    }
}

void Simulator::process_operation(std::string op, int waitValues, int index)
{
    if (op == "INPUT")
    {
        std::string aux;
        std::cin >> aux;
        memory[std::stoi(codeArray[index + 1])] = std::stoi(aux);
    }
}