#pragma once

#include <string>

#include "SymbTable.h"
#include "DefTable.h"
#include "ObjectCode.h"
#include "UsageTable.h"

class FileToMount
{
    private:
        std::string moduleName;
        SymbTable symbTable;
        DefTable defTable;
        ObjectCode objCode;
        UsageTable usageTable;
        int correctionFactor;
    public:
        std::string moduleExt = ".obj";
        std::string assemblyExt = ".asm";
        FileToMount();
        FileToMount(std::string programName);
        void parseModuleName(std::string programName);
        void set_tables(SymbTable _symbTable, DefTable _defTable, 
                        ObjectCode _objCode, UsageTable _usageTable);
        void set_programName(std::string _programName);
};