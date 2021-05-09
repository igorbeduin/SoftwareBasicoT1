#pragma once

#include <vector>
#include <string>

class ObjectCode 
{
    private:
        std::vector<std::string> objCodeArray;
        std::vector<bool> relAdresses;
    public:
        void set_objCodeArray(std::vector<std::string> _objCodeArray);
        void set_relAdresses(std::vector<bool> _relAdresses);
};