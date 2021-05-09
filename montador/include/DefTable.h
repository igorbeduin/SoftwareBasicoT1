#pragma once

#include <map>
#include <string>

class DefTable 
{
    private:
    public:
        std::map<std::string, int> table;
        void insert_value(std::string symbol, int value);
        bool exist(std::string symbol);
        void reset_class();
};  