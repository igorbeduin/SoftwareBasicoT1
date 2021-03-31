#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Simulator
{
private:
    std::string inputProgramPath;
    std::ifstream objectFile;
    int memory[216];
    int acc = 0;
    int pc = 0;
    bool quitRequest = false;
    bool jump = false;
public:
    Simulator(std::string programPath);
    ~Simulator();
    void read_obj_file();
    void execute();
    void process_operation(std::string operation);
    bool get_quit_request();
};
