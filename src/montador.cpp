#include "../include/montador.h"

Montador::Montador(std::string programName) : programName(programName)
{}
Montador::~Montador()
{}

void Montador::set_programName(std::string fileName)
{
    programName = fileName;
}

std::string Montador::get_programName()
{
    std::cout << programName << std::endl;
    return programName;
}

void Montador::read_file(bool showLines)
{
    inputFile.open(programName);
    if (inputFile.is_open())
    {
        while (getline(inputFile, currLine))
        {
            if (showLines)
            {
                std::cout << currLine << std::endl;
            }
            linesRead.push_back(currLine);
        }
        inputFile.close();
    }
}

void Montador::read_file(std::string fileName, bool showLines)
{
    set_programName(fileName);
    read_file(showLines=showLines);
}


int Montador::get_n_linesRead()
{
    return linesRead.size();
}