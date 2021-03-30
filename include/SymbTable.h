#include <map>
#include <string>
#include <limits>

class SymbTable{
    private:
        std::map<std::string, int> table;
    public:
        void insert_symbol(std::string symbol);
        bool exist(std::string symbol);
        void insert_value(std::string symbol, int value);
};