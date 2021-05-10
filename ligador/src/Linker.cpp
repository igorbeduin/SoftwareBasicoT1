#include "../include/Linker.h"
#include "../include/ControlVariables.h"

void Linker::read_module(std::string programName)
{
    clear_buffers();
    std::string currLine;
    std::string correctedLine;

    inputFile.open(programName);
    if (inputFile.is_open())
    {
        correctFactor += auxCorrectFactor;
        auxCorrectFactor = 0;
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
    organize_tables();
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
    solve_relatives();
}

void Linker::organize_tables()
{
    // Get correction factors
    auxCorrectFactor += std::stoi(header_lines[1]);

    // Get realocation bits
    std::string::iterator it_realoc = realoc_lines[0].begin();
    while (it_realoc != realoc_lines[0].end())
    {
        objCode.relAdresses.push_back((bool)(*it_realoc == '1'));
        it_realoc++;
    }

    // Get object code array
    std::string::iterator it_obj = text_lines[0].begin();
    std::string stringChar = "";
    while (it_obj != text_lines[0].end())
    {
        if (*it_obj == ',')
        {
            objCode.objCodeArray.push_back(stringChar);
            stringChar.clear();
        } else
        {
            stringChar.insert(stringChar.end(),*it_obj);
        }
        it_obj++;
    }
    objCode.objCodeArray.push_back(stringChar);

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
        defTable.insert_value(stringSymb, std::stoi(stringValue) + correctFactor);
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
        usageTable.insert_usage(std::stoi(stringValue) + correctFactor, stringSymb);
    }
    std::cout << std::endl;
}

void Linker::write_outputFile()
{}

void Linker::clear_buffers()
{
   header_lines.clear();
   realoc_lines.clear();
   usage_lines.clear();
   def_lines.clear();
   text_lines.clear();
}

void Linker::solve_relatives()
{
    for (std::map<int, std::string>::iterator it = usageTable.table.begin(); it != usageTable.table.end(); it++)
    {
        int pos = it->first;
        std::string symbol = it->second;
        int offset = defTable.table[symbol];
        objCode.objCodeArray[pos] = std::to_string(std::stoi(objCode.objCodeArray[pos]) + offset);
    }
    for (uint i = (uint)correctFactor; i < objCode.objCodeArray.size(); i++)
    {
        if (!is_in_usage_table(i) && objCode.relAdresses[i] == true)
        {
            objCode.objCodeArray[i] = std::to_string(std::stoi(objCode.objCodeArray[i]) + correctFactor);
        }
    }
}

bool Linker::is_in_usage_table(int pos)
{
    for (std::map<int, std::string>::iterator it = usageTable.table.begin(); it != usageTable.table.end(); it ++)
    {
        if (it->first == pos)
        {
            return true;
        }
    }
    return false;
}