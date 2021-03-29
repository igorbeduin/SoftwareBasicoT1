#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Parser
{
    private:
        std::vector<std::string> elements;
        std::vector<char> separators{',', ' ', ':'};
        std::vector<int> indexes{0};
        void obtain_separators(std::string line);
    public:
        void split_elements(std::string line);
        void reset_elements();
};