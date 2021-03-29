#include "../include/Compiler.h"

Compiler::Compiler(std::string programName) : programName(programName)
{}
Compiler::~Compiler()
{}

void Compiler::set_programName(std::string fileName)
{
    programName = fileName;
}

std::string Compiler::get_programName()
{
    std::cout << programName << std::endl;
    return programName;
}

void Compiler::read_file(bool showLines)
{
    std::string currLine;
    std::string correctedLine;

    inputFile.open(programName);
    if (inputFile.is_open())
    {
        while (getline(inputFile, currLine))
        {
            correctedLine = remove_comments(currLine);
            correctedLine = convert_to_uppercase(correctedLine);
            correctedLine = remove_mult_spaces(correctedLine);
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

std::string Compiler::remove_mult_spaces(std::string line)
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

std::string Compiler::remove_comments(std::string line)
{
    std::size_t found = line.find(commentMark);
    if (found != std::string::npos)
        line.erase(found);
    return line;
}

std::string Compiler::convert_to_uppercase(std::string line)
{
    std::locale loc;

    for (uint i = 0; i < line.length(); i++)
    {
        line[i] = std::toupper(line[i], loc);
    }
    return line;
}

void Compiler::read_file(std::string fileName, bool showLines)
{
    set_programName(fileName);
    read_file(showLines=showLines);
}


int Compiler::get_n_linesRead()
{
    return orgLines.size();
}

void Compiler::first_pass() 
{
    for (uint i = 0; i < orgLines.size(); i++)
    {   
        lineCounter = i;
        std::string line = orgLines[lineCounter];
        std::cout << "line: " << line << std::endl;
        parser.split_elements(line, lineCounter);
    }       
}
void Compiler::second_pass() 
{
    // TODO: Implementar segunda passada
}
void Compiler::write_output(std::string outputFile) 
{
    // TODO: Implementar escrita no arquivo final
}