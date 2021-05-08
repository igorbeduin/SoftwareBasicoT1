#include <iostream>
#include <fstream>
#include <string>

#include "../include/Translator.h"
#include "../include/FileToMount.h"
#include "../include/ControlVariables.h"

int main(int argc, char **argv)
{
    FileToMount modules[3];
    int number_of_modules = argc - 1;

    for (int i = 0; i < number_of_modules; i++)
    {   
        std::string programName = argv[i+1];
        Translator translator(programName);
        translator.read_file(false);
        translator.set_is_module((bool)i);
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
            translator.write_output(programName);
            std::cout << std::endl << "SUCCESS!" << std::endl;
        }

        return 0;
    }

}