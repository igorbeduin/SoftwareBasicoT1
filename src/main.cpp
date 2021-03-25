#include <iostream>
#include <fstream>
#include <string>

#include "../include/montador.h"

int main(int argc, char **argv)
{
    // Passing "test.asm" as argument
    std::string programName = argv[argc - 1];
    std::string line;


    Montador montador(programName);
    montador.read_file();
    std::cout << montador.get_n_linesRead() << std::endl;

    return 0;
}