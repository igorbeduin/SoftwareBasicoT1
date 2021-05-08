#include <map>
#include <string>
#include <limits>
#include <vector>

class SymbTable{
    private:
        std::map<std::string, int> table;
        std::vector<int> externTable;
    public:
        void insert_symbol(std::string symbol);
        bool exist(std::string symbol);
        void insert_value(std::string symbol, int value);
        int get_value(std::string symbol);
        void reset_class();
};