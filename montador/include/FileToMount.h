#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "SymbTable.h"
#include "DefTable.h"
#include "ObjectCode.h"
#include "UsageTable.h"
#include "ControlVariables.h"

class FileToMount
{
    private:
        std::string moduleName;
        SymbTable symbTable;
        DefTable defTable;
        ObjectCode objCode;
        UsageTable usageTable;
        int correctionFactor;

        std::ofstream outputFile;

        std::vector<std::vector<std::string>> outputStrings;

    public:
        std::string outputExt = ".obj";
        std::string assemblyExt = ".asm";
        FileToMount();
        FileToMount(std::string programName);
        void parseModuleName(std::string programName);
        void set_tables(SymbTable _symbTable, DefTable _defTable, 
                        ObjectCode _objCode, UsageTable _usageTable);
        void set_programName(std::string _programName);
        void build_outputStrings();
        void set_correctionFactor(int _correctionFactor);
        int get_next_correctionFactor();

        void build_headerStrings();
        void build_realocationStrings();
        void build_usageStrings();
        void build_defStrings();
        void build_textStrings();
        void write_outputFile();
};