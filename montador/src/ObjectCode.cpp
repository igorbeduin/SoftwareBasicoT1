#include "../include/ObjectCode.h"

void ObjectCode::set_objCodeArray(std::vector<std::string> _objCodeArrray)
{
    objCodeArray = _objCodeArrray;
}

void ObjectCode::set_relAdresses(std::vector<bool> _relAdresses)
{
    relAdresses = _relAdresses;
}