#pragma once

#include <map>
#include <string>

class UsageTable
{
    private:
        std::map<int, std::string> table;
    public:
        void insert_usage(int pos, std::string symbol);
        void reset_class();
};