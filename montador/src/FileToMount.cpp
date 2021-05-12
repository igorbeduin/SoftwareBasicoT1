#include "../include/FileToMount.h"

FileToMount::FileToMount()
{}

FileToMount::FileToMount(std::string programName)
{
    parseModuleName(programName);
}

void FileToMount::parseModuleName(std::string programName)
{
    std::size_t posExt = programName.find(assemblyExt);
    moduleName = programName.substr(0, posExt);
}

void FileToMount::set_tables(SymbTable _symbTable, DefTable _defTable, 
                             ObjectCode _objCode, UsageTable _usageTable)
{
    symbTable = _symbTable;
    defTable = _defTable;
    objCode = _objCode;
    usageTable = _usageTable;
}

void FileToMount::build_outputStrings()
{
    build_headerStrings();
    build_realocationStrings();
    build_usageStrings();
    build_defStrings();
    build_textStrings();
}

void FileToMount::set_correctionFactor(int _correctionFactor)
{
    correctionFactor = _correctionFactor;
}

int FileToMount::get_next_correctionFactor()
{
    return objCode.objCodeArray.size();
}

void FileToMount::build_headerStrings()
{
    std::vector<std::string> header_model = {"H",","};

    std::vector<std::string> header_line = header_model;
    header_line.push_back(moduleName);
    outputStrings.push_back(header_line);

    header_line = header_model;
    header_line.push_back(std::to_string(objCode.objCodeArray.size()));
    outputStrings.push_back(header_line);
}

void FileToMount::build_realocationStrings()
{
    std::vector<std::string> realoc_model = {"R", ","};

    std::vector<std::string> realoc_line = realoc_model;
    for (uint i = 0; i < objCode.relAdresses.size(); i++)
    {
        realoc_line.push_back(std::to_string((int)objCode.relAdresses[i]));
    }
    outputStrings.push_back(realoc_line);
}

void FileToMount::build_usageStrings()
{
    std::vector<std::string> usage_model = {"U", ","};

    std::vector<std::string> usage_line = usage_model;
    std::map<int, std::string>::iterator it = usageTable.table.begin();
    while (it != usageTable.table.end())
    {
        usage_line.push_back(it->second);
        usage_line.push_back(",");
        usage_line.push_back(std::to_string(it->first));
        outputStrings.push_back(usage_line);
        usage_line = usage_model;
        it++;
    }
}

void FileToMount::build_defStrings()
{
    std::vector<std::string> def_model = {"D", ","};

    std::vector<std::string> def_line = def_model;
    std::map<std::string, int>::iterator it = defTable.table.begin();
    while (it != defTable.table.end())
    {
        def_line.push_back(it->first);
        def_line.push_back(",");
        def_line.push_back(std::to_string(it->second));
        outputStrings.push_back(def_line);
        def_line = def_model;
        it++;
    }
}

void FileToMount::build_textStrings()
{
    std::vector<std::string> text_model = {"T"};

    std::vector<std::string> text_line = text_model;
    std::vector<std::string>::iterator it = objCode.objCodeArray.begin();
    while (it != objCode.objCodeArray.end())
    {
        text_line.push_back(",");
        text_line.push_back(*it);
        it++;
    }
    outputStrings.push_back(text_line);
}

void FileToMount::write_outputFile()
{
    std::string outputProgramName = moduleName + outputExt;
    outputFile.open(outputProgramName);
    if (outputFile.is_open())
    {
        for (uint i = 0; i < outputStrings.size(); i++)
        {
            for (uint j = 0; j < outputStrings[i].size(); j++)
            {
                outputFile << outputStrings[i][j];
            }
            outputFile << "\n";
        }
        outputFile.close();
    } else
    {
        ControlVariables::set_quitRequest(true);
        std::cout << "ERROR: Unable to write object file for module " << moduleName << std::endl;
    }
}