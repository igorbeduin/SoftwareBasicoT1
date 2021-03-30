#include <iostream>
#include <fstream>
#include <string>

#include "../include/Translator.h"

int main(int argc, char **argv)
{
    // Passing "test.asm" as argument
    std::string programName = argv[argc - 1];
    std::string line;
    std::string outputFile;

    Translator translator(programName);

    translator.read_file(false);
    translator.first_pass();
    translator.second_pass();
    translator.write_output(programName);

    return 0;
}