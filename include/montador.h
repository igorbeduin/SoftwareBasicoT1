#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Montador 
{
    private:
        std::string programName;
        std::string currLine;
        std::ifstream inputFile;
        std::vector<std::string> linesRead;
        static int acc;
        static int pc;
    public:
        Montador(std::string programName);
        ~Montador();
        std::string get_programName();
        void set_programName(std::string fileName);
        void read_file(bool showLines=false);
        void read_file(std::string fileName, bool showLines=false);
        int get_n_linesRead();
};