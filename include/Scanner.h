#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

class Scanner
{
    private:
        std::vector<std::string> elements;
        std::vector<int> elementsLine;
        std::vector<std::string> elementsClass;
        std::vector<char> separators{',', ' ', ':'};
        std::vector<int> indexes{0};
        void obtain_separators(std::string line);
    public:
        void split_elements(std::string line, int nLine);
        void reset_indexes();
        std::string classify_element(std::string element);
        bool is_label_sep(std::string element);
        bool is_argument_sep(std::string element);
        bool is_operation(std::string element);
        bool is_argument(std::string element);
        void print_elements();
};