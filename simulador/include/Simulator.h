#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

class Simulator
{
private:
    static int defaultValue;
    std::vector<std::string> codeArray;
    std::string inputProgramPath;
    std::ifstream objectFile;
    int memory[216];
    int acc = 0;
    int pc = 0;
    bool quitRequest = false;
public:
    Simulator(std::string programPath);
    ~Simulator();
    void read_obj_file();
    void execute();
    void process_operation(std::string op, int waitValues, int index);
    bool get_quit_request();
};
