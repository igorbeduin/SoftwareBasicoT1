#include <iostream>

#include "../include/FileToMount.h"
#include "../include/Linker.h"

int main(int argc, char **argv)
{
    int number_of_modules = argc - 1;
    if (number_of_modules > 3)
    {
        ControlVariables::set_quitRequest(true);
        std::cout << "ERROR: Number of modules exceeding maximum permited (3)." << std::endl;
    }
    FileToMount modules[number_of_modules];
    Linker linker;

    for (int i = 0; i < number_of_modules && !ControlVariables::quitRequest; i++)
    {
        std::string programName = argv[i + 1];
        std::cout << "Processing module " << programName << " ..." << std::endl;
        linker.read_module(programName);
        std::cout << std::endl;
    }

    linker.link();
    linker.write_outputFile();
    return 0;
}