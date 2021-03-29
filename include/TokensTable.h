#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

class TokensTable
{
    private:
        std::vector<std::string> elements;
        std::vector<int> elementsLine;
        std::vector<std::string> elementsClass;
        std::map<std::string, int> dataSection;
        std::map<std::string, int> textSection;
    public:
        void insert_token(std::string element, int elementLine, std::string elementClass);
        void print_elements();
        void classify_tokens();
        bool is_label_sep(std::string element);
        bool is_argument_sep(std::string element);
        bool is_operation(std::string element);
        bool is_argument(std::string element);
        void search_for_sections();
};