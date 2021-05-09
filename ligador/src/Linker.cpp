#include "../include/Linker.h"
#include "../include/ControlVariables.h"

void Linker::read_module(std::string programName)
{
    std::string currLine;
    std::string correctedLine;

    inputFile.open(programName);
    if (inputFile.is_open())
    {
        while (getline(inputFile, currLine))
        {
            parse_line(currLine);
        }
        inputFile.close();
        nModules ++;
    }
    else
    {
        std::cout << "ERROR: Unable to read file " << programName << std::endl;
        ControlVariables::set_quitRequest(true);
    }
}

void Linker::parse_line(std::string line)
{
    std::string::iterator it = line.begin();
    switch (*(it))
    {
    case 'H':
        header_lines.push_back(line.substr(2, line.end() - it + 2));
        break;

    case 'R':
        realoc_lines.push_back(line.substr(2, line.end() - it + 2));
        break;

    case 'U':
        usage_lines.push_back(line.substr(2, line.end() - it + 2));
        break;

    case 'D':
        def_lines.push_back(line.substr(2, line.end() - it + 2));
        break;

    case 'T':
        text_lines.push_back(line.substr(2, line.end() - it + 2));
        break;

    default:
        break;
    }
}

void Linker::link()
{
    organize_tables();
}

void Linker::organize_tables()
{   
    // Get correction factors
    for (int i = 0; i < nModules; i+=2)
    {
        correctFactors.push_back(std::stoi(header_lines[i + 1]));
    }

    // Get realocation bits
    for (uint i = 0; i < realoc_lines.size(); i++)
    {
        std::string::iterator it = realoc_lines[i].begin();
        while (it != realoc_lines[i].end())
        {
            objCode.relAdresses.push_back((bool)(*it == '1'));
            it++;
        }
    }

    // Get object code array
    for (uint i = 0; i < text_lines.size(); i++)
    {
        std::string::iterator it = text_lines[i].begin();
        std::string stringChar = "";
        while (it != text_lines[i].end())
        {
            if (*it == ',')
            {
                objCode.objCodeArray.push_back(stringChar);
                stringChar.clear();
            } else
            {
                stringChar.insert(stringChar.end(),*it);
            }
            it++;
        }
        objCode.objCodeArray.push_back(stringChar);
    }

    // Get def table
    for (uint i = 0; i < def_lines.size(); i++)
    {
        std::string::iterator it = def_lines[i].begin();
        std::string stringSymb = "";
        std::string stringValue = "";

        while (*it != ',')
        {
            stringSymb.insert(stringSymb.end(), *it);
            it++;
        }
        it++;
        while (it != def_lines[i].end())
        {
            stringValue.insert(stringValue.end(), *it);
            it++;
        }
        defTable.insert_value(stringSymb, std::stoi(stringValue));
    }

    // Get usage table
    for (uint i = 0; i < usage_lines.size(); i++)
    {
        std::string::iterator it = usage_lines[i].begin();
        std::string stringValue = "";
        std::string stringSymb = "";

        while (*it != ',')
        {
            stringSymb.insert(stringSymb.end(), *it);
            it++;
        }
        it++;
        while (it != usage_lines[i].end())
        {
            stringValue.insert(stringValue.end(), *it);
            it++;
        }
        usageTable.insert_usage(std::stoi(stringValue), stringSymb);
    }
}

void Linker::write_outputFile()
{}