#pragma once

#include <vector>
#include <string>

class ObjectCode 
{
    private:
    public:
        std::vector<std::string> objCodeArray;
        std::vector<bool> relAdresses;
        void set_objCodeArray(std::vector<std::string> _objCodeArray);
        void set_relAdresses(std::vector<bool> _relAdresses);
};