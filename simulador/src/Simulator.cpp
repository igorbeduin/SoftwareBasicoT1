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
    int i = 0;
    objectFile.open(inputProgramPath);
    while (!objectFile.eof())
    {
        std::string code;
        objectFile >> code;
        memory[i] = std::stoi(code);
        i++;
    }
    objectFile.close();
}

void Simulator::execute()
{
    int arguments;
    int code;
    for (int i = 0; !quitRequest; i++)
    {
        code = memory[i];
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
        acc = acc + memory[index + 1];
    }
    else if (op == "SUB")
    {
        acc = acc - memory[index + 1];
    }
    else if (op == "MUL")
    {
        acc = acc * memory[index + 1];
    }
    else if (op == "DIV")
    {
        acc = acc / memory[index + 1];
    }
    else if (op == "JMP")
    {
        pc = memory[index + 1];
    }
    else if (op == "JMPN")
    {
        if (acc < 0)
        {
            pc = memory[index + 1];
        }
    }
    else if (op == "JMPP")
    {
        if (acc > 0)
        {
            pc = memory[index + 1];
        }
    }
    else if (op == "JMPZ")
    {
        if (acc == 0)
        {
            pc = memory[index + 1];
        }
    }
    else if (op == "COPY")
    {
        memory[index + 2] = memory[index + 1];
    }
    else if (op == "LOAD")
    {
        acc = memory[index + 1];
    }
    else if (op == "STORE")
    {
        memory[index + 1] = acc;
    }
    else if (op == "INPUT")
    {
        std::string aux;
        std::cin >> aux;
        memory[index + 1] = std::stoi(aux);
    }
    else if (op == "OUTPUT")
    {
        std::cout << (std::to_string(memory[index + 1])) << std::endl;
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