#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "TokensTable.h"

class Scanner
{
    private:
        std::vector<int> indexes{0};
        void obtain_separators(std::string line);
        std::vector<char> numbers= {'0','1','2','3','4','5','6','7','8','9'};
        std::vector<char> letters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                                     'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                                     'V', 'W', 'X', 'Y', 'Z', '_'};

    public:
        void split_elements(std::string line, int nLine);
        void reset_indexes();
        void classify_elements();
        void print_elements();
        bool verify_lexical_errors();
        bool lexical_error(int index);
};