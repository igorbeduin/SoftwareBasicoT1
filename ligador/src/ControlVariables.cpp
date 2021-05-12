#include "../include/ControlVariables.h"

bool ControlVariables::quitRequest = false;

void ControlVariables::set_quitRequest(bool request)
{
    quitRequest = request;
}

bool ControlVariables::get_quitRequest()
{
    return quitRequest;
}
