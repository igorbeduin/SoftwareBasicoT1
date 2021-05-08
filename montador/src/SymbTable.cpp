#include "../include/SymbTable.h"

void SymbTable::insert_symbol(std::string symbol)
{   
    table[symbol] = std::numeric_limits<int>::min();
    externTable[symbol] = false;
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

void SymbTable::insert_value(std::string symbol, int value, bool is_extern)
{
    insert_value(symbol, value);
    externTable[symbol] = is_extern;
}

void SymbTable::set_as_extern(std::string symbol, bool is_extern)
{
    externTable[symbol] = is_extern;
}

int SymbTable::get_value(std::string symbol)
{
    return table[symbol];
}

bool SymbTable::get_is_extern(std::string symbol)
{
    return externTable[symbol];
}

void SymbTable::reset_class()
{
    table.clear();
    externTable.clear();
}