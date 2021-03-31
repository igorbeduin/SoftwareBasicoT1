#include <iostream>
#include <string>

#include "../include/Simulator.h"


int main(int argc, char **argv)
{
    std::string programPath = argv[argc - 1];
    
    Simulator simulator(programPath);
    simulator.read_obj_file();
    simulator.execute();
    return 0;
}