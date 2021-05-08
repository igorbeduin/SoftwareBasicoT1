#pragma once

#include <map>
#include <string>

class DefTable 
{
    private:
        std::map<std::string, int> table;
    public:
        void insert_value(std::string symbol, int value);
        bool exist(std::string symbol);
        void reset_class();
};  