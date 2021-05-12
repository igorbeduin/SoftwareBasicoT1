#include "../include/UsageTable.h"

void UsageTable::insert_usage(int pos, std::string symbol)
{
    table[pos] = symbol;
}

void UsageTable::reset_class()
{
    table.clear();
}