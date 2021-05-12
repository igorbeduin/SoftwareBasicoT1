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
        std::string outputProgramName = "progs";
        int nModules = 0;
        std::ifstream inputFile;
        std::ofstream outputFile;
        int correctFactor = 0;
        int auxCorrectFactor = 0;

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
        std::string outputSufix = "_linked";
        std::string outputExt = ".obj";
        void read_module(std::string programName);
        void link();
        void write_outputFile();
        void parse_line(std::string line);
        void organize_tables();
        void clear_buffers();

        void solve_usage();
        void solve_relatives();
        bool is_in_usage_table(int pos);
};