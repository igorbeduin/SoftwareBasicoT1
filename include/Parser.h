#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

class Parser
{
    private:
        std::vector<std::string> elements;
        std::vector<std::map<int, std::string>> elementInfoTable;
        std::vector<char> separators{',', ' ', ':'};
        std::vector<int> indexes{0};
        void obtain_separators(std::string line);
    public:
        void split_elements(std::string line, int nLine);
        void reset_indexes();
        std::string classify_element(std::string element);
};