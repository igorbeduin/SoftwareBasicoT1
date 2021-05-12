#pragma once

#include <map>
#include <string>

class UsageTable
{
    private:
    public:
        std::map<int, std::string> table;
        void insert_usage(int pos, std::string symbol);
        void reset_class();
};