#include <iostream>
#include <vector>
#include <string>

class TokensTable
{
    private:
        std::vector<std::string> elements;
        std::vector<int> elementsLine;
        std::vector<std::string> elementsClass;
    public:
        void insert_token(std::string element, int elementLine, std::string elementClass);
        void print_elements();
        void classify_tokens();
        bool is_label_sep(std::string element);
        bool is_argument_sep(std::string element);
        bool is_operation(std::string element);
        bool is_argument(std::string element);
};