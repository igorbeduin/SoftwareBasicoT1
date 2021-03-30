#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "TokensTable.h"

class Scanner
{
    private:
        TokensTable tokensTable;
        std::vector<int> indexes{0};
        void obtain_separators(std::string line);
    public:
        void split_elements(std::string line, int nLine);
        void reset_indexes();
        void classify_elements();
        void print_elements();
        TokensTable get_tokens_table();
};