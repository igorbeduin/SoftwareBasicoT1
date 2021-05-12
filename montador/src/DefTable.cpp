#include "../include/DefTable.h"

void DefTable::insert_value(std::string symbol, int value)
{
    table[symbol] = value;
}

void DefTable::reset_class()
{
    table.clear();
}

bool DefTable::exist(std::string symbol)
{
    std::map<std::string, int>::iterator found = table.find(symbol);
    return (found != table.end());
}