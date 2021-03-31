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
        if (quitRequest)
        {
            break;
        }
    }
}

void Simulator::process_operation(std::string op, int waitValues, int index)
{

    if (op == "ADD")
    {
        acc = acc + memory[std::stoi(codeArray[index + 1])];
    }
    else if (op == "SUB")
    {
        acc = acc - memory[std::stoi(codeArray[index + 1])];
    }
    else if (op == "MUL")
    {
        acc = acc * memory[std::stoi(codeArray[index + 1])];
    }
    else if (op == "DIV")
    {
        acc = acc / memory[std::stoi(codeArray[index + 1])];
    }
    else if (op == "JMP")
    {
        pc = std::stoi(codeArray[index + 1]);
    }
    else if (op == "JMPN")
    {
        if (acc < 0)
        {
            pc = std::stoi(codeArray[index + 1]);
        }
    }
    else if (op == "JMPP")
    {
        if (acc > 0)
        {
            pc = std::stoi(codeArray[index + 1]);
        }
    }
    else if (op == "JMPZ")
    {
        if (acc == 0)
        {
            pc = std::stoi(codeArray[index + 1]);
        }
    }
    else if (op == "COPY")
    {
        memory[std::stoi(codeArray[index + 2])] = memory[std::stoi(codeArray[index + 1])];
    }
    else if (op == "LOAD")
    {
        acc = memory[std::stoi(codeArray[index + 1])];
    }
    else if (op == "STORE")
    {
        memory[std::stoi(codeArray[index + 1])] = acc;
    }
    else if (op == "INPUT")
    {
        std::string aux;
        std::cin >> aux;
        memory[std::stoi(codeArray[index + 1])] = std::stoi(aux);
    }
    else if (op == "OUTPUT")
    {
        std::cout << (std::to_string(memory[std::stoi(codeArray[index + 1])])) << std::endl;
        // escreve no arquivo de saida
    }
    else if (op == "STOP")
    {
        quitRequest = true;
    }
}

bool Simulator::get_quit_request()
{
    return quitRequest;
}