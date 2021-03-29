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
    std::string correctedLine;

    inputFile.open(programName);
    if (inputFile.is_open())
    {
        while (getline(inputFile, currLine))
        {
            correctedLine = remove_mult_spaces(currLine);
            orgLines.push_back(correctedLine);
            if (showLines)
            {
                std::cout << "original line: " << currLine << std::endl;
                std::cout << "corrected line: " << correctedLine << std::endl;
            }
        }
        inputFile.close();
    }
}

std::string Montador::remove_mult_spaces(std::string line)
{
    for (uint i = 0; i < line.length() - 1; i++)
    {
        if (line[i] == line[i + 1]) 
        {
            line.erase(i, 1);
            i = 0;
        }
    }
    return line;
}

void Montador::read_file(std::string fileName, bool showLines)
{
    set_programName(fileName);
    read_file(showLines=showLines);
}


int Montador::get_n_linesRead()
{
    return orgLines.size();
}

void Montador::first_pass() 
{
    for (uint i = 0; i < orgLines.size(); i++)
    {
        std::string line = orgLines[i];
        std::cout << "line: " << line << std::endl;
        parser.split_elements(line);
    }       
}
void Montador::second_pass() 
{
    // TODO: Implementar segunda passada
}
void Montador::write_output(std::string outputFile) 
{
    // TODO: Implementar escrita no arquivo final
}