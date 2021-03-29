#include <iostream>
#include <fstream>
#include <string>

#include "../include/Compiler.h"

int main(int argc, char **argv)
{
    // Passing "test.asm" as argument
    std::string programName = argv[argc - 1];
    std::string line;
    std::string outputFile;

    Compiler montador(programName);

    montador.read_file(false);
    montador.first_pass();
    montador.second_pass();
    montador.write_output(outputFile);

    return 0;
}