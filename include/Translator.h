#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>

#include "Scanner.h"


class Translator 
{
    private:
        std::string programName;
        std::ifstream inputFile;
        std::vector<std::string> orgLines;
        static int acc;
        static int pc;
        int lineCounter = 0;
        int posCounter = 1;
        Scanner scanner;
        std::string commentMark = ";";

    public:
        Translator(std::string programName);
        ~Translator();
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
        std::string convert_to_uppercase(std::string line);
};