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