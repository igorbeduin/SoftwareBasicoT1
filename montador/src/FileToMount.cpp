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
    moduleName = programName.substr(posExt);
}