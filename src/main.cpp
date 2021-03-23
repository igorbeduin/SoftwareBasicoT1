#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
    // Passing "test.asm" as argument
    std::ifstream myfile;
    std::string line;

    myfile.open(argv[argc-1]);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::cout << line << std::endl;
        }
    myfile.close();
    }
    // TODO: 
    //  classe parser
    //      recebe nome do arquivo
    //          faz primeira passagem

    // TODO:
    //  lidar com o caso que arquivo não foi passado como argumento



    return 0;
}