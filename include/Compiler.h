#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "SymbTable.h"
#include "DirectTable.h"
#include "Parser.h"


class Compiler 
{
    private:
        std::string programName;
        std::ifstream inputFile;
        std::vector<std::string> orgLines;
        static int acc;
        static int pc;
        int lineCounter = 0;
        int posCounter = 1;
        SymbTable symbTable;
        DirectTable directTable;
        Parser parser;
        std::string commentMark = ";";

    public:
        Compiler(std::string programName);
        ~Compiler();
        void first_pass();
        void second_pass();
        void write_output(std::string outputFile);
        std::string get_programName();
        void set_programName(std::string fileName);
        void read_file(bool showLines=false);
        void read_file(std::string fileName, bool showLines=false);
        int get_n_linesRead();
        std::string remove_mult_spaces(std::string line);
        std::string remove_comments(std::string line);
};