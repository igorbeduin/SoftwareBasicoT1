#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "SymbTable.h"
#include "DefTable.h"
#include "UsageTable.h"
#include "ObjectCode.h"

class Linker
{
    private:
        int nModules = 0;
        std::ifstream inputFile;
        std::ofstream outputFile;
        std::vector<int> correctFactors;

        SymbTable symbTable;
        DefTable defTable;
        UsageTable usageTable;
        ObjectCode objCode;

        std::vector<std::string> header_lines;
        std::vector<std::string> realoc_lines;
        std::vector<std::string> usage_lines;
        std::vector<std::string> def_lines;
        std::vector<std::string> text_lines;

    public:
        std::string outputSufix = "linked";
        std::string outputExt = ".obj";
        void read_module(std::string programName);
        void link();
        void write_outputFile();
        void parse_line(std::string line);
        void organize_tables();
};