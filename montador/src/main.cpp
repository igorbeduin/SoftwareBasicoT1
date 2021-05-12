#include <iostream>
#include <fstream>
#include <string>

#include "../include/Translator.h"
#include "../include/FileToMount.h"
#include "../include/ControlVariables.h"

int main(int argc, char **argv)
{
    int number_of_modules = argc - 1;
    if (number_of_modules > 3)
    {
        ControlVariables::set_quitRequest(true);
        std::cout << "ERROR: Number of modules exceeding maximum permited (3)." << std::endl;
    }
    FileToMount modules[number_of_modules];

    for (int i = 0; i < number_of_modules && !ControlVariables::quitRequest; i++)
    {   
        std::string programName = argv[i+1];
        std::cout << "Processing module " << programName << " ..." << std::endl;
        Translator translator(programName);
        translator.read_file(false);
        translator.set_is_module((bool)(number_of_modules - 1));
        if (!ControlVariables::quitRequest)
        {
            translator.first_pass();
        }
        if (!ControlVariables::quitRequest)
        {
            translator.second_pass();
        }
        if (!ControlVariables::quitRequest)
        {
            modules[i] = translator.get_FileToMount();
            translator.reset_processing();
        }
        std::cout << std::endl;
    }

    int correctionFactor = 0;
    for (int i = 0; i < number_of_modules && !ControlVariables::quitRequest; i++)
    {
        modules[i].set_correctionFactor(correctionFactor);
        modules[i].build_outputStrings();
        modules[i].write_outputFile();
        correctionFactor += modules[i].get_next_correctionFactor();
    }

    return 0;
}