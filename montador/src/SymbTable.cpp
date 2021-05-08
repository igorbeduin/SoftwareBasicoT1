#include "../include/SymbTable.h"

void SymbTable::insert_symbol(std::string symbol)
{
    table[symbol] = std::numeric_limits<int>::min();
}

bool SymbTable::exist(std::string symbol)
{
    std::map<std::string, int>::iterator found = table.find(symbol);
    return (found != table.end());
}

void SymbTable::insert_value(std::string symbol, int value)
{
    table[symbol] = value;
}

int SymbTable::get_value(std::string symbol)
{
    return table[symbol];
}

void SymbTable::reset_class()
{
    table.clear();
    externTable.clear();
}