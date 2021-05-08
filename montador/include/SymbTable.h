#pragma once

#include <map>
#include <string>
#include <limits>
#include <vector>

class SymbTable{
    private:
        std::map<std::string, bool> externTable;
        std::map<std::string, int> table;
    public:
        void insert_symbol(std::string symbol);
        bool exist(std::string symbol);
        void insert_value(std::string symbol, int value);
        void insert_value(std::string symbol, int value, bool is_extern);
        void set_as_extern(std::string symbol, bool is_extern);
        int get_value(std::string symbol);
        bool get_is_extern(std::string symbol);
        void reset_class();
};