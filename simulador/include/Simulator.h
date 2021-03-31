#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Simulator
{
private:
    int code_len = 0;
    std::string inputProgramPath;
    std::string outputProgramPath;
    std::string extMark = ".";
    std::string outputExt = ".out";
    std::ifstream objectFile;
    std::ofstream outputFile;
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
    void print_on_output_file(std::string out);
};
