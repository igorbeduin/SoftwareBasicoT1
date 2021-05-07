#include "../include/Translator.h"

Translator::Translator(std::string programName) : programName(programName)
{}

Translator::~Translator()
{}

void Translator::set_programName(std::string fileName)
{
    programName = fileName;
}

std::string Translator::get_programName()
{
    std::cout << programName << std::endl;
    return programName;
}

void Translator::read_file(bool showLines)
{
    std::string currLine;
    std::string correctedLine;

    inputFile.open(programName);
    if (inputFile.is_open())
    {
        while (getline(inputFile, currLine))
        {
            
            correctedLine = convert_tabs_to_spaces(currLine);
            correctedLine = remove_comments(correctedLine);
            correctedLine = remove_starting_spaces(correctedLine);
            if (correctedLine.length() == 0)
            {
                continue;
            }
            correctedLine = convert_to_uppercase(correctedLine);
            correctedLine = remove_ending_spaces(correctedLine);
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

std::string Translator::remove_starting_spaces(std::string line)
{
    while (line[0] == ' ')
    {
        line.erase(0, 1);
    }
    return line;
}

std::string Translator::convert_tabs_to_spaces(std::string line)
{
    for (int i = 0; i < (int)line.length() - 1; i++)
    {
        if (line[i] == '\t')
        {
            line.erase(i, 1);
            line.insert(i, "    ");
        }
    }
    return line;
}

std::string Translator::remove_mult_spaces(std::string line)
{
    for (uint i = 0; i < line.length() - 1; i++)
    {
        if (line[i] == line[i + 1] && line[i] == ' ') 
        {
            line.erase(i, 1);
            i = 0;
        }
    }
    return line;
}

std::string Translator::remove_comments(std::string line)
{
    std::size_t found = line.find(commentMark);
    if (found != std::string::npos)
        line.erase(found);
    return line;
}

std::string Translator::convert_to_uppercase(std::string line)
{
    std::locale loc;

    for (uint i = 0; i < line.length(); i++)
    {
        line[i] = std::toupper(line[i], loc);
    }
    return line;
}

void Translator::read_file(std::string fileName, bool showLines)
{
    set_programName(fileName);
    read_file(showLines=showLines);
}


int Translator::get_n_linesRead()
{
    return orgLines.size();
}

void Translator::first_pass() 
{
    mount_elements_array();
    // scanner.print_elements();
    scanner.classify_elements();
}
void Translator::second_pass() 
{
    parser.verify_syntactic_errors();
    parser.mount_output();
}

void Translator::write_output(std::string programName) 
{
    std::string outputProgramName = programName.substr(0, programName.find(extensionMark));
    outputProgramName = outputProgramName + outputExt;
    outputFile.open(outputProgramName);
    if (outputFile.is_open())
    {
        for (uint i = 0; i < parser.outputStringVector.size(); i++)
        {
            outputFile << parser.outputStringVector[i];
            if (i != parser.outputStringVector.size() - 1)
            {
                outputFile << " ";
            }
        }
        outputFile.close();
    }
}

void Translator::mount_elements_array()
{
    int lineCounter;
    for (uint i = 0; i < orgLines.size(); i++)
    {
        lineCounter = i + 1;
        std::string line = orgLines[i];
        scanner.split_elements(line, lineCounter);
    }
}

std::string Translator::remove_ending_spaces(std::string line)
{
    while (line[line.size() - 1] == ' ')
    {
        line.erase(line.size() - 1, 1);
    }
    return line;
}